#ifndef ast_stat_if_hpp
#define ast_stat_if_hpp

#include <string>
#include <iostream>

#include "../ast_expressions.hpp"
#include "../ast_primitives.hpp"
#include "../ast_statements.hpp"
#include "../ast_symtab.hpp"

class IfStat
    : public SelectStat
{
private:
    StatPtr else_branch = nullptr;

public:
    IfStat(ExprPtr _cond, StatPtr _if_branch = nullptr, StatPtr _else_branch = nullptr)
        : SelectStat(_cond, _if_branch), else_branch(_else_branch)
    {
    }
    ~IfStat()
    {
        delete else_branch;
    }
    StatPtr returnElse() const
    {
        return else_branch;
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << "if ( ";
        returnCond()->pretty_print(dst);
        dst << " ) ";
        dst << '\n';
        returnStat()->pretty_print(dst);
        if (else_branch != nullptr)
        {
            dst << "else ";
            else_branch->pretty_print(dst);
        }
        dst << '\n';
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnCond()->Translate2MIPS("$t0");
        std::string exit = makeName("exit");
        if (else_branch != nullptr)
        {
            std::string else_stat = makeName("else_stat");
            std::cout << "beq $t0, $0, " << else_stat << std::endl;
            returnStat()->Translate2MIPS(destReg);
            std::string exit = makeName("exit");
            std::cout << "j " << exit << std::endl;
            std::cout << else_stat << ":" << std::endl;
            returnElse()->Translate2MIPS(destReg);
            std::cout << exit << ":" << std::endl;
        }
        else
        {
            std::string exit = makeName("exit");
            std::cout << "beq $t0, $0, " << exit << std::endl;
            returnStat()->Translate2MIPS(destReg);
            std::cout << exit << ":" << std::endl;
        }
    }
};
#endif