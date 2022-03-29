#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>

#include "ast_symtab.hpp"
#include "ast_expressions.hpp"

enum VarTypeDef
{
    INT,
    FLOAT,
    DOUBLE,
    CHAR
};

enum DecType
{
    CALL,
    ASSIGN,
    DECLARATION,
    ARGUMENT
};

class Identifier
    : public Expr
{
private:
    mutable std::string type;
    std::string varID;
    mutable std::string address;
    std::string assignOp;
    DecType VarType;
    ExprPtr Expr = nullptr;
    bool addressTrue;

public:
    Identifier()
    {
    }

    Identifier(const std::string *_varID, bool _addressTrue = false)
    {
        VarType = CALL;
        varID = *_varID;
        addressTrue = _addressTrue;
    }

    Identifier(const std::string *_varID, std::string *_assignOp, ExprPtr _Expr)
    {
        VarType = ASSIGN;
        varID = *_varID;
        assignOp = *_assignOp;
        Expr = _Expr;
    }

    Identifier(VarTypeDef _type, const std::string *_varID, DecType _kind, ExprPtr _Expr = nullptr)
    {
        if (_kind == ARGUMENT)
        {
            VarType = ARGUMENT;
            switch (_type)
            {
            case INT:
                type = "INT";
                varID = *_varID;
                break;
            case FLOAT:
                type = "FLOAT";
                varID = *_varID;
                break;
            case DOUBLE:
                type = "DOUBLE";
                varID = *_varID;
                break;
            case CHAR:
                type = "CHAR";
                varID = *_varID;
                break;
            default:
                type = "ARGUMENT TYPE UNKNOWN";
            }
        }
        else if (_kind == DECLARATION)
        {
            VarType = DECLARATION;
            switch (_type)
            {
            case INT:
                type = "INT";
                varID = *_varID;
                Expr = _Expr;
                break;
            case FLOAT:
                type = "FLOAT";
                varID = *_varID;
                Expr = _Expr;
                break;
            case DOUBLE:
                type = "DOUBLE";
                varID = *_varID;
                Expr = _Expr;
                break;
            case CHAR:
                type = "CHAR";
                varID = *_varID;
                Expr = _Expr;
                break;
            default:
                type = "DECLARATION TYPE UNKNOWN";
            }
        }
    }

    const std::string returnType() const
    {
        return type;
    }

    const std::string returnFuncId() const
    {
        return varID;
    }

    const std::string returnAddress() const
    {
        return address;
    }

    ExprPtr returnExpr() const
    {
        return Expr;
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        switch (VarType)
        {
        case CALL:
            dst << varID;
            break;
        case ASSIGN:
            dst << varID;
            dst << " ";
            dst << assignOp;
            dst << " ";
            Expr->pretty_print(dst);
            break;
        case DECLARATION:
            dst << type;
            dst << " ";
            dst << varID;
            if (Expr != nullptr)
            {
                dst << " = ";
                Expr->pretty_print(dst);
            }
            dst << ";";
            dst << '\n';
            break;
        default:
            break;
        }
    }

    virtual const std::string returnData() const override
    {
        type = SymTab.returnType(varID);
        return type;
    }

    virtual const std::string returnDataKind() const override
    {
        std::string format = SymTab.returnKind(varID);
        return format;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        std::string format;
        switch (VarType)
        {
        case CALL:
            address = SymTab.lookup(varID);
            type = SymTab.returnType(varID);
            format = SymTab.returnKind(varID);
            if (format == "ptr")
            {
                if (addressTrue)
                {
                    std::cout << "addi " << destReg << ", $fp, -" << address << std::endl;
                }
                else
                {
                    std::cout << "lw " << destReg << ", -" << address << "($fp)" << std::endl;
                }
            }
            else if (format == "var")
            {
                if (addressTrue)
                {
                    std::cout << "addi " << destReg << ", $fp, -" << address << std::endl;
                }
                else
                {
                    if (type == "INT")
                    {
                        std::cout << "lw " << destReg << ", -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "FLOAT")
                    {
                        std::cout << "lwc1 " << destReg << ", -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "DOUBLE")
                    {
                        std::cout << "lwc1 " << destReg << ", -" << address << "($fp)" << std::endl;
                        std::cout << "lwc1 " << destReg[0] << destReg[1] << (int)destReg[2] - 48 + 1 << ", -" << std::stoi(address) - 4 << "($fp)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        std::cout << "lb " << destReg << ", -" << address << "($fp)" << std::endl;
                    }
                }
            }
            break;
        case ASSIGN:
            address = SymTab.lookup(varID);
            type = SymTab.returnType(varID);
            format = SymTab.returnKind(varID);
            if (format == "ptr")
            {
                if (assignOp == "=")
                {
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "sw $t0, -" << address << "($fp)" << std::endl;
                }
                else if (assignOp == "+=")
                {
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                    if (type == "DOUBLE")
                    {
                        for (int i = 0; i < 8; i++)
                        {
                            std::cout << "add $t1, $t1, $t0" << std::endl;
                        }
                    }
                    else
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            std::cout << "add $t1, $t1, $t0" << std::endl;
                        }
                    }
                    std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
                }
                else if (assignOp == "-=")
                {
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                    if (type == "DOUBLE")
                    {
                        for (int i = 0; i < 8; i++)
                        {
                            std::cout << "sub $t1, $t1, $t0" << std::endl;
                        }
                    }
                    else
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            std::cout << "sub $t1, $t1, $t0" << std::endl;
                        }
                    }
                    std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
                }
                else if (assignOp == "/=")
                {
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                    std::cout << "div $t1, $t0" << std::endl;
                    std::cout << "mflo $t1" << std::endl;
                    std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
                }
                else if (assignOp == "*=")
                {
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                    std::cout << "mul $t1, $t1, $t0" << std::endl;
                    std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
                }
                else if (assignOp == "%=")
                {
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                    std::cout << "div $t1, $t0" << std::endl;
                    std::cout << "mfhi $t1" << std::endl;
                    std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
                }
                else if (assignOp == "<<=")
                {
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                    std::cout << "sllv $t1, $t1, $t0" << std::endl;
                    std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
                }
                else if (assignOp == ">>=")
                {
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                    std::cout << "srlv $t1, $t1, $t0" << std::endl;
                    std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
                }
                else if (assignOp == "^=")
                {
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                    std::cout << "xor $t1, $t1, $t0" << std::endl;
                    std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
                }
                else if (assignOp == "&=")
                {
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                    std::cout << "and $t1, $t1, $t0" << std::endl;
                    std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
                }
                else if (assignOp == "|=")
                {
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                    std::cout << "or $t1, $t1, $t0" << std::endl;
                    std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
                }
                else if (assignOp == "++")
                {
                    std::cout << "lw $t0, -" << address << "($fp)" << std::endl;
                    if (type == "DOUBLE")
                    {
                        std::cout << "addi $t0, $t0, 8" << std::endl;
                    }
                    else
                    {
                        std::cout << "addi $t0, $t0, 4" << std::endl;
                    }
                    std::cout << "sw $t0, -" << address << "($fp)" << std::endl;
                }
                else if (assignOp == "--")
                {
                    std::cout << "lw $t0, -" << address << "($fp)" << std::endl;
                    if (type == "DOUBLE")
                    {
                        std::cout << "addi $t0, $t0, -8" << std::endl;
                    }
                    else
                    {
                        std::cout << "addi $t0, $t0, -4" << std::endl;
                    }
                    std::cout << "sw $t0, -" << address << "($fp)" << std::endl;
                }
            }
            else if (format == "var")
            {
                if (assignOp == "=")
                {
                    if (type == "INT")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "sw $t0, -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "FLOAT")
                    {
                        returnExpr()->Translate2MIPS("$f0");
                        std::cout << "swc1 $f0, -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "DOUBLE")
                    {
                        returnExpr()->Translate2MIPS("$f0");
                        std::cout << "swc1 $f0, -" << address << "($fp)" << std::endl;
                        std::cout << "swc1 $f1, -" << std::stoi(address) - 4 << "($fp)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "sb $t0, -" << address << "($fp)" << std::endl;
                    }
                    else
                    {
                        std::cout << returnType() << std::endl;
                        std::cout << "ERROR: type missing" << std::endl;
                    }
                }
                else if (assignOp == "+=")
                {
                    if (type == "INT")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                        std::cout << "add $t1, $t1, $t0" << std::endl;
                        std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "FLOAT")
                    {
                        returnExpr()->Translate2MIPS("$f0");
                        std::cout << "lwc1 $f2, -" << address << "($fp)" << std::endl;
                        std::cout << "add.s $f2, $f2, $f0" << std::endl;
                        std::cout << "swc1 $f2, -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "DOUBLE")
                    {
                        returnExpr()->Translate2MIPS("$f0");
                        std::cout << "lwc1 $f2, -" << address << "($fp)" << std::endl;
                        std::cout << "lwc1 $f3, -" << std::stoi(address) - 4 << "($fp)" << std::endl;
                        std::cout << "add.d $f2, $f2, $f0" << std::endl;
                        std::cout << "swc1 $f2, -" << address << "($fp)" << std::endl;
                        std::cout << "swc1 #f3, -" << std::stoi(address) - 4 << "($fp)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lbu $t1, -" << address << "($fp)" << std::endl;
                        std::cout << "add $t1, $t1, $t0" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, -" << address << "($fp)" << std::endl;
                    }
                }
                else if (assignOp == "-=")
                {
                    if (type == "INT")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                        std::cout << "sub $t1, $t1, $t0" << std::endl;
                        std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "FLOAT")
                    {
                        returnExpr()->Translate2MIPS("$f0");
                        std::cout << "lwc1 $f2, -" << address << "($fp)" << std::endl;
                        std::cout << "sub.s $f2, $f2, $f0" << std::endl;
                        std::cout << "swc1 $f2, -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "DOUBLE")
                    {
                        returnExpr()->Translate2MIPS("$f0");
                        std::cout << "lwc1 $f2, -" << address << "($fp)" << std::endl;
                        std::cout << "lwc1 $f3, -" << std::stoi(address) - 4 << "($fp)" << std::endl;
                        std::cout << "sub.d $f2, $f2, $f0" << std::endl;
                        std::cout << "swc1 $f2, -" << address << "($fp)" << std::endl;
                        std::cout << "swc1 #f3, -" << std::stoi(address) - 4 << "($fp)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lbu $t1, -" << address << "($fp)" << std::endl;
                        std::cout << "sub $t1, $t1, $t0" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, -" << address << "($fp)" << std::endl;
                    }
                }
                else if (assignOp == "/=")
                {
                    if (type == "INT")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                        std::cout << "div $t1, $t0" << std::endl;
                        std::cout << "mflo $t1" << std::endl;
                        std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "FLOAT")
                    {
                        returnExpr()->Translate2MIPS("$f0");
                        std::cout << "lwc1 $f2, -" << address << "($fp)" << std::endl;
                        std::cout << "div.s $f2, $f2, $f0" << std::endl;
                        std::cout << "swc1 $f2, -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "DOUBLE")
                    {
                        returnExpr()->Translate2MIPS("$f0");
                        std::cout << "lwc1 $f2, -" << address << "($fp)" << std::endl;
                        std::cout << "lwc1 $f3, -" << std::stoi(address) - 4 << "($fp)" << std::endl;
                        std::cout << "div.d $f2, $f2, $f0" << std::endl;
                        std::cout << "swc1 $f2, -" << address << "($fp)" << std::endl;
                        std::cout << "swc1 #f3, -" << std::stoi(address) - 4 << "($fp)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lbu $t1, -" << address << "($fp)" << std::endl;
                        std::cout << "div $t1, $t0" << std::endl;
                        std::cout << "mflo $t1" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, -" << address << "($fp)" << std::endl;
                    }
                }
                else if (assignOp == "*=")
                {
                    if (type == "INT")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                        std::cout << "mul $t1, $t1, $t0" << std::endl;
                        std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "FLOAT")
                    {
                        returnExpr()->Translate2MIPS("$f0");
                        std::cout << "lwc1 $f2, -" << address << "($fp)" << std::endl;
                        std::cout << "mul.s $f2, $f2, $f0" << std::endl;
                        std::cout << "swc1 $f2, -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "DOUBLE")
                    {
                        returnExpr()->Translate2MIPS("$f0");
                        std::cout << "lwc1 $f2, -" << address << "($fp)" << std::endl;
                        std::cout << "lwc1 $f3, -" << std::stoi(address) - 4 << "($fp)" << std::endl;
                        std::cout << "mul.d $f2, $f2, $f0" << std::endl;
                        std::cout << "swc1 $f2, -" << address << "($fp)" << std::endl;
                        std::cout << "swc1 #f3, -" << std::stoi(address) - 4 << "($fp)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lbu $t1, -" << address << "($fp)" << std::endl;
                        std::cout << "mul $t1, $t1, $t0" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, -" << address << "($fp)" << std::endl;
                    }
                }
                else if (assignOp == "%=")
                {
                    if (type == "INT")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                        std::cout << "div $t1, $t0" << std::endl;
                        std::cout << "mfhi $t1" << std::endl;
                        std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lbu $t1, -" << address << "($fp)" << std::endl;
                        std::cout << "div $t1, $t0" << std::endl;
                        std::cout << "mfhi $t1" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, -" << address << "($fp)" << std::endl;
                    }
                }
                else if (assignOp == "<<=")
                {
                    if (type == "INT")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                        std::cout << "sllv $t1, $t1, $t0" << std::endl;
                        std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lbu $t1, -" << address << "($fp)" << std::endl;
                        std::cout << "sllv $t1, $t1, $t0" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, -" << address << "($fp)" << std::endl;
                    }
                }
                else if (assignOp == ">>=")
                {
                    if (type == "INT")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                        std::cout << "srlv $t1, $t1, $t0" << std::endl;
                        std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lbu $t1, -" << address << "($fp)" << std::endl;
                        std::cout << "srlv $t1, $t1, $t0" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, -" << address << "($fp)" << std::endl;
                    }
                }
                else if (assignOp == "^=")
                {
                    if (type == "INT")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                        std::cout << "xor $t1, $t1, $t0" << std::endl;
                        std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lbu $t1, -" << address << "($fp)" << std::endl;
                        std::cout << "xor $t1, $t1, $t0" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, -" << address << "($fp)" << std::endl;
                    }
                }
                else if (assignOp == "&=")
                {
                    if (type == "INT")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                        std::cout << "and $t1, $t1, $t0" << std::endl;
                        std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lbu $t1, -" << address << "($fp)" << std::endl;
                        std::cout << "and $t1, $t1, $t0" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, -" << address << "($fp)" << std::endl;
                    }
                }
                else if (assignOp == "|=")
                {
                    if (type == "INT")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                        std::cout << "or $t1, $t1, $t0" << std::endl;
                        std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lbu $t1, -" << address << "($fp)" << std::endl;
                        std::cout << "or $t1, $t1, $t0" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, -" << address << "($fp)" << std::endl;
                    }
                }
                else if (assignOp == "++")
                {
                    if (type == "INT")
                    {
                        std::cout << "lw $t0, -" << address << "($fp)" << std::endl;
                        std::cout << "addi $t0, $t0, 1" << std::endl;
                        std::cout << "sw $t0, -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "FLOAT")
                    {
                        std::cout << "lwc1 $f0, -" << address << "($fp)" << std::endl;
                        std::cout << "addi.s $f0, $f0, 1" << std::endl;
                        std::cout << "swc1 $f0, -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "DOUBLE")
                    {
                        std::cout << "lwc1 $f0, -" << address << "($fp)" << std::endl;
                        std::cout << "lwc1 $f1, -" << std::stoi(address) + 4 << "($fp)" << std::endl;
                        std::cout << "addi.d $f0, $f0, 1" << std::endl;
                        std::cout << "swc1 $f0, -" << address << "($fp)" << std::endl;
                        std::cout << "swc1 $f1, -" << std::stoi(address) + 4 << "($fp)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        std::cout << "lbu $t0, -" << address << "($fp)" << std::endl;
                        std::cout << "addi $t0, $t0, 1" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, -" << address << "($fp)" << std::endl;
                    }
                }
                else if (assignOp == "--")
                {
                    if (type == "INT")
                    {
                        std::cout << "lw $t0, -" << address << "($fp)" << std::endl;
                        std::cout << "addi $t0, $t0, -1" << std::endl;
                        std::cout << "sw $t0, -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "FLOAT")
                    {
                        std::cout << "lwc1 $f0, -" << address << "($fp)" << std::endl;
                        std::cout << "addi.s $f0, $f0, -1" << std::endl;
                        std::cout << "swc1 $f0, -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "DOUBLE")
                    {
                        std::cout << "lwc1 $f0, -" << address << "($fp)" << std::endl;
                        std::cout << "lwc1 $f1, -" << std::stoi(address) + 4 << "($fp)" << std::endl;
                        std::cout << "addi.d $f0, $f0, -1" << std::endl;
                        std::cout << "swc1 $f0, -" << address << "($fp)" << std::endl;
                        std::cout << "swc1 $f1, -" << std::stoi(address) + 4 << "($fp)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        std::cout << "lbu $t0, -" << address << "($fp)" << std::endl;
                        std::cout << "addi $t0, $t0, -1" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, -" << address << "($fp)" << std::endl;
                    }
                }
            }
            break;
        case DECLARATION:
            if (returnType() == "INT")
            {
                std::cout << "addi $sp, $sp, -4" << std::endl;
                StkPtr.setIncrement(StkPtr.getIncrement() + 4);
                StkPtr.setScopeIncrement(StkPtr.returnScopeIncrement() + 4);
                address = std::to_string(StkPtr.getIncrement());
                if (SymTab.lookup(varID) == "Unknown reference from ID")
                {
                    SymTab.insert(type, "var", varID, address);
                }
                else
                {
                    SymTab.edit(type, "var", varID, address);
                }
                if (Expr != nullptr)
                {
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "sw $t0, -" << address << "($fp)" << std::endl;
                }
                if (SymTab.returnScopeCurrent() == 0)
                {
                    std::cout << ".global " << returnFuncId() << std::endl;
                }
            }
            else if (returnType() == "FLOAT")
            {
                std::cout << "addi $sp, $sp, -4" << std::endl;
                StkPtr.setIncrement(StkPtr.getIncrement() + 4);
                StkPtr.setScopeIncrement(StkPtr.returnScopeIncrement() + 4);
                address = std::to_string(StkPtr.getIncrement());
                if (SymTab.lookup(varID) == "Unknown reference from ID")
                {
                    SymTab.insert(type, "var", varID, address);
                }
                else
                {
                    SymTab.edit(type, "var", varID, address);
                }
                if (Expr != nullptr)
                {
                    returnExpr()->Translate2MIPS("$f0");
                    std::cout << "swc1 $f0, -" << address << "($fp)" << std::endl;
                }
                if (SymTab.returnScopeCurrent() == 0)
                {
                    std::cout << ".global " << returnFuncId() << std::endl;
                }
            }
            else if (returnType() == "DOUBLE")
            {
                std::cout << "addi $sp, $sp, -8" << std::endl;
                StkPtr.setIncrement(StkPtr.getIncrement() + 8);
                StkPtr.setScopeIncrement(StkPtr.returnScopeIncrement() + 8);
                address = std::to_string(StkPtr.getIncrement() - 4);
                if (SymTab.lookup(varID) == "Unknown reference from ID")
                {
                    SymTab.insert(type, "var", varID, address);
                }
                else
                {
                    SymTab.edit(type, "var", varID, address);
                }
                if (Expr != nullptr)
                {
                    returnExpr()->Translate2MIPS("$f0");
                    std::cout << "swc1 $f0, -" << address << "($fp)" << std::endl;
                    std::cout << "swc1 $f1, -" << std::stoi(address) - 4 << "($fp)" << std::endl;
                }
                if (SymTab.returnScopeCurrent() == 0)
                {
                    std::cout << ".global " << returnFuncId() << std::endl;
                }
            }
            else if (returnType() == "CHAR")
            {
                std::cout << "addi $sp, $sp, -4" << std::endl;
                StkPtr.setIncrement(StkPtr.getIncrement() + 4);
                StkPtr.setScopeIncrement(StkPtr.returnScopeIncrement() + 4);
                address = std::to_string(StkPtr.getIncrement());
                if (SymTab.lookup(varID) == "Unknown reference from ID")
                {
                    SymTab.insert(type, "var", varID, address);
                }
                else
                {
                    SymTab.edit(type, "var", varID, address);
                }
                if (Expr != nullptr)
                {
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "andi $t0, $t0, 0x00ff" << std::endl;
                    std::cout << "sb $t0, -" << address << "($fp)" << std::endl;
                }
                if (SymTab.returnScopeCurrent() == 0)
                {
                    std::cout << ".global " << returnFuncId() << std::endl;
                }
            }
            break;
        case ARGUMENT:
            if (returnType() == "INT")
            {
                std::cout << "addi $sp, $sp, -4" << std::endl;
                if (StkPtr.returnArgCount() < 4)
                {
                    std::cout << "sw $a" << StkPtr.returnArgCount() << ", 0($sp)" << std::endl;
                }
                StkPtr.setIncrement(StkPtr.getIncrement() + 4);
                StkPtr.setScopeIncrement(StkPtr.returnScopeIncrement() + 4);
                address = std::to_string(StkPtr.getIncrement());
                if (SymTab.lookup(varID) == "Unknown reference from ID")
                {
                    SymTab.insert(type, "var", varID, address);
                }
                else
                {
                    SymTab.edit(type, "var", varID, address);
                }
                if (Expr != nullptr)
                {
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "sw $t0, -" << address << "($fp)" << std::endl;
                }
                if (SymTab.returnScopeCurrent() == 0)
                {
                    std::cout << ".global " << returnFuncId() << std::endl;
                }
            }
            else if (returnType() == "FLOAT")
            {
                std::cout << "addi $sp, $sp, -4" << std::endl;
                if (StkPtr.returnArgCount() < 4)
                {
                    if (StkPtr.returnArgCount() == 0)
                    {
                        std::cout << "swc1 $f12, 0($sp)" << std::endl;
                    }
                    else if (StkPtr.returnArgCount() == 1)
                    {
                        std::cout << "swc1 $f14, 0($sp)" << std::endl;
                    }
                    else if (StkPtr.returnArgCount() == 2)
                    {
                        std::cout << "sw $6, 0($sp)" << std::endl;
                    }
                    else if (StkPtr.returnArgCount() == 3)
                    {
                        std::cout << "sw $7, 0($sp)" << std::endl;
                    }
                }
                StkPtr.setIncrement(StkPtr.getIncrement() + 4);
                StkPtr.setScopeIncrement(StkPtr.returnScopeIncrement() + 4);
                address = std::to_string(StkPtr.getIncrement());
                if (SymTab.lookup(varID) == "Unknown reference from ID")
                {
                    SymTab.insert(type, "var", varID, address);
                }
                else
                {
                    SymTab.edit(type, "var", varID, address);
                }
                if (Expr != nullptr)
                {
                    returnExpr()->Translate2MIPS("$f0");
                    std::cout << "swc1 $f0, -" << address << "($fp)" << std::endl;
                }
                if (SymTab.returnScopeCurrent() == 0)
                {
                    std::cout << ".global " << returnFuncId() << std::endl;
                }
            }
            else if (returnType() == "DOUBLE")
            {
                std::cout << "addi $sp, $sp, -8" << std::endl;
                if (StkPtr.returnArgCount() < 4)
                {
                    int float_argNum;
                    if (StkPtr.returnArgCount() == 0)
                    {
                        float_argNum = 12;
                    }
                    else if (StkPtr.returnArgCount() == 1)
                    {
                        float_argNum = 14;
                    }
                    else if (StkPtr.returnArgCount() == 2)
                    {
                        float_argNum = 16;
                    }
                    else if (StkPtr.returnArgCount() == 3)
                    {
                        float_argNum = 18;
                    }
                    std::cout << "swc1 $f" << float_argNum << ", 0($sp)" << std::endl;
                    std::cout << "swc1 $f" << float_argNum + 1 << ", 4($sp)" << std::endl;
                }
                StkPtr.setIncrement(StkPtr.getIncrement() + 8);
                StkPtr.setScopeIncrement(StkPtr.returnScopeIncrement() + 8);
                address = std::to_string(StkPtr.getIncrement());
                if (SymTab.lookup(varID) == "Unknown reference from ID")
                {
                    SymTab.insert(type, "var", varID, address);
                }
                else
                {
                    SymTab.edit(type, "var", varID, address);
                }
                if (Expr != nullptr)
                {
                    returnExpr()->Translate2MIPS("$f0");
                    std::cout << "swc1 $f0, -" << address << "($fp)" << std::endl;
                    std::cout << "swc1 $f1, -" << std::stoi(address) - 4 << "($fp)" << std::endl;
                }
                if (SymTab.returnScopeCurrent() == 0)
                {
                    std::cout << ".global " << returnFuncId() << std::endl;
                }
            }
            else if (returnType() == "CHAR")
            {
                std::cout << "addi $sp, $sp, -4" << std::endl;
                if (StkPtr.returnArgCount() < 4)
                {
                    std::cout << "sb $a" << StkPtr.returnArgCount() << ", 0($sp)" << std::endl;
                }
                StkPtr.setIncrement(StkPtr.getIncrement() + 4);
                StkPtr.setScopeIncrement(StkPtr.returnScopeIncrement() + 4);
                address = std::to_string(StkPtr.getIncrement());
                if (SymTab.lookup(varID) == "Unknown reference from ID")
                {
                    SymTab.insert(type, "var", varID, address);
                }
                else
                {
                    SymTab.edit(type, "var", varID, address);
                }
                if (Expr != nullptr)
                {
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "andi $t0, $t0, 0x00ff" << std::endl;
                    std::cout << "sb $t0, -" << address << "($fp)" << std::endl;
                }
                if (SymTab.returnScopeCurrent() == 0)
                {
                    std::cout << ".global " << returnFuncId() << std::endl;
                }
            }
            break;
        }
    }
    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        return bindings.at(varID);
    }
};

class DecList;

typedef const DecList *DecListPtr;

class DecList
    : public Identifier
{
private:
    Identifier *variable;
    DecListPtr decList = nullptr;

public:
    DecList(Identifier *_variable, DecListPtr _decList = nullptr)
        : variable(_variable), decList(_decList)
    {
    }

    virtual ~DecList()
    {
        delete variable;
        delete decList;
    }
    Identifier *returnVar() const
    {
        return variable;
    }

    DecListPtr returnDecList() const
    {
        return decList;
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        variable->pretty_print(dst);
        if (decList != nullptr)
        {
            dst << ", ";
            decList->pretty_print(dst);
        }
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnVar()->Translate2MIPS(destReg);
        StkPtr.setArgCount(StkPtr.returnArgCount() + 1);
        if (decList != nullptr)
        {
            returnDecList()->Translate2MIPS(destReg);
        }
        StkPtr.setArgCount(0);
    }
};

// class Number_INT
//     : public Expr
// {
// private:
//     double value;

// public:
//     Number_INT(double _value)
//     {
//         value = _value;
//     }
//     double getValue() const
//     {
//         return value;
//     }
//     virtual void pretty_print(std::ostream &dst) const override
//     {
//         dst << value;
//     }
//     virtual double evaluate(
//         const std::map<std::string, double> &bindings) const override
//     {
//         return value;
//     }
//     virtual const std::string returnData() const override
//     {
//         return "INT";
//     }
//     virtual void Translate2MIPS(std::string destReg) const override
//     {
//         std::cout << "addi " << destReg << ", $0, " << value << std::endl;
//     }
// };

// class Number_DOUBLE
//     : public Expr
// {
// private:
//     double value;

// public:
//     Number_DOUBLE(double _value)
//     {
//         value = _value;
//     }
//     double getValue() const
//     {
//         return value;
//     }
//     virtual void pretty_print(std::ostream &dst) const override
//     {
//         dst << value;
//     }
//     virtual double evaluate(
//         const std::map<std::string, double> &bindings) const override
//     {
//         return value;
//     }
//     virtual const std::string returnData() const override
//     {
//         return "FLOAT";
//     }
//     virtual void Translate2MIPS(std::string destReg) const override
//     {
//         std::cout << "li.s " << destReg << ", " << value << std::endl;
//     }
// };
#endif
