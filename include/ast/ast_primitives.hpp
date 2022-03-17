#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>

enum TypeDef{
  INT,
  DOUBLE,
  FLOAT
};

class Variable
    : public Expression
{
private:
    std::string id;
    std::string type;
    ExpressionPtr Expr;
public:
    Variable() {}

    Variable(TypeDef _type, const std::string *_id, ExpressionPtr _Expr = nullptr) {
        switch(_type) {
            case INT:
                type = "INT";
                Expr = _Expr;
                id = *_id;
                break;
            case DOUBLE:
                type = "DOUBLE";
                Expr = _Expr;
                id = *_id;
                break;
            case FLOAT:
                type = "FLOAT";
                Expr = _Expr;
                id = *_id;
                break;
            default:
                type = "UNDEFINED";
        }
    }

    const std::string getId() const
    { return id; }

    const std::string getType() const
    { return type; }

    ExpressionPtr getExpr() const
    { return Expr; }

    virtual void pretty_print(std::ostream &dst) const override
    {
        dst<<type;
        dst<<" ";
        dst<<id;
        if(Expr!=nullptr){
            dst<<" = ";
            Expr->pretty_print(dst);
            dst<<";";
            dst<<'\n';
        }
    }

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        return bindings.at(id);
    }    
};

class Number
    : public Expression
{
private:
    double value;
public:
    Number(double _value)
        : value(_value)
    {}

    double getValue() const
    { return value; }
    

    virtual void pretty_print(std::ostream &dst) const override
    {
        dst<<value;
    }

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        return value;
    }
};

class Decl_list;

typedef const Decl_list *Decl_listPtr;

class Decl_list
    : public Variable
{
private:
    Variable *variable;
    Decl_listPtr decl_List;
public:
    Decl_list(Variable *_variable, Decl_listPtr _declarationList = nullptr)
        : variable(_variable)
        , decl_List(_declarationList)
    {}

    virtual ~Decl_list() {
        delete variable;
        delete decl_List;
    }
    Variable *getVar() const
    { return variable; }
    Decl_listPtr getdecllist() const
    { return decl_List; }

    virtual void pretty_print(std::ostream &dst) const override
    {
        variable->pretty_print(dst);
        if(decl_List!=nullptr){
            decl_List->pretty_print(dst);
        }
    }
  
};

#endif