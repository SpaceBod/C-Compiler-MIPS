/* A Bison parser, made by GNU Bison 3.7.6.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SRC_C90PARSER_TAB_HPP_INCLUDED
# define YY_YY_SRC_C90PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/C90Parser.y"

  #include "ast.hpp"
  #include <cassert>

  extern const Function *g_root; // A way of getting the AST out
  extern FILE* yyin; // File input

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);

#line 63 "src/C90Parser.tab.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_VARIABLE = 258,              /* T_VARIABLE  */
    T_NUMBER = 259,                /* T_NUMBER  */
    T_GT = 260,                    /* T_GT  */
    T_LT = 261,                    /* T_LT  */
    T_GTE = 262,                   /* T_GTE  */
    T_LTE = 263,                   /* T_LTE  */
    T_EQUAL = 264,                 /* T_EQUAL  */
    T_NEQUAL = 265,                /* T_NEQUAL  */
    T_LOR = 266,                   /* T_LOR  */
    T_BOR = 267,                   /* T_BOR  */
    T_LAND = 268,                  /* T_LAND  */
    T_BAND = 269,                  /* T_BAND  */
    T_BXOR = 270,                  /* T_BXOR  */
    T_SUB = 271,                   /* T_SUB  */
    T_ADD = 272,                   /* T_ADD  */
    T_MULT = 273,                  /* T_MULT  */
    T_DIV = 274,                   /* T_DIV  */
    T_MOD = 275,                   /* T_MOD  */
    T_NOT = 276,                   /* T_NOT  */
    T_ASSIGN = 277,                /* T_ASSIGN  */
    T_SEMI = 278,                  /* T_SEMI  */
    T_COMMA = 279,                 /* T_COMMA  */
    T_LBRACE = 280,                /* T_LBRACE  */
    T_RBRACE = 281,                /* T_RBRACE  */
    T_LPAREN = 282,                /* T_LPAREN  */
    T_RPAREN = 283,                /* T_RPAREN  */
    T_INT_TYPE = 284,              /* T_INT_TYPE  */
    T_RETURN = 285,                /* T_RETURN  */
    T_WHILE = 286,                 /* T_WHILE  */
    T_IF = 287,                    /* T_IF  */
    T_ELSE = 288,                  /* T_ELSE  */
    T_FOR = 289,                   /* T_FOR  */
    T_SWITCH = 290,                /* T_SWITCH  */
    T_CASE = 291,                  /* T_CASE  */
    T_CONTINUE = 292,              /* T_CONTINUE  */
    T_BREAK = 293                  /* T_BREAK  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "src/C90Parser.y"

  const Function *func;
  const Stat *stat;
  const Stat_list *statlist;
  const Expression *expr;
  const Decl_list *decllist;
  double number;
  Variable *var;
  std::string *str;
  TypeDef T_type;

#line 130 "src/C90Parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_C90PARSER_TAB_HPP_INCLUDED  */
