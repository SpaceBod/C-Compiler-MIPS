#ifndef ast_hpp
#define ast_hpp

#include "ast/ast_expressions.hpp"
#include "ast/ast_primitives.hpp"
#include "ast/ast_operators.hpp"
#include "ast/ast_unary.hpp"
#include "ast/ast_functions.hpp"
#include "ast/ast_statements.hpp"

extern const Expression *parseAST();

#endif