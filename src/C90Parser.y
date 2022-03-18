%code requires{
  #include "ast.hpp"
  #include <cassert>

  extern const Function *g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  const Function *func;
  const Stat *stat;
  const Stat_list *statlist;
  const Expression *expr;
  const Decl_list *decllist;
  double number;
  Variable *var;
  std::string *str;
  TypeDef T_type;
}

%token T_VARIABLE T_NUMBER
%token T_GT T_LT T_GTE T_LTE T_EQUAL T_NEQUAL
%token T_LOR T_BOR T_LAND T_BAND T_BXOR 
%token T_SUB T_ADD T_MULT T_DIV T_MOD T_NOT
%token T_ASSIGN T_SEMI T_COMMA
%token T_LBRACE T_RBRACE T_LPAREN T_RPAREN
%token T_INT_TYPE T_RETURN T_WHILE T_IF T_ELSE T_FOR

%type <func> FUNCTION
%type <stat> STAT COMPOUND_STAT EXPRESSION_STAT SELECTION_STAT ITERATION_STAT JUMP_STAT
%type <expr> EXPR CONDITIONAL_EXPR LOR_EXPR LAND_EXPR BOR_EXPR BAND_EXPR BXOR_EXPR EQUAL_EXPR RELATION_EXPR ARITHMETIC_EXPR TERM_EXPR UNARY_EXPR FACTOR_EXPR
%type <statlist> STAT_LIST
%type <number> T_NUMBER
%type <decllist> DECLARATION_LIST
%type <str> T_INT_TYPE T_VARIABLE
%type <var> DECLARATION
%type <T_type> TYPE_DEF

%start PROGRAM

%%

PROGRAM             : FUNCTION                                                      { g_root = $1; }

FUNCTION            : TYPE_DEF T_VARIABLE T_LPAREN T_RPAREN COMPOUND_STAT           { $$ = new Function((new Variable($1, $2)), $5); }

DECLARATION_LIST    : DECLARATION                                                   { $$ = new Decl_list($1)    ; }
                    | DECLARATION  DECLARATION_LIST                                 { $$ = new Decl_list($1, $2); }

STAT_LIST           : STAT                                                          { $$ = new Stat_list($1)    ; }
                    | STAT STAT_LIST                                                { $$ = new Stat_list($1, $2); }

DECLARATION         : TYPE_DEF T_VARIABLE T_SEMI                                    { $$ = new Variable($1, $2); }
                    | TYPE_DEF T_VARIABLE T_ASSIGN EXPR T_SEMI                      { $$ = new Variable($1, $2, $4); }

STAT                : COMPOUND_STAT                                                 { $$ = $1; }
                    | EXPRESSION_STAT                                               { $$ = $1; }
                    | SELECTION_STAT                                                { $$ = $1; }
                    | ITERATION_STAT                                                { $$ = $1; }
                    | JUMP_STAT                                                     { $$ = $1; }

COMPOUND_STAT       : T_LBRACE T_RBRACE                                             { $$ = new Comp_Stat()      ; }
                    | T_LBRACE STAT_LIST T_RBRACE                                   { $$ = new Comp_Stat($2)    ; }
                    | T_LBRACE DECLARATION_LIST T_RBRACE                            { $$ = new Comp_Stat($2)    ; }
                    | T_LBRACE DECLARATION_LIST STAT_LIST T_RBRACE                  { $$ = new Comp_Stat($2, $3); }

EXPRESSION_STAT     : T_SEMI                                                        { $$ = new Expression_Stat()  ; }
                    | EXPR T_SEMI                                                   { $$ = new Expression_Stat($1); }

SELECTION_STAT      : T_IF T_LPAREN EXPR T_RPAREN STAT                              { $$ = new If_Stat($3, $5)    ; }
                    | T_IF T_LPAREN EXPR T_RPAREN STAT T_ELSE STAT                  { $$ = new If_Stat($3, $5, $7); }

ITERATION_STAT      : T_WHILE T_LPAREN EXPR T_RPAREN STAT                           { $$ = new While_Stat($3, $5)      ; }
                    | T_FOR T_LPAREN EXPR T_SEMI EXPR T_SEMI EXPR T_RPAREN STAT     { $$ = new For_Stat($3, $5, $7, $9); }
                    | T_FOR T_LPAREN DECLARATION EXPR T_SEMI EXPR T_RPAREN STAT     { $$ = new For_Stat($3, $4, $6, $8); }

JUMP_STAT           : T_RETURN T_SEMI                                               { $$ = new Jump_Stat()  ; }
                    | T_RETURN EXPR T_SEMI                                          { $$ = new Jump_Stat($2); }

EXPR                : CONDITIONAL_EXPR                                              { $$ = $1; }
                    | T_VARIABLE T_ASSIGN EXPR                                      {          }

CONDITIONAL_EXPR    : LOR_EXPR                                                      { $$ = $1; }

LOR_EXPR            : LAND_EXPR                                                     { $$ = $1                 ; }
                    | LOR_EXPR T_LOR LAND_EXPR                                      { $$ = new LogicOr($1, $3); }

LAND_EXPR           : BOR_EXPR                                                    { $$ = $1                  ; }
                    | LAND_EXPR T_LAND EQUAL_EXPR                                   { $$ = new LogicAnd($1, $3); }

BOR_EXPR            : BXOR_EXPR                                                     { $$ = $1; }
                    | BOR_EXPR T_BOR BXOR_EXPR                                      { $$ = new BitOr($1, $3); }

BAND_EXPR           : EQUAL_EXPR                                                    { $$ = $1                ; }
                    | BAND_EXPR T_BAND EQUAL_EXPR                                   { $$ = new BitAnd($1, $3); }

BXOR_EXPR           : BAND_EXPR                                                     { $$ = $1; }
                    | BXOR_EXPR T_BXOR BAND_EXPR                                    { $$ = new BitXOr($1, $3); }

EQUAL_EXPR          : RELATION_EXPR                                                 { $$ = $1                          ; }
                    | EQUAL_EXPR T_EQUAL RELATION_EXPR                              { $$ = new EqualOperator($1, $3)   ; }
                    | EQUAL_EXPR T_NEQUAL RELATION_EXPR                             { $$ = new NotEqualOperator($1, $3); }
                  
RELATION_EXPR       : ARITHMETIC_EXPR                                               { $$ = $1                                    ; }
                    | RELATION_EXPR T_GT ARITHMETIC_EXPR                            { $$ = new GreaterThanOperator($1, $3)       ; }
                    | RELATION_EXPR T_LT ARITHMETIC_EXPR                            { $$ = new LessThanOperator($1, $3)          ; }
                    | RELATION_EXPR T_GTE ARITHMETIC_EXPR                           { $$ = new GreaterOrEqualThanOperator($1, $3); }
                    | RELATION_EXPR T_LTE ARITHMETIC_EXPR                           { $$ = new LessOrEqualThanOperator($1, $3)   ; }

ARITHMETIC_EXPR     : TERM_EXPR                                                     { $$ = $1                     ; }
                    | ARITHMETIC_EXPR T_ADD TERM_EXPR                               { $$ = new AddOperator($1, $3); }
                    | ARITHMETIC_EXPR T_SUB TERM_EXPR                               { $$ = new SubOperator($1, $3); }

TERM_EXPR           : UNARY_EXPR                                                    { $$ = $1                     ; }
                    | TERM_EXPR T_MULT UNARY_EXPR                                   { $$ = new MulOperator($1, $3); }
                    | TERM_EXPR T_DIV UNARY_EXPR                                    { $$ = new DivOperator($1, $3); }
                    | TERM_EXPR T_MOD UNARY_EXPR                                    { $$ = new ModOperator($1, $3); }

UNARY_EXPR          : FACTOR_EXPR                                                   { $$ = $1                 ; }
                    | T_SUB FACTOR_EXPR                                             { $$ = new NegOperator($2); }
                    | T_NOT FACTOR_EXPR                                             { $$ = new NotOperator($2)   ; }

FACTOR_EXPR         : T_NUMBER                                                      { $$ = new Number($1)  ; }
                    | T_VARIABLE                                                    { $$ = new Variable($1); }
                    | T_LPAREN EXPR T_RPAREN                                        { $$ = $2              ; }

TYPE_DEF            : T_INT_TYPE                                                    { $$ = TypeDef::INT; }

%%

const Function *g_root;

const Function *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
