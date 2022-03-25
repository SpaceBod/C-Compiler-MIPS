#ifndef ast_expressions_hpp
#define ast_expressions_hpp

#include <string>
#include <iostream>
#include <map>

#include <memory>

class Expression;

typedef const Expression *ExpressionPtr;

class Expression
{
public:
    virtual ~Expression()
    {
    }
    virtual void pretty_print(std::ostream &dst) const = 0;
    virtual void Translate2MIPS(std::string destReg) const = 0;

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const
    {
        throw std::runtime_error("Not yet implemented!");
    }
};

static int makeNameUnq = 0;
static std::string makeName(std::string base)
{
    return "_" + base + "_" + std::to_string(makeNameUnq++);
}

#endif