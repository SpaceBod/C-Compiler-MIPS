%code requires{
  #include "ast.hpp"
  #include <cassert>
  #include <map>

  extern const Function *g_root;
  extern FILE* yyin;

  int yylex(void);
  void yyerror(const char *);
}

%union{
  const Function *func;
  const Stat *stat;
  const Expression *expr;
  const Stat_list *statlist;
  Variable *var;
  double number;
  std::string *str;
  VarType T_type;
}

%token T_VARIABLE T_NUMBER
%token T_GT T_LT T_GTE T_LTE T_EQUAL T_NEQUAL
%token T_LSHIFT T_RSHIFT
%token T_LOR T_BOR T_LAND T_BAND T_BXOR 
%token T_SUB T_ADD T_MULT T_DIV T_MOD T_NOT
%token T_INCR T_DECR
%token T_ASSIGN T_ADD_ASSIGN T_SUB_ASSIGN T_MULT_ASSIGN T_DIV_ASSIGN T_MOD_ASSIGN T_LSHIFT_ASSIGN T_RSHIFT_ASSIGN T_AND_ASSIGN T_OR_ASSIGN T_XOR_ASSIGN
%token T_SEMI T_COMMA T_COLON
%token T_LBRACE T_RBRACE T_LPAREN T_RPAREN T_LSQUARE T_RSQUARE
%token T_INT_TYPE T_RETURN T_WHILE T_IF T_ELSE T_FOR T_SWITCH T_CASE T_CONTINUE T_BREAK T_ENUM

%type <func> FUNCTION
%type <stat> STAT COMPOUND_STAT EXPRESSION_STAT SELECTION_STAT ITERATION_STAT JUMP_STAT LABEL_STAT
%type <expr> EXPR CONDITIONAL_EXPR LOR_EXPR LAND_EXPR BOR_EXPR BAND_EXPR BXOR_EXPR EQUAL_EXPR RELATION_EXPR SHIFT_EXPR ARITHMETIC_EXPR TERM_EXPR UNARY_EXPR FACTOR_EXPR
%type <statlist> STAT_LIST
%type <number> T_NUMBER
%type <str> T_INT_TYPE T_VARIABLE ASSIGNS
%type <var> DECLARATION
%type <T_type> VAR_TYPE

%start PROGRAM

%%

PROGRAM             : FUNCTION                                                      { g_root = $1; }

FUNCTION            : VAR_TYPE T_VARIABLE T_LPAREN T_RPAREN COMPOUND_STAT           { $$ = new Function((new Variable($1, $2)), $5); }

STAT_LIST           : STAT                                                          { $$ = new Stat_list($1, nullptr); }
                    | DECLARATION                                                   { $$ = new Stat_list($1, nullptr); }
                    | STAT STAT_LIST                                                { $$ = new Stat_list($1, $2)     ; }
                    | DECLARATION STAT_LIST                                         { $$ = new Stat_list($1, $2)     ; }

DECLARATION         : VAR_TYPE T_VARIABLE T_SEMI                                    { $$ = new Variable($1, $2, nullptr); }
                    | VAR_TYPE T_VARIABLE T_ASSIGN EXPR T_SEMI                      { $$ = new Variable($1, $2, $4)     ; }

STAT                : COMPOUND_STAT                                                 { $$ = $1; }
                    | EXPRESSION_STAT                                               { $$ = $1; }
                    | SELECTION_STAT                                                { $$ = $1; }
                    | ITERATION_STAT                                                { $$ = $1; }
                    | JUMP_STAT                                                     { $$ = $1; }
                    | LABEL_STAT                                                    { $$ = $1; }

COMPOUND_STAT       : T_LBRACE T_RBRACE                                             { $$ = new Comp_Stat()  ; }
                    | T_LBRACE STAT_LIST T_RBRACE                                   { $$ = new Comp_Stat($2); }
          
EXPRESSION_STAT     : T_SEMI                                                        { $$ = new Expression_Stat()  ; }
                    | EXPR T_SEMI                                                   { $$ = new Expression_Stat($1); }

SELECTION_STAT      : T_IF T_LPAREN EXPR T_RPAREN STAT                              { $$ = new If_Stat($3, $5)    ; }
                    | T_IF T_LPAREN EXPR T_RPAREN STAT T_ELSE STAT                  { $$ = new If_Stat($3, $5, $7); }
                    | T_SWITCH T_LPAREN EXPR T_RPAREN STAT                          { $$ = new Switch_Stat($3, $5); }

ITERATION_STAT      : T_WHILE T_LPAREN EXPR T_RPAREN STAT                           { $$ = new While_Stat($3, $5)      ; }
                    | T_FOR T_LPAREN EXPR T_SEMI EXPR T_SEMI EXPR T_RPAREN STAT     { $$ = new For_Stat($3, $5, $7, $9); }
                    | T_FOR T_LPAREN DECLARATION EXPR T_SEMI EXPR T_RPAREN STAT     { $$ = new For_Stat($3, $4, $6, $8); }

JUMP_STAT           : T_RETURN T_SEMI                                               { $$ = new Return_Stat()    ; }
                    | T_RETURN EXPR T_SEMI                                          { $$ = new Return_Stat($2)  ; }
                    | T_CONTINUE T_SEMI                                             { $$ = new Continue_Stat(); }
                    | T_BREAK T_SEMI                                                { $$ = new Break_Stat()   ; }

LABEL_STAT          : T_CASE CONDITIONAL_EXPR T_COLON STAT                           { $$ = new Label_Stat($2, $4); }

EXPR                : CONDITIONAL_EXPR                                              { $$ = $1                      ; }
                    | T_VARIABLE ASSIGNS EXPR                                       { $$ = new Variable($1, $2, $3); }

CONDITIONAL_EXPR    : LOR_EXPR                                                      { $$ = $1; }

ASSIGNS             : T_ASSIGN                                                      { $$ = new std::string("=")  ; }
                    | T_ADD_ASSIGN                                                  { $$ = new std::string("+=") ; }
                    | T_SUB_ASSIGN                                                  { $$ = new std::string("-=") ; }
                    | T_DIV_ASSIGN                                                  { $$ = new std::string("/=") ; }
                    | T_MULT_ASSIGN                                                 { $$ = new std::string("*=") ; }
                    | T_MOD_ASSIGN                                                  { $$ = new std::string("%=") ; }
                    | T_AND_ASSIGN                                                  { $$ = new std::string("&=") ; }
                    | T_XOR_ASSIGN                                                  { $$ = new std::string("^=") ; }
                    | T_OR_ASSIGN                                                   { $$ = new std::string("|=") ; }
                    | T_LSHIFT_ASSIGN                                               { $$ = new std::string("<<="); }
                    | T_RSHIFT_ASSIGN                                               { $$ = new std::string(">>="); }

LAND_EXPR           : BOR_EXPR                                                      { $$ = $1                  ; }
                    | LAND_EXPR T_LAND EQUAL_EXPR                                   { $$ = new LogicAnd($1, $3); }

LOR_EXPR            : LAND_EXPR                                                     { $$ = $1                 ; }
                    | LOR_EXPR T_LOR LAND_EXPR                                      { $$ = new LogicOr($1, $3); }

BOR_EXPR            : BXOR_EXPR                                                     { $$ = $1               ; }
                    | BOR_EXPR T_BOR BXOR_EXPR                                      { $$ = new BitOr($1, $3); }

BAND_EXPR           : EQUAL_EXPR                                                    { $$ = $1                ; }
                    | BAND_EXPR T_BAND EQUAL_EXPR                                   { $$ = new BitAnd($1, $3); }

BXOR_EXPR           : BAND_EXPR                                                     { $$ = $1                ; }
                    | BXOR_EXPR T_BXOR BAND_EXPR                                    { $$ = new BitXOr($1, $3); }

EQUAL_EXPR          : RELATION_EXPR                                                 { $$ = $1                          ; }
                    | EQUAL_EXPR T_EQUAL RELATION_EXPR                              { $$ = new EqualOperator($1, $3)   ; }
                    | EQUAL_EXPR T_NEQUAL RELATION_EXPR                             { $$ = new NotEqualOperator($1, $3); }          

SHIFT_EXPR          : ARITHMETIC_EXPR                                               { $$ = $1                    ; }
                    | SHIFT_EXPR T_RSHIFT ARITHMETIC_EXPR                           { $$ = new RightShift($1, $3); }
                    | SHIFT_EXPR T_LSHIFT ARITHMETIC_EXPR                           { $$ = new LeftShift($1, $3) ; }     

RELATION_EXPR       : SHIFT_EXPR                                                    { $$ = $1; }
                    | RELATION_EXPR T_GT SHIFT_EXPR                                 { $$ = new GreaterThanOperator($1, $3); }
                    | RELATION_EXPR T_LT SHIFT_EXPR                                 { $$ = new LessThanOperator($1, $3); }
                    | RELATION_EXPR T_GTE SHIFT_EXPR                                { $$ = new GreaterOrEqualThanOperator($1, $3); }
                    | RELATION_EXPR T_LTE SHIFT_EXPR                                { $$ = new LessOrEqualThanOperator($1,$3); }


ARITHMETIC_EXPR     : TERM_EXPR                                                     { $$ = $1                     ; }
                    | ARITHMETIC_EXPR T_ADD TERM_EXPR                               { $$ = new AddOperator($1, $3); }
                    | ARITHMETIC_EXPR T_SUB TERM_EXPR                               { $$ = new SubOperator($1, $3); }

TERM_EXPR           : UNARY_EXPR                                                    { $$ = $1                     ; }
                    | TERM_EXPR T_MULT UNARY_EXPR                                   { $$ = new MulOperator($1, $3); }
                    | TERM_EXPR T_DIV UNARY_EXPR                                    { $$ = new DivOperator($1, $3); }
                    | TERM_EXPR T_MOD UNARY_EXPR                                    { $$ = new ModOperator($1, $3); }

UNARY_EXPR          : FACTOR_EXPR                                                   { $$ = $1                 ; }
                    | T_ADD FACTOR_EXPR                                             { $$ = new PosOperator($2); }
                    | T_SUB FACTOR_EXPR                                             { $$ = new NegOperator($2); }
                    | T_NOT FACTOR_EXPR                                             { $$ = new NotOperator($2); }

FACTOR_EXPR         : T_NUMBER                                                      { $$ = new Number($1)  ; }
                    | T_VARIABLE                                                    { $$ = new Variable($1); }
                    | T_LPAREN EXPR T_RPAREN                                        { $$ = $2              ; }

/* ENUM                : T_VARIABLE                                                    {}
                    | T_VARIABLE T_ASSIGN ENUM_LIST                                 {}

ENUM_DECL           : ENUM T_LBRACE ENUM_LIST T_RBRACE                              {}
                    | ENUM T_VARIABLE T_LBRACE ENUM_LIST T_RBRACE                   {}
                    | ENUM T_VARIABLE                                               {}

ENUM_LIST           : ENUM                                                          {}
                    | ENUM T_COMMA ENUM_LIST                                        {} */
 
VAR_TYPE            : T_INT_TYPE                                                    { $$ = VarType::INT; }

%%

const Function *g_root;

const Function *parseAST(FILE *fileInput)
{
  g_root=0;
  yyin = fileInput;
  yyparse();
  return g_root;
}
