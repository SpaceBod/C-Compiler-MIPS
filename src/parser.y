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
  const Statement *stat;
  const StatementList *statlist;
  const Expression *expr;
  const DeclarationList *decllist;
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
%type <expr> EXPR CONDITIONAL_EXPR LOR_EXPR LAND_EXPR EQUAL_EXPR RELATION_EXPR ARITHMETIC_EXPR TERM_EXPR UNARY_EXPR FACTOR_EXPR
%type <statlist> STAT_LIST
%type <decllist> DECLARATION_LIST
%type <str> T_INT T_VAR
%type <var> DECLARATION
%type <T_type> TYPE_DEF

%start PROGRAM

%%

PROGRAM             : FUNCTION                                                      { g_root = $1; }

FUNCTION            : TYPE_DEF T_VAR T_LPAREN T_RPAREN COMPOUND_STAT                { $$ = new Function((new Variable($1, $2)), $5); }

STAT                : COMPOUND_STAT                                                 { $$ = $1; }
                    | EXPRESSION_STAT                                               { $$ = $1; }
                    | SELECTION_STAT                                                { $$ = $1; }
                    | ITERATION_STAT                                                { $$ = $1; }
                    | JUMP_STAT                                                     { $$ = $1; }

COMPOUND_STAT       : T_LBRACE T_RBRACE                                             { $$ = new Compound_Stat()      ; }
                    | T_LBRACE STAT_LIST T_RBRACE                                   { $$ = new Compound_Stat($2)    ; }
                    | T_LBRACE DECLARATION_LIST T_RBRACE                            { $$ = new Compound_Stat($2)    ; }
                    | T_LBRACE DECLARATION_LIST STAT_LIST T_RBRACE                  { $$ = new Compound_Stat($2, $3); }

EXPRESSION_STAT     : T_SEMI                                                        { $$ = new Expression_Stat()  ; }
                    | EXPR T_SEMI                                                   { $$ = new Expression_Stat($1); }

SELECTION_STAT      : T_IF T_LPAREN EXPR T_RPAREN STAT                              { $$ = new If_Stat($3, $5)    ; }
                    | T_IF T_LPAREN EXPR T_RPAREN STAT T_ELSE STAT                  { $$ = new If_Stat($3, $5, $7); }

ITERATION_STAT      : T_WHILE T_LPAREN EXPR T_RPAREN STAT                           { $$ = new While_Stat($3, $5)  ; }
                    | T_FOR T_LPAREN EXPR T_SEMI EXPR T_SEMI EXPR T_RPAREN STAT     { $$ = new For_Stat($3, $5, $7); }
                    | T_FOR T_LPAREN DECLARATION EXPR T_SEMI EXPR T_RPAREN STAT     { $$ = new For_Stat($3, $5, $7); }

JUMP_STAT           : T_RETURN T_SEMI                                               { $$ = new Jump_Stat()  ; }
                    | T_RETURN EXPR T_SEMI                                          { $$ = new Jump_Stat($2); }

%%

const Expression *g_root; // Definition of variable (to match declaration earlier)

const Expression *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}

