#ifndef ast_stacks_hpp
#define ast_stacks_hpp

#include <cassert>

class StackPtr
{
private:
    int incr;
    int argc;
    int scopeincr[50];
    int current_scope = 0;
    int nullfunc = 0;
    int freturn = 0;

public:
    StackPtr()
    {
    }

    int getIncrement()
    {
        return incr;
    }

    void setIncrement(int _incr)
    {
        incr = _incr;
    }

    int returnScopeIncrement()
    {
        return scopeincr[current_scope];
    }

    int returnScopeIncrement(int scope)
    {
        return scopeincr[scope];
    }

    void setScopeIncrement(int _scopeincr)
    {
        scopeincr[current_scope] = _scopeincr;
    }

    int returnScopeCurrent()
    {
        return current_scope;
    }

    void setScopeCurrent(int _current_scope)
    {
        current_scope = _current_scope;
    }

    int returnArgCount()
    {
        return argc;
    }

    void setArgCount(int _argc)
    {
        argc = _argc;
    }

    int returnNullFunc()
    {
        return nullfunc;
    }

    void setNullFunc(int _nullfunc)
    {
        nullfunc = _nullfunc;
    }

    int getfreturn()
    {
        return freturn;
    }

    void setReturnFunc(int _freturn)
    {
        freturn = _freturn;
    }
};

#endif