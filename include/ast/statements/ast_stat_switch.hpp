#ifndef ast_stat_switch_hpp
#define ast_stat_switch_hpp

#include <string>
#include <iostream>

#include "../ast_functions.hpp"
#include "../ast_expressions.hpp"
#include "../ast_primitives.hpp"
#include "../ast_statements.hpp"
#include "../ast_symtab.hpp"

class SwitchStat
    : public SelectStat
{
public:
    SwitchStat(ExprPtr _cond, StatPtr _stat)
        : SelectStat(_cond, _stat)
    {
    }
    ~SwitchStat()
    {
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << "switch ( ";
        returnCond()->pretty_print(dst);
        dst << " ) ";
        returnStat()->pretty_print(dst);
        dst << '\n';
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnCond()->Translate2MIPS("$s0");
        std::string exit = makeName("exit");
        SymTab.setScopeLoop(SymTab.returnLoopScope() + 1);
        SymTab.setEndLoop(exit);
        StkPtr.setIncrement(StkPtr.getIncrement() + 4);
        StkPtr.setScopeIncrement(StkPtr.returnScopeIncrement() + 4);
        std::cout << "addiu $sp, $sp, -4" << std::endl;
        std::cout << "sw $s1, 0($sp)" << std::endl;
        std::cout << "addiu $s1, $0, 0" << std::endl;
        returnStat()->Translate2MIPS(destReg);
        std::cout << exit << ":" << std::endl;
        std::string startCase = makeName("case");
        std::cout << startCase << ":" << std::endl;
    }
};

class LabelStat
    : public Stat
{
private:
    ExprPtr expr = nullptr;
    StatPtr stat = nullptr;

public:
    LabelStat(StatPtr _stat, ExprPtr _expr = nullptr)
        : expr(_expr), stat(_stat)
    {
    }
    ~LabelStat()
    {
        delete expr;
        delete stat;
    }
    ExprPtr returnExp() const
    {
        return expr;
    }
    StatPtr returnStat() const
    {
        return stat;
    }
    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << "case ";
        if (expr != nullptr)
        {
            expr->pretty_print(dst);
        }
        dst << ": ";
        if (stat != nullptr)
        {
            stat->pretty_print(dst);
        }
        dst << '\n';
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        if (expr != nullptr)
        {
            std::string startCase = makeName("case");
            std::string endCase = makeName("caseEnd");
            std::cout << startCase << ":" << std::endl;
            std::cout << "bne $0, $s1, " << endCase << std::endl;
            returnExp()->Translate2MIPS("$t0");
            std::cout << "bne $t0, $s0, " << startCase.substr(0, 6) + std::to_string(std::stoi(startCase.substr(6, startCase.length() - 6)) + 2) << std::endl;
            std::cout << "addiu $s1, $0, 1" << std::endl;
            std::cout << endCase << ":" << std::endl;
            returnStat()->Translate2MIPS("destReg");
        }
        else
        {
            std::string startCase = makeName("case");
            std::string endCase = makeName("caseEnd");
            std::cout << startCase << ":" << std::endl;
            std::cout << "bne $0, $s1, " << endCase << std::endl;
            std::cout << "lw $s1, 0($sp)" << std::endl;
            std::cout << endCase << ":" << std::endl;
            returnStat()->Translate2MIPS("destReg");
        }
    }
};

#endif