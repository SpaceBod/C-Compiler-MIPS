#ifndef symtab_hpp
#define symtab_hpp
#include <vector>
#include <cassert>
#include <map>

class SymTab;
class StackPtr;

class StackPtr
{
private:
    bool label = 0;

    int argCount;
    int argSize = 0;

    int increment;
    int enumerate;

    int scopeCurrent = 0;
    int scopeIncrement[100];
    int structSize = 0;

    int functionNull = 0;
    int functionReturn = 0;

    std::string declaration;

public:
    bool returnLabel()
    {
        return label;
    }
    void setLabel(bool labelW)
    {
        label = labelW;
    }

    int returnArgCount()
    {
        return argCount;
    }
    void setArgCount(int newArgCount)
    {
        argCount = newArgCount;
    }

    int returnArgSize()
    {
        return argSize;
    }
    void setArgSize(int newArgSize)
    {
        argSize = newArgSize;
    }

    int returnIncrement()
    {
        return increment;
    }
    void setIncrement(int newIncrement)
    {
        increment = newIncrement;
    }

    int returnEnumerate()
    {
        return enumerate;
    }
    void setEnumerate(int newEnumerate)
    {
        enumerate = newEnumerate;
    }

    int returnScopeCurrent()
    {
        return scopeCurrent;
    }
    void getScopeCurrent(int newScopeCurrent)
    {
        scopeCurrent = newScopeCurrent;
    }

    int returnScopeIncrement(int scope = -1)
    {
        return scopeIncrement[scope != -1 ? scope : scopeCurrent];
    }
    void setScopeIncrement(int newScopeIncrement)
    {
        scopeIncrement[scopeCurrent] = newScopeIncrement;
    }

    int returnStructSize()
    {
        return structSize;
    }
    void setStructSize(int newStructSize)
    {
        structSize = newStructSize;
    }

    int returnFunctionNull()
    {
        return functionNull;
    }
    void setFunctionNull(int newFunctionNull)
    {
        functionNull = newFunctionNull;
    }

    int returnFunctionReturn()
    {
        return functionReturn;
    }
    void setFunctionReturn(int newFunctionReturn)
    {
        functionReturn = newFunctionReturn;
    }

    std::string returnDeclaration()
    {
        return declaration;
    }
    void setDeclaration(std::string newDeclaration)
    {
        declaration = newDeclaration;
    }

};