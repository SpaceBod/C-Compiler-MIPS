/* A Bison parser, made by GNU Bison 3.7.6.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30706

/* Bison version string.  */
#define YYBISON_VERSION "3.7.6"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1





# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "C90Parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_VARIABLE = 3,                 /* T_VARIABLE  */
  YYSYMBOL_T_NUMBER = 4,                   /* T_NUMBER  */
  YYSYMBOL_T_GT = 5,                       /* T_GT  */
  YYSYMBOL_T_LT = 6,                       /* T_LT  */
  YYSYMBOL_T_GTE = 7,                      /* T_GTE  */
  YYSYMBOL_T_LTE = 8,                      /* T_LTE  */
  YYSYMBOL_T_EQUAL = 9,                    /* T_EQUAL  */
  YYSYMBOL_T_NEQUAL = 10,                  /* T_NEQUAL  */
  YYSYMBOL_T_LOR = 11,                     /* T_LOR  */
  YYSYMBOL_T_BOR = 12,                     /* T_BOR  */
  YYSYMBOL_T_LAND = 13,                    /* T_LAND  */
  YYSYMBOL_T_BAND = 14,                    /* T_BAND  */
  YYSYMBOL_T_BXOR = 15,                    /* T_BXOR  */
  YYSYMBOL_T_SUB = 16,                     /* T_SUB  */
  YYSYMBOL_T_ADD = 17,                     /* T_ADD  */
  YYSYMBOL_T_MULT = 18,                    /* T_MULT  */
  YYSYMBOL_T_DIV = 19,                     /* T_DIV  */
  YYSYMBOL_T_MOD = 20,                     /* T_MOD  */
  YYSYMBOL_T_NOT = 21,                     /* T_NOT  */
  YYSYMBOL_T_ASSIGN = 22,                  /* T_ASSIGN  */
  YYSYMBOL_T_SEMI = 23,                    /* T_SEMI  */
  YYSYMBOL_T_COMMA = 24,                   /* T_COMMA  */
  YYSYMBOL_T_LBRACE = 25,                  /* T_LBRACE  */
  YYSYMBOL_T_RBRACE = 26,                  /* T_RBRACE  */
  YYSYMBOL_T_LPAREN = 27,                  /* T_LPAREN  */
  YYSYMBOL_T_RPAREN = 28,                  /* T_RPAREN  */
  YYSYMBOL_T_INT_TYPE = 29,                /* T_INT_TYPE  */
  YYSYMBOL_T_RETURN = 30,                  /* T_RETURN  */
  YYSYMBOL_T_WHILE = 31,                   /* T_WHILE  */
  YYSYMBOL_T_IF = 32,                      /* T_IF  */
  YYSYMBOL_T_ELSE = 33,                    /* T_ELSE  */
  YYSYMBOL_T_FOR = 34,                     /* T_FOR  */
  YYSYMBOL_YYACCEPT = 35,                  /* $accept  */
  YYSYMBOL_PROGRAM = 36,                   /* PROGRAM  */
  YYSYMBOL_FUNCTION = 37,                  /* FUNCTION  */
  YYSYMBOL_DECLARATION_LIST = 38,          /* DECLARATION_LIST  */
  YYSYMBOL_STAT_LIST = 39,                 /* STAT_LIST  */
  YYSYMBOL_DECLARATION = 40,               /* DECLARATION  */
  YYSYMBOL_STAT = 41,                      /* STAT  */
  YYSYMBOL_COMPOUND_STAT = 42,             /* COMPOUND_STAT  */
  YYSYMBOL_EXPRESSION_STAT = 43,           /* EXPRESSION_STAT  */
  YYSYMBOL_SELECTION_STAT = 44,            /* SELECTION_STAT  */
  YYSYMBOL_ITERATION_STAT = 45,            /* ITERATION_STAT  */
  YYSYMBOL_JUMP_STAT = 46,                 /* JUMP_STAT  */
  YYSYMBOL_EXPR = 47,                      /* EXPR  */
  YYSYMBOL_CONDITIONAL_EXPR = 48,          /* CONDITIONAL_EXPR  */
  YYSYMBOL_LOR_EXPR = 49,                  /* LOR_EXPR  */
  YYSYMBOL_LAND_EXPR = 50,                 /* LAND_EXPR  */
  YYSYMBOL_BOR_EXPR = 51,                  /* BOR_EXPR  */
  YYSYMBOL_BAND_EXPR = 52,                 /* BAND_EXPR  */
  YYSYMBOL_BXOR_EXPR = 53,                 /* BXOR_EXPR  */
  YYSYMBOL_EQUAL_EXPR = 54,                /* EQUAL_EXPR  */
  YYSYMBOL_RELATION_EXPR = 55,             /* RELATION_EXPR  */
  YYSYMBOL_ARITHMETIC_EXPR = 56,           /* ARITHMETIC_EXPR  */
  YYSYMBOL_TERM_EXPR = 57,                 /* TERM_EXPR  */
  YYSYMBOL_UNARY_EXPR = 58,                /* UNARY_EXPR  */
  YYSYMBOL_FACTOR_EXPR = 59,               /* FACTOR_EXPR  */
  YYSYMBOL_TYPE_DEF = 60                   /* TYPE_DEF  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   157

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  123

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   289


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    51,    51,    53,    55,    56,    58,    59,    61,    62,
      64,    65,    66,    67,    68,    70,    71,    72,    73,    75,
      76,    78,    79,    81,    82,    83,    85,    86,    88,    89,
      91,    93,    94,    96,    97,    99,   100,   102,   103,   105,
     106,   108,   109,   110,   112,   113,   114,   115,   116,   118,
     119,   120,   122,   123,   124,   125,   127,   128,   129,   131,
     132,   133,   135
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "T_VARIABLE",
  "T_NUMBER", "T_GT", "T_LT", "T_GTE", "T_LTE", "T_EQUAL", "T_NEQUAL",
  "T_LOR", "T_BOR", "T_LAND", "T_BAND", "T_BXOR", "T_SUB", "T_ADD",
  "T_MULT", "T_DIV", "T_MOD", "T_NOT", "T_ASSIGN", "T_SEMI", "T_COMMA",
  "T_LBRACE", "T_RBRACE", "T_LPAREN", "T_RPAREN", "T_INT_TYPE", "T_RETURN",
  "T_WHILE", "T_IF", "T_ELSE", "T_FOR", "$accept", "PROGRAM", "FUNCTION",
  "DECLARATION_LIST", "STAT_LIST", "DECLARATION", "STAT", "COMPOUND_STAT",
  "EXPRESSION_STAT", "SELECTION_STAT", "ITERATION_STAT", "JUMP_STAT",
  "EXPR", "CONDITIONAL_EXPR", "LOR_EXPR", "LAND_EXPR", "BOR_EXPR",
  "BAND_EXPR", "BXOR_EXPR", "EQUAL_EXPR", "RELATION_EXPR",
  "ARITHMETIC_EXPR", "TERM_EXPR", "UNARY_EXPR", "FACTOR_EXPR", "TYPE_DEF", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289
};
#endif

#define YYPACT_NINF (-100)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -27,  -100,    18,  -100,    21,  -100,    15,    27,    32,     0,
    -100,    39,  -100,     6,     6,  -100,  -100,   109,   105,    43,
      45,    56,    37,    33,   -27,    70,  -100,  -100,  -100,  -100,
    -100,    42,  -100,    73,    74,    76,    75,    77,    -2,    38,
      22,    29,  -100,  -100,    93,   109,  -100,  -100,  -100,    79,
    -100,    80,   109,   109,   102,  -100,    72,  -100,  -100,  -100,
    -100,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,    53,  -100,  -100,
    -100,    82,    83,   109,    91,  -100,    74,    -2,    77,    -2,
      75,    38,    38,    22,    22,    22,    22,    29,    29,  -100,
    -100,  -100,   109,  -100,    70,    70,    92,   109,    94,  -100,
      86,   109,    97,  -100,    70,    88,   109,  -100,    70,    96,
    -100,    70,  -100
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    62,     0,     2,     0,     1,     0,     0,     0,     0,
       3,    60,    59,     0,     0,    19,    15,     0,     0,     0,
       0,     0,     0,     0,     4,     6,    10,    11,    12,    13,
      14,     0,    28,    30,    31,    33,    39,    35,    37,    41,
      44,    49,    52,    56,     0,     0,    60,    57,    58,     0,
      26,     0,     0,     0,     0,    17,     0,    16,     5,     7,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    29,    61,
      27,     0,     0,     0,     0,    18,    32,    34,    36,    38,
      40,    42,    43,    45,    46,    47,    48,    51,    50,    53,
      54,    55,     0,     8,     0,     0,     0,     0,     0,    23,
      21,     0,     0,     9,     0,     0,     0,    22,     0,     0,
      25,     0,    24
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -100,  -100,  -100,    98,    -5,    81,   -99,   119,  -100,  -100,
    -100,  -100,   -17,  -100,  -100,    78,  -100,    84,    85,    -8,
      11,   -57,     7,   -24,    68,   137
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      49,    51,     1,    11,    12,   109,   110,    66,    67,    46,
      12,    93,    94,    95,    96,   117,    13,    56,     5,   120,
      59,    14,   122,    15,     6,     9,    16,    17,    78,     1,
      18,    19,    20,    17,    21,    81,    82,    84,    72,    73,
      11,    12,     7,    68,    69,    70,    71,    74,    75,    76,
      99,   100,   101,    13,    87,     8,    89,     9,    14,    57,
      15,    45,     9,    55,    17,    60,   106,    18,    19,    20,
      52,    21,    53,    11,    12,   102,   103,    91,    92,    97,
      98,    47,    48,    54,    61,   108,    13,    62,    63,    64,
     112,    14,    65,    15,   115,     9,    77,    17,    85,   119,
      18,    19,    20,    80,    21,    11,    12,    79,    11,    12,
     104,   105,    11,    12,   107,   111,   118,   113,    13,   114,
     116,    13,    58,    14,   121,    13,    14,    10,    50,    17,
      14,     1,    17,    46,    12,    83,    17,     4,     0,    86,
       0,     0,     0,     0,     0,     0,    13,     0,    88,    90,
       0,    14,     0,     0,     0,     0,     0,    17
};

static const yytype_int8 yycheck[] =
{
      17,    18,    29,     3,     4,   104,   105,     9,    10,     3,
       4,    68,    69,    70,    71,   114,    16,    22,     0,   118,
      25,    21,   121,    23,     3,    25,    26,    27,    45,    29,
      30,    31,    32,    27,    34,    52,    53,    54,    16,    17,
       3,     4,    27,     5,     6,     7,     8,    18,    19,    20,
      74,    75,    76,    16,    62,    28,    64,    25,    21,    26,
      23,    22,    25,    26,    27,    23,    83,    30,    31,    32,
      27,    34,    27,     3,     4,    22,    23,    66,    67,    72,
      73,    13,    14,    27,    11,   102,    16,    13,    12,    14,
     107,    21,    15,    23,   111,    25,     3,    27,    26,   116,
      30,    31,    32,    23,    34,     3,     4,    28,     3,     4,
      28,    28,     3,     4,    23,    23,    28,    23,    16,    33,
      23,    16,    24,    21,    28,    16,    21,     8,    23,    27,
      21,    29,    27,     3,     4,    54,    27,     0,    -1,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    16,    -1,    63,    65,
      -1,    21,    -1,    -1,    -1,    -1,    -1,    27
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    29,    36,    37,    60,     0,     3,    27,    28,    25,
      42,     3,     4,    16,    21,    23,    26,    27,    30,    31,
      32,    34,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    22,     3,    59,    59,    47,
      23,    47,    27,    27,    27,    26,    39,    26,    38,    39,
      23,    11,    13,    12,    14,    15,     9,    10,     5,     6,
       7,     8,    16,    17,    18,    19,    20,     3,    47,    28,
      23,    47,    47,    40,    47,    26,    50,    54,    53,    54,
      52,    55,    55,    56,    56,    56,    56,    57,    57,    58,
      58,    58,    22,    23,    28,    28,    47,    23,    47,    41,
      41,    23,    47,    23,    33,    47,    23,    41,    28,    47,
      41,    28,    41
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    35,    36,    37,    38,    38,    39,    39,    40,    40,
      41,    41,    41,    41,    41,    42,    42,    42,    42,    43,
      43,    44,    44,    45,    45,    45,    46,    46,    47,    47,
      48,    49,    49,    50,    50,    51,    51,    52,    52,    53,
      53,    54,    54,    54,    55,    55,    55,    55,    55,    56,
      56,    56,    57,    57,    57,    57,    58,    58,    58,    59,
      59,    59,    60
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     5,     1,     2,     1,     2,     3,     5,
       1,     1,     1,     1,     1,     2,     3,     3,     4,     1,
       2,     5,     7,     5,     9,     8,     2,     3,     1,     3,
       1,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     1,     2,     2,     1,
       1,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* PROGRAM: FUNCTION  */
#line 51 "src/C90Parser.y"
                                                                                    { g_root = (yyvsp[0].func); }
#line 1212 "src/C90Parser.tab.cpp"
    break;

  case 3: /* FUNCTION: TYPE_DEF T_VARIABLE T_LPAREN T_RPAREN COMPOUND_STAT  */
#line 53 "src/C90Parser.y"
                                                                                    { (yyval.func) = new Function((new Variable((yyvsp[-4].T_type), (yyvsp[-3].str))), (yyvsp[0].stat)); }
#line 1218 "src/C90Parser.tab.cpp"
    break;

  case 4: /* DECLARATION_LIST: DECLARATION  */
#line 55 "src/C90Parser.y"
                                                                                    { (yyval.decllist) = new Decl_list((yyvsp[0].var))    ; }
#line 1224 "src/C90Parser.tab.cpp"
    break;

  case 5: /* DECLARATION_LIST: DECLARATION DECLARATION_LIST  */
#line 56 "src/C90Parser.y"
                                                                                    { (yyval.decllist) = new Decl_list((yyvsp[-1].var), (yyvsp[0].decllist)); }
#line 1230 "src/C90Parser.tab.cpp"
    break;

  case 6: /* STAT_LIST: STAT  */
#line 58 "src/C90Parser.y"
                                                                                    { (yyval.statlist) = new Stat_list((yyvsp[0].stat))    ; }
#line 1236 "src/C90Parser.tab.cpp"
    break;

  case 7: /* STAT_LIST: STAT STAT_LIST  */
#line 59 "src/C90Parser.y"
                                                                                    { (yyval.statlist) = new Stat_list((yyvsp[-1].stat), (yyvsp[0].statlist)); }
#line 1242 "src/C90Parser.tab.cpp"
    break;

  case 8: /* DECLARATION: TYPE_DEF T_VARIABLE T_SEMI  */
#line 61 "src/C90Parser.y"
                                                                                    { (yyval.var) = new Variable((yyvsp[-2].T_type), (yyvsp[-1].str)); }
#line 1248 "src/C90Parser.tab.cpp"
    break;

  case 9: /* DECLARATION: TYPE_DEF T_VARIABLE T_ASSIGN EXPR T_SEMI  */
#line 62 "src/C90Parser.y"
                                                                                    { (yyval.var) = new Variable((yyvsp[-4].T_type), (yyvsp[-3].str), (yyvsp[-1].expr)); }
#line 1254 "src/C90Parser.tab.cpp"
    break;

  case 10: /* STAT: COMPOUND_STAT  */
#line 64 "src/C90Parser.y"
                                                                                    { (yyval.stat) = (yyvsp[0].stat); }
#line 1260 "src/C90Parser.tab.cpp"
    break;

  case 11: /* STAT: EXPRESSION_STAT  */
#line 65 "src/C90Parser.y"
                                                                                    { (yyval.stat) = (yyvsp[0].stat); }
#line 1266 "src/C90Parser.tab.cpp"
    break;

  case 12: /* STAT: SELECTION_STAT  */
#line 66 "src/C90Parser.y"
                                                                                    { (yyval.stat) = (yyvsp[0].stat); }
#line 1272 "src/C90Parser.tab.cpp"
    break;

  case 13: /* STAT: ITERATION_STAT  */
#line 67 "src/C90Parser.y"
                                                                                    { (yyval.stat) = (yyvsp[0].stat); }
#line 1278 "src/C90Parser.tab.cpp"
    break;

  case 14: /* STAT: JUMP_STAT  */
#line 68 "src/C90Parser.y"
                                                                                    { (yyval.stat) = (yyvsp[0].stat); }
#line 1284 "src/C90Parser.tab.cpp"
    break;

  case 15: /* COMPOUND_STAT: T_LBRACE T_RBRACE  */
#line 70 "src/C90Parser.y"
                                                                                    { (yyval.stat) = new Comp_Stat()      ; }
#line 1290 "src/C90Parser.tab.cpp"
    break;

  case 16: /* COMPOUND_STAT: T_LBRACE STAT_LIST T_RBRACE  */
#line 71 "src/C90Parser.y"
                                                                                    { (yyval.stat) = new Comp_Stat((yyvsp[-1].statlist))    ; }
#line 1296 "src/C90Parser.tab.cpp"
    break;

  case 17: /* COMPOUND_STAT: T_LBRACE DECLARATION_LIST T_RBRACE  */
#line 72 "src/C90Parser.y"
                                                                                    { (yyval.stat) = new Comp_Stat((yyvsp[-1].decllist))    ; }
#line 1302 "src/C90Parser.tab.cpp"
    break;

  case 18: /* COMPOUND_STAT: T_LBRACE DECLARATION_LIST STAT_LIST T_RBRACE  */
#line 73 "src/C90Parser.y"
                                                                                    { (yyval.stat) = new Comp_Stat((yyvsp[-2].decllist), (yyvsp[-1].statlist)); }
#line 1308 "src/C90Parser.tab.cpp"
    break;

  case 19: /* EXPRESSION_STAT: T_SEMI  */
#line 75 "src/C90Parser.y"
                                                                                    { (yyval.stat) = new Expression_Stat()  ; }
#line 1314 "src/C90Parser.tab.cpp"
    break;

  case 20: /* EXPRESSION_STAT: EXPR T_SEMI  */
#line 76 "src/C90Parser.y"
                                                                                    { (yyval.stat) = new Expression_Stat((yyvsp[-1].expr)); }
#line 1320 "src/C90Parser.tab.cpp"
    break;

  case 21: /* SELECTION_STAT: T_IF T_LPAREN EXPR T_RPAREN STAT  */
#line 78 "src/C90Parser.y"
                                                                                    { (yyval.stat) = new If_Stat((yyvsp[-2].expr), (yyvsp[0].stat))    ; }
#line 1326 "src/C90Parser.tab.cpp"
    break;

  case 22: /* SELECTION_STAT: T_IF T_LPAREN EXPR T_RPAREN STAT T_ELSE STAT  */
#line 79 "src/C90Parser.y"
                                                                                    { (yyval.stat) = new If_Stat((yyvsp[-4].expr), (yyvsp[-2].stat), (yyvsp[0].stat)); }
#line 1332 "src/C90Parser.tab.cpp"
    break;

  case 23: /* ITERATION_STAT: T_WHILE T_LPAREN EXPR T_RPAREN STAT  */
#line 81 "src/C90Parser.y"
                                                                                    { (yyval.stat) = new While_Stat((yyvsp[-2].expr), (yyvsp[0].stat))      ; }
#line 1338 "src/C90Parser.tab.cpp"
    break;

  case 24: /* ITERATION_STAT: T_FOR T_LPAREN EXPR T_SEMI EXPR T_SEMI EXPR T_RPAREN STAT  */
#line 82 "src/C90Parser.y"
                                                                                    { (yyval.stat) = new For_Stat((yyvsp[-6].expr), (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].stat)); }
#line 1344 "src/C90Parser.tab.cpp"
    break;

  case 25: /* ITERATION_STAT: T_FOR T_LPAREN DECLARATION EXPR T_SEMI EXPR T_RPAREN STAT  */
#line 83 "src/C90Parser.y"
                                                                                    { (yyval.stat) = new For_Stat((yyvsp[-5].var), (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].stat)); }
#line 1350 "src/C90Parser.tab.cpp"
    break;

  case 26: /* JUMP_STAT: T_RETURN T_SEMI  */
#line 85 "src/C90Parser.y"
                                                                                    { (yyval.stat) = new Jump_Stat()  ; }
#line 1356 "src/C90Parser.tab.cpp"
    break;

  case 27: /* JUMP_STAT: T_RETURN EXPR T_SEMI  */
#line 86 "src/C90Parser.y"
                                                                                    { (yyval.stat) = new Jump_Stat((yyvsp[-1].expr)); }
#line 1362 "src/C90Parser.tab.cpp"
    break;

  case 28: /* EXPR: CONDITIONAL_EXPR  */
#line 88 "src/C90Parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1368 "src/C90Parser.tab.cpp"
    break;

  case 29: /* EXPR: T_VARIABLE T_ASSIGN EXPR  */
#line 89 "src/C90Parser.y"
                                                                                    {          }
#line 1374 "src/C90Parser.tab.cpp"
    break;

  case 30: /* CONDITIONAL_EXPR: LOR_EXPR  */
#line 91 "src/C90Parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1380 "src/C90Parser.tab.cpp"
    break;

  case 31: /* LOR_EXPR: LAND_EXPR  */
#line 93 "src/C90Parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr)                 ; }
#line 1386 "src/C90Parser.tab.cpp"
    break;

  case 32: /* LOR_EXPR: LOR_EXPR T_LOR LAND_EXPR  */
#line 94 "src/C90Parser.y"
                                                                                    { (yyval.expr) = new LogicOr((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1392 "src/C90Parser.tab.cpp"
    break;

  case 33: /* LAND_EXPR: BOR_EXPR  */
#line 96 "src/C90Parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr)                  ; }
#line 1398 "src/C90Parser.tab.cpp"
    break;

  case 34: /* LAND_EXPR: LAND_EXPR T_LAND EQUAL_EXPR  */
#line 97 "src/C90Parser.y"
                                                                                    { (yyval.expr) = new LogicAnd((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1404 "src/C90Parser.tab.cpp"
    break;

  case 35: /* BOR_EXPR: BXOR_EXPR  */
#line 99 "src/C90Parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1410 "src/C90Parser.tab.cpp"
    break;

  case 36: /* BOR_EXPR: BOR_EXPR T_BOR BXOR_EXPR  */
#line 100 "src/C90Parser.y"
                                                                                    { (yyval.expr) = new BitOr((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1416 "src/C90Parser.tab.cpp"
    break;

  case 37: /* BAND_EXPR: EQUAL_EXPR  */
#line 102 "src/C90Parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr)                ; }
#line 1422 "src/C90Parser.tab.cpp"
    break;

  case 38: /* BAND_EXPR: BAND_EXPR T_BAND EQUAL_EXPR  */
#line 103 "src/C90Parser.y"
                                                                                    { (yyval.expr) = new BitAnd((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1428 "src/C90Parser.tab.cpp"
    break;

  case 39: /* BXOR_EXPR: BAND_EXPR  */
#line 105 "src/C90Parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1434 "src/C90Parser.tab.cpp"
    break;

  case 40: /* BXOR_EXPR: BXOR_EXPR T_BXOR BAND_EXPR  */
#line 106 "src/C90Parser.y"
                                                                                    { (yyval.expr) = new BitXOr((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1440 "src/C90Parser.tab.cpp"
    break;

  case 41: /* EQUAL_EXPR: RELATION_EXPR  */
#line 108 "src/C90Parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr)                          ; }
#line 1446 "src/C90Parser.tab.cpp"
    break;

  case 42: /* EQUAL_EXPR: EQUAL_EXPR T_EQUAL RELATION_EXPR  */
#line 109 "src/C90Parser.y"
                                                                                    { (yyval.expr) = new EqualOperator((yyvsp[-2].expr), (yyvsp[0].expr))   ; }
#line 1452 "src/C90Parser.tab.cpp"
    break;

  case 43: /* EQUAL_EXPR: EQUAL_EXPR T_NEQUAL RELATION_EXPR  */
#line 110 "src/C90Parser.y"
                                                                                    { (yyval.expr) = new NotEqualOperator((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1458 "src/C90Parser.tab.cpp"
    break;

  case 44: /* RELATION_EXPR: ARITHMETIC_EXPR  */
#line 112 "src/C90Parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr)                                    ; }
#line 1464 "src/C90Parser.tab.cpp"
    break;

  case 45: /* RELATION_EXPR: RELATION_EXPR T_GT ARITHMETIC_EXPR  */
#line 113 "src/C90Parser.y"
                                                                                    { (yyval.expr) = new GreaterThanOperator((yyvsp[-2].expr), (yyvsp[0].expr))       ; }
#line 1470 "src/C90Parser.tab.cpp"
    break;

  case 46: /* RELATION_EXPR: RELATION_EXPR T_LT ARITHMETIC_EXPR  */
#line 114 "src/C90Parser.y"
                                                                                    { (yyval.expr) = new LessThanOperator((yyvsp[-2].expr), (yyvsp[0].expr))          ; }
#line 1476 "src/C90Parser.tab.cpp"
    break;

  case 47: /* RELATION_EXPR: RELATION_EXPR T_GTE ARITHMETIC_EXPR  */
#line 115 "src/C90Parser.y"
                                                                                    { (yyval.expr) = new GreaterOrEqualThanOperator((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1482 "src/C90Parser.tab.cpp"
    break;

  case 48: /* RELATION_EXPR: RELATION_EXPR T_LTE ARITHMETIC_EXPR  */
#line 116 "src/C90Parser.y"
                                                                                    { (yyval.expr) = new LessOrEqualThanOperator((yyvsp[-2].expr), (yyvsp[0].expr))   ; }
#line 1488 "src/C90Parser.tab.cpp"
    break;

  case 49: /* ARITHMETIC_EXPR: TERM_EXPR  */
#line 118 "src/C90Parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr)                     ; }
#line 1494 "src/C90Parser.tab.cpp"
    break;

  case 50: /* ARITHMETIC_EXPR: ARITHMETIC_EXPR T_ADD TERM_EXPR  */
#line 119 "src/C90Parser.y"
                                                                                    { (yyval.expr) = new AddOperator((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1500 "src/C90Parser.tab.cpp"
    break;

  case 51: /* ARITHMETIC_EXPR: ARITHMETIC_EXPR T_SUB TERM_EXPR  */
#line 120 "src/C90Parser.y"
                                                                                    { (yyval.expr) = new SubOperator((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1506 "src/C90Parser.tab.cpp"
    break;

  case 52: /* TERM_EXPR: UNARY_EXPR  */
#line 122 "src/C90Parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr)                     ; }
#line 1512 "src/C90Parser.tab.cpp"
    break;

  case 53: /* TERM_EXPR: TERM_EXPR T_MULT UNARY_EXPR  */
#line 123 "src/C90Parser.y"
                                                                                    { (yyval.expr) = new MulOperator((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1518 "src/C90Parser.tab.cpp"
    break;

  case 54: /* TERM_EXPR: TERM_EXPR T_DIV UNARY_EXPR  */
#line 124 "src/C90Parser.y"
                                                                                    { (yyval.expr) = new DivOperator((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1524 "src/C90Parser.tab.cpp"
    break;

  case 55: /* TERM_EXPR: TERM_EXPR T_MOD UNARY_EXPR  */
#line 125 "src/C90Parser.y"
                                                                                    { (yyval.expr) = new ModOperator((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1530 "src/C90Parser.tab.cpp"
    break;

  case 56: /* UNARY_EXPR: FACTOR_EXPR  */
#line 127 "src/C90Parser.y"
                                                                                    { (yyval.expr) = (yyvsp[0].expr)                 ; }
#line 1536 "src/C90Parser.tab.cpp"
    break;

  case 57: /* UNARY_EXPR: T_SUB FACTOR_EXPR  */
#line 128 "src/C90Parser.y"
                                                                                    { (yyval.expr) = new NegOperator((yyvsp[0].expr)); }
#line 1542 "src/C90Parser.tab.cpp"
    break;

  case 58: /* UNARY_EXPR: T_NOT FACTOR_EXPR  */
#line 129 "src/C90Parser.y"
                                                                                    { (yyval.expr) = new NotOperator((yyvsp[0].expr))   ; }
#line 1548 "src/C90Parser.tab.cpp"
    break;

  case 59: /* FACTOR_EXPR: T_NUMBER  */
#line 131 "src/C90Parser.y"
                                                                                    { (yyval.expr) = new Number((yyvsp[0].number))  ; }
#line 1554 "src/C90Parser.tab.cpp"
    break;

  case 60: /* FACTOR_EXPR: T_VARIABLE  */
#line 132 "src/C90Parser.y"
                                                                                    { (yyval.expr) = new Variable((yyvsp[0].str)); }
#line 1560 "src/C90Parser.tab.cpp"
    break;

  case 61: /* FACTOR_EXPR: T_LPAREN EXPR T_RPAREN  */
#line 133 "src/C90Parser.y"
                                                                                    { (yyval.expr) = (yyvsp[-1].expr)              ; }
#line 1566 "src/C90Parser.tab.cpp"
    break;

  case 62: /* TYPE_DEF: T_INT_TYPE  */
#line 135 "src/C90Parser.y"
                                                                                    { (yyval.T_type) = TypeDef::INT; }
#line 1572 "src/C90Parser.tab.cpp"
    break;


#line 1576 "src/C90Parser.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 137 "src/C90Parser.y"


const Function *g_root;

const Function *parseAST(FILE *fileInput)
{
  g_root=0;
  yyin = fileInput;
  yyparse();
  return g_root;
}
