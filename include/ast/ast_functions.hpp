#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_expressions.hpp"
#include "ast_primitives.hpp"
#include "ast_statements.hpp"

class Function
{
private:
    Decl_listPtr arguements;
    Variable *name;
    StatPtr stat;

public:
    Function(Variable *_name, StatPtr _stat = nullptr)
        : name(_name), stat(_stat)
    {
    }
    Function(Variable *_name, Decl_listPtr _arguements = nullptr, StatPtr _stat = nullptr)
        : name(_name), arguements(_arguements), stat(_stat)
    {
    }

    virtual ~Function()
    {
        delete arguements;
        delete name;
        delete stat;
    }

    const std::string returnFunc() const
    {
        return name->return_var_name();
    }

    Decl_listPtr returnArg() const
    {
        return arguements;
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
        std::cout << name->return_var_name() << ":" << std::endl;
        std::cout << "move $fp, $sp" << std::endl;
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
        StackPointer.setIncrement(StackPointer.returnIncrement() + 44);

        if (arguements != nullptr)
        {
            SymbolTable.scopeEnter();
            StackPointer.setScopeCurrent(StackPointer.returnScopeCurrent() + 1);
            StackPointer.setScopeIncrement(0);
            arguements->Translate2MIPS(destReg);
            stat->Translate2MIPS(destReg);
            std::cout << "addiu $sp, $sp, " << StackPointer.returnScopeIncrement() << std::endl;
            StackPointer.setScopeCurrent(StackPointer.returnScopeCurrent() - 1);
            SymbolTable.scopeExit();
        }
        else
        {
            stat->Translate2MIPS(destReg);
        }

        StackPointer.setIncrement(StackPointer.returnIncrement() - 44);
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
        std::cout << "move $sp, $fp" << std::endl;
        std::cout << "jr $ra" << std::endl;
        if (SymbolTable.returnScopeCurrent() == 0)
        {
            std::cout << ".global " << returnFunc() << std::endl;
        }
    }
};

#endif