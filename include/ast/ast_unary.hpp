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

    virtual const char *return_Opcode() const = 0;

    ExpressionPtr return_Expr() const
    {
        return expr;
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << "( ";
        dst << return_Opcode();
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

    virtual const char *return_Opcode() const override
    {
        return "-";
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double neg = return_Expr()->evaluate(bindings);
        return -neg;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        return_Expr()->Translate2MIPS("$t0");
        std::cout << "subu " << destReg << ", $0, $t0" << std::endl;
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

    virtual const char *return_Opcode() const override
    {
        return "!";
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double val = return_Expr()->evaluate(bindings);
        return (!val);
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        return_Expr()->Translate2MIPS("t0");
        std::string zero = makeName("zero");
        std::cout << "bne $t0, $0, " << zero << std::endl;
        std::cout << "addi " << destReg << ", $0, 1" << std::endl;
        std::cout << zero << ":" << std::endl;
        std::cout << "add " << destReg << ", $0, $0" << std::endl;
    }
};

class PosOperator
    : public Unary
{
public:
    PosOperator(const ExpressionPtr _expr)
        : Unary(_expr)
    {
    }

    virtual const char *return_Opcode() const override
    {
        return "+";
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        return_Expr()->Translate2MIPS("$t0");
        std::cout << "subu " << destReg << ", $t0, $0" << std::endl;
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double pos = return_Expr()->evaluate(bindings);
        return (+pos);
    }
};

#endif