#ifndef ast_unary_hpp
#define ast_unary_hpp

#include <string>
#include <iostream>

class Unary
    : public Expression
{
private:
    ExpressionPtr expr;

protected:
    Unary(const ExpressionPtr _expr)
        : expr(_expr)
    {
    }

public:
    virtual ~Unary()
    {
        delete expr;
    }

    virtual const char *getOpcode() const = 0;

    ExpressionPtr getExpr() const
    {
        return expr;
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << "( ";
        dst << getOpcode();
        dst << " ";
        expr->pretty_print(dst);
        dst << " )";
    }
};

class NegOperator
    : public Unary
{
public:
    NegOperator(const ExpressionPtr _expr)
        : Unary(_expr)
    {
    }

    virtual const char *getOpcode() const override
    {
        return "-";
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double neg = getExpr()->evaluate(bindings);
        return -neg;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        std::string srcRegA = makeName("srcRegA");
        getExpr()->Translate2MIPS(srcRegA);
        std::cout << "subu " << destReg << " $0 " << srcRegA << std::endl;
    }
};

class NotOperator
    : public Unary
{
public:
    NotOperator(const ExpressionPtr _expr)
        : Unary(_expr)
    {
    }

    virtual const char *getOpcode() const override
    {
        return "!";
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double val = getExpr()->evaluate(bindings);
        return (!val);
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        std::string srcRegA = makeName("srcRegA");
        getExpr()->Translate2MIPS(srcRegA);
        std::string setZero = makeName("setZero");
        std::cout << "beq " << srcRegA << " $0 " << setZero << std::endl;
        std::cout << "addi " << destReg << " $0 1" << std::endl;
        std::cout << setZero << ":" << std::endl;
        std::cout << "add " << destReg << " $0 $0" << std::endl;
    }
};

class Return
    : public Unary
{
public:
    Return(const ExpressionPtr _expr)
        : Unary(_expr)
    {
    }

    virtual const char *getOpcode() const override
    {
        return "return";
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double ret = getExpr()->evaluate(bindings);
        return ret;
    }
};

#endif