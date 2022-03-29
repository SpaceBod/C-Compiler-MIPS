#ifndef ast_op_mod_hpp
#define ast_op_mod_hpp

#include <string>
#include <iostream>
#include "../ast_expressions.hpp"
#include "../ast_operators.hpp"

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

#endif