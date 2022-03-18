%option noyywrap

%{
extern "C" int fileno(FILE *stream);
#include "C90Parser.tab.hpp"
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

"||"                { return T_LOR              ; }
"|"                 { return T_BOR              ; }
"&&"                { return T_LAND             ; }
"&"                 { return T_BAND             ; }
"^"	  			        { return T_BXOR             ; }

"="			            { return T_ASSIGN           ; }
";"                 { return T_SEMI             ; }
","                 { return T_COMMA            ; }

"("                 { return T_LPAREN           ; }
")"                 { return T_RPAREN           ; }
"{"                 { return T_LBRACE           ; }
"}"                 { return T_RBRACE           ; }

"if"			          { return T_IF               ; }
"else"			        { return T_ELSE             ; }
"while"			        { return T_WHILE            ; }
"return"		        { return T_RETURN           ; }
"for"               { return T_FOR              ; }
"int"               { return T_INT_TYPE         ; }

[0-9]+([.][0-9]*)?              { yylval.number=strtod(yytext, 0); return T_NUMBER; }
[a-zA-Z_][0-9a-zA-Z_]*          { yylval.str=new std::string(yytext); return T_VARIABLE; }
[ \t\r\n]+		                  {;}
.                               { fprintf(stderr, "Invalid token\n"); exit(1); }

%%

void yyerror (char const *s)
{
  fprintf (stderr, "Token Error -> %s\n", s);
  exit(1);
}