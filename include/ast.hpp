#ifndef ast_hpp
#define ast_hpp

#include "ast/ast_expressions.hpp"
#include "ast/ast_functions.hpp"
#include "ast/ast_primitives.hpp"
#include "ast/ast_operators.hpp"
#include "ast/ast_statements.hpp"
#include "ast/ast_unary.hpp"
#include "ast/ast_symtab.hpp"

#include "ast/primitives/ast_prim_sizeof.hpp"
#include "ast/primitives/ast_prim_array.hpp"
#include "ast/primitives/ast_prim_pointer.hpp"
#include "ast/primitives/ast_prim_char.hpp"
#include "ast/primitives/ast_prim_storefunc.hpp"
#include "ast/primitives/ast_prim_number.hpp"

#include "ast/statements/ast_stat_iteration.hpp"
#include "ast/statements/ast_stat_if.hpp"
#include "ast/statements/ast_stat_switch.hpp"

#include "ast/operators/ast_op_add.hpp"
#include "ast/operators/ast_op_sub.hpp"
#include "ast/operators/ast_op_mult.hpp"
#include "ast/operators/ast_op_div.hpp"
#include "ast/operators/ast_op_mod.hpp"

extern const Main *parseAST(FILE *fileInput);
// extern const Main *parseAST();
extern SymTabADT SymTab;
extern StackPtr StkPtr;

#endif
