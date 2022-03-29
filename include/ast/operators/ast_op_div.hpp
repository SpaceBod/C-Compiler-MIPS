#ifndef ast_op_div_hpp
#define ast_op_div_hpp

#include <string>
#include <iostream>
#include "../ast_expressions.hpp"
#include "../ast_operators.hpp"

// Arithmatical Operator DIV
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

#endif