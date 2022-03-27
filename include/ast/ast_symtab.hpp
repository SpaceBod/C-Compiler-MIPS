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

    void setLabel(bool n)
    {
        label = n;
    }

    int returnArgCount()
    {
        return argCount;
    }

    void setArgCount(int _argCount)
    {
        argCount = _argCount;
    }

    int returnArgSize()
    {
        return argSize;
    }

    void setArgSize(int n)
    {
        argSize = n;
    }

    int returnIncrement()
    {
        return increment;
    }

    void setIncrement(int _increment)
    {
        increment = _increment;
    }

    int returnEnumerate()
    {
        return enumerate;
    }

    void setEnumerate(int _enumerate)
    {
        enumerate = _enumerate;
    }
};