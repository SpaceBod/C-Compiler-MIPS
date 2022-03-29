#ifndef ast_stat_switch_hpp
#define ast_stat_switch_hpp

#include <string>
#include <iostream>

#include "ast_expressions.hpp"
#include "ast_functions.hpp"
#include "ast_statements.hpp"
#include "ast_primitives.hpp"
#include "ast_symtab.hpp"

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

#endif