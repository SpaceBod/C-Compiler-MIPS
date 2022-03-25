#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_expressions.hpp"
#include "ast_primitives.hpp"
#include "ast_statements.hpp"

class Function : public Expression
{
private:
    ExpressionPtr arg;
    Variable *name;
    StatPtr stat;

public:
    Function(Variable *_name, StatPtr _stat = nullptr)
        : name(_name), stat(_stat)
    {
    }

    virtual ~Function()
    {
        delete arg;
        delete name;
        delete stat;
    }

    const std::string getFunction() const
    {
        return name->getId();
    }

    ExpressionPtr getArg() const
    {
        return arg;
    }

    void pretty_print(std::ostream &dst) const
    {
        name->pretty_print(dst);
        dst << "( ";
        dst << " )";
        dst << "\n";
        stat->pretty_print(dst);
    }

    void Translate2MIPS(std::string destReg) const
    {
        std::cout << name->getId() << ":" << std::endl;
        stat->Translate2MIPS(destReg);
    }
};

#endif