#ifndef ast_operators_hpp
#define ast_operators_hpp

#include <string>
#include <iostream>
#include <cmath>

class Operator
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr right;

protected:
    Operator(ExpressionPtr _left, ExpressionPtr _right)
        : left(_left), right(_right)
    {
    }

public:
    virtual ~Operator()
    {
        delete left;
        delete right;
    }

    virtual const char *getOpcode() const = 0;

    ExpressionPtr getLeft() const
    {
        return left;
    }

    ExpressionPtr getRight() const
    {
        return right;
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << "( ";
        left->pretty_print(dst);
        dst << " ";
        dst << getOpcode();
        dst << " ";
        right->pretty_print(dst);
        dst << " )";
    }
};

// Arithmetic Operators

class AddOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "+";
    }

public:
    AddOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {

        double vl = getLeft()->evaluate(bindings);
        double vr = getRight()->evaluate(bindings);
        return vl + vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override {
        std::string srcRegA = makeName("srcRegA");
        std::string srcRegB = makeName("srcRegB");
        getLeft()->Translate2MIPS(srcRegA);
        getRight()->Translate2MIPS(srcRegB);
        std::cout << "add " << destReg << " " << srcRegA << " " << srcRegB << std::endl;
    }
};

class SubOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "-";
    }

public:
    SubOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = getLeft()->evaluate(bindings);
        double vr = getRight()->evaluate(bindings);
        return vl - vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override {
        std::string srcRegA = makeName("srcRegA");
        std::string srcRegB = makeName("srcRegB");
        getLeft()->Translate2MIPS(srcRegA);
        getRight()->Translate2MIPS(srcRegB);
        std::cout << "sub " << destReg << " " << srcRegA << " " << srcRegB << std::endl;
    }
};

class MulOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "*";
    }

public:
    MulOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = getLeft()->evaluate(bindings);
        double vr = getRight()->evaluate(bindings);
        return vl * vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override {
        std::string srcRegA = makeName("srcRegA");
        std::string srcRegB = makeName("srcRegB");
        getLeft()->Translate2MIPS(srcRegA);
        getRight()->Translate2MIPS(srcRegB);
        std::cout << "mul " << destReg << " " << srcRegA << " " << srcRegB << std::endl;
    }
};

class DivOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "/";
    }

public:
    DivOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = getLeft()->evaluate(bindings);
        double vr = getRight()->evaluate(bindings);
        return vl / vr;
    }
};

class ModOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "%";
    }

public:
    ModOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        int vl = getLeft()->evaluate(bindings);
        int vr = getRight()->evaluate(bindings);
        return vl % vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override {
        std::string srcRegA = makeName("srcRegA");
        std::string srcRegB = makeName("srcRegB");
        getLeft()->Translate2MIPS(srcRegA);
        getRight()->Translate2MIPS(srcRegB);
        std::cout << "div " << srcRegA << " " << srcRegB << std::endl; // quotient stored in hi, remainder stored in lo
        std::cout << "mflo " << destReg << std::endl;
    }
};

// Comparitive Operators

class GreaterThanOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return ">";
    }

public:
    GreaterThanOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = getLeft()->evaluate(bindings);
        double vr = getRight()->evaluate(bindings);
        return vl > vr;
    }
    
    virtual void Translate2MIPS(std::string destReg) const override {
        std::string srcRegA = makeName("srcRegA");
        std::string srcRegB = makeName("srcRegB");
        getLeft()->Translate2MIPS(srcRegA);
        getRight()->Translate2MIPS(srcRegB);
        std::cout << "slt " << destReg << " " << srcRegB << " " << srcRegA << std::endl;
    }

class LessThanOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "<";
    }

public:
    LessThanOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = getLeft()->evaluate(bindings);
        double vr = getRight()->evaluate(bindings);
        return vl < vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override {
        std::string srcRegA = makeName("srcRegA");
        std::string srcRegB = makeName("srcRegB");
        getLeft()->Translate2MIPS(srcRegA);
        getRight()->Translate2MIPS(srcRegB);
        std::cout << "slt " << destReg << " " << srcRegA << " " << srcRegB << std::endl;
    }
};

class GreaterOrEqualThanOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return ">=";
    }

public:
    GreaterOrEqualThanOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = getLeft()->evaluate(bindings);
        double vr = getRight()->evaluate(bindings);
        return vl >= vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override {
        std::string srcRegA = makeName("srcRegA");
        std::string srcRegB = makeName("srcRegB");
        getLeft()->Translate2MIPS(srcRegA);
        getRight()->Translate2MIPS(srcRegB);

        std::cout << "sge " << destReg << " " << srcRegA << " " << srcRegB << std::endl;
        // std::string set_one = makeName("set_one");
        // std::cout << "beq " << srcRegA << " " << srcRegB << " " << set_one << std::endl;
        // std::cout << "slt " << destReg << " " << srcRegB << " " << srcRegA << std::endl;
        // std::string exit = makeName("exit");
        // std::cout << "jump " << exit << std::endl;
        // std::cout << ":" << set_one << std::endl;
        // std::cout << "addi " << destReg << " $0 1" << std::endl;
        // std::cout << ":" << exit << std::endl;
    }
};

class LessOrEqualThanOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "=<";
    }

public:
    LessOrEqualThanOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = getLeft()->evaluate(bindings);
        double vr = getRight()->evaluate(bindings);
        return vl <= vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override {
        std::string srcRegA = makeName("srcRegA");
        std::string srcRegB = makeName("srcRegB");
        getLeft()->Translate2MIPS(srcRegA);
        getRight()->Translate2MIPS(srcRegB);

        std::cout << "sge " << destReg << " " << srcRegA << " " << srcRegB << std::endl;
};

class EqualOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "==";
    }

public:
    EqualOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = getLeft()->evaluate(bindings);
        double vr = getRight()->evaluate(bindings);
        return vl == vr;
    }
};

class NotEqualOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "!=";
    }

public:
    NotEqualOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = getLeft()->evaluate(bindings);
        double vr = getRight()->evaluate(bindings);
        return vl != vr;
    }
};

// Logic Operators

class LogicAnd
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "&&";
    }

public:
    LogicAnd(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = getLeft()->evaluate(bindings);
        double vr = getRight()->evaluate(bindings);
        return vl && vr;
    }
};

class BitAnd
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "&";
    }

public:
    BitAnd(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        int vl = getLeft()->evaluate(bindings);
        int vr = getRight()->evaluate(bindings);
        return vl & vr;
    }
};

class LogicOr
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "||";
    }

public:
    LogicOr(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = getLeft()->evaluate(bindings);
        double vr = getRight()->evaluate(bindings);
        return vl || vr;
    }
};

class BitOr
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "|";
    }

public:
    BitOr(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        int vl = getLeft()->evaluate(bindings);
        int vr = getRight()->evaluate(bindings);
        return vl | vr;
    }
};

class BitXOr
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "^";
    }

public:
    BitXOr(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        int vl = getLeft()->evaluate(bindings);
        int vr = getRight()->evaluate(bindings);
        return vl ^ vr;
    }
};

#endif