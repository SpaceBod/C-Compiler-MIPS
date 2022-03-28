#ifndef ast_operators_hpp
#define ast_operators_hpp

#include <string>
#include <iostream>
#include <cmath>

#include "ast/ast_symtab.hpp"

class Operator
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr right;

protected:
    Operator(ExpressionPtr _left, ExpressionPtr _right)
        : left(_left), right(_right)
    {
    }

public:
    virtual ~Operator()
    {
        delete left;
        delete right;
    }

    virtual const char *getOpcode() const = 0;

    ExpressionPtr return_left() const
    {
        return left;
    }

    ExpressionPtr return_right() const
    {
        return right;
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << "( ";
        left->pretty_print(dst);
        dst << " ";
        dst << getOpcode();
        dst << " ";
        right->pretty_print(dst);
        dst << " )";
    }
};

// Arithmetic Operators

class AddOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "+";
    }

public:
    AddOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {

        double vl = return_left()->evaluate(bindings);
        double vr = return_right()->evaluate(bindings);
        return vl + vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        return_left()->Translate2MIPS("$t0");
        std::cout << "sw $t0, 4($sp)" << std::endl;
        return_right()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 4($sp)" << std::endl;
        std::cout << "add " << destReg << ", $t0, $t1" << std::endl;
    }
};

class SubOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "-";
    }

public:
    SubOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = return_left()->evaluate(bindings);
        double vr = return_right()->evaluate(bindings);
        return vl - vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        return_left()->Translate2MIPS("$t0");
        std::cout << "sw $t0, 4($sp)" << std::endl;
        return_right()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 4($sp)" << std::endl;
        std::cout << "sub " << destReg << ", $t0, $t1" << std::endl;
        }
};

class MulOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "*";
    }

public:
    MulOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = return_left()->evaluate(bindings);
        double vr = return_right()->evaluate(bindings);
        return vl * vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        return_left()->Translate2MIPS("$t0");
        std::cout << "sw $t0, 4($sp)" << std::endl;
        return_right()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 4($sp)" << std::endl;
        std::cout << "mul " << destReg << ", $t0, $t1" << std::endl;
    }
};

class DivOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "/";
    }

public:
    DivOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = return_left()->evaluate(bindings);
        double vr = return_right()->evaluate(bindings);
        return vl / vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        return_left()->Translate2MIPS("$t0");
        std::cout << "sw $t0, 4($sp)" << std::endl;
        return_right()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 4($sp)" << std::endl;
        std::cout << "div $t0, $t1" << std::endl;
        std::cout << "mfhi " << destReg << std::endl;
    }
};

class ModOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "%";
    }

public:
    ModOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        int vl = return_left()->evaluate(bindings);
        int vr = return_right()->evaluate(bindings);
        return vl % vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        return_left()->Translate2MIPS("$t0");
        std::cout << "sw $t0, 4($sp)" << std::endl;
        return_right()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 4($sp)" << std::endl;
        std::cout << "div $t0, $t1" << std::endl;
        std::cout << "mflo " << destReg << std::endl;
    }
};

// Comparitive Operators

class GreaterThanOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return ">";
    }

public:
    GreaterThanOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = return_left()->evaluate(bindings);
        double vr = return_right()->evaluate(bindings);
        return vl > vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        return_left()->Translate2MIPS("$t0");
        std::cout << "sw $t0, 4($sp)" << std::endl;
        return_right()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 4($sp)" << std::endl;
        std::cout << "slt " << destReg << ", $t1, $t0" << std::endl;
    }
};

class LessThanOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "<";
    }

public:
    LessThanOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = return_left()->evaluate(bindings);
        double vr = return_right()->evaluate(bindings);
        return vl < vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
       return_left()->Translate2MIPS("$t0");
        std::cout << "sw $t0, 4($sp)" << std::endl;
        return_right()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 4($sp)" << std::endl;
        std::cout << "slt " << destReg << ", $t0, $t1" << std::endl;
    }
};

class GreaterOrEqualThanOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return ">=";
    }

public:
    GreaterOrEqualThanOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = return_left()->evaluate(bindings);
        double vr = return_right()->evaluate(bindings);
        return vl >= vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        return_left()->Translate2MIPS("$t0");
        std::cout << "sw $t0, 4($sp)" << std::endl;
        return_right()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 4($sp)" << std::endl;
        std::string set_one = makeName("set_one");
        std::cout << "beq $t0, $t1, " << set_one << std::endl;
        std::cout << "slt " << destReg << ", $t1, $t0" << std::endl;
        std::string exit = makeName("exit");
        std::cout << "jump " << exit << std::endl;
        std::cout << ":" << set_one << std::endl;
        std::cout << "addi " << destReg << ", $0, 1" << std::endl;
        std::cout << ":" << exit << std::endl;
    }
};

class LessOrEqualThanOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "=<";
    }

public:
    LessOrEqualThanOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = return_left()->evaluate(bindings);
        double vr = return_right()->evaluate(bindings);
        return vl <= vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        return_left()->Translate2MIPS("$t0");
        std::cout << "sw $t0, 4($sp)" << std::endl;
        return_right()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 4($sp)" << std::endl;
        std::string set_one = makeName("set_one");
        std::cout << "beq $t0, $t1, " << set_one << std::endl;
        std::cout << "slt " << destReg << ", $t0, $t1" << std::endl;
        std::string exit = makeName("exit");
        std::cout << "jump " << exit << std::endl;
        std::cout << ":" << set_one << std::endl;
        std::cout << "addi " << destReg << ", $0, 1" << std::endl;
        std::cout << ":" << exit << std::endl;
    }
};

class EqualOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "==";
    }

public:
    EqualOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = return_left()->evaluate(bindings);
        double vr = return_right()->evaluate(bindings);
        return vl == vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
         return_left()->Translate2MIPS("$t0");
        std::cout << "sw $t0, 4($sp)" << std::endl;
        return_right()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 4($sp)" << std::endl;
        std::string set_one = makeName("set_one");
        std::cout << "beq $t0, $t1, " << set_one << std::endl;
        std::cout << "add " << destReg << ", $0, $0" << std::endl;
        std::string exit = makeName("exit");
        std::cout << "jump " << exit << std::endl;
        std::cout << ":" << set_one << std::endl;
        std::cout << "addi " << destReg << ", $0, 1" << std::endl;
        std::cout << ":" << exit << std::endl;
    }
};

class NotEqualOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "!=";
    }

public:
    NotEqualOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = return_left()->evaluate(bindings);
        double vr = return_right()->evaluate(bindings);
        return vl != vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        return_left()->Translate2MIPS("$t0");
        std::cout << "sw $t0, 4($sp)" << std::endl;
        return_right()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 4($sp)" << std::endl;
        std::string set_one = makeName("set_one");
        std::cout << "bne $t0, $t1, " << set_one << std::endl;
        std::cout << "add " << destReg << ", $0, $0" << std::endl;
        std::string exit = makeName("exit");
        std::cout << "jump " << exit << std::endl;
        std::cout << ":" << set_one << std::endl;
        std::cout << "addi " << destReg << ", $0, 1" << std::endl;
        std::cout << ":" << exit << std::endl;
    }
};

// Logic Operators

class LogicAnd
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "&&";
    }

public:
    LogicAnd(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = return_left()->evaluate(bindings);
        double vr = return_right()->evaluate(bindings);
        return vl && vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        return_left()->Translate2MIPS("$t0");
        std::cout << "sw $t0, 4($sp)" << std::endl;
        return_right()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 4($sp)" << std::endl;
        std::string set_zero = makeName("set_zero");
        std::cout << "beq $t0, $0, " << set_zero << std::endl;
        std::cout << "beq $t1, $0, " << set_zero << std::endl;
        std::cout << "addi " << destReg << ", $0, 1" << std::endl;
        std::string exit = makeName("exit");
        std::cout << "jump " << exit << std::endl;
        std::cout <<  set_zero <<":" << std::endl;
        std::cout << "add " << destReg << ", $0, $0" << std::endl;
        std::cout <<  exit <<":" << std::endl;
    }
};

class BitAnd
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "&";
    }

public:
    BitAnd(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        int vl = return_left()->evaluate(bindings);
        int vr = return_right()->evaluate(bindings);
        return vl & vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        return_left()->Translate2MIPS("$t0");
        std::cout << "sw $t0, 4($sp)" << std::endl;
        return_right()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 4($sp)" << std::endl;
        std::cout << "and " << destReg << ", $t0, $t1" << std::endl;
    }
};

class LogicOr
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "||";
    }

public:
    LogicOr(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double vl = return_left()->evaluate(bindings);
        double vr = return_right()->evaluate(bindings);
        return vl || vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        return_left()->Translate2MIPS("$t0");
        std::cout << "sw $t0, 4($sp)" << std::endl;
        return_right()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 4($sp)" << std::endl;
        std::string set_one = makeName("set_one");
        std::cout << "bne $t0, $0, " << set_one << std::endl;
        std::cout << "bne $t1, $0, " << set_one << std::endl;
        std::cout << "add " << destReg << ", $0, $0" << std::endl;
        std::string exit = makeName("exit");
        std::cout << "jump " << exit << std::endl;
        std::cout << set_one << ":" <<  std::endl;
        std::cout << "addi " << destReg << ", $0, 1" << std::endl;
        std::cout <<exit << ":" <<  std::endl;
    }
};

class BitOr
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "|";
    }

public:
    BitOr(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        int vl = return_left()->evaluate(bindings);
        int vr = return_right()->evaluate(bindings);
        return vl | vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        return_left()->Translate2MIPS("$t0");
        std::cout << "sw $t0, 4($sp)" << std::endl;
        return_right()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 4($sp)" << std::endl;
        std::cout << "or " << destReg << ", $t0, $t1" << std::endl;
    }
};

class BitXOr
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {
        return "^";
    }

public:
    BitXOr(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        int vl = return_left()->evaluate(bindings);
        int vr = return_right()->evaluate(bindings);
        return vl ^ vr;
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        return_left()->Translate2MIPS("$t0");
        std::cout << "sw $t0, 4($sp)" << std::endl;
        return_right()->Translate2MIPS("$t1");
        std::cout << "lw $t0, 4($sp)" << std::endl;
        std::cout << "xor " << destReg << ", $t0, $t1" << std::endl;
    }
};

#endif