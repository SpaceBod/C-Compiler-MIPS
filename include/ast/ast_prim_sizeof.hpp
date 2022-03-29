#ifndef ast_prim_sizeof_hpp
#define ast_prim_sizeof_hpp

#include <string>
#include <iostream>

#include "ast_symtab.hpp"
#include "ast_expressions.hpp"
#include "ast_primitives.hpp"

class SizeOf
    : public Expr
{
private:
    mutable double value;
    ExprPtr expr = nullptr;

public:
    SizeOf()
    {
    }
    SizeOf(ExprPtr _expr)
    {
        expr = _expr;
    }
    SizeOf(VarTypeDef _type)
    {
        switch (_type)
        {
        case INT:
            value = 4;
            break;
        case FLOAT:
            value = 4;
            break;
        case DOUBLE:
            value = 8;
            break;
        case CHAR:
            value = 1;
            break;
        default:
            value = -1;
        }
    }
    virtual void Translate2MIPS(std::string destReg) const override
    {
        if (expr != nullptr)
        {
            const std::string type = expr->returnData();
            if (type == "INT" || type == "FLOAT")
            {
                value = 4;
            }
            else if (type == "DOUBLE")
            {
                value = 8;
            }
            else if (type == "CHAR")
            {
                value = 1;
            }
        }
        std::cout << "addi " << destReg << " , $0, " << value << std::endl;
    }
};

#endif