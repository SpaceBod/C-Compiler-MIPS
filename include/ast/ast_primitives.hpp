#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>

enum VarType
{
    INT,
    DOUBLE,
    FLOAT
};

enum DecType{
    CALL,
    ASSIGN,
    DECLARATION
};

class Variable
    : public Expression
{
private:
    std::string var_name;
    std::string type;
    ExpressionPtr Expr;
    DecType Dec_type;
    std::string assign_type;
    std::string address;
    //to do address 

public:
    Variable()
    {
    }

    Variable(const std::string *_var_name)
    {
        var_name = *_var_name;
    }

    Variable(VarType _type, const std::string *_var_name, ExpressionPtr _Expr = nullptr)
    {
        switch (_type)
        {
        case INT:
            type = "int";
            Expr = _Expr;
            var_name = *_var_name;
            break;
        case DOUBLE:
            type = "double";
            Expr = _Expr;
            var_name = *_var_name;
            break;
        case FLOAT:
            type = "float";
            Expr = _Expr;
            var_name = *_var_name;
            break;
        default:
            type = "UNDEFINED";
        }
    }

    const std::string getVar_name() const
    {
        return var_name;
    }

    const std::string getType() const
    {
        return type;
    }

    ExpressionPtr getExpr() const
    {
        return Expr;
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        switch(Dec_type){ 
        case CALL:
            dst<<var_name;
            break;
        case ASSIGN:
            dst<<var_name;
            dst<<" ";
            dst<<assign_type;
            dst<<" ";
            Expr ->pretty_print(dst);

            break;        
        case DECLARATION:
            dst << type;
            dst << " ";
            dst << var_name;
            if (Expr != nullptr)
            {
                dst << " = ";
                Expr->pretty_print(dst);
            }            
            dst << ";";
            dst << '\n';
            break;
        
        }

    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        return bindings.at(var_name);
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
    switch(Dec_type){
        case CALL:
            std::cout<<"addi $t0, $0, "<< address <<std::endl;
            break;
        case ASSIGN:
                    if(assign_type == "="){
                    getExpr()->Translate2MIPS("$t1");
                    std::cout << "addi $t0, $0, " << address << std::endl;
                    std::cout << "sw $t1, 0($t0)" << std::endl;
                }else if(assign_type == "+="){
                    getExpr()->Translate2MIPS("$t1");
                    std::cout << "addi $t0, $0, " << address << std::endl;
                    std::cout << "lw $t2, 0($t0)" << std::endl;
                    std::cout << "add $t2, $t2, $t1" << std::endl;
                    std::cout << "sw $t2, 0($t0)" << std::endl;
                }else if(assign_type == "-="){
                    getExpr()->Translate2MIPS("$t1");
                    std::cout << "addi $t0, $0, " << address << std::endl;
                    std::cout << "lw $t2, 0($t0)" << std::endl;
                    std::cout << "sub $t2, $t2, $t1" << std::endl;
                    std::cout << "sw $t2, 0($t0)" << std::endl;
                }else if(assign_type == "/="){
                    getExpr()->Translate2MIPS("$t1");
                    std::cout << "addi $t0, $0, " << address << std::endl;
                    std::cout << "lw $t2, 0($t0)" << std::endl;
                    std::cout << "div $t2, $t1" << std::endl;
                    std::cout << "mfhi $t2" << std::endl;
                    std::cout << "sw $t2, 0($t0)" << std::endl;
                }else if(assign_type == "*="){
                    getExpr()->Translate2MIPS("$t1");
                    std::cout << "addi $t0, $0, " << address << std::endl;
                    std::cout << "lw $t2, 0($t0)" << std::endl;
                    std::cout << "mul $t2, $t2, $t1" << std::endl;
                    std::cout << "sw $t2, 0($t0)" << std::endl;
                }else if(assign_type == "%="){

                }else if(assign_type == "<<="){

                }else if(assign_type == ">>="){

                }else if(assign_type == "^="){

                }else if(assign_type == "^="){

                }
                break;
        case DECLARATION:
                if(getType()=="INT"){
                    if(Expr!=nullptr){
                        getExpr()->Translate2MIPS("$t1");
                        std::cout << "addi $t0, $0, " << address << std::endl;
                        std::cout << "sw $t1, 0($t0)" << std::endl;
                    }
                }
                break;
    }
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
    {
    }

    double getValue() const
    {
        return value;
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << value;
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        return value;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        std::cout << "addi " << destReg << " $0 " << value << std::endl;
    }
};

class Decl_list;

typedef const Decl_list *DeclarationListPtr;

class Decl_list
    : public Variable
{
private:
    Variable *variable;
    DeclarationListPtr declarationList = nullptr;
public:
    Decl_list(Variable *_variable, DeclarationListPtr _declarationList = nullptr)
        : variable(_variable)
        , declarationList(_declarationList)
    {}

    virtual ~Decl_list() {
        delete variable;
        delete declarationList;
    }
    Variable *getVar() const
    { return variable; }

    DeclarationListPtr getdecllist() const
    { return declarationList; }

    virtual void pretty_print(std::ostream &dst) const override
    {
        variable->pretty_print(dst);
        if(declarationList!=nullptr){
            dst << ", ";
            declarationList->pretty_print(dst);
        }
    }

    virtual void Translate2MIPS(std::string destReg) const override{
        getVar()->Translate2MIPS(destReg);
        if(declarationList!=nullptr){
            getdecllist()->Translate2MIPS(destReg);
        }
    }  
  
};

#endif
