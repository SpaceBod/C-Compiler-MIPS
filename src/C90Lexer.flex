%option noyywrap

%{
extern "C" int fileno(FILE *stream);

#include "parser.tab.hpp"
%}

%%
"*"                 { return T_MULT             ; }
"/"                 { return T_DIV              ; }
"+"                 { return T_ADD              ; }
"-"                 { return T_SUB              ; }
"%"                 { return T_MOD              ; }
"!"                 { return T_NOT              ; }

">"                 { return T_GT               ; }
"<"                 { return T_LT               ; }
">="                { return T_GTE              ; }
"<="                { return T_LTE              ; }
"=="                { return T_EQUAL            ; }
"!="                { return T_NEQUAL           ; }

"<<"                { return T_LSHIFT           ; }
">>"                { return T_RSHIFT           ; }

"&"                 { return T_BAND             ; }
"|"                 { return T_BOR              ; }
"^"	  			        { return T_BXOR             ; }
"||"                { return T_LOR              ; }
"&&"                { return T_LAND             ; }

"++"                { return T_INCR             ; }
"--"                { return T_DECR             ; }

"="			            { return T_ASSIGN           ; }
"+="                { return T_ADD_ASSIGN       ; }
"-="                { return T_SUB_ASSIGN       ; }
"/="                { return T_DIV_ASSIGN       ; }
"*="                { return T_MULT_ASSIGN      ; }
"%="                { return T_MOD_ASSIGN       ; }
"<<="               { return T_LSHIFT_ASSIGN    ; }
">>="               { return T_RSHIFT_ASSIGN    ; }
"&="                { return T_AND_ASSIGN       ; }
"|="                { return T_XOR_ASSIGN       ; }
"^="                { return T_OR_ASSIGN        ; }

";"                 { return T_SEMI             ; }
":"                 { return T_COLON            ; }
","                 { return T_COMMA            ; }

"{"                 { return T_LBRACE           ; }
"}"                 { return T_RBRACE           ; }
"("                 { return T_LPAREN           ; }
")"                 { return T_RPAREN           ; }
"["                 { return T_LSQUARE          ; }
"]"                 { return T_RSQUARE          ; }

"int"               { return T_INT              ; }
"float"             { return T_FLOAT            ; }
"double"            { return T_DOUBLE           ; }
"char"              { return T_CHAR             ; }
"return"            { return T_RETURN           ; }
"while"             { return T_WHILE            ; }
"if"                { return T_IF               ; }
"else"              { return T_ELSE             ; }
"for"               { return T_FOR              ; }
"switch"            { return T_SWITCH           ; }
"continue"          { return T_CONTINUE         ; }
"break"             { return T_BREAK            ; }
"case"              { return T_CASE             ; }
"default"           { return T_DEFAULT          ; }
"enum"              { return T_ENUM             ; }
"sizeof"            { return T_SIZEOF           ; }

[0-9]+                         { yylval.number=strtod(yytext, 0); return T_NUMBER_INT; }
[0-9]+[.]([0-9]+)*             { yylval.number=strtod(yytext, 0); return T_NUMBER_DOUBLE; }
[0-9]+[.]([0-9]+)*f            { yylval.number=strtod(yytext, 0); return T_NUMBER_DOUBLE; }
[a-zA-Z_][a-zA-Z_0-9]*         { yylval.string=new std::string(yytext); return T_VARIABLE; }
[\'][^\n][\']                  { yylval.string=new std::string(yytext); return T_CHARS; }

[ \t\r\n]+		                 {;}

.                              { fprintf(stderr, "Invalid token\n"); exit(1); }
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  fprintf(stderr, "line %d: %s\n", yylineno, s);
  exit(1);
}