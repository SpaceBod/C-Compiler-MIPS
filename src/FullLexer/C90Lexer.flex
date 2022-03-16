%option noyywrap

%{
extern "C" int fileno(FILE *stream);
include "C90Parser.tab.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int lineno = 1;
void yyerror();
%}

ALPHA               [a-zA-Z_]
DIGIT               [0-9]
HEX                 [0-9A-Fa-f]
IDENTIFIER          [a-zA-Z_][a-zA-Z0-9_]*
STRUCTVAR           [a-zA-Z_][a-zA-Z_0-9]*[.][a-zA-Z_][a-zA-Z_0-9]*
CHAR_DATA           [\'][\\][0|t|r|n][\']|['].[']
STRING_DATA         ["].*["]
EXPO                [Ee][+-]?[0-9]+
WHITESPACE          [ \t\r\n]+

%%
"="			        { return T_ASSIGN           ; }

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

"++"                { return T_INCR             ; }
"--"                { return T_DECR             ; }
"+="                { return T_ADD_ASSIGN       ; }
"-="                { return T_SUB_ASSIGN       ; }
"*="                { return T_MULT_ASSIGN      ; }
"/="                { return T_DIV_ASSIGN       ; }

"<<"                { return T_LSHIFT           ; }
">>"                { return T_RSHIFT           ; }
"||"                { return T_LOR              ; }
"|"                 { return T_BOR              ; }
"&&"                { return T_LAND             ; }
"&"                 { return T_BAND             ; }
"^"	  			    { return T_BXOR             ; }

"("                 { return T_LPAREN           ; }
")"                 { return T_RPAREN           ; }
"]"                 { return T_LBRACK           ; }
"["                 { return T_RBRACK           ; }
"{"                 { return T_LBRACE           ; }
"}"                 { return T_RBRACE           ; }
";"                 { return T_SEMI             ; }
"."                 { return T_DOT              ; }
","                 { return T_COMMA            ; }

"if"			    { return T_IF               ; }
"else"			    { return T_ELSE             ; }
"while"			    { return T_WHILE            ; }
"for"			    { return T_FOR              ; }
"case"			    { return T_CASE             ; }
"default"		    { return T_DEFAULT          ; }
"break"		        { return T_BREAK            ; }
"return"		    { return T_RETURN           ; }
"switch"            { return T_SWITCH           ; }
"continue"          { return T_CONTINUE         ; }
"enum"              { return T_ENUM             ; }
"struct"            { return T_STRUCT           ; }
"sizeof"            { return T_SIZEOF           ; }
"typedef"           { return T_TYPEDEF          ; }

"int"               { return T_INT_TYPE         ; }
"float"             { return T_FLOAT_TYPE       ; }
"double"            { return T_DOUBLE_TYPE      ; }
"signed"            { return T_SIGNED_TYPE      ; }
"unsigned"          { return T_UNSIGNED_TYPE    ; }
"char"              { return T_CHAR_TYPE        ; }
"void"              { return T_VOID             ; }

IDENTIFIER                  { std::string var = yytext; yylval.word = new std::string(var); return IDENTIFIER; }
DIGIT+                      { yylval.number=strtod(yytext, 0); return T_NUMBER_INT; }
DIGIT+[\.](DIGIT+)*         { yylval.number=strtod(yytext, 0); return T_NUMBER_DOUBLE; }
DIGIT+[\.](DIGIT+)*f        { yylval.number=strtod(yytext, 0); return T_NUMBER_DOUBLE; }
STRUCTVAR                   { yylval.string=new std::string(yytext); return T_STRUCTVAR; }
STRING_DATA                 { yylval.string=new std::string(yytext); return T_STRING_DATA; }
CHAR_DATA                   { yylval.string=new std::string(yytext); return T_CHAR_DATA; }
WHITESPACE		            {;}
.                           { fprintf(stderr, "Invalid token\n"); exit(1); }

%%

void yyerror (char const *s)
{
  fprintf (stderr, "Lexing error -> %s\n", s);
  fprintf(stderr, "Line: %d: %s\n", yylineno, s);
  exit(1);
}