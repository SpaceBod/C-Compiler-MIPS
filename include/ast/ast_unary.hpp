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