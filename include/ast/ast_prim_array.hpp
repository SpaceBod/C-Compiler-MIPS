#ifndef ast_prim_array_hpp
#define ast_prim_array_hpp

#include <string>
#include <iostream>

#include "ast_symtab.hpp"
#include "ast_primitives.hpp"
#include "ast_expressions.hpp"

class Array
    : public Identifier
{
private:
    mutable std::string type;
    mutable std::string address;
    double length;
    ExprPtr index;
    DecType VarType;
    ExprPtr Expr = nullptr;
    std::string varID;
    std::string assignOp;

public:
    Array() {}

    Array(const std::string *_varID, ExprPtr _index)
    {
        VarType = CALL;
        varID = *_varID;
        index = _index;
    }

    Array(const std::string *_varID, ExprPtr _index, std::string *_assignop, ExprPtr _Expr)
    {
        VarType = ASSIGN;
        varID = *_varID;
        assignOp = *_assignop;
        Expr = _Expr;
        index = _index;
    }

    Array(VarTypeDef _type, const std::string *_varID, double _length)
    {
        VarType = DECLARATION;
        varID = *_varID;
        length = _length;
        switch (_type)
        {
        case INT:
            type = "INT";
            break;
        case FLOAT:
            type = "FLOAT";
            break;
        case DOUBLE:
            type = "DOUBLE";
            break;
        default:
            type = "Array type unknown!";
        }
    }

    Array(VarTypeDef _type, const std::string *_varID)
    {
        VarType = ARGUMENT;
        varID = *_varID;
        switch (_type)
        {
        case INT:
            type = "INT";
            break;
        case FLOAT:
            type = "FLOAT";
            break;
        case DOUBLE:
            type = "DOUBLE";
            break;
        default:
            type = "Array type unknown!";
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

    ExprPtr returnIndex() const
    {
        return index;
    }

    double returnLength() const
    {
        return length;
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
            returnIndex()->Translate2MIPS("$t0");
            if (type == "INT")
            {
                std::cout << "sll $t0, $t0, 2" << std::endl;
                std::cout << "addiu $t1, $fp, -" << address << std::endl;
                std::cout << "subu $t1, $t1, $t0" << std::endl;
                std::cout << "lw " << destReg << ", 0($t1)" << std::endl;
            }
            else if (type == "FLOAT")
            {
                std::cout << "sll $t0, $t0, 2" << std::endl;
                std::cout << "addiu $t1, $fp, -" << address << std::endl;
                std::cout << "subu $t1, $t1, $t0" << std::endl;
                std::cout << "lwc1 " << destReg << ", 0($t1)" << std::endl;
            }
            else if (type == "DOUBLE")
            {
                std::cout << "sll $t0, $t0, 3" << std::endl;
                std::cout << "addiu $t1, $fp, -" << address << std::endl;
                std::cout << "subu $t1, $t1, $t0" << std::endl;
                std::cout << "lwc1 " << destReg << ", 0($t1)" << std::endl;
                std::cout << "lwc1 " << destReg[0] << destReg[1] << (int)destReg[2] - 48 + 1 << ", -4($t1)" << std::endl;
            }
            break;

        case ASSIGN:
            address = SymTab.lookup(varID);
            type = SymTab.returnType(varID);
            if (assignOp == "=")
            {
                if (type == "INT")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 2" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t1, 0($sp)" << std::endl;
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "lw $t1, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "sw $t0, 0($t1)" << std::endl;
                }
                if (type == "FLOAT")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 2" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t1, 0($sp)" << std::endl;
                    returnExpr()->Translate2MIPS("$f0");
                    std::cout << "lw $t1, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "swc1 $f0, 0($t1)" << std::endl;
                }
                if (type == "DOUBLE")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 3" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t1, 0($sp)" << std::endl;
                    returnExpr()->Translate2MIPS("$f0");
                    std::cout << "lw $t1, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "swc1 $f0, 0($t1)" << std::endl;
                    std::cout << "swc1 $f1, -4($t1)" << std::endl;
                }
            }
            else if (assignOp == "+=")
            {
                if (type == "INT")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 2" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t1, 0($sp)" << std::endl;
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "lw $t1, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "lw $t2, 0($t1)" << std::endl;
                    std::cout << "add $t2, t2, t0" << std::endl;
                    std::cout << "sw $t2, 0($t1)" << std::endl;
                }
                if (type == "FLOAT")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 2" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t1, 0($sp)" << std::endl;
                    returnExpr()->Translate2MIPS("$f0");
                    std::cout << "lw $t1, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "lwc1 $f2, 0($t1)" << std::endl;
                    std::cout << "add.s $f2, f2, f0" << std::endl;
                    std::cout << "swc1 $f2, 0($t1)" << std::endl;
                }
                if (type == "DOUBLE")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 3" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t1, 0($sp)" << std::endl;
                    returnExpr()->Translate2MIPS("$f0");
                    std::cout << "lw $t1, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "lwc1 $f2, 0($t1)" << std::endl;
                    std::cout << "lwc1 $f3, -4($t1)" << std::endl;
                    std::cout << "add.d $f2, $f2, $f0" << std::endl;
                    std::cout << "swc1 $f2, 0($t1)" << std::endl;
                    std::cout << "swc1 $f3, -4($t1)" << std::endl;
                }
            }
            else if (assignOp == "-=")
            {
                if (type == "INT")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 2" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t1, 0($sp)" << std::endl;
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "lw $t1, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "lw $t2, 0($t1)" << std::endl;
                    std::cout << "sub $t2, t2, t0" << std::endl;
                    std::cout << "sw $t2, 0($t1)" << std::endl;
                }
                if (type == "FLOAT")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 2" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t1, 0($sp)" << std::endl;
                    returnExpr()->Translate2MIPS("$f0");
                    std::cout << "lw $t1, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "lwc1 $f2, 0($t1)" << std::endl;
                    std::cout << "sub.s $f2, f2, f0" << std::endl;
                    std::cout << "swc1 $f2, 0($t1)" << std::endl;
                }
                if (type == "DOUBLE")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 3" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t1, 0($sp)" << std::endl;
                    returnExpr()->Translate2MIPS("$f0");
                    std::cout << "lw $t1, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "lwc1 $f2, 0($t1)" << std::endl;
                    std::cout << "lwc1 $f3, -4($t1)" << std::endl;
                    std::cout << "sub.d $f2, $f2, $f0" << std::endl;
                    std::cout << "swc1 $f2, 0($t1)" << std::endl;
                    std::cout << "swc1 $f3, -4($t1)" << std::endl;
                }
            }
            else if (assignOp == "/=")
            {
                if (type == "INT")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 2" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t1, 0($sp)" << std::endl;
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "lw $t1, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "lw $t2, 0($t1)" << std::endl;
                    std::cout << "div t2, t0" << std::endl;
                    std::cout << "mflo $t2" << std::endl;
                    std::cout << "sw $t2, 0($t1)" << std::endl;
                }
                if (type == "FLOAT")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 2" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t1, 0($sp)" << std::endl;
                    returnExpr()->Translate2MIPS("$f0");
                    std::cout << "lw $t1, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "lwc1 $f2, 0($t1)" << std::endl;
                    std::cout << "div.s $f2, f2, f0" << std::endl;
                    std::cout << "swc1 $f2, 0($t1)" << std::endl;
                }
                if (type == "DOUBLE")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 3" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t1, 0($sp)" << std::endl;
                    returnExpr()->Translate2MIPS("$f0");
                    std::cout << "lw $t1, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "lwc1 $f2, 0($t1)" << std::endl;
                    std::cout << "lwc1 $f3, -4($t1)" << std::endl;
                    std::cout << "div.d $f2, $f2, $f0" << std::endl;
                    std::cout << "swc1 $f2, 0($t1)" << std::endl;
                    std::cout << "swc1 $f3, -4($t1)" << std::endl;
                }
            }
            else if (assignOp == "*=")
            {
                if (type == "INT")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 2" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t1, 0($sp)" << std::endl;
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "lw $t1, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "lw $t2, 0($t1)" << std::endl;
                    std::cout << "mul $t2, t2, t0" << std::endl;
                    std::cout << "sw $t2, 0($t1)" << std::endl;
                }
                if (type == "FLOAT")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 2" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t1, 0($sp)" << std::endl;
                    returnExpr()->Translate2MIPS("$f0");
                    std::cout << "lw $t1, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "lwc1 $f2, 0($t1)" << std::endl;
                    std::cout << "mul.s $f2, f2, f0" << std::endl;
                    std::cout << "swc1 $f2, 0($t1)" << std::endl;
                }
                if (type == "DOUBLE")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 3" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t1, 0($sp)" << std::endl;
                    returnExpr()->Translate2MIPS("$f0");
                    std::cout << "lw $t1, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "lwc1 $f2, 0($t1)" << std::endl;
                    std::cout << "lwc1 $f3, -4($t1)" << std::endl;
                    std::cout << "mul.d $f2, $f2, $f0" << std::endl;
                    std::cout << "swc1 $f2, 0($t1)" << std::endl;
                    std::cout << "swc1 $f3, -4($t1)" << std::endl;
                }
            }
            else if (assignOp == "%=")
            {
                if (type == "INT")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 2" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t1, 0($sp)" << std::endl;
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "lw $t1, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "lw $t2, 0($t1)" << std::endl;
                    std::cout << "div t2, t0" << std::endl;
                    std::cout << "mfhi $t2" << std::endl;
                    std::cout << "sw $t2, 0($t1)" << std::endl;
                }
            }
            else if (assignOp == "<<=")
            {
                if (type == "INT")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 2" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t1, 0($sp)" << std::endl;
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "lw $t1, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "lw $t2, 0($t1)" << std::endl;
                    std::cout << "sllv $t2, t2, t0" << std::endl;
                    std::cout << "sw $t2, 0($t1)" << std::endl;
                }
            }
            else if (assignOp == ">>=")
            {
                if (type == "INT")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 2" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t1, 0($sp)" << std::endl;
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "lw $t1, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "lw $t2, 0($t1)" << std::endl;
                    std::cout << "srlv $t2, t2, t0" << std::endl;
                    std::cout << "sw $t2, 0($t1)" << std::endl;
                }
            }
            else if (assignOp == "^=")
            {
                if (type == "INT")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 2" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t1, 0($sp)" << std::endl;
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "lw $t1, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "lw $t2, 0($t1)" << std::endl;
                    std::cout << "xor $t2, t2, t0" << std::endl;
                    std::cout << "sw $t2, 0($t1)" << std::endl;
                }
            }
            else if (assignOp == "&=")
            {
                if (type == "INT")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 2" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t1, 0($sp)" << std::endl;
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "lw $t1, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "lw $t2, 0($t1)" << std::endl;
                    std::cout << "and $t2, t2, t0" << std::endl;
                    std::cout << "sw $t2, 0($t1)" << std::endl;
                }
            }
            else if (assignOp == "|=")
            {
                if (type == "INT")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 2" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t1, 0($sp)" << std::endl;
                    returnExpr()->Translate2MIPS("$t0");
                    std::cout << "lw $t1, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "lw $t2, 0($t1)" << std::endl;
                    std::cout << "or $t2, t2, t0" << std::endl;
                    std::cout << "sw $t2, 0($t1)" << std::endl;
                }
            }
            else if (assignOp == "++")
            {
                if (type == "INT")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 2" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "lw $t2, 0($t1)" << std::endl;
                    std::cout << "addi $t2, t2, 1" << std::endl;
                    std::cout << "sw $t2, 0($t1)" << std::endl;
                }
                else if (type == "FLOAT")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 2" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "lwc1 $f0, 0($t1)" << std::endl;
                    std::cout << "addi.s $f0, $f0, 1" << std::endl;
                    std::cout << "swc1 $f0, 0($t1)" << std::endl;
                }
                else if (type == "DOUBLE")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 3" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "lwc1 $f0, 0($t1)" << std::endl;
                    std::cout << "lwc1 $f1, -4($t1)" << std::endl;
                    std::cout << "addi.d $f0, $f0, 1" << std::endl;
                    std::cout << "swc1 $f0, 0($t1)" << std::endl;
                    std::cout << "swc1 $f1, -4($t1)" << std::endl;
                }
            }
            else if (assignOp == "--")
            {
                if (type == "INT")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 2" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "lw $t2, 0($t1)" << std::endl;
                    std::cout << "addi $t2, t2, -1" << std::endl;
                    std::cout << "sw $t2, 0($t1)" << std::endl;
                }
                else if (type == "FLOAT")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 2" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "lwc1 $f0, 0($t1)" << std::endl;
                    std::cout << "addi.s $f0, $f0, -1" << std::endl;
                    std::cout << "swc1 $f0, 0($t1)" << std::endl;
                }
                else if (type == "DOUBLE")
                {
                    returnIndex()->Translate2MIPS("$t0");
                    std::cout << "sll $t0, $t0, 3" << std::endl;
                    std::cout << "addiu $t1, $fp, -" << address << std::endl;
                    std::cout << "subu $t1, $t1, $t0" << std::endl;
                    std::cout << "lwc1 $f0, 0($t1)" << std::endl;
                    std::cout << "lwc1 $f1, -4($t1)" << std::endl;
                    std::cout << "addi.d $f0, $f0, -1" << std::endl;
                    std::cout << "swc1 $f0, 0($t1)" << std::endl;
                    std::cout << "swc1 $f1, -4($t1)" << std::endl;
                }
            }
            break;

        case DECLARATION:
            if (returnType() == "INT" || returnType() == "FLOAT")
            {
                std::cout << "addi $sp, $sp, -" << 4 * returnLength() << std::endl;
                address = std::to_string(StkPtr.getIncrement() + 4);
                StkPtr.setIncrement(StkPtr.getIncrement() + 4 * returnLength());
                StkPtr.setScopeIncrement(StkPtr.returnScopeIncrement() + 4 * returnLength());
                if (SymTab.lookup(varID) == "Unknown reference from ID")
                {
                    SymTab.insert(type, "array", varID, address);
                }
                else
                {
                    SymTab.edit(type, "array", varID, address);
                }
                if (SymTab.returnScopeCurrent() == 0)
                {
                    std::cout << ".global " << returnFuncId() << std::endl;
                }
            }
            else if (returnType() == "DOUBLE")
            {
                std::cout << "addi $sp, $sp, -" << 8 * returnLength() << std::endl;
                address = std::to_string(StkPtr.getIncrement() + 4);
                StkPtr.setIncrement(StkPtr.getIncrement() + 8 * returnLength());
                StkPtr.setScopeIncrement(StkPtr.returnScopeIncrement() + 8 * returnLength());
                if (SymTab.lookup(varID) == "ERROR: undefined reference")
                {
                    SymTab.insert(type, "array", varID, address);
                }
                else
                {
                    SymTab.edit(type, "array", varID, address);
                }
                if (SymTab.returnScopeCurrent() == 0)
                {
                    std::cout << ".global " << returnFuncId() << std::endl;
                }
            }
            break;
        default:
            break;
        }
    }
};
#endif