#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_primitives.hpp"
#include "ast_statements.hpp"
#include "ast_expressions.hpp"
#include "ast_prim_storefunc.hpp"

class Function
{
private:
    StoreFunc *funcName;
    DecListPtr args;
    StatPtr stats;

public:
    Function(StoreFunc *_name, DecListPtr _args = nullptr, StatPtr _statements = nullptr)
        : funcName(_name), args(_args), stats(_statements)
    {
    }

    virtual ~Function()
    {
        delete funcName,
            delete args,
            delete stats;
    }

    const std::string returnFunc() const
    {
        return funcName->returnFuncId();
    }

    const std::string returnType() const
    {
        return funcName->returnType();
    }

    DecListPtr returnArgs() const
    {
        return args;
    }

    void Translate2MIPS(std::string destReg) const
    {
        if (stats != nullptr)
        {
            funcName->Translate2MIPS(destReg);
        }
        else
        {
            funcName->Translate2MIPS("$0");
        }
        std::string functionType = returnType();
        if (stats != nullptr)
        {
            SymTab.setScopeFunc(SymTab.getScopeFunc() + 1);
            SymTab.setfuncstart(funcName->returnFuncId());
            SymTab.setfuncend(funcName->returnFuncId() + "end");
            std::cout << funcName->returnFuncId() << ":" << std::endl;
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
            StkPtr.setIncrement(StkPtr.getIncrement() + 44);

            if (args != nullptr)
            {
                SymTab.enterScope();
                StkPtr.setScopeCurrent(StkPtr.returnScopeCurrent() + 1);
                StkPtr.setScopeIncrement(0);
                args->Translate2MIPS(destReg);
                if (functionType == "INT")
                {
                    stats->Translate2MIPS(destReg);
                }
                else if (functionType == "FLOAT")
                {
                    stats->Translate2MIPS("$f0");
                }
                else if (functionType == "DOUBLE")
                {
                    stats->Translate2MIPS("$f0");
                }
                else
                {
                    std::cout << "Function datatype missing" << std::endl;
                }
                std::cout << funcName->returnFuncId() << "end:" << std::endl;
                for (int i = StkPtr.returnScopeCurrent(); i < 50; i++)
                {
                    if (StkPtr.returnScopeIncrement(i) != 0)
                    {
                        std::cout << "addiu $sp, $sp, " << StkPtr.returnScopeIncrement(i) << std::endl;
                    }
                }
                StkPtr.setScopeIncrement(0);
                StkPtr.setScopeCurrent(StkPtr.returnScopeCurrent() - 1);
                SymTab.exitScope();
            }
            else
            {
                std::string functionType = returnType();
                if (functionType == "INT")
                {
                    stats->Translate2MIPS(destReg);
                }
                else if (functionType == "FLOAT")
                {
                    stats->Translate2MIPS("$f0");
                }
                else if (functionType == "DOUBLE")
                {
                    stats->Translate2MIPS("$f0");
                }
                else
                {
                    std::cout << "ERROR: function datatype missing" << std::endl;
                }
                std::cout << funcName->returnFuncId() << "end:" << std::endl;
                for (int i = StkPtr.returnScopeCurrent() + 1; i < 50; i++)
                {
                    if (StkPtr.returnScopeIncrement(i) != 0)
                    {
                        std::cout << "addiu $sp, $sp, " << StkPtr.returnScopeIncrement(i) << std::endl;
                    }
                }
            }
            StkPtr.setIncrement(StkPtr.getIncrement() - 44);
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
            if (SymTab.returnScopeCurrent() == 0)
            {
                std::cout << ".global " << funcName->returnFuncId() << std::endl;
                SymTab.setScopeFunc(SymTab.getScopeFunc() - 1);
                StkPtr.setReturnFunc(0);
            }
        }
        else
        {
            if (args != nullptr)
            {
                SymTab.enterScope();
                StkPtr.setScopeCurrent(StkPtr.returnScopeCurrent() + 1);
                StkPtr.setScopeIncrement(0);
                args->Translate2MIPS(destReg);
                std::cout << "addiu $sp, $sp, " << StkPtr.returnScopeIncrement() << std::endl;
                StkPtr.setScopeIncrement(0);
                StkPtr.setScopeCurrent(StkPtr.returnScopeCurrent() - 1);
                SymTab.exitScope();
            }
        }
    }

    void pretty_print(std::ostream &dst) const
    {
        funcName->pretty_print(dst);
        dst << "( ";
        dst << " )";
        dst << '\n';
        stats->pretty_print(dst);
    }
};

class Main
{
private:
    Function *func = nullptr;
    Identifier *decl = nullptr;
    Main *main = nullptr;

public:
    Main(Function *_func, Main *_main = nullptr)
        : func(_func), main(_main)
    {
    }

    Main(Identifier *_decl, Main *_main = nullptr)
        : decl(_decl), main(_main)
    {
    }
    virtual ~Main()
    {
        delete func,
            delete decl,
            delete main;
    }

    Function *returnFunc() const
    {
        return func;
    }
    Identifier *returnDecl() const
    {
        return decl;
    }
    Main *returnMain() const
    {
        return main;
    }

    void Translate2MIPS(std::string destReg) const
    {
        if (returnFunc() != nullptr)
        {
            returnFunc()->Translate2MIPS(destReg);
        }
        else if (returnDecl() != nullptr)
        {
            returnDecl()->Translate2MIPS(destReg);
        }
        if (returnMain() != nullptr)
        {
            returnMain()->Translate2MIPS(destReg);
        }
    }
};
#endif