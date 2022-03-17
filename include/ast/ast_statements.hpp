#ifndef ast_statements_hpp
#define ast_statements_hpp

#include "ast_expressions.hpp"
#include "ast_primitives.hpp"

class Stat;

typedef const Stat *StatPtr;

class Stat
{
public:
    virtual ~Stat() {}
    virtual void pretty_print(std::ostream &dst) const = 0;
};

class Stat_list;

typedef const Stat_list *Stat_listPtr;

class Stat_list
    : public Stat
{
private:
    StatPtr stat;
    Stat_listPtr stat_list;
public:
    Stat_list(StatPtr _stat, Stat_listPtr _stat_list = nullptr)
        : stat(_stat)
        , stat_list(_stat_list)
    {}
    virtual ~Stat_list() {
        delete stat;
        delete stat_list;
    }
    StatPtr return_Stat() const
    { return stat; }
    Stat_listPtr return_Stat_list() const
    { return stat_list; }
    virtual void pretty_print(std::ostream &dst) const override
    {
        stat->pretty_print(dst);
        if(stat_list!=nullptr){
            stat_list->pretty_print(dst);
        }
    }
};

class Select_Stat
    : public Stat
{
private:
    ExpressionPtr condition;
    StatPtr stat;
public:
    Select_Stat(ExpressionPtr _condition, StatPtr _stat = nullptr)
        : condition(_condition)
        , stat(_stat)
    {}
    virtual ~Select_Stat() {
        delete condition;
        delete stat;
    }
    ExpressionPtr getCond() const
    { return condition; }
    StatPtr return_Stat() const
    { return stat; }
    
};

class If_Stat
    : public Select_Stat
{
private:
    StatPtr else_branch;
public:
    If_Stat(ExpressionPtr _condition, StatPtr _if_branch = nullptr, StatPtr _else_branch = nullptr)
        : Select_Stat(_condition, _if_branch)
        , else_branch(_else_branch)
    {}
    ~If_Stat() {
        delete else_branch;
    }
    StatPtr getElse() const
    { return else_branch; }


    virtual void pretty_print(std::ostream &dst) const override
    {
        dst<<"if ( ";
        getCond()->pretty_print(dst);
        dst<<" ) ";
        return_Stat()->pretty_print(dst);
        if(else_branch!=nullptr) {
            dst<<"else ";
            else_branch->pretty_print(dst);
        }
        dst<<'\n';
    }
};

class Loop_Stat
    : public Stat
{
private:
    ExpressionPtr condition;
    StatPtr stat;
public:
    Loop_Stat() {}
    Loop_Stat(ExpressionPtr _condition, StatPtr _stat = nullptr)
        : condition(_condition)
        , stat(_stat)
    {}
    ~Loop_Stat() {
        delete condition;
        delete stat;
    }
    ExpressionPtr getCond() const
    { return condition; }
    StatPtr return_Stat() const
    { return stat; }
};

class While_loop
    : public Loop_Stat
{
public:
    While_loop(ExpressionPtr _condition, StatPtr _stat = nullptr)
        : Loop_Stat(_condition, _stat)
    {}

    virtual void pretty_print(std::ostream &dst) const override
    {
        dst<<"while ( ";
        getCond()->pretty_print(dst);
        dst<<" ) ";
        return_Stat()->pretty_print(dst);
        dst<<'\n';
    }
};

class For_loop
    : public Loop_Stat
{
private:
    Variable *initVar = nullptr;
    ExpressionPtr initExpr = nullptr;
    ExpressionPtr checkExpr;
    ExpressionPtr updateExpr;
    StatPtr stat;
public:
    For_loop(ExpressionPtr _initExpr, ExpressionPtr _checkExpr, ExpressionPtr _updateExpr, StatPtr _stat)
     : initExpr(_initExpr)
     , checkExpr(_checkExpr)
     , updateExpr(_updateExpr)
     , stat(_stat)
    {}
    For_loop(Variable *_initVar, ExpressionPtr _checkExpr, ExpressionPtr _updateExpr, StatPtr _stat)
    : initVar(_initVar)
    , checkExpr(_checkExpr)
    , updateExpr(_updateExpr)
    , stat(_stat)
    {}
    ~For_loop() {
        delete initVar;
        delete initExpr;
        delete checkExpr;
        delete updateExpr;
        delete stat;
    }
    virtual void pretty_print(std::ostream &dst) const override
    {
        dst<<"for ( ";
        if(initVar != nullptr && initExpr == nullptr) {
            initVar->pretty_print(dst);
        }
        else if(initVar == nullptr && initExpr != nullptr) {
            initExpr->pretty_print(dst);
        }
        dst<<" ; ";
        checkExpr->pretty_print(dst);
        dst<<" ; ";
        updateExpr->pretty_print(dst);
        dst<<" ) \n";
        return_Stat()->pretty_print(dst);
    }
};

class Expression_Stat
    : public Stat
{
private:
    ExpressionPtr expression;
public:
    Expression_Stat(ExpressionPtr _expression = nullptr)
        : expression(_expression)
    {}
    ~Expression_Stat() {
        delete expression;
    }
    ExpressionPtr getExp() const
    { return expression; }
    virtual void pretty_print(std::ostream &dst) const override
    {
        if(expression!=nullptr){
            expression->pretty_print(dst);
        }
        dst<<";";
        dst<<'\n';
    }
};

class Jump_Stat
    : public Stat
{
private:
    ExpressionPtr expression;
public:
    Jump_Stat(ExpressionPtr _expression = nullptr)
        : expression(_expression)
    {}
    ~Jump_Stat() {
        delete expression;
    }
    ExpressionPtr getExp() const
    { return expression; }
    virtual void pretty_print(std::ostream &dst) const override
    {
        dst<<"return ";
        if(expression!=nullptr){
            expression->pretty_print(dst);
        }
        dst<<";";
        dst<<'\n';
    }
};

#endif