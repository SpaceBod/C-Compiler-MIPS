#ifndef ast_prim_storefunc_hpp
#define ast_prim_storefunc_hpp

#include <string>
#include <iostream>

#include "ast_symtab.hpp"
#include "ast_expressions.hpp"
#include "ast_primitives.hpp"
#include "ast_primitives.hpp"

class StoreFunc
    : public Expr
{
private:
    std::string type;
    std::string varID;
    mutable std::string address;
    ExprListPtr Args = nullptr;
    DecType VarType;

public:
    StoreFunc()
    {
    }

    StoreFunc(const std::string *_varID, ExprListPtr _Args = nullptr)
    {
        VarType = CALL;
        varID = *_varID;
        Args = _Args;
    }

    StoreFunc(VarTypeDef _type, const std::string *_varID)
    {
        VarType = DECLARATION;
        switch (_type)
        {
        case INT:
            type = "INT";
            varID = *_varID;
            break;
        case FLOAT:
            type = "FLOAT";
            varID = *_varID;
            break;
        case DOUBLE:
            type = "DOUBLE";
            varID = *_varID;
            break;
        default:
            type = "something went wrong";
        }
    }

    const std::string returnType() const
    {
        return type;
    }

    virtual const std::string returnData() const override
    {
        return SymTab.returnType(varID);
    }

    const std::string returnFuncId() const
    {
        return varID;
    }

    const std::string returnAddress() const
    {
        return address;
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        switch (VarType)
        {
        case CALL:
            dst << varID;
            break;
        case DECLARATION:
            dst << type;
            dst << " ";
            dst << varID;
            dst << "();";
            dst << '\n';
            break;
        default:
            break;
        }
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        switch (VarType)
        {
        case CALL:
            if (SymTab.lookup(varID)[0] == 'n')
            {
                address = std::to_string(std::stoi(SymTab.lookup(varID).substr(1, SymTab.lookup(varID).length() - 1)) + 44);
                StkPtr.setNullFunc(1);
                if (Args != nullptr)
                {
                    Args->Translate2MIPS(destReg, address);
                }
                std::cout << "jal " << varID << std::endl;
            }
            else
            {
                address = std::to_string(std::stoi(SymTab.lookup(varID)) + 44);
                if (Args != nullptr)
                {
                    Args->Translate2MIPS(destReg, address);
                }
                std::cout << "jal " << varID << std::endl;
                if (returnData() == "INT")
                {
                    std::cout << "add " << destReg << ", $v0, $0" << std::endl;
                }
                else if (returnData() == "FLOAT")
                {
                    std::cout << "addi.s " << destReg << ", $f0, 0" << std::endl;
                }
                else if (returnData() == "DOUBLE")
                {
                    std::cout << "addi.d " << destReg << ", $f0, 0" << std::endl;
                }
                else if (returnData() == "CHAR")
                {
                    std::cout << "add " << destReg << ", $v0, $0" << std::endl;
                    std::cout << "andi " << destReg << ", " << destReg << ", 0x00ff" << std::endl;
                }
            }
            break;

        case DECLARATION:
            if (destReg == "$0")
            {
                address = "n" + std::to_string(StkPtr.getIncrement());
                if (SymTab.lookup(varID) == "Unknown reference from ID")
                {
                    SymTab.insert(type, "func", varID, address);
                }
                else
                {
                    SymTab.edit(type, "func", varID, address);
                }
            }
            else if (returnType() == "INT")
            {
                address = std::to_string(StkPtr.getIncrement());
                if (SymTab.lookup(varID) == "Unknown reference from ID")
                {
                    SymTab.insert(type, "func", varID, address);
                }
                else
                {
                    SymTab.edit(type, "func", varID, address);
                }
            }
            break;
        default:
            break;
        }
    }
    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        return bindings.at(varID);
    }
};

#endif