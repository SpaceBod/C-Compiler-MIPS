#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>

#include "ast_symtab.hpp"

extern SymTab SymbolTable;
extern StackPtr StackPointer;

enum VarType
{
    INTEGER,
    DOUBLE,
    FLOAT
};

enum DecType
{
    CALL,
    ASSIGN,
    ARGUEMENT,
    DECLARATION
};

class Variable
    : public Expression
{
private:
    std::string var_name;
    std::string type;
    ExpressionPtr Expr = nullptr;
    DecType dec_type;
    std::string assign_type;
    mutable std::string address;

public:
    Variable()
    {
    }

    Variable(const std::string *_var_name)
    {
        dec_type = CALL;
        var_name = *_var_name;
    }

    Variable(const std::string *_var_name, std::string *_assign_type, ExpressionPtr _Expr)
    {
        dec_type = ASSIGN;
        var_name = *_var_name;
        assign_type = *_assign_type;
        Expr = _Expr;
    }

    Variable(VarType _type, const std::string *_var_name, DecType _kind, ExpressionPtr _Expr = nullptr)
    {
        if (_kind == ARGUEMENT)
        {
            dec_type = ARGUEMENT;
            switch (_type)
            {
            case INTEGER:
                type = "int";
                Expr = _Expr;
                var_name = *_var_name;

                // StackPointer.setIncrement(StackPointer.returnIncrement() + 4);
                // address = std::to_string(StackPointer.returnIncrement() + 2000);
                // if (SymbolTable.lookup(var_name) == "Error")
                // {
                //     SymbolTable.insert(type, "var", var_name, address);
                // }
                // else
                // {
                //     SymbolTable.edit(type, "var", var_name, address);
                // }

                break;
            case DOUBLE:
                type = "double";
                var_name = *_var_name;

                // StackPointer.setIncrement(StackPointer.returnIncrement() + 4);
                // address = std::to_string(StackPointer.returnIncrement() + 2000);
                // if (SymbolTable.lookup(var_name) == "Error")
                // {
                //     SymbolTable.insert(var_name, "var", type, address);
                // }
                // else
                // {
                //     SymbolTable.edit(var_name, "var", type, address);
                // }
                break;
            case FLOAT:
                type = "float";
                var_name = *_var_name;

                // StackPointer.setIncrement(StackPointer.returnIncrement() + 4);
                // address = std::to_string(StackPointer.returnIncrement() + 2000);
                // if (SymbolTable.lookup(var_name) == "Error")
                // {
                //     SymbolTable.insert(var_name, "var", type, address);
                // }
                // else
                // {
                //     SymbolTable.edit(var_name, "var", type, address);
                // }
                break;
            default:
                type = "UNDEFINED";
            }
        }

        else if (_kind == DECLARATION)
        {
            dec_type = DECLARATION;
            switch (_type)
            {
            case INTEGER:
                type = "int";
                var_name = *_var_name;
                Expr = _Expr;
                break;
            case DOUBLE:
                type = "double";
                var_name = *_var_name;
                Expr = _Expr;
                break;
            case FLOAT:
                type = "float";
                var_name = *_var_name;
                Expr = _Expr;
                break;
            default:
                type = "UNDEFINED";
            }
        }
    }

    const std::string return_var_name() const
    {
        return var_name;
    }

    const std::string return_type() const
    {
        return type;
    }

    const std::string return_address() const
    {
        return address;
    }

    ExpressionPtr return_expr() const
    {
        return Expr;
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        switch (dec_type)
        {
        case CALL:
            dst << var_name;
            break;

        case ASSIGN:
            dst << var_name;
            dst << " ";
            dst << assign_type;
            dst << " ";
            Expr->pretty_print(dst);
            break;

        case DECLARATION:
            dst << type;
            dst << " ";
            dst << var_name;
            if (Expr != nullptr)
            {
                dst << " = ";
                Expr->pretty_print(dst);
            }
            dst << ";";
            dst << '\n';
            break;
        }
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        return bindings.at(var_name);
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        switch (dec_type)
        {
        case CALL:
            address = SymbolTable.lookup(var_name);
            std::cout << "addi $t0, $0, " << address << std::endl;
            break;
        case ASSIGN:
            if (assign_type == "=")
            {
                return_expr()->Translate2MIPS("$t0");
                std::cout << "sw $t0, -" << address << "($fp)" << std::endl;
            }
            else if (assign_type == "+=")
            {
                return_expr()->Translate2MIPS("$t0");
                std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                std::cout << "add $t1, $t1, $t0" << std::endl;
                std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
            }
            else if (assign_type == "-=")
            {
                return_expr()->Translate2MIPS("$t0");
                std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                std::cout << "sub $t1, $t1, $t0" << std::endl;
                std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
            }
            else if (assign_type == "/=")
            {
                return_expr()->Translate2MIPS("$t0");
                std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                std::cout << "div $t1, $t0" << std::endl;
                std::cout << "mfhi $t1" << std::endl;
                std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
            }
            else if (assign_type == "*=")
            {
                return_expr()->Translate2MIPS("$t0");
                std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                std::cout << "mul $t1, $t1, $t0" << std::endl;
                std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
            }
            else if (assign_type == "%=")
            {
                return_expr()->Translate2MIPS("$t0");
                std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                std::cout << "div $t1, $t0" << std::endl;
                std::cout << "mflo $t1" << std::endl;
                std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
            }
            else if (assign_type == "<<=")
            {
                return_expr()->Translate2MIPS("$t0");
                std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                std::cout << "sllv $t1, $t1, $t0" << std::endl;
                std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
            }
            else if (assign_type == ">>=")
            {
                return_expr()->Translate2MIPS("$t0");
                std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                std::cout << "srlv $t1, $t1, $t0" << std::endl;
                std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
            }
            else if (assign_type == "^=")
            {
                return_expr()->Translate2MIPS("$t0");
                std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                std::cout << "xor $t1, $t1, $t0" << std::endl;
                std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
            }
            else if (assign_type == "&=")
            {
                return_expr()->Translate2MIPS("$t0");
                std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                std::cout << "and $t1, $t1, $t0" << std::endl;
                std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
            }
            else if (assign_type == "|=")
            {
                return_expr()->Translate2MIPS("$t0");
                std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                std::cout << "or $t1, $t1, $t0" << std::endl;
                std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
            }
            break;

        case DECLARATION:
            if (return_type() == "INTEGER")
            {
                std::cout << "addi $sp, $sp, -4" << std::endl;
                StackPointer.setIncrement(StackPointer.returnIncrement() + 4);
                StackPointer.setScopeIncrement(StackPointer.returnScopeIncrement() + 4);
                address = std::to_string(StackPointer.returnIncrement());
                if (SymbolTable.lookup(var_name) == "Error: undefined reference")
                {
                    SymbolTable.insert(var_name, "var", type, address);
                }
                else
                {
                    SymbolTable.edit(var_name, "var", type, address);
                }
                if (Expr != nullptr)
                {
                    return_expr()->Translate2MIPS("$t0");
                    std::cout << "sw $t0, -" << address << "($fp)" << std::endl;
                }
                if (SymbolTable.returnScopeCurrent() == 0)
                {
                    std::cout << ".global " << return_var_name() << std::endl;
                }
            }
            break;
        case ARGUEMENT:
            if (return_type() == "INTEGER")
            {
                std::cout << "addi $sp, $sp, -4" << std::endl;
                if (StackPointer.returnArgCount() < 4)
                {
                    std::cout << "sw $a" << StackPointer.returnArgCount() << ", 0($sp)" << std::endl;
                }
                StackPointer.setIncrement(StackPointer.returnIncrement() + 4);
                StackPointer.setScopeIncrement(StackPointer.returnScopeIncrement() + 4);
                address = std::to_string(StackPointer.returnIncrement());
                if (SymbolTable.lookup(var_name) == "Error: undefined reference")
                {
                    SymbolTable.insert(var_name, "var", type, address);
                }
                else
                {
                    SymbolTable.edit(var_name, "var", type, address);
                }
                if (Expr != nullptr)
                {
                    return_expr()->Translate2MIPS("$t0");
                    std::cout << "sw $t0, -" << address << "($fp)" << std::endl;
                }
                if (SymbolTable.returnScopeCurrent() == 0)
                {
                    std::cout << ".global " << return_var_name() << std::endl;
                }
            }
            break;
        }
    }
};

class Number
    : public Expression
{
private:
    double value;

public:
    Number(double _value)
        : value(_value)
    {
    }

    double return_val() const
    {
        return value;
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << value;
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        return value;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        std::cout << "addi " << destReg << " $0 " << value << std::endl;
    }
};

class Decl_list;
typedef const Decl_list *Decl_listPtr;

class Decl_list
    : public Variable
{
private:
    Variable *variable;
    Decl_listPtr decl_list = nullptr;

public:
    Decl_list(Variable *_variable, Decl_listPtr _decl_list = nullptr)
        : variable(_variable), decl_list(_decl_list)
    {
    }

    virtual ~Decl_list()
    {
        delete variable;
        delete decl_list;
    }
    Variable *return_var() const
    {
        return variable;
    }

    Decl_listPtr return_decllist() const
    {
        return decl_list;
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        variable->pretty_print(dst);
        if (decl_list != nullptr)
        {
            dst << ", ";
            decl_list->pretty_print(dst);
        }
    }
    virtual void Translate2MIPS(std::string destReg) const override
    {
        return_var()->Translate2MIPS(destReg);
        StackPointer.setArgCount(StackPointer.returnArgCount() + 1);
        if (decl_list != nullptr)
        {
            return_decllist()->Translate2MIPS(destReg);
        }
        StackPointer.setArgCount(0);
    }
};
#endif
