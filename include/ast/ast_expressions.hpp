#ifndef ast_expressions_hpp
#define ast_expressions_hpp

#include <string>
#include <iostream>
#include <map>

#include <memory>
#include "ast_symtab.hpp"

extern SymTabADT SymTab;
extern StackPtr StkPtr;

class Expr;

typedef const Expr *ExprPtr;

class Expr
{
public:
    virtual ~Expr()
    {
    }

    virtual void pretty_print(std::ostream &dst) const
    {
    }

    virtual const std::string returnData() const
    {
        return "null";
    }

    virtual const std::string returnDataKind() const
    {
        return "null";
    }

    virtual void Translate2MIPS(std::string destReg) const
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const
    {
        throw std::runtime_error("Evalualtion Failed...");
    }
};

class ExprList;

typedef const ExprList *ExprListPtr;

class ExprList
    : public Expr
{
private:
    ExprPtr arg = nullptr;
    ExprListPtr argList = nullptr;

public:
    ExprList(ExprPtr _arg, ExprListPtr _argList = nullptr)
        : arg(_arg), argList(_argList)
    {
    }

    virtual ~ExprList()
    {
        delete arg;
        delete argList;
    }
    ExprPtr returnArg() const
    {
        return arg;
    }

    ExprListPtr returnArgList() const
    {
        return argList;
    }

    virtual void Translate2MIPS(std::string destReg, std::string address) const
    {
        if (returnArg() != nullptr)
        {
            if (StkPtr.returnArgCount() < 4)
            {
                returnArg()->Translate2MIPS("$a" + std::to_string(StkPtr.returnArgCount()));
            }
            else
            {
                returnArg()->Translate2MIPS("$t0");
                std::cout << "sw $t0, -" << std::to_string(44 + (StkPtr.returnArgCount() + 1) * 4) << "($sp)" << std::endl;
            }
            StkPtr.setArgCount(StkPtr.returnArgCount() + 1);
        }
        if (returnArgList() != nullptr)
        {
            returnArgList()->Translate2MIPS(destReg, address);
        }
        StkPtr.setArgCount(0);
    }
};

static int makeNameUnq = 0;
static std::string makeName(std::string base)
{
    return "_" + base + "_" + std::to_string(makeNameUnq++);
}

#endif
