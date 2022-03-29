#ifndef ast_unary_hpp
#define ast_unary_hpp

#include <string>
#include <iostream>

class Unary
    : public Expr
{
private:
    ExprPtr expr;

protected:
    Unary(const ExprPtr _expr)
        : expr(_expr)
    {
    }

public:
    virtual ~Unary()
    {
        delete expr;
    }

    virtual const char *returnOp() const = 0;

    ExprPtr returnExpr() const
    {
        return expr;
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << "( ";
        dst << returnOp();
        dst << " ";
        expr->pretty_print(dst);
        dst << " )";
    }
};

class NegOp
    : public Unary
{
public:
    NegOp(const ExprPtr _expr)
        : Unary(_expr)
    {
    }

    virtual const char *returnOp() const override
    {
        return "-";
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnExpr()->Translate2MIPS("$t0");
        std::cout << "subu " << destReg << ", $0, $t0" << std::endl;
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double neg = returnExpr()->evaluate(bindings);
        return (-neg);
    }
};

class PosOp
    : public Unary
{
public:
    PosOp(const ExprPtr _expr)
        : Unary(_expr)
    {
    }

    virtual const char *returnOp() const override
    {
        return "+";
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnExpr()->Translate2MIPS("$t0");
        std::cout << "subu " << destReg << ", $t0, $0" << std::endl;
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double pos = returnExpr()->evaluate(bindings);
        return (-pos);
    }
};

class NotOp
    : public Unary
{
public:
    NotOp(const ExprPtr _expr)
        : Unary(_expr)
    {
    }

    virtual const char *returnOp() const override
    {
        return "!";
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnExpr()->Translate2MIPS("$t0");
        std::string zero = makeName("zero");
        std::cout << "bne $t0, $0, " << zero << std::endl;
        std::cout << "addi " << destReg << ", $0, 1" << std::endl;
        std::cout << zero << ":" << std::endl;
        std::cout << "add " << destReg << ", $0, $0" << std::endl;
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double val = returnExpr()->evaluate(bindings);
        return (!val);
    }
};

#endif
