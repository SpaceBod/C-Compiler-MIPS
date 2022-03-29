#ifndef ast_prim_pointer_hpp
#define ast_prim_pointer_hpp

#include <string>
#include <iostream>

#include "ast_symtab.hpp"
#include "ast_primitives.hpp"
#include "ast_expressions.hpp"

class Pointer
    : public Identifier
{
private:
    mutable std::string type;
    mutable std::string address;
    bool deref;
    bool addressTrue;
    std::string varID;
    DecType VarType;
    ExprPtr Expr;
    std::string assignOp;

public:
    Pointer() {}

    Pointer(const std::string *_varID, bool _deref = false, bool _addressTrue = false)
    {
        VarType = CALL;
        varID = *_varID;
        deref = _deref;
        addressTrue = _addressTrue;
    }

    Pointer(const std::string *_varID, std::string *_assignop, ExprPtr _Expr, bool _deref = false)
    {
        VarType = ASSIGN;
        varID = *_varID;
        assignOp = *_assignop;
        Expr = _Expr;
        deref = _deref;
    }

    Pointer(VarTypeDef _type, const std::string *_varID, DecType _kind, ExprPtr _Expr = nullptr)
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
                type = "something went wrong";
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
                type = "something went wrong";
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

    virtual const std::string returnData() const override
    {
        type = SymTab.returnType(varID);
        return type;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        switch (VarType)
        {
        case CALL:
            address = SymTab.lookup(varID);
            type = SymTab.returnType(varID);
            if (deref)
            {
                std::cout << "lw $t0, -" << address << "($fp)" << std::endl;
                if (type == "INT")
                {
                    std::cout << "lw " << destReg << ", 0($t0)" << std::endl;
                }
                else if (type == "FLOAT")
                {
                    std::cout << "lwc1 " << destReg << ", 0($t0)" << std::endl;
                }
                else if (type == "DOUBLE")
                {
                    std::cout << "lwc1 " << destReg << ", 0($t0)" << std::endl;
                    std::cout << "lwc1 " << destReg[0] << destReg[1] << (int)destReg[2] - 48 + 1 << ", -4($t0)" << std::endl;
                }
                else if (type == "CHAR")
                {
                    std::cout << "lb " << destReg << ", 0($t0)" << std::endl;
                }
            }
            else if (addressTrue)
            {
                std::cout << "addi " << destReg << ", $fp, -" << address << std::endl;
            }
            else
            {
                std::cout << "lw " << destReg << ", -" << address << "($fp)" << std::endl;
            }
            break;

        case ASSIGN:
            address = SymTab.lookup(varID);
            type = SymTab.returnType(varID);
            if (deref)
            {
                std::cout << "lw $t2, -" << address << "($fp)" << std::endl;
                if (assignOp == "=")
                {
                    if (type == "INT")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "sw $t0, 0($t2)" << std::endl;
                    }
                    else if (type == "FLOAT")
                    {
                        returnExpr()->Translate2MIPS("$f0");
                        std::cout << "swc1 $f0, 0($t2)" << std::endl;
                    }
                    else if (type == "DOUBLE")
                    {
                        returnExpr()->Translate2MIPS("$f0");
                        std::cout << "swc1 $f0, 0($t2)" << std::endl;
                        std::cout << "swc1 $f1, -4($t2)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "sb $t0, 0($t2)" << std::endl;
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
                        std::cout << "lw $t1, 0($t2)" << std::endl;
                        std::cout << "add $t1, $t1, $t0" << std::endl;
                        std::cout << "sw $t1, 0($t2)" << std::endl;
                    }
                    else if (type == "FLOAT")
                    {
                        returnExpr()->Translate2MIPS("$f0");
                        std::cout << "lwc1 $f2, 0($t2)" << std::endl;
                        std::cout << "add.s $f2, $f2, $f0" << std::endl;
                        std::cout << "swc1 $f2, 0($t2)" << std::endl;
                    }
                    else if (type == "DOUBLE")
                    {
                        returnExpr()->Translate2MIPS("$f0");
                        std::cout << "lwc1 $f2, 0($t2)" << std::endl;
                        std::cout << "lwc1 $f3, -4($t2)" << std::endl;
                        std::cout << "add.d $f2, $f2, $f0" << std::endl;
                        std::cout << "swc1 $f2, 0($t2)" << std::endl;
                        std::cout << "swc1 #f3, -4($t2)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lbu $t1, 0($t2)" << std::endl;
                        std::cout << "add $t1, $t1, $t0" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, 0($t2)" << std::endl;
                    }
                }
                else if (assignOp == "-=")
                {
                    if (type == "INT")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lw $t1, 0($t2)" << std::endl;
                        std::cout << "sub $t1, $t1, $t0" << std::endl;
                        std::cout << "sw $t1, 0($t2)" << std::endl;
                    }
                    else if (type == "FLOAT")
                    {
                        returnExpr()->Translate2MIPS("$f0");
                        std::cout << "lwc1 $f2, 0($t2)" << std::endl;
                        std::cout << "sub.s $f2, $f2, $f0" << std::endl;
                        std::cout << "swc1 $f2, 0($t2)" << std::endl;
                    }
                    else if (type == "DOUBLE")
                    {
                        returnExpr()->Translate2MIPS("$f0");
                        std::cout << "lwc1 $f2, 0($t2)" << std::endl;
                        std::cout << "lwc1 $f3, -4($t2)" << std::endl;
                        std::cout << "sub.d $f2, $f2, $f0" << std::endl;
                        std::cout << "swc1 $f2, 0($t2)" << std::endl;
                        std::cout << "swc1 #f3, -4($t2)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lbu $t1, 0($t2)" << std::endl;
                        std::cout << "sub $t1, $t1, $t0" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, 0($t2)" << std::endl;
                    }
                }
                else if (assignOp == "/=")
                {
                    if (type == "INT")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lw $t1, 0($t2)" << std::endl;
                        std::cout << "div $t1, $t0" << std::endl;
                        std::cout << "mflo $t1" << std::endl;
                        std::cout << "sw $t1, 0($t2)" << std::endl;
                    }
                    else if (type == "FLOAT")
                    {
                        returnExpr()->Translate2MIPS("$f0");
                        std::cout << "lwc1 $f2, 0($t2)" << std::endl;
                        std::cout << "div.s $f2, $f2, $f0" << std::endl;
                        std::cout << "swc1 $f2, -" << address << "($fp)" << std::endl;
                    }
                    else if (type == "DOUBLE")
                    {
                        returnExpr()->Translate2MIPS("$f0");
                        std::cout << "lwc1 $f2, 0($t2)" << std::endl;
                        std::cout << "lwc1 $f3, -4($t2)" << std::endl;
                        std::cout << "div.d $f2, $f2, $f0" << std::endl;
                        std::cout << "swc1 $f2, 0($t2)" << std::endl;
                        std::cout << "swc1 #f3, -4($t2)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lbu $t1, 0($t2)" << std::endl;
                        std::cout << "div $t1, $t0" << std::endl;
                        std::cout << "mflo $t1" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, 0($t2)" << std::endl;
                    }
                }
                else if (assignOp == "*=")
                {
                    if (type == "INT")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lw $t1, 0($t2)" << std::endl;
                        std::cout << "mul $t1, $t1, $t0" << std::endl;
                        std::cout << "sw $t1, 0($t2)" << std::endl;
                    }
                    else if (type == "FLOAT")
                    {
                        returnExpr()->Translate2MIPS("$f0");
                        std::cout << "lwc1 $f2, 0($t2)" << std::endl;
                        std::cout << "mul.s $f2, $f2, $f0" << std::endl;
                        std::cout << "swc1 $f2, 0($t2)" << std::endl;
                    }
                    else if (type == "DOUBLE")
                    {
                        returnExpr()->Translate2MIPS("$f0");
                        std::cout << "lwc1 $f2, 0($t2)" << std::endl;
                        std::cout << "lwc1 $f3, -4($t2)" << std::endl;
                        std::cout << "mul.d $f2, $f2, $f0" << std::endl;
                        std::cout << "swc1 $f2, 0($t2)" << std::endl;
                        std::cout << "swc1 #f3, -4($t2)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lbu $t1, 0($t2)" << std::endl;
                        std::cout << "mul $t1, $t1, $t0" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, 0($t2)" << std::endl;
                    }
                }
                else if (assignOp == "%=")
                {
                    if (type == "INT")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lw $t1, 0($t2)" << std::endl;
                        std::cout << "div $t1, $t0" << std::endl;
                        std::cout << "mfhi $t1" << std::endl;
                        std::cout << "sw $t1, 0($t2)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lbu $t1, 0($t2)" << std::endl;
                        std::cout << "div $t1, $t0" << std::endl;
                        std::cout << "mfhi $t1" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, 0($t2)" << std::endl;
                    }
                }
                else if (assignOp == "<<=")
                {
                    if (type == "INT")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lw $t1, 0($t2)" << std::endl;
                        std::cout << "sllv $t1, $t1, $t0" << std::endl;
                        std::cout << "sw $t1, 0($t2)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lbu $t1, 0($t2)" << std::endl;
                        std::cout << "sllv $t1, $t1, $t0" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, 0($t2)" << std::endl;
                    }
                }
                else if (assignOp == ">>=")
                {
                    if (type == "INT")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lw $t1, 0($t2)" << std::endl;
                        std::cout << "srlv $t1, $t1, $t0" << std::endl;
                        std::cout << "sw $t1, 0($t2)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lbu $t1, 0($t2)" << std::endl;
                        std::cout << "srlv $t1, $t1, $t0" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, 0($t2)" << std::endl;
                    }
                }
                else if (assignOp == "^=")
                {
                    if (type == "INT")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lw $t1, 0($t2)" << std::endl;
                        std::cout << "xor $t1, $t1, $t0" << std::endl;
                        std::cout << "sw $t1, 0($t2)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lbu $t1, 0($t2)" << std::endl;
                        std::cout << "xor $t1, $t1, $t0" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, 0($t2)" << std::endl;
                    }
                }
                else if (assignOp == "&=")
                {
                    if (type == "INT")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lw $t1, 0($t2)" << std::endl;
                        std::cout << "and $t1, $t1, $t0" << std::endl;
                        std::cout << "sw $t1, 0($t2)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lbu $t1, 0($t2)" << std::endl;
                        std::cout << "and $t1, $t1, $t0" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, 0($t2)" << std::endl;
                    }
                }
                else if (assignOp == "|=")
                {
                    if (type == "INT")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lw $t1, 0($t2)" << std::endl;
                        std::cout << "or $t1, $t1, $t0" << std::endl;
                        std::cout << "sw $t1, 0($t2)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        returnExpr()->Translate2MIPS("$t0");
                        std::cout << "lbu $t1, 0($t2)" << std::endl;
                        std::cout << "or $t1, $t1, $t0" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, 0($t2)" << std::endl;
                    }
                }
                else if (assignOp == "++")
                {
                    if (type == "INT")
                    {
                        std::cout << "lw $t0, 0($t2)" << std::endl;
                        std::cout << "addi $t0, $t0, 1" << std::endl;
                        std::cout << "sw $t0, 0($t2)" << std::endl;
                    }
                    else if (type == "FLOAT")
                    {
                        std::cout << "lwc1 $f0, 0($t2)" << std::endl;
                        std::cout << "addi.s $f0, $f0, 1" << std::endl;
                        std::cout << "swc1 $f0, 0($t2)" << std::endl;
                    }
                    else if (type == "DOUBLE")
                    {
                        std::cout << "lwc1 $f0, 0($t2)" << std::endl;
                        std::cout << "lwc1 $f1, -4($t2)" << std::endl;
                        std::cout << "addi.d $f0, $f0, 1" << std::endl;
                        std::cout << "swc1 $f0, 0($t2)" << std::endl;
                        std::cout << "swc1 $f1, -4($t2)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        std::cout << "lbu $t0, 0($t2)" << std::endl;
                        std::cout << "addi $t0, $t0, 1" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, 0($t2)" << std::endl;
                    }
                }
                else if (assignOp == "--")
                {
                    if (type == "INT")
                    {
                        std::cout << "lw $t0, 0($t2)" << std::endl;
                        std::cout << "addi $t0, $t0, -1" << std::endl;
                        std::cout << "sw $t0, 0($t2)" << std::endl;
                    }
                    else if (type == "FLOAT")
                    {
                        std::cout << "lwc1 $f0, 0($t2)" << std::endl;
                        std::cout << "addi.s $f0, $f0, -1" << std::endl;
                        std::cout << "swc1 $f0, 0($t2)" << std::endl;
                    }
                    else if (type == "DOUBLE")
                    {
                        std::cout << "lwc1 $f0, 0($t2)" << std::endl;
                        std::cout << "lwc1 $f1, -4($t2)" << std::endl;
                        std::cout << "addi.d $f0, $f0, -1" << std::endl;
                        std::cout << "swc1 $f0, 0($t2)" << std::endl;
                        std::cout << "swc1 $f1, -4($t2)" << std::endl;
                    }
                    else if (type == "CHAR")
                    {
                        std::cout << "lbu $t0, 0($t2)" << std::endl;
                        std::cout << "addi $t0, $t0, -1" << std::endl;
                        std::cout << "andi $t1, $t1, 0x00ff" << std::endl;
                        std::cout << "sb $t1, 0($t2)" << std::endl;
                    }
                }
            }
            else
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
                    std::cout << "add $t1, $t1, $t0" << std::endl;
                    std::cout << "sw $t1, -" << address << "($fp)" << std::endl;
                }
                else if (assignOp == "-=")
                {
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "lw $t1, -" << address << "($fp)" << std::endl;
                    std::cout << "sub $t1, $t1, $t0" << std::endl;
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
                    std::cout << "addi $t0, $t0, 1" << std::endl;
                    std::cout << "sw $t0, -" << address << "($fp)" << std::endl;
                }
                else if (assignOp == "--")
                {
                    std::cout << "lw $t0, -" << address << "($fp)" << std::endl;
                    std::cout << "addi $t0, $t0, -1" << std::endl;
                    std::cout << "sw $t0, -" << address << "($fp)" << std::endl;
                }
            }
            break;
        case DECLARATION:
            std::cout << "addi $sp, $sp, -4" << std::endl;
            StkPtr.setIncrement(StkPtr.getIncrement() + 4);
            StkPtr.setScopeIncrement(StkPtr.returnScopeIncrement() + 4);
            address = std::to_string(StkPtr.getIncrement());
            if (SymTab.lookup(varID) == "Unknown reference from ID")
            {
                SymTab.insert(type, "ptr", varID, address);
            }
            else
            {
                SymTab.edit(type, "ptr", varID, address);
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
            break;
        case ARGUMENT:
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
                SymTab.insert(type, "ptr", varID, address);
            }
            else
            {
                SymTab.insert(type, "ptr", varID, address);
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
            break;
        }
    }
};
#endif