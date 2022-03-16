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

    virtual void print(std::ostream &dst) const override
    {
        dst<<id;
        dst<<" -> ";
        dst<<type;
        if(Expr!=nullptr){
            dst<<" = ";
            Expr->print(dst);
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
    

    virtual void print(std::ostream &dst) const override
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


#endif