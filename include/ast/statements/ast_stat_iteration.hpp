#ifndef ast_stat_iteration_hpp
#define ast_stat_iteration_hpp

#include <string>
#include <iostream>

#include "../ast_expressions.hpp"
#include "../ast_primitives.hpp"
#include "../ast_statements.hpp"
#include "../ast_symtab.hpp"

class LoopStat
    : public Stat
{
private:
    ExprPtr cond;
    StatPtr stat = nullptr;

public:
    LoopStat()
    {
    }
    LoopStat(ExprPtr _cond, StatPtr _stat = nullptr)
        : cond(_cond), stat(_stat)
    {
    }
    ~LoopStat()
    {
        delete cond;
        delete stat;
    }
    ExprPtr returnCond() const
    {
        return cond;
    }
    StatPtr returnStat() const
    {
        return stat;
    }
};

class WhileStat
    : public LoopStat
{
public:
    WhileStat(ExprPtr _cond, StatPtr _stat = nullptr)
        : LoopStat(_cond, _stat)
    {
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << "while ( ";
        returnCond()->pretty_print(dst);
        dst << " ) ";
        returnStat()->pretty_print(dst);
        dst << '\n';
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        std::string exit = makeName("exit");
        std::string enter = makeName("enter");
        SymTab.setScopeLoop(SymTab.returnLoopScope() + 1);
        SymTab.setStartLoop(enter);
        SymTab.setEndLoop(exit);
        std::cout << enter << ":" << std::endl;
        returnCond()->Translate2MIPS("$t0");
        std::cout << "beq $t0, $0, " << exit << std::endl;
        returnStat()->Translate2MIPS(destReg);
        std::cout << "j " << enter << std::endl;
        std::cout << exit << ":" << std::endl;
        SymTab.setScopeLoop(SymTab.returnLoopScope() - 1);
    }
};

class ForStat
    : public LoopStat
{
private:
    Identifier *initVar = nullptr;
    ExprPtr initExpr = nullptr;
    ExprPtr incrementExpr;

public:
    ForStat(ExprPtr _initExpr, ExprPtr _checkExpr, ExprPtr _incrementExpr, StatPtr _stat)
        : LoopStat(_checkExpr, _stat), initExpr(_initExpr), incrementExpr(_incrementExpr)
    {
    }
    ForStat(Identifier *_initVar, ExprPtr _checkExpr, ExprPtr _incrementExpr, StatPtr _stat)
        : LoopStat(_checkExpr, _stat), initVar(_initVar), incrementExpr(_incrementExpr)
    {
    }
    ~ForStat()
    {
        delete initVar;
        delete initExpr;
        delete incrementExpr;
    }
    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << "for ( ";
        if (initVar != nullptr && initExpr == nullptr)
        {
            initVar->pretty_print(dst);
        }
        else if (initVar == nullptr && initExpr != nullptr)
        {
            initExpr->pretty_print(dst);
            dst << " ; ";
        }
        returnCond()->pretty_print(dst);
        dst << " ; ";
        incrementExpr->pretty_print(dst);
        dst << " ) \n";
        returnStat()->pretty_print(dst);
        dst << '\n';
    }
    virtual void Translate2MIPS(std::string destReg) const override
    {
        if (initVar != nullptr && initExpr == nullptr)
        {
            initVar->returnExpr()->Translate2MIPS("$t0");
        }
        else if (initVar == nullptr && initExpr != nullptr)
        {
            initExpr->Translate2MIPS("$t0");
        }
        else
        {
            std::cout << "ERROR: no initial value in for loop" << std::endl;
        }

        std::string enter = makeName("enter");
        std::cout << enter << ":" << std::endl;
        std::string exit = makeName("exit");
        SymTab.setScopeLoop(SymTab.returnLoopScope() + 1);
        SymTab.setStartLoop(enter);
        SymTab.setEndLoop(exit);
        returnCond()->Translate2MIPS("$t1");
        std::cout << "beq $t1, $0, " << exit << std::endl;
        returnStat()->Translate2MIPS(destReg);
        incrementExpr->Translate2MIPS("$t0");
        std::cout << "j " << enter << std::endl;
        std::cout << exit << ":" << std::endl;
        SymTab.setScopeLoop(SymTab.returnLoopScope() - 1);
    }
};

#endif