#ifndef ast_number_hpp
#define ast_number_hpp

#include <string>
#include <iostream>

#include "ast_symtab.hpp"
#include "ast_primitives.hpp"
#include "ast_expressions.hpp"

class Number_INT
    : public Expr
{
private:
    double value;

public:
    Number_INT(double _value)
    {
        value = _value;
    }
    double getValue() const
    {
        return value;
    }
    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << value;
    }
    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        return value;
    }
    virtual const std::string returnData() const override
    {
        return "INT";
    }
    virtual void Translate2MIPS(std::string destReg) const override
    {
        std::cout << "addi " << destReg << ", $0, " << value << std::endl;
    }
};

class Number_DOUBLE
    : public Expr
{
private:
    double value;

public:
    Number_DOUBLE(double _value)
    {
        value = _value;
    }
    double getValue() const
    {
        return value;
    }
    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << value;
    }
    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        return value;
    }
    virtual const std::string returnData() const override
    {
        return "FLOAT";
    }
    virtual void Translate2MIPS(std::string destReg) const override
    {
        std::cout << "li.s " << destReg << ", " << value << std::endl;
    }
};

#endif
