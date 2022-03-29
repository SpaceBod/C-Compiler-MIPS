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

// Comparitive Operators
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