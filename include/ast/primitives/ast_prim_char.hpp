#ifndef ast_prim_char_hpp
#define ast_prim_char_hpp

#include <string>
#include <iostream>

#include "../ast_symtab.hpp"
#include "../ast_primitives.hpp"
#include "../ast_expressions.hpp"

class Char
    : public Expr
{
private:
    char character;
    std::string Chars;

public:
    Char(const std::string *input)
    {
        character = (*input)[1];
    }
    char getValue() const
    {
        return character;
    }
    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << character;
    }
    virtual const std::string returnData() const override
    {
        return "CHAR";
    }
    virtual void Translate2MIPS(std::string destReg) const override
    {
        std::cout << "li " << destReg << ", " << (int)character << std::endl;
    }
};

#endif