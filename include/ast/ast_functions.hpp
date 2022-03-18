#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_expressions.hpp"
#include "ast_primitives.hpp"
#include "ast_statements.hpp"

#include <cmath>

class Function
    : public Expression
{
private:
    ExpressionPtr arg;
    Variable *name;
    StatPtr stat;

public:
    Function(Variable *_name, StatPtr _stat = nullptr)
        : name(_name)
        , stat(_stat)
    {
    }
    
    virtual ~Function()
    {
        delete arg;
        delete name;
        delete stat;
    }

    const std::string getFunction() const
    {
        return name->getId();
    }

    ExpressionPtr getArg() const
    {
        return arg;
    }

    void pretty_print(std::ostream &dst) const
    {
        name->pretty_print(dst);
        dst << "( ";
        dst << " )";
        dst << "\n";
        stat->pretty_print(dst);
    }
};

class LogFunction
    : public Function
{
public:
    LogFunction(Variable *_name, StatPtr _stat = nullptr)
        : Function(_name, _stat)
    {
    }

    virtual const char *getFunction() const
    {
        return "log";
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double v = getArg()->evaluate(bindings);
        return log(v);
    }
};

class ExpFunction
    : public Function
{
public:
    ExpFunction(Variable *_name, StatPtr _stat = nullptr)
        : Function(_name, _stat)
    {
    }

    virtual const char *getFunction() const
    {
        return "exp";
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double v = getArg()->evaluate(bindings);
        return exp(v);
    }
};

class SqrtFunction
    : public Function
{
public:
    SqrtFunction(Variable *_name, StatPtr _stat = nullptr)
        : Function(_name, _stat)
    {
    }

    virtual const char *getFunction() const
    {
        return "sqrt";
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double v = getArg()->evaluate(bindings);
        return sqrt(v);
    }
};

#endif