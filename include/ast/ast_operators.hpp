#ifndef ast_operators_hpp
#define ast_operators_hpp

#include <string>
#include <iostream>

#include "ast_expressions.hpp"

class Operator
    : public Expr
{
private:
    ExprPtr left;
    ExprPtr right;

protected:
    Operator(ExprPtr _left, ExprPtr _right)
    {
        left = _left;
        right = _right;
    }

public:
    virtual ~Operator()
    {
        delete left;
        delete right;
    }

    virtual const char *returnOp() const = 0;

    ExprPtr returnLeft() const
    {
        return left;
    }

    ExprPtr returnRight() const
    {
        return right;
    }

    virtual const std::string returnData() const override
    {
        std::string leftDataType = returnLeft()->returnData();
        std::string rightDataType = returnRight()->returnData();
        if (leftDataType == "INT")
        {
            if (rightDataType == "INT")
            {
                return "INT";
            }
            else if (rightDataType == "FLOAT")
            {
                return "FLOAT";
            }
            else if (rightDataType == "DOUBLE")
            {
                return "DOUBLE";
            }
            else
            {
                return "Datatype error";
            }
        }
        else if (leftDataType == "FLOAT")
        {
            if (rightDataType == "INT" || rightDataType == "FLOAT")
            {
                return "FLOAT";
            }
            else if (rightDataType == "DOUBLE")
            {
                return "DOUBLE";
            }
        }
        else if (leftDataType == "DOUBLE")
        {
            return "DOUBLE";
        }
        else
        {
            return "Error";
        }
        return "Null";
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << "( ";
        left->pretty_print(dst);
        dst << " ";
        dst << returnOp();
        dst << " ";
        right->pretty_print(dst);
        dst << " )";
    }
};

// Arithmatical Operators
class AddOp
    : public Operator
{
protected:
    virtual const char *returnOp() const override
    {
        return "+";
    }

public:
    AddOp(ExprPtr _left, ExprPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = returnLeft()->evaluate(bindings);
        double vr = returnRight()->evaluate(bindings);
        return vl + vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        std::string leftVar = returnLeft()->returnData();
        std::string rightVar = returnRight()->returnData();
        std::string leftFormat = returnLeft()->returnDataKind();
        if (leftFormat == "ptr")
        {
            returnLeft()->Translate2MIPS("$t0");
            std::cout << "addi $sp, $sp, -4" << std::endl;
            std::cout << "sw $t0, 0($sp)" << std::endl;
            returnRight()->Translate2MIPS("$t1");
            std::cout << "lw $t0, 0($sp)" << std::endl;
            std::cout << "addi $sp, $sp, 4" << std::endl;
            if (leftVar != "DOUBLE")
            {
                for (int i = 0; i < 4; i++)
                {
                    std::cout << "add $t0, $t0, $t1" << std::endl;
                }
            }
            else
            {
                for (int i = 0; i < 8; i++)
                {
                    std::cout << "add $t0, $t0, $t1" << std::endl;
                }
            }
            std::cout << "addi " << destReg << ", $t0, 0" << std::endl;
        }
        else
        {
            if (leftVar == "INT")
            {
                if (rightVar == "INT")
                {
                    returnLeft()->Translate2MIPS("$t0");
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t0, 0($sp)" << std::endl;
                    returnRight()->Translate2MIPS("$t1");
                    std::cout << "lw $t0, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    if (destReg[1] == 'f')
                    {
                        std::cout << "wrong dstReg" << std::endl;
                    }
                    std::cout << "add " << destReg << ", $t0, $t1" << std::endl;
                }
                else if (rightVar == "FLOAT")
                {
                    returnLeft()->Translate2MIPS("$t0");
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t0, 0($sp)" << std::endl;
                    returnRight()->Translate2MIPS("$f2");
                    std::cout << "lwc1 $f0, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    if (destReg[1] != 'f')
                    {
                        std::cout << "Wrong dstReg" << std::endl;
                    }
                    std::cout << "add.s " << destReg << ", $f0, $f2" << std::endl;
                }
                else if (rightVar == "DOUBLE")
                {
                    returnLeft()->Translate2MIPS("$t0");
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t0, 0($sp)" << std::endl;
                    returnRight()->Translate2MIPS("$f2");
                    std::cout << "lwc1 $f0, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "cvt.d.s $f0, $f0" << std::endl;
                    if (destReg[1] != 'f')
                    {
                        std::cout << "Wrong dstReg" << std::endl;
                    }
                    std::cout << "add.d " << destReg << ", $f0, $f2" << std::endl;
                }
            }
            else if (leftVar == "FLOAT")
            {
                if (rightVar == "INT")
                {
                    returnRight()->Translate2MIPS("$t0");
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t0, 0($sp)" << std::endl;
                    returnLeft()->Translate2MIPS("$f0");
                    std::cout << "lwc1 $f2, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    if (destReg[1] != 'f')
                    {
                        std::cout << "Wrong dstReg" << std::endl;
                    }
                    std::cout << "add.s " << destReg << ", $f0, $f2" << std::endl;
                }
                else if (rightVar == "FLOAT")
                {
                    returnLeft()->Translate2MIPS("$f0");
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "swc1 $f0, 0($sp)" << std::endl;
                    returnRight()->Translate2MIPS("$f2");
                    std::cout << "lwc1 $f0, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    if (destReg[1] != 'f')
                    {
                        std::cout << "Wrong dstReg" << std::endl;
                    }
                    std::cout << "add.s " << destReg << ", $f0, $f2" << std::endl;
                }
                else if (rightVar == "DOUBLE")
                {
                    returnLeft()->Translate2MIPS("$f0");
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "swc1 $f0, 0($sp)" << std::endl;
                    returnRight()->Translate2MIPS("$f2");
                    std::cout << "lwc1 $f0, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "cvt.d.s $f0, $f0" << std::endl;
                    if (destReg[1] != 'f')
                    {
                        std::cout << "Wrong dstReg" << std::endl;
                    }
                    std::cout << "add.d " << destReg << " , $f0, $f2" << std::endl;
                }
            }
            else if (leftVar == "DOUBLE")
            {
                if (rightVar == "INT")
                {
                    returnRight()->Translate2MIPS("$t0");
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t0, 0($sp)" << std::endl;
                    returnLeft()->Translate2MIPS("$f0");
                    std::cout << "lwc1 $f2, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "cvt.d.s $f2, $f2" << std::endl;
                    if (destReg[1] != 'f')
                    {
                        std::cout << "Wrong dstReg" << std::endl;
                    }
                    std::cout << "add.d " << destReg << ", $f0, $f2" << std::endl;
                }
                else if (rightVar == "FLOAT")
                {
                    returnRight()->Translate2MIPS("$f2");
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "swc1 $f2, 0($sp)" << std::endl;
                    returnLeft()->Translate2MIPS("$f0");
                    std::cout << "lwc1, $f2, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "cvt.d.s $f2, $f2" << std::endl;
                    if (destReg[1] != 'f')
                    {
                        std::cout << "Wrong dstReg" << std::endl;
                    }
                    std::cout << "add.d " << destReg << ", $f0, $f2" << std::endl;
                }
                else if (rightVar == "DOUBLE")
                {
                    returnLeft()->Translate2MIPS("$f0");
                    std::cout << "addi $sp, $sp, -8" << std::endl;
                    std::cout << "swc1 $f1, 4($sp)" << std::endl;
                    std::cout << "swc1 $f0, 0($sp)" << std::endl;
                    returnRight()->Translate2MIPS("$f2");
                    std::cout << "lwc1 $f1, 4($sp)" << std::endl;
                    std::cout << "lwc1 $f0, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 8" << std::endl;
                    if (destReg[1] != 'f')
                    {
                        std::cout << "Wrong dstReg" << std::endl;
                    }
                    std::cout << "add.d " << destReg << ", $f0, $f2" << std::endl;
                }
            }
        }
    }
};

class SubOp
    : public Operator
{
protected:
    virtual const char *returnOp() const override
    {
        return "-";
    }

public:
    SubOp(ExprPtr _left, ExprPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = returnLeft()->evaluate(bindings);
        double vr = returnRight()->evaluate(bindings);
        return vl - vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        std::string leftVar = returnLeft()->returnData();
        std::string rightVar = returnRight()->returnData();
        std::string leftFormat = returnLeft()->returnDataKind();
        if (leftFormat == "ptr")
        {
            returnLeft()->Translate2MIPS("$t0");
            std::cout << "addi $sp, $sp, -4" << std::endl;
            std::cout << "sw $t0, 0($sp)" << std::endl;
            returnRight()->Translate2MIPS("$t1");
            std::cout << "lw $t0, 0($sp)" << std::endl;
            std::cout << "addi $sp, $sp, 4" << std::endl;
            if (leftVar != "DOUBLE")
            {
                for (int i = 0; i < 4; i++)
                {
                    std::cout << "sub $t0, $t0, $t1" << std::endl;
                }
            }
            else
            {
                for (int i = 0; i < 8; i++)
                {
                    std::cout << "sub $t0, $t0, $t1" << std::endl;
                }
            }
            std::cout << "addi " << destReg << ", $t0, 0" << std::endl;
        }
        else
        {
            if (leftVar == "INT")
            {
                if (rightVar == "INT")
                {
                    returnLeft()->Translate2MIPS("$t0");
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t0, 0($sp)" << std::endl;
                    returnRight()->Translate2MIPS("$t1");
                    std::cout << "lw $t0, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    if (destReg[1] == 'f')
                    {
                        std::cout << "wrong dstReg" << std::endl;
                    }
                    std::cout << "sub " << destReg << ", $t0, $t1" << std::endl;
                }
                else if (rightVar == "FLOAT")
                {
                    returnLeft()->Translate2MIPS("$t0");
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t0, 0($sp)" << std::endl;
                    returnRight()->Translate2MIPS("$f2");
                    std::cout << "lwc1 $f0, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    if (destReg[1] != 'f')
                    {
                        std::cout << "ERROR: Wrong destReg" << std::endl;
                    }
                    std::cout << "sub.s " << destReg << ", $f0, $f2" << std::endl;
                }
                else if (rightVar == "DOUBLE")
                {
                    returnLeft()->Translate2MIPS("$t0");
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t0, 0($sp)" << std::endl;
                    returnRight()->Translate2MIPS("$f2");
                    std::cout << "lwc1 $f0, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "cvt.d.s $f0, $f0" << std::endl;
                    if (destReg[1] != 'f')
                    {
                        std::cout << "ERROR: Wrong destReg" << std::endl;
                    }
                    std::cout << "sub.d " << destReg << ", $f0, $f2" << std::endl;
                }
            }
            else if (leftVar == "FLOAT")
            {
                if (rightVar == "INT")
                {
                    returnRight()->Translate2MIPS("$t0");
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t0, 0($sp)" << std::endl;
                    returnLeft()->Translate2MIPS("$f0");
                    std::cout << "lwc1 $f2, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    if (destReg[1] != 'f')
                    {
                        std::cout << "ERROR: Wrong destReg" << std::endl;
                    }
                    std::cout << "sub.s " << destReg << ", $f0, $f2" << std::endl;
                }
                else if (rightVar == "FLOAT")
                {

                    returnLeft()->Translate2MIPS("$f0");
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "swc1 $f0, 0($sp)" << std::endl;
                    returnRight()->Translate2MIPS("$f2");
                    std::cout << "lwc1 $f0, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    if (destReg[1] != 'f')
                    {
                        std::cout << "ERROR: Wrong destReg" << std::endl;
                    }
                    std::cout << "sub.s " << destReg << ", $f0, $f2" << std::endl;
                }
                else if (rightVar == "DOUBLE")
                {

                    returnLeft()->Translate2MIPS("$f0");
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "swc1 $f0, 0($sp)" << std::endl;
                    returnRight()->Translate2MIPS("$f2");
                    std::cout << "lwc1 $f0, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "cvt.d.s $f0, $f0" << std::endl;
                    if (destReg[1] != 'f')
                    {
                        std::cout << "ERROR: Wrong destReg" << std::endl;
                    }
                    std::cout << "sub.d " << destReg << " , $f0, $f2" << std::endl;
                }
            }
            else if (leftVar == "DOUBLE")
            {
                if (rightVar == "INT")
                {

                    returnRight()->Translate2MIPS("$t0");
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "sw $t0, 0($sp)" << std::endl;
                    returnLeft()->Translate2MIPS("$f0");
                    std::cout << "lwc1 $f2, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "cvt.d.s $f2, $f2" << std::endl;
                    if (destReg[1] != 'f')
                    {
                        std::cout << "ERROR: Wrong destReg" << std::endl;
                    }
                    std::cout << "sub.d " << destReg << ", $f0, $f2" << std::endl;
                }
                else if (rightVar == "FLOAT")
                {

                    returnRight()->Translate2MIPS("$f2");
                    std::cout << "addi $sp, $sp, -4" << std::endl;
                    std::cout << "swc1 $f2, 0($sp)" << std::endl;
                    returnLeft()->Translate2MIPS("$f0");
                    std::cout << "lwc1, $f2, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 4" << std::endl;
                    std::cout << "cvt.d.s $f2, $f2" << std::endl;
                    if (destReg[1] != 'f')
                    {
                        std::cout << "ERROR: Wrong destReg" << std::endl;
                    }
                    std::cout << "sub.d " << destReg << ", $f0, $f2" << std::endl;
                }
                else if (rightVar == "DOUBLE")
                {

                    returnLeft()->Translate2MIPS("$f0");
                    std::cout << "addi $sp, $sp, -8" << std::endl;
                    std::cout << "swc1 $f1, 4($sp)" << std::endl;
                    std::cout << "swc1 $f0, 0($sp)" << std::endl;
                    returnRight()->Translate2MIPS("$f2");
                    std::cout << "lwc1 $f1, 4($sp)" << std::endl;
                    std::cout << "lwc1 $f0, 0($sp)" << std::endl;
                    std::cout << "addi $sp, $sp, 8" << std::endl;
                    if (destReg[1] != 'f')
                    {
                        std::cout << "ERROR: Wrong destReg" << std::endl;
                    }
                    std::cout << "sub.d " << destReg << ", $f0, $f2" << std::endl;
                }
            }
        }
    }
};

class MultOp
    : public Operator
{
protected:
    virtual const char *returnOp() const override
    {
        return "*";
    }

public:
    MultOp(ExprPtr _left, ExprPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = returnLeft()->evaluate(bindings);
        double vr = returnRight()->evaluate(bindings);
        return vl * vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        std::string leftVar = returnLeft()->returnData();
        std::string rightVar = returnRight()->returnData();
        if (leftVar == "INT")
        {
            if (rightVar == "INT")
            {
                returnLeft()->Translate2MIPS("$t0");
                std::cout << "addi $sp, $sp, -4" << std::endl;
                std::cout << "sw $t0, 0($sp)" << std::endl;
                returnRight()->Translate2MIPS("$t1");
                std::cout << "lw $t0, 0($sp)" << std::endl;
                std::cout << "addi $sp, $sp, 4" << std::endl;
                if (destReg[1] == 'f')
                {
                    std::cout << "wrong dstReg" << std::endl;
                }
                std::cout << "mul " << destReg << ", $t0, $t1" << std::endl;
            }
            else if (rightVar == "FLOAT")
            {
                returnLeft()->Translate2MIPS("$t0");
                std::cout << "addi $sp, $sp, -4" << std::endl;
                std::cout << "sw $t0, 0($sp)" << std::endl;
                returnRight()->Translate2MIPS("$f2");
                std::cout << "lwc1 $f0, 0($sp)" << std::endl;
                std::cout << "addi $sp, $sp, 4" << std::endl;
                if (destReg[1] != 'f')
                {
                    std::cout << "ERROR: Wrong destReg" << std::endl;
                }
                std::cout << "mul.s " << destReg << ", $f0, $f2" << std::endl;
            }
            else if (rightVar == "DOUBLE")
            {
                returnLeft()->Translate2MIPS("$t0");
                std::cout << "addi $sp, $sp, -4" << std::endl;
                std::cout << "sw $t0, 0($sp)" << std::endl;
                returnRight()->Translate2MIPS("$f2");
                std::cout << "lwc1 $f0, 0($sp)" << std::endl;
                std::cout << "addi $sp, $sp, 4" << std::endl;
                std::cout << "cvt.d.s $f0, $f0" << std::endl;
                if (destReg[1] != 'f')
                {
                    std::cout << "ERROR: Wrong destReg" << std::endl;
                }
                std::cout << "mul.d " << destReg << ", $f0, $f2" << std::endl;
            }
        }
        else if (leftVar == "FLOAT")
        {
            if (rightVar == "INT")
            {
                returnRight()->Translate2MIPS("$t0");
                std::cout << "addi $sp, $sp, -4" << std::endl;
                std::cout << "sw $t0, 0($sp)" << std::endl;
                returnLeft()->Translate2MIPS("$f0");
                std::cout << "lwc1 $f2, 0($sp)" << std::endl;
                std::cout << "addi $sp, $sp, 4" << std::endl;
                if (destReg[1] != 'f')
                {
                    std::cout << "ERROR: Wrong destReg" << std::endl;
                }
                std::cout << "mul.s " << destReg << ", $f0, $f2" << std::endl;
            }
            else if (rightVar == "FLOAT")
            {
                returnLeft()->Translate2MIPS("$f0");
                std::cout << "addi $sp, $sp, -4" << std::endl;
                std::cout << "swc1 $f0, 0($sp)" << std::endl;
                returnRight()->Translate2MIPS("$f2");
                std::cout << "lwc1 $f0, 0($sp)" << std::endl;
                std::cout << "addi $sp, $sp, 4" << std::endl;
                if (destReg[1] != 'f')
                {
                    std::cout << "ERROR: Wrong destReg" << std::endl;
                }
                std::cout << "mul.s " << destReg << ", $f0, $f2" << std::endl;
            }
            else if (rightVar == "DOUBLE")
            {
                returnLeft()->Translate2MIPS("$f0");
                std::cout << "addi $sp, $sp, -4" << std::endl;
                std::cout << "swc1 $f0, 0($sp)" << std::endl;
                returnRight()->Translate2MIPS("$f2");
                std::cout << "lwc1 $f0, 0($sp)" << std::endl;
                std::cout << "addi $sp, $sp, 4" << std::endl;
                std::cout << "cvt.d.s $f0, $f0" << std::endl;
                if (destReg[1] != 'f')
                {
                    std::cout << "ERROR: Wrong destReg" << std::endl;
                }
                std::cout << "mul.d " << destReg << " , $f0, $f2" << std::endl;
            }
        }
        else if (leftVar == "DOUBLE")
        {
            if (rightVar == "INT")
            {
                returnRight()->Translate2MIPS("$t0");
                std::cout << "addi $sp, $sp, -4" << std::endl;
                std::cout << "sw $t0, 0($sp)" << std::endl;
                returnLeft()->Translate2MIPS("$f0");
                std::cout << "lwc1 $f2, 0($sp)" << std::endl;
                std::cout << "addi $sp, $sp, 4" << std::endl;
                std::cout << "cvt.d.s $f2, $f2" << std::endl;
                if (destReg[1] != 'f')
                {
                    std::cout << "ERROR: Wrong destReg" << std::endl;
                }
                std::cout << "mul.d " << destReg << ", $f0, $f2" << std::endl;
            }
            else if (rightVar == "FLOAT")
            {
                returnRight()->Translate2MIPS("$f2");
                std::cout << "addi $sp, $sp, -4" << std::endl;
                std::cout << "swc1 $f2, 0($sp)" << std::endl;
                returnLeft()->Translate2MIPS("$f0");
                std::cout << "lwc1, $f2, 0($sp)" << std::endl;
                std::cout << "addi $sp, $sp, 4" << std::endl;
                std::cout << "cvt.d.s $f2, $f2" << std::endl;
                if (destReg[1] != 'f')
                {
                    std::cout << "ERROR: Wrong destReg" << std::endl;
                }
                std::cout << "mul.d " << destReg << ", $f0, $f2" << std::endl;
            }
            else if (rightVar == "DOUBLE")
            {
                returnLeft()->Translate2MIPS("$f0");
                std::cout << "addi $sp, $sp, -8" << std::endl;
                std::cout << "swc1 $f1, 4($sp)" << std::endl;
                std::cout << "swc1 $f0, 0($sp)" << std::endl;
                returnRight()->Translate2MIPS("$f2");
                std::cout << "lwc1 $f1, 4($sp)" << std::endl;
                std::cout << "lwc1 $f0, 0($sp)" << std::endl;
                std::cout << "addi $sp, $sp, 8" << std::endl;
                if (destReg[1] != 'f')
                {
                    std::cout << "ERROR: Wrong destReg" << std::endl;
                }
                std::cout << "mul.d " << destReg << ", $f0, $f2" << std::endl;
            }
        }
    }
};

class DivOp
    : public Operator
{
protected:
    virtual const char *returnOp() const override
    {
        return "/";
    }

public:
    DivOp(ExprPtr _left, ExprPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        std::string leftVar = returnLeft()->returnData();
        std::string rightVar = returnRight()->returnData();
        if (leftVar == "INT")
        {
            if (rightVar == "INT")
            {
                returnLeft()->Translate2MIPS("$t0");
                std::cout << "addi $sp, $sp, -4" << std::endl;
                std::cout << "sw $t0, 0($sp)" << std::endl;
                returnRight()->Translate2MIPS("$t1");
                std::cout << "lw $t0, 0($sp)" << std::endl;
                std::cout << "addi $sp, $sp, 4" << std::endl;
                std::cout << "div $t0, $t1" << std::endl;
                if (destReg[1] == 'f')
                {
                    std::cout << "wrong dstReg" << std::endl;
                }
                std::cout << "mflo " << destReg << std::endl;
            }
            else if (rightVar == "FLOAT")
            {

                returnLeft()->Translate2MIPS("$t0");
                std::cout << "addi $sp, $sp, -4" << std::endl;
                std::cout << "sw $t0, 0($sp)" << std::endl;
                returnRight()->Translate2MIPS("$f2");
                std::cout << "lwc1 $f0, 0($sp)" << std::endl;
                std::cout << "addi $sp, $sp, 4" << std::endl;
                if (destReg[1] != 'f')
                {
                    std::cout << "ERROR: Wrong destReg" << std::endl;
                }
                std::cout << "div.s " << destReg << ", $f0, $f2" << std::endl;
            }
            else if (rightVar == "DOUBLE")
            {
                returnLeft()->Translate2MIPS("$t0");
                std::cout << "addi $sp, $sp, -4" << std::endl;
                std::cout << "sw $t0, 0($sp)" << std::endl;
                returnRight()->Translate2MIPS("$f2");
                std::cout << "lwc1 $f0, 0($sp)" << std::endl;
                std::cout << "addi $sp, $sp, 4" << std::endl;
                std::cout << "cvt.d.s $f0, $f0" << std::endl;
                if (destReg[1] != 'f')
                {
                    std::cout << "ERROR: Wrong destReg" << std::endl;
                }
                std::cout << "div.d " << destReg << ", $f0, $f2" << std::endl;
            }
        }
        else if (leftVar == "FLOAT")
        {
            if (rightVar == "INT")
            {
                returnRight()->Translate2MIPS("$t0");
                std::cout << "addi $sp, $sp, -4" << std::endl;
                std::cout << "sw $t0, 0($sp)" << std::endl;
                returnLeft()->Translate2MIPS("$f0");
                std::cout << "lwc1 $f2, 0($sp)" << std::endl;
                std::cout << "addi $sp, $sp, 4" << std::endl;
                if (destReg[1] != 'f')
                {
                    std::cout << "ERROR: Wrong destReg" << std::endl;
                }
                std::cout << "div.s " << destReg << ", $f0, $f2" << std::endl;
            }
            else if (rightVar == "FLOAT")
            {
                returnLeft()->Translate2MIPS("$f0");
                std::cout << "addi $sp, $sp, -4" << std::endl;
                std::cout << "swc1 $f0, 0($sp)" << std::endl;
                returnRight()->Translate2MIPS("$f2");
                std::cout << "lwc1 $f0, 0($sp)" << std::endl;
                std::cout << "addi $sp, $sp, 4" << std::endl;
                if (destReg[1] != 'f')
                {
                    std::cout << "ERROR: Wrong destReg" << std::endl;
                }
                std::cout << "div.s " << destReg << ", $f0, $f2" << std::endl;
            }
            else if (rightVar == "DOUBLE")
            {
                returnLeft()->Translate2MIPS("$f0");
                std::cout << "addi $sp, $sp, -4" << std::endl;
                std::cout << "swc1 $f0, 0($sp)" << std::endl;
                returnRight()->Translate2MIPS("$f2");
                std::cout << "lwc1 $f0, 0($sp)" << std::endl;
                std::cout << "addi $sp, $sp, 4" << std::endl;
                std::cout << "cvt.d.s $f0, $f0" << std::endl;
                if (destReg[1] != 'f')
                {
                    std::cout << "ERROR: Wrong destReg" << std::endl;
                }
                std::cout << "div.d " << destReg << " , $f0, $f2" << std::endl;
            }
        }
        else if (leftVar == "DOUBLE")
        {
            if (rightVar == "INT")
            {
                returnRight()->Translate2MIPS("$t0");
                std::cout << "addi $sp, $sp, -4" << std::endl;
                std::cout << "sw $t0, 0($sp)" << std::endl;
                returnLeft()->Translate2MIPS("$f0");
                std::cout << "lwc1 $f2, 0($sp)" << std::endl;
                std::cout << "addi $sp, $sp, 4" << std::endl;
                std::cout << "cvt.d.s $f2, $f2" << std::endl;
                if (destReg[1] != 'f')
                {
                    std::cout << "ERROR: Wrong destReg" << std::endl;
                }
                std::cout << "div.d " << destReg << ", $f0, $f2" << std::endl;
            }
            else if (rightVar == "FLOAT")
            {
                returnRight()->Translate2MIPS("$f2");
                std::cout << "addi $sp, $sp, -4" << std::endl;
                std::cout << "swc1 $f2, 0($sp)" << std::endl;
                returnLeft()->Translate2MIPS("$f0");
                std::cout << "lwc1, $f2, 0($sp)" << std::endl;
                std::cout << "addi $sp, $sp, 4" << std::endl;
                std::cout << "cvt.d.s $f2, $f2" << std::endl;
                if (destReg[1] != 'f')
                {
                    std::cout << "ERROR: Wrong destReg" << std::endl;
                }
                std::cout << "div.d " << destReg << ", $f0, $f2" << std::endl;
            }
            else if (rightVar == "DOUBLE")
            {
                returnLeft()->Translate2MIPS("$f0");
                std::cout << "addi $sp, $sp, -8" << std::endl;
                std::cout << "swc1 $f1, 4($sp)" << std::endl;
                std::cout << "swc1 $f0, 0($sp)" << std::endl;
                returnRight()->Translate2MIPS("$f2");
                std::cout << "lwc1 $f1, 4($sp)" << std::endl;
                std::cout << "lwc1 $f0, 0($sp)" << std::endl;
                std::cout << "addi $sp, $sp, 8" << std::endl;
                if (destReg[1] != 'f')
                {
                    std::cout << "ERROR: Wrong destReg" << std::endl;
                }
                std::cout << "div.d " << destReg << ", $f0, $f2" << std::endl;
            }
        }
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = returnLeft()->evaluate(bindings);
        double vr = returnRight()->evaluate(bindings);
        return vl / vr;
    }
};

class ModOp
    : public Operator
{
protected:
    virtual const char *returnOp() const override
    {
        return "%";
    }

public:
    ModOp(ExprPtr _left, ExprPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnLeft()->Translate2MIPS("$t0");
        std::cout << "addi $sp, $sp, -4" << std::endl;
        std::cout << "sw $t0, 0($sp)" << std::endl;
        returnRight()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 0($sp)" << std::endl;
        std::cout << "addi $sp, $sp, 4" << std::endl;
        std::cout << "div $t0, $t1" << std::endl;
        std::cout << "mfhi " << destReg << std::endl;
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        int vl = returnLeft()->evaluate(bindings);
        int vr = returnRight()->evaluate(bindings);
        return vl % vr;
    }
};

// Compare Operators
class GreaterThanOp
    : public Operator
{
protected:
    virtual const char *returnOp() const override
    {
        return ">";
    }

public:
    GreaterThanOp(ExprPtr _left, ExprPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnLeft()->Translate2MIPS("$t0");
        std::cout << "addi $sp, $sp, -4" << std::endl;
        std::cout << "sw $t0, 0($sp)" << std::endl;
        returnRight()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 0($sp)" << std::endl;
        std::cout << "addi $sp, $sp, 4" << std::endl;
        std::cout << "slt " << destReg << ", $t1, $t0" << std::endl;
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = returnLeft()->evaluate(bindings);
        double vr = returnRight()->evaluate(bindings);
        return vl > vr;
    }
};

class GreaterOrEqualOp
    : public Operator
{
protected:
    virtual const char *returnOp() const override
    {
        return ">=";
    }

public:
    GreaterOrEqualOp(ExprPtr _left, ExprPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnLeft()->Translate2MIPS("$t0");
        std::cout << "addi $sp, $sp, -4" << std::endl;
        std::cout << "sw $t0, 0($sp)" << std::endl;
        returnRight()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 0($sp)" << std::endl;
        std::cout << "addi $sp, $sp, 4" << std::endl;
        std::string one = makeName("one");
        std::cout << "beq $t0, $t1, " << one << std::endl;
        std::cout << "slt " << destReg << ", $t1, $t0" << std::endl;
        std::string exit = makeName("exit");
        std::cout << "j " << exit << std::endl;
        std::cout << one << ":" << std::endl;
        std::cout << "addi " << destReg << ", $0, 1" << std::endl;
        std::cout << exit << ":" << std::endl;
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = returnLeft()->evaluate(bindings);
        double vr = returnRight()->evaluate(bindings);
        return vl >= vr;
    }
};

class LessThanOp
    : public Operator
{
protected:
    virtual const char *returnOp() const override
    {
        return "<";
    }

public:
    LessThanOp(ExprPtr _left, ExprPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnLeft()->Translate2MIPS("$t0");
        std::cout << "addi $sp, $sp, -4" << std::endl;
        std::cout << "sw $t0, 0($sp)" << std::endl;
        returnRight()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 0($sp)" << std::endl;
        std::cout << "addi $sp, $sp, 4" << std::endl;
        std::cout << "slt " << destReg << ", $t0, $t1" << std::endl;
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = returnLeft()->evaluate(bindings);
        double vr = returnRight()->evaluate(bindings);
        return vl < vr;
    }
};

class LessOrEqualOp
    : public Operator
{
protected:
    virtual const char *returnOp() const override
    {
        return "<=";
    }

public:
    LessOrEqualOp(ExprPtr _left, ExprPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnLeft()->Translate2MIPS("$t0");
        std::cout << "addi $sp, $sp, -4" << std::endl;
        std::cout << "sw $t0, 0($sp)" << std::endl;
        returnRight()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 0($sp)" << std::endl;
        std::cout << "addi $sp, $sp, 4" << std::endl;
        std::string one = makeName("one");
        std::cout << "beq $t0, $t1, " << one << std::endl;
        std::cout << "slt " << destReg << ", $t0, $t1" << std::endl;
        std::string exit = makeName("exit");
        std::cout << "j " << exit << std::endl;
        std::cout << one << ":" << std::endl;
        std::cout << "addi " << destReg << ", $0, 1" << std::endl;
        std::cout << exit << ":" << std::endl;
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = returnLeft()->evaluate(bindings);
        double vr = returnRight()->evaluate(bindings);
        return vl <= vr;
    }
};

class EqualOp
    : public Operator
{
protected:
    virtual const char *returnOp() const override
    {
        return "==";
    }

public:
    EqualOp(ExprPtr _left, ExprPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnLeft()->Translate2MIPS("$t0");
        std::cout << "addi $sp, $sp, -4" << std::endl;
        std::cout << "sw $t0, 0($sp)" << std::endl;
        returnRight()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 0($sp)" << std::endl;
        std::cout << "addi $sp, $sp, 4" << std::endl;
        std::string one = makeName("one");
        std::cout << "beq $t0, $t1, " << one << std::endl;
        std::cout << "add " << destReg << ", $0, $0" << std::endl;
        std::string exit = makeName("exit");
        std::cout << "j " << exit << std::endl;
        std::cout << one << ":" << std::endl;
        std::cout << "addi " << destReg << ", $0, 1" << std::endl;
        std::cout << exit << ":" << std::endl;
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = returnLeft()->evaluate(bindings);
        double vr = returnRight()->evaluate(bindings);
        return vl == vr;
    }
};

class NotEqualOp
    : public Operator
{
protected:
    virtual const char *returnOp() const override
    {
        return "!=";
    }

public:
    NotEqualOp(ExprPtr _left, ExprPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnLeft()->Translate2MIPS("$t0");
        std::cout << "addi $sp, $sp, -4" << std::endl;
        std::cout << "sw $t0, 0($sp)" << std::endl;
        returnRight()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 0($sp)" << std::endl;
        std::cout << "addi $sp, $sp, 4" << std::endl;
        std::string one = makeName("one");
        std::cout << "bne $t0, $t1, " << one << std::endl;
        std::cout << "add " << destReg << ", $0, $0" << std::endl;
        std::string exit = makeName("exit");
        std::cout << "j " << exit << std::endl;
        std::cout << one << ":" << std::endl;
        std::cout << "addi " << destReg << ", $0, 1" << std::endl;
        std::cout << exit << ":" << std::endl;
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = returnLeft()->evaluate(bindings);
        double vr = returnRight()->evaluate(bindings);
        return vl != vr;
    }
};
// Bitwise Operators

class BitAndOp
    : public Operator
{
protected:
    virtual const char *returnOp() const override
    {
        return "&";
    }

public:
    BitAndOp(ExprPtr _left, ExprPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        int vl = returnLeft()->evaluate(bindings);
        int vr = returnRight()->evaluate(bindings);
        return vl & vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnLeft()->Translate2MIPS("$t0");
        std::cout << "addi $sp, $sp, -4" << std::endl;
        std::cout << "sw $t0, 0($sp)" << std::endl;
        returnRight()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 0($sp)" << std::endl;
        std::cout << "addi $sp, $sp, 4" << std::endl;
        std::cout << "and " << destReg << ", $t0, $t1" << std::endl;
    }
};

class BitOrOp
    : public Operator
{
protected:
    virtual const char *returnOp() const override
    {
        return "|";
    }

public:
    BitOrOp(ExprPtr _left, ExprPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        int vl = returnLeft()->evaluate(bindings);
        int vr = returnRight()->evaluate(bindings);
        return vl | vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnLeft()->Translate2MIPS("$t0");
        std::cout << "addi $sp, $sp, -4" << std::endl;
        std::cout << "sw $t0, 0($sp)" << std::endl;
        returnRight()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 0($sp)" << std::endl;
        std::cout << "addi $sp, $sp, 4" << std::endl;
        std::cout << "or " << destReg << ", $t0, $t1" << std::endl;
    }
};

class BitXorOp
    : public Operator
{
protected:
    virtual const char *returnOp() const override
    {
        return "^";
    }

public:
    BitXorOp(ExprPtr _left, ExprPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = returnLeft()->evaluate(bindings);
        double vr = returnRight()->evaluate(bindings);
        return vl - vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnLeft()->Translate2MIPS("$t0");
        std::cout << "addi $sp, $sp, -4" << std::endl;
        std::cout << "sw $t0, 0($sp)" << std::endl;
        returnRight()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 0($sp)" << std::endl;
        std::cout << "addi $sp, $sp, 4" << std::endl;
        std::cout << "xor " << destReg << ", $t0, $t1" << std::endl;
    }
};

class LeftShiftOp
    : public Operator
{
protected:
    virtual const char *returnOp() const override
    {
        return "<<";
    }

public:
    LeftShiftOp(ExprPtr _left, ExprPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnLeft()->Translate2MIPS("$t0");
        std::cout << "addi $sp, $sp, -4" << std::endl;
        std::cout << "sw $t0, 0($sp)" << std::endl;
        returnRight()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 0($sp)" << std::endl;
        std::cout << "addi $sp, $sp, 4" << std::endl;
        std::cout << "sllv " << destReg << ", $t0, $t1" << std::endl;
    }
};

class RightShiftOp
    : public Operator
{
protected:
    virtual const char *returnOp() const override
    {
        return ">>";
    }

public:
    RightShiftOp(ExprPtr _left, ExprPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnLeft()->Translate2MIPS("$t0");
        std::cout << "addi $sp, $sp, -4" << std::endl;
        std::cout << "sw $t0, 0($sp)" << std::endl;
        returnRight()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 0($sp)" << std::endl;
        std::cout << "addi $sp, $sp, 4" << std::endl;
        std::cout << "srlv " << destReg << ", $t0, $t1" << std::endl;
    }
};

// Logic Operators
class LogicAndOp
    : public Operator
{
protected:
    virtual const char *returnOp() const override
    {
        return "&&";
    }

public:
    LogicAndOp(ExprPtr _left, ExprPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnLeft()->Translate2MIPS("$t0");
        std::cout << "addi $sp, $sp, -4" << std::endl;
        std::cout << "sw $t0, 0($sp)" << std::endl;
        returnRight()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 0($sp)" << std::endl;
        std::cout << "addi $sp, $sp, 4" << std::endl;
        std::string zero = makeName("zero");
        std::cout << "beq $t0, $0, " << zero << std::endl;
        std::cout << "beq $t1, $0, " << zero << std::endl;
        std::cout << "addi " << destReg << ", $0, 1" << std::endl;
        std::string exit = makeName("exit");
        std::cout << "j " << exit << std::endl;
        std::cout << zero << ":" << std::endl;
        std::cout << "add " << destReg << ", $0, $0" << std::endl;
        std::cout << exit << ":" << std::endl;
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = returnLeft()->evaluate(bindings);
        double vr = returnRight()->evaluate(bindings);
        return vl && vr;
    }
};

class LogicOrOp
    : public Operator
{
protected:
    virtual const char *returnOp() const override
    {
        return "||";
    }

public:
    LogicOrOp(ExprPtr _left, ExprPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnLeft()->Translate2MIPS("$t0");
        std::cout << "addi $sp, $sp, -4" << std::endl;
        std::cout << "sw $t0, 0($sp)" << std::endl;
        returnRight()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 0($sp)" << std::endl;
        std::cout << "addi $sp, $sp, 4" << std::endl;
        std::string one = makeName("one");
        std::cout << "bne $t0, $0, " << one << std::endl;
        std::cout << "bne $t1, $0, " << one << std::endl;
        std::cout << "add " << destReg << ", $0, $0" << std::endl;
        std::string exit = makeName("exit");
        std::cout << "j " << exit << std::endl;
        std::cout << one << ":" << std::endl;
        std::cout << "addi " << destReg << ", $0, 1" << std::endl;
        std::cout << exit << ":" << std::endl;
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = returnLeft()->evaluate(bindings);
        double vr = returnRight()->evaluate(bindings);
        return vl || vr;
    }
};

#endif
