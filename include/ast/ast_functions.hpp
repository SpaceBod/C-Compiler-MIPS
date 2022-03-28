#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_expressions.hpp"
#include "ast_primitives.hpp"
#include "ast_statements.hpp"


class Function
{
private:
    ExpressionPtr arg;
    Variable *name;
    StatPtr stat;

public:
    Function(Variable *_name, StatPtr _stat = nullptr)
        : name(_name)
        , stat(_stat)
    {}
     Function(Variable *_name, ExpressionPtr _arg = nullptr, StatPtr _stat = nullptr)
        : name(_name)
        , arg(_arg) 
        , stat(_stat)
    {}


    virtual ~Function()
    {
        delete arg;
        delete name;
        delete stat;
    }

    const std::string returnFunc() const
    {
        return name->getVar_name();
    }

    ExpressionPtr returnArg() const
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
        std::cout << name->getVar_name() << ":" << std::endl;
        std::cout << "addiu $sp, $sp, -44" << std::endl;
        std::cout << "sw $s0, 4($sp)" << std::endl;
        std::cout << "sw $s1, 8($sp)" << std::endl;
        std::cout << "sw $s2, 12($sp)" << std::endl;
        std::cout << "sw $s3, 16($sp)" << std::endl;
        std::cout << "sw $s4, 20($sp)" << std::endl;
        std::cout << "sw $s5, 24($sp)" << std::endl;
        std::cout << "sw $s6, 28($sp)" << std::endl;
        std::cout << "sw $s7, 32($sp)" << std::endl;
        std::cout << "sw $fp, 36($sp)" << std::endl;
        std::cout << "sw $ra, 40($sp)" << std::endl;

        stat->Translate2MIPS(destReg);

        std::cout << "lw $s0, 4($sp)" << std::endl;
        std::cout << "lw $s1, 8($sp)" << std::endl;
        std::cout << "lw $s2, 12($sp)" << std::endl;
        std::cout << "lw $s3, 16($sp)" << std::endl;
        std::cout << "lw $s4, 20($sp)" << std::endl;
        std::cout << "lw $s5, 24($sp)" << std::endl;
        std::cout << "lw $s6, 28($sp)" << std::endl;
        std::cout << "lw $s7, 32($sp)" << std::endl;
        std::cout << "lw $fp, 36($sp)" << std::endl;
        std::cout << "lw $ra, 40($sp)" << std::endl;
        std::cout << "move $fp, $sp" << std::endl;
        std::cout << "jr $ra" << std::endl;

    }
};

#endif