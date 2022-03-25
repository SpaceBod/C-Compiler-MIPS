/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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

#line 62 "src/C90Parser.tab.hpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_VARIABLE = 258,
    T_NUMBER = 259,
    T_GT = 260,
    T_LT = 261,
    T_GTE = 262,
    T_LTE = 263,
    T_EQUAL = 264,
    T_NEQUAL = 265,
    T_LOR = 266,
    T_BOR = 267,
    T_LAND = 268,
    T_BAND = 269,
    T_BXOR = 270,
    T_SUB = 271,
    T_ADD = 272,
    T_MULT = 273,
    T_DIV = 274,
    T_MOD = 275,
    T_NOT = 276,
    T_ASSIGN = 277,
    T_SEMI = 278,
    T_COMMA = 279,
    T_LBRACE = 280,
    T_RBRACE = 281,
    T_LPAREN = 282,
    T_RPAREN = 283,
    T_INT_TYPE = 284,
    T_RETURN = 285,
    T_WHILE = 286,
    T_IF = 287,
    T_ELSE = 288,
    T_FOR = 289
  };
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

#line 120 "src/C90Parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_C90PARSER_TAB_HPP_INCLUDED  */
