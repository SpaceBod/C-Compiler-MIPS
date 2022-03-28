#ifndef ast_hpp
#define ast_hpp

#include "ast/ast_expressions.hpp"
#include "ast/ast_primitives.hpp"
#include "ast/ast_operators.hpp"
#include "ast/ast_unary.hpp"
#include "ast/ast_functions.hpp"
#include "ast/ast_statements.hpp"
#include "ast/ast_symtab.hpp"
#include "ast/ast_nodes.hpp"
#include "ast/ast_stackptr.hpp"

extern const Function *parseAST(FILE *fileInput);
extern SymTab SymbolTable;
extern StackPtr StackPointer;

#endif