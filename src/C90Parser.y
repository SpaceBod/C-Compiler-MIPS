%code requires{
  #include "ast.hpp"

  #include <cassert>

  extern const Main *g_root; // A way of getting the AST out
  extern FILE* yyin;
  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  Main *main;
  Function *function;
  const Stat *stat;
  const Expr *expr;
  const StatList *statList;
  const DecList *decllist;
  const ExprList *arglist;
  Identifier *variable;
  Array *array;
  double number;
  std::string *string;
  VarTypeDef T_type;
}

%token T_NUMBER_INT T_NUMBER_DOUBLE T_VARIABLE T_CHARS
%token T_MULT T_DIV T_ADD T_SUB T_MOD
%token T_GT T_LT T_GTE T_LTE T_EQUAL T_NEQUAL
%token T_LSHIFT T_RSHIFT
%token T_BAND T_BOR T_BXOR
%token T_NOT T_LAND T_LOR
%token T_COLON T_SEMI T_COMMA T_INCR T_DECR
%token T_ASSIGN T_ADD_ASSIGN T_SUB_ASSIGN T_DIV_ASSIGN T_MULT_ASSIGN T_MOD_ASSIGN T_LSHIFT_ASSIGN T_RSHIFT_ASSIGN T_AND_ASSIGN T_XOR_ASSIGN T_OR_ASSIGN
%token T_LBRACE T_RBRACE T_LPAREN T_RPAREN T_LSQUARE T_RSQUARE
%token T_INT T_FLOAT T_DOUBLE T_CHAR T_RETURN T_WHILE T_IF T_ELSE T_FOR T_SWITCH T_CONTINUE T_BREAK T_CASE T_DEFAULT T_ENUM
%token T_SIZEOF

%type <stat> EXPR_STAT SEL_STAT ITERATION_STAT COMPOUND_STAT JUMP_STAT LABEL_STAT STAT
%type <expr> EXPR CONDITIONAL_EXPR LOR_EXPR LAND_EXPR BOR_EXPR BXOR_EXPR BAND_EXPR EQUALITY_EXPR RELAT_EXPR SHIFT_EXPR ARITH_EXPR TERM_EXPR UNARY_EXPR NEXT_EXPR FACTOR_EXPR
%type <number> T_NUMBER_INT T_NUMBER_DOUBLE
%type <string> T_INT T_FLOAT T_DOUBLE T_CHAR T_VARIABLE ASSIGNOP T_CHARS
%type <T_type> TYPE_DEF
%type <variable> DECLARATION ARGUMENT
%type <statList> ITEM_LIST_STAT
%type <decllist> ARG_LIST
%type <arglist> EXPR_LIST
%type <function> FUNCTION
%type <main> MAIN

%start PROGRAM

%%

PROGRAM             : MAIN                                                          { g_root = $1; }

MAIN                : FUNCTION                                                      { $$ = new Main($1); }
                    | DECLARATION                                                   { $$ = new Main($1); }
                    | FUNCTION MAIN                                                 { $$ = new Main($1, $2); }
                    | DECLARATION MAIN                                              { $$ = new Main($1, $2); }

FUNCTION            : TYPE_DEF T_VARIABLE T_LPAREN T_RPAREN COMPOUND_STAT           { $$ = new Function((new StoreFunc($1, $2)), nullptr, $5); }
                    | TYPE_DEF T_VARIABLE T_LPAREN ARG_LIST T_RPAREN COMPOUND_STAT  { $$ = new Function((new StoreFunc($1, $2)), $4, $6); }
                    | TYPE_DEF T_VARIABLE T_LPAREN T_RPAREN T_SEMI                  { $$ = new Function((new StoreFunc($1, $2)), nullptr, nullptr); }
                    | TYPE_DEF T_VARIABLE T_LPAREN ARG_LIST T_RPAREN T_SEMI         { $$ = new Function((new StoreFunc($1, $2)), $4, nullptr); }

ARGUMENT                 : TYPE_DEF T_VARIABLE                                     { $$ = new Identifier($1, $2, DecType::ARGUMENT); }
                    | TYPE_DEF T_LSQUARE T_RSQUARE T_VARIABLE                       { $$ = new Array($1, $4); }
                    | TYPE_DEF T_MULT T_VARIABLE                                    { $$ = new Pointer($1, $3, DecType::ARGUMENT); }

ARG_LIST            : ARGUMENT                                                     { $$ = new DecList($1, nullptr); }
                    | ARGUMENT T_COMMA ARG_LIST                                    { $$ = new DecList($1, $3); }

STAT                : COMPOUND_STAT                                                 { $$ = $1; }
                    | ITERATION_STAT                                                { $$ = $1; }
                    | SEL_STAT                                                      { $$ = $1; }
                    | EXPR_STAT                                                     { $$ = $1; }
                    | JUMP_STAT                                                     { $$ = $1; }
                    | LABEL_STAT                                                    { $$ = $1; }
                    
COMPOUND_STAT       : T_LBRACE T_RBRACE                                             { $$ = new CompoundStat(); }
                    | T_LBRACE ITEM_LIST_STAT T_RBRACE                              { $$ = new CompoundStat($2); }

ITERATION_STAT      : T_WHILE T_LPAREN EXPR T_RPAREN STAT                           { $$ = new WhileStat($3, $5); }
                    | T_FOR T_LPAREN EXPR T_SEMI EXPR T_SEMI EXPR T_RPAREN STAT     { $$ = new ForStat($3, $5, $7, $9); }
                    | T_FOR T_LPAREN DECLARATION EXPR T_SEMI EXPR T_RPAREN STAT     { $$ = new ForStat($3, $4, $6, $8); }

SEL_STAT            : T_IF T_LPAREN EXPR T_RPAREN STAT                              { $$ = new IfStat($3, $5); }
                    | T_IF T_LPAREN EXPR T_RPAREN STAT T_ELSE STAT                  { $$ = new IfStat($3, $5, $7); }
                    | T_SWITCH T_LPAREN EXPR T_RPAREN STAT                          { $$ = new SwitchStat($3, $5);}

EXPR_STAT           : T_SEMI                                                        { $$ = new ExprStat(); }
                    | EXPR T_SEMI                                                   { $$ = new ExprStat($1); }

JUMP_STAT           : T_CONTINUE T_SEMI                                             { $$ = new ContinueStat(); }
                    | T_BREAK T_SEMI                                                { $$ = new BreakStat(); }
                    | T_RETURN T_SEMI                                               { $$ = new ReturnStat(); }
                    | T_RETURN EXPR T_SEMI                                          { $$ = new ReturnStat($2); }

LABEL_STAT          : T_CASE CONDITIONAL_EXPR T_COLON STAT                          { $$ = new LabelStat($4, $2); }
                    | T_DEFAULT T_COLON STAT                                        { $$ = new LabelStat($3); }                

ITEM_LIST_STAT      : STAT                                                          { $$ = new StatList($1, nullptr); }
                    | DECLARATION                                                   { $$ = new StatList($1, nullptr); }
                    | STAT ITEM_LIST_STAT                                           { $$ = new StatList($1, $2); }
                    | DECLARATION ITEM_LIST_STAT                                    { $$ = new StatList($1, $2); }

ENUM                : T_VARIABLE                                                    {}
                    | T_VARIABLE T_ASSIGN CONDITIONAL_EXPR                          {}

ENUM_LIST           : ENUM                                                          {}
                    | ENUM T_COMMA ENUM_LIST                                        {}

ENUM_DECL           : ENUM T_LBRACE ENUM_LIST T_RBRACE                              {}
                    | ENUM T_VARIABLE T_LBRACE ENUM_LIST T_RBRACE                   {}
                    | ENUM T_VARIABLE                                               {}

DECLARATION         : TYPE_DEF T_VARIABLE T_SEMI                                    { $$ = new Identifier($1, $2, DecType::DECLARATION)     ; }
                    | TYPE_DEF T_VARIABLE T_ASSIGN EXPR T_SEMI                      { $$ = new Identifier($1, $2, DecType::DECLARATION, $4) ; }
                    | TYPE_DEF T_VARIABLE T_LSQUARE T_NUMBER_INT T_RSQUARE T_SEMI   { $$ = new Array($1, $2, $4)                            ; }
                    | TYPE_DEF T_VARIABLE T_LSQUARE CONDITIONAL_EXPR T_RSQUARE T_ASSIGN EXPR T_SEMI                                          {}
                    | TYPE_DEF T_MULT T_VARIABLE T_SEMI                             { $$ = new Pointer($1, $3, DecType::DECLARATION)        ; }
                    | TYPE_DEF T_MULT T_VARIABLE T_ASSIGN EXPR T_SEMI               { $$ = new Pointer($1, $3, DecType::DECLARATION, $5)    ; }



ASSIGNOP            : T_ASSIGN                                                      { $$ = new std::string("="); }
                    | T_ADD_ASSIGN                                                  { $$ = new std::string("+="); }
                    | T_SUB_ASSIGN                                                  { $$ = new std::string("-="); }
                    | T_DIV_ASSIGN                                                  { $$ = new std::string("/="); }
                    | T_MULT_ASSIGN                                                 { $$ = new std::string("*="); }
                    | T_MOD_ASSIGN                                                  { $$ = new std::string("%="); }
                    | T_LSHIFT_ASSIGN                                               { $$ = new std::string("<<="); }
                    | T_RSHIFT_ASSIGN                                               { $$ = new std::string(">>="); }
                    | T_AND_ASSIGN                                                  { $$ = new std::string("&="); }
                    | T_XOR_ASSIGN                                                  { $$ = new std::string("^="); }
                    | T_OR_ASSIGN                                                   { $$ = new std::string("|="); }

EXPR                : CONDITIONAL_EXPR                                              { $$ = $1; }
                    | T_VARIABLE ASSIGNOP EXPR                                      { $$ = new Identifier($1, $2, $3);}
                    | T_VARIABLE T_LSQUARE EXPR T_RSQUARE ASSIGNOP EXPR             { $$ = new Array($1, $3, $5, $6); }
                    | T_VARIABLE T_LSQUARE EXPR T_RSQUARE T_INCR                    { $$ = new Array($1, $3, new std::string("++"), nullptr); }
                    | T_VARIABLE T_LSQUARE EXPR T_RSQUARE T_DECR                    { $$ = new Array($1, $3, new std::string("--"), nullptr); }
                    | T_VARIABLE T_INCR                                             { $$ = new Identifier($1, new std::string("++"), nullptr); }
                    | T_VARIABLE T_DECR                                             { $$ = new Identifier($1, new std::string("--"), nullptr); }
                    | T_MULT T_VARIABLE ASSIGNOP EXPR                               { $$ = new Pointer($2, $3, $4, true); }

CONDITIONAL_EXPR     : LOR_EXPR                                                     { $$ = $1; }

LOR_EXPR            : LAND_EXPR                                                     { $$ = $1; }
                    | LOR_EXPR T_LOR LAND_EXPR                                      { $$ = new LogicOrOp($1, $3); }

LAND_EXPR           : BOR_EXPR                                                      { $$ = $1; }
                    | LAND_EXPR T_LAND BOR_EXPR                                     { $$ = new LogicAndOp($1, $3); }

BOR_EXPR            : BXOR_EXPR                                                     { $$ = $1; }
                    | BOR_EXPR T_BOR BXOR_EXPR                                      { $$ = new BitOrOp($1, $3); }

BXOR_EXPR            : BAND_EXPR                                                    { $$ = $1; }
                    | BXOR_EXPR T_BXOR BAND_EXPR                                    { $$ = new BitXorOp($1, $3); }

BAND_EXPR            : EQUALITY_EXPR                                                { $$ = $1; }
                    | BAND_EXPR T_BAND EQUALITY_EXPR                                { $$ = new BitAndOp($1, $3); }

EQUALITY_EXPR       : RELAT_EXPR                                                    { $$ = $1; }
                    | EQUALITY_EXPR T_EQUAL RELAT_EXPR                              { $$ = new EqualOp($1, $3); }
                    | EQUALITY_EXPR T_NEQUAL RELAT_EXPR                             { $$ = new NotEqualOp($1, $3); }

RELAT_EXPR          : SHIFT_EXPR                                                    { $$ = $1; }
                    | RELAT_EXPR T_GT SHIFT_EXPR                                    { $$ = new GreaterThanOp($1, $3); }
                    | RELAT_EXPR T_LT SHIFT_EXPR                                    { $$ = new LessThanOp($1, $3); }
                    | RELAT_EXPR T_GTE SHIFT_EXPR                                   { $$ = new GreaterOrEqualOp($1, $3); }
                    | RELAT_EXPR T_LTE SHIFT_EXPR                                   { $$ = new LessOrEqualOp($1, $3); }

SHIFT_EXPR          : ARITH_EXPR                                                    { $$ = $1; }  
                    | SHIFT_EXPR T_RSHIFT ARITH_EXPR                                { $$ = new RightShiftOp($1, $3); }
                    | SHIFT_EXPR T_LSHIFT ARITH_EXPR                                { $$ = new LeftShiftOp($1, $3); }

ARITH_EXPR          : TERM_EXPR                                                     { $$ = $1; }
                    | ARITH_EXPR T_ADD TERM_EXPR                                    { $$ = new AddOp($1, $3); }
                    | ARITH_EXPR T_SUB TERM_EXPR                                    { $$ = new SubOp($1, $3); }

TERM_EXPR           : UNARY_EXPR                                                    { $$ = $1; }
                    | TERM_EXPR T_MULT UNARY_EXPR                                   { $$ = new MultOp($1, $3); }
                    | TERM_EXPR T_DIV UNARY_EXPR                                    { $$ = new DivOp($1, $3); }
                    | TERM_EXPR T_MOD UNARY_EXPR                                    { $$ = new ModOp($1, $3); }

UNARY_EXPR          : FACTOR_EXPR                                                   { $$ = $1; }
                    | T_SUB NEXT_EXPR                                               { $$ = new NegOp($2); }
                    | T_ADD NEXT_EXPR                                               { $$ = new PosOp($2); }
                    | T_NOT NEXT_EXPR                                               { $$ = new NotOp($2); }

NEXT_EXPR           : FACTOR_EXPR                                                   { $$ = $1; }

EXPR_LIST           : EXPR                                                          { $$ = new ExprList($1); }
                    | EXPR T_COMMA EXPR_LIST                                        { $$ = new ExprList($1, $3); }

TYPE_DEF            : T_INT                                                         { $$ = VarTypeDef::INT; }
                    | T_FLOAT                                                       { $$ = VarTypeDef::FLOAT; }
                    | T_DOUBLE                                                      { $$ = VarTypeDef::DOUBLE; }
                    | T_CHAR                                                        { $$ = VarTypeDef::CHAR; }

FACTOR_EXPR         : T_NUMBER_INT                                                  { $$ = new Number_INT($1); }
                    | T_NUMBER_DOUBLE                                               { $$ = new Number_DOUBLE($1); }
                    | T_VARIABLE                                                    { $$ = new Identifier($1); }
                    | T_CHARS                                                       { $$ = new Char($1); }
                    | T_VARIABLE T_LPAREN T_RPAREN                                  { $$ = new StoreFunc($1); }
                    | T_VARIABLE T_LPAREN EXPR_LIST T_RPAREN                        { $$ = new StoreFunc($1, $3); }
                    | T_LPAREN EXPR T_RPAREN                                        { $$ = $2; }
                    | T_VARIABLE T_LSQUARE EXPR T_RSQUARE                           { $$ = new Array($1, $3); }
                    | T_SIZEOF T_LPAREN EXPR T_RPAREN                               { $$ = new SizeOf($3); }
                    | T_SIZEOF T_LPAREN TYPE_DEF T_RPAREN                           { $$ = new SizeOf($3); }
                    | T_MULT T_VARIABLE                                             { $$ = new Pointer($2, true, false); }
                    | T_BAND T_VARIABLE                                             { $$ = new Identifier($2, true); }

%%

const Main *g_root;

const Main *parseAST(FILE *inputFile)
{
  g_root=0;
  yyin = inputFile;
  yyparse();
  return g_root;
}