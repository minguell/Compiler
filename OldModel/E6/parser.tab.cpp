/* A Bison parser, made by GNU Bison 3.8.2.  */

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
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 6 "parser.ypp"
 
//Aluno: Miguel Dutra Fontes Guerra
//Cartão UFRGS: 00342573
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include "symbols.hpp"
#include "ast.hpp"
#include "semantic.hpp"
#include "tac.hpp"

using namespace std;

extern int lineNumber;
extern const char* outputFile;

int yylex();
void yyerror(string msg);
int getLineNumber();

#line 94 "parser.tab.cpp"

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

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_KW_BYTE = 3,                    /* KW_BYTE  */
  YYSYMBOL_KW_INT = 4,                     /* KW_INT  */
  YYSYMBOL_KW_REAL = 5,                    /* KW_REAL  */
  YYSYMBOL_KW_IF = 6,                      /* KW_IF  */
  YYSYMBOL_KW_ELSE = 7,                    /* KW_ELSE  */
  YYSYMBOL_KW_DO = 8,                      /* KW_DO  */
  YYSYMBOL_KW_WHILE = 9,                   /* KW_WHILE  */
  YYSYMBOL_KW_READ = 10,                   /* KW_READ  */
  YYSYMBOL_KW_PRINT = 11,                  /* KW_PRINT  */
  YYSYMBOL_KW_RETURN = 12,                 /* KW_RETURN  */
  YYSYMBOL_OPERATOR_LE = 13,               /* OPERATOR_LE  */
  YYSYMBOL_OPERATOR_GE = 14,               /* OPERATOR_GE  */
  YYSYMBOL_OPERATOR_EQ = 15,               /* OPERATOR_EQ  */
  YYSYMBOL_OPERATOR_DIF = 16,              /* OPERATOR_DIF  */
  YYSYMBOL_TK_IDENTIFIER = 17,             /* TK_IDENTIFIER  */
  YYSYMBOL_LIT_INT = 18,                   /* LIT_INT  */
  YYSYMBOL_LIT_CHAR = 19,                  /* LIT_CHAR  */
  YYSYMBOL_LIT_REAL = 20,                  /* LIT_REAL  */
  YYSYMBOL_LIT_STRING = 21,                /* LIT_STRING  */
  YYSYMBOL_TOKEN_ERROR = 22,               /* TOKEN_ERROR  */
  YYSYMBOL_LOWER_THAN_ELSE = 23,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_24_ = 24,                       /* '+'  */
  YYSYMBOL_25_ = 25,                       /* '-'  */
  YYSYMBOL_26_ = 26,                       /* '*'  */
  YYSYMBOL_27_ = 27,                       /* '/'  */
  YYSYMBOL_28_ = 28,                       /* '&'  */
  YYSYMBOL_29_ = 29,                       /* '|'  */
  YYSYMBOL_30_ = 30,                       /* '~'  */
  YYSYMBOL_31_ = 31,                       /* '('  */
  YYSYMBOL_32_ = 32,                       /* ')'  */
  YYSYMBOL_33_ = 33,                       /* '<'  */
  YYSYMBOL_34_ = 34,                       /* '>'  */
  YYSYMBOL_35_ = 35,                       /* '='  */
  YYSYMBOL_36_ = 36,                       /* ';'  */
  YYSYMBOL_37_ = 37,                       /* ','  */
  YYSYMBOL_38_ = 38,                       /* '['  */
  YYSYMBOL_39_ = 39,                       /* ']'  */
  YYSYMBOL_40_ = 40,                       /* '{'  */
  YYSYMBOL_41_ = 41,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_program = 43,                   /* program  */
  YYSYMBOL_ldecl = 44,                     /* ldecl  */
  YYSYMBOL_dec = 45,                       /* dec  */
  YYSYMBOL_vardec = 46,                    /* vardec  */
  YYSYMBOL_expr_vet_elem_list = 47,        /* expr_vet_elem_list  */
  YYSYMBOL_expr_vet_elem = 48,             /* expr_vet_elem  */
  YYSYMBOL_expr_vet_real_list = 49,        /* expr_vet_real_list  */
  YYSYMBOL_vetdec = 50,                    /* vetdec  */
  YYSYMBOL_parlist = 51,                   /* parlist  */
  YYSYMBOL_parlist_nvazio = 52,            /* parlist_nvazio  */
  YYSYMBOL_par_elem = 53,                  /* par_elem  */
  YYSYMBOL_fundec = 54,                    /* fundec  */
  YYSYMBOL_cmd_blc = 55,                   /* cmd_blc  */
  YYSYMBOL_cmd_lst = 56,                   /* cmd_lst  */
  YYSYMBOL_print_lst = 57,                 /* print_lst  */
  YYSYMBOL_print_elem = 58,                /* print_elem  */
  YYSYMBOL_cmd = 59,                       /* cmd  */
  YYSYMBOL_par = 60,                       /* par  */
  YYSYMBOL_par_nvazio = 61,                /* par_nvazio  */
  YYSYMBOL_func = 62,                      /* func  */
  YYSYMBOL_expr = 63                       /* expr  */
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
typedef yytype_uint8 yy_state_t;

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

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   438

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  177

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   278


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
       2,     2,     2,     2,     2,     2,     2,     2,    28,     2,
      31,    32,    26,    24,    37,    25,     2,    27,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    36,
      33,    35,    34,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    38,     2,    39,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,    29,    41,    30,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    94,    94,   136,   137,   140,   141,   142,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   164,   165,   168,
     169,   171,   172,   175,   176,   177,   178,   179,   180,   187,
     188,   191,   192,   195,   196,   197,   200,   201,   202,   205,
     208,   209,   216,   217,   220,   221,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   243,   244,   247,
     248,   253,   255,   256,   257,   258,   259,   260,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275
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
  "\"end of file\"", "error", "\"invalid token\"", "KW_BYTE", "KW_INT",
  "KW_REAL", "KW_IF", "KW_ELSE", "KW_DO", "KW_WHILE", "KW_READ",
  "KW_PRINT", "KW_RETURN", "OPERATOR_LE", "OPERATOR_GE", "OPERATOR_EQ",
  "OPERATOR_DIF", "TK_IDENTIFIER", "LIT_INT", "LIT_CHAR", "LIT_REAL",
  "LIT_STRING", "TOKEN_ERROR", "LOWER_THAN_ELSE", "'+'", "'-'", "'*'",
  "'/'", "'&'", "'|'", "'~'", "'('", "')'", "'<'", "'>'", "'='", "';'",
  "','", "'['", "']'", "'{'", "'}'", "$accept", "program", "ldecl", "dec",
  "vardec", "expr_vet_elem_list", "expr_vet_elem", "expr_vet_real_list",
  "vetdec", "parlist", "parlist_nvazio", "par_elem", "fundec", "cmd_blc",
  "cmd_lst", "print_lst", "print_elem", "cmd", "par", "par_nvazio", "func",
  "expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-109)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      61,   -13,     1,    15,    36,  -109,    61,  -109,  -109,  -109,
      -8,     2,     3,  -109,  -109,    87,    85,    -5,    87,    94,
      -5,    87,   116,    -5,    57,    76,    83,    90,  -109,    80,
      89,    93,   103,    47,  -109,  -109,  -109,    -5,    -5,  -109,
      55,    91,   104,   111,   112,    82,   105,   113,   118,   125,
     117,  -109,  -109,  -109,    86,    87,  -109,  -109,  -109,    -5,
      -5,   151,   331,    -5,    -5,    -5,    -5,    -5,    -5,    -5,
      -5,    -5,    -5,    -5,    -5,     9,    86,  -109,  -109,  -109,
      41,    86,  -109,  -109,  -109,    51,    -1,  -109,  -109,   120,
    -109,   210,   144,  -109,   173,   173,   173,   173,   397,   397,
     404,   404,   151,   151,   173,   173,   101,  -109,  -109,   101,
    -109,  -109,   133,  -109,   131,    -1,    -5,   146,    42,    -5,
     -16,  -109,  -109,   134,    -1,  -109,    -5,  -109,  -109,  -109,
     140,   159,   161,   168,   162,    -5,   199,   166,   174,  -109,
     175,    42,   375,   235,    -5,    -5,  -109,  -109,  -109,  -109,
     101,  -109,   133,  -109,   353,    -5,    -1,  -109,  -109,  -109,
    -109,   259,   188,  -109,  -109,    -1,   283,  -109,  -109,   183,
     202,  -109,    -5,    -1,   307,  -109,  -109
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     0,     0,     2,     4,     5,     6,     7,
       0,     0,     0,     1,     3,    29,     0,     0,    29,     0,
       0,    29,     0,     0,     0,     0,     0,     0,    30,    31,
       0,     0,     0,    64,    65,    66,    67,     0,     0,    62,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,    33,    35,     0,     0,    12,    11,    13,    58,
       0,    76,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     9,     8,    10,
       0,     0,    14,    15,    16,     0,    40,    37,    32,     0,
      57,    59,     0,    81,    80,    79,    77,    78,    68,    69,
      70,    71,    72,    73,    74,    75,     0,    26,    36,     0,
      24,    38,     0,    28,     0,     0,     0,     0,     0,     0,
       0,    56,    55,     0,    40,    61,     0,    63,    20,    19,
       0,    17,     0,    21,     0,     0,     0,     0,     0,    44,
       0,    42,    45,     0,     0,     0,    39,    41,    60,    25,
       0,    23,     0,    27,     0,     0,     0,    50,    48,    43,
      49,     0,     0,    18,    22,     0,     0,    53,    46,     0,
      51,    54,     0,     0,     0,    52,    47
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -109,  -109,   213,  -109,  -109,  -108,  -109,    68,  -109,    10,
     176,  -109,  -109,   -52,   106,    88,  -109,   -98,  -109,   102,
    -109,   -17
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     4,     5,     6,     7,   130,   131,   134,     8,    27,
      28,    29,     9,   122,   123,   140,   141,   124,    89,    90,
      39,    91
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      40,   132,    87,    45,    10,   114,    50,   115,   116,   117,
     118,   119,    33,    34,    35,    36,   120,   136,    11,   144,
      61,    62,   145,    15,   108,    37,    38,    16,    41,   111,
      17,    46,    12,    18,    21,   121,    13,    19,    22,    86,
      20,    23,   163,    92,   106,   107,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   167,    33,
      34,    35,    36,   139,     1,     2,     3,   170,    63,    64,
      65,    66,    37,    38,    51,   175,   109,   110,    59,    67,
      68,    69,    70,    71,    72,    60,   112,   113,    73,    74,
      24,    25,    26,    52,    75,    63,    64,    65,    66,   137,
      53,   142,   143,    30,    31,    32,    67,    68,    69,    70,
      71,    72,    42,    43,    44,    73,    74,    55,   154,   128,
     129,    80,    54,    76,   142,    56,    86,   161,   162,    57,
      63,    64,    65,    66,    47,    48,    49,    81,   166,    58,
      77,    67,    68,    69,    70,    71,    72,    78,    79,    82,
      73,    74,   125,   133,    83,   174,    85,    63,    64,    65,
      66,    84,   135,   138,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,   156,   146,   149,    73,    74,    63,
      64,    65,    66,   127,    73,    74,    -1,    -1,    -1,    -1,
      67,    68,    69,    70,    71,    72,   150,   151,   153,    73,
      74,    63,    64,    65,    66,   152,    -1,    -1,   155,   173,
     157,   158,    67,    68,    69,    70,    71,    72,   172,    14,
     164,    73,    74,    63,    64,    65,    66,   169,   148,   159,
     147,    88,     0,     0,    67,    68,    69,    70,    71,    72,
       0,     0,     0,    73,    74,     0,     0,   126,    63,    64,
      65,    66,     0,     0,     0,     0,     0,     0,     0,    67,
      68,    69,    70,    71,    72,     0,     0,     0,    73,    74,
       0,   160,    63,    64,    65,    66,     0,     0,     0,     0,
       0,     0,     0,    67,    68,    69,    70,    71,    72,     0,
       0,     0,    73,    74,     0,   168,    63,    64,    65,    66,
       0,     0,     0,     0,     0,     0,     0,    67,    68,    69,
      70,    71,    72,     0,     0,     0,    73,    74,     0,   171,
      63,    64,    65,    66,     0,     0,     0,     0,     0,     0,
       0,    67,    68,    69,    70,    71,    72,     0,     0,     0,
      73,    74,     0,   176,    63,    64,    65,    66,     0,     0,
       0,     0,     0,     0,     0,    67,    68,    69,    70,    71,
      72,     0,     0,    93,    73,    74,    63,    64,    65,    66,
       0,     0,     0,     0,     0,     0,     0,    67,    68,    69,
      70,    71,    72,     0,     0,   165,    73,    74,    63,    64,
      65,    66,     0,     0,     0,     0,     0,     0,     0,    67,
      68,    69,    70,    71,    72,     0,     0,     0,    73,    74,
      63,    64,    65,    66,     0,     0,     0,    63,    64,    65,
      66,     0,     0,    69,    70,    71,    72,     0,     0,     0,
      73,    74,    71,    72,     0,     0,     0,    73,    74
};

static const yytype_int16 yycheck[] =
{
      17,   109,    54,    20,    17,     6,    23,     8,     9,    10,
      11,    12,    17,    18,    19,    20,    17,   115,    17,    35,
      37,    38,    38,    31,    76,    30,    31,    35,    18,    81,
      38,    21,    17,    31,    31,    36,     0,    35,    35,    40,
      38,    38,   150,    60,    35,    36,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,   156,    17,
      18,    19,    20,    21,     3,     4,     5,   165,    13,    14,
      15,    16,    30,    31,    17,   173,    35,    36,    31,    24,
      25,    26,    27,    28,    29,    38,    35,    36,    33,    34,
       3,     4,     5,    17,    39,    13,    14,    15,    16,   116,
      17,   118,   119,    18,    19,    20,    24,    25,    26,    27,
      28,    29,    18,    19,    20,    33,    34,    37,   135,    18,
      19,    39,    32,    32,   141,    36,    40,   144,   145,    36,
      13,    14,    15,    16,    18,    19,    20,    32,   155,    36,
      36,    24,    25,    26,    27,    28,    29,    36,    36,    36,
      33,    34,    32,    20,    36,   172,    39,    13,    14,    15,
      16,    36,    31,    17,    13,    14,    15,    16,    24,    25,
      26,    27,    28,    29,     8,    41,    36,    33,    34,    13,
      14,    15,    16,    39,    33,    34,    13,    14,    15,    16,
      24,    25,    26,    27,    28,    29,    37,    36,    36,    33,
      34,    13,    14,    15,    16,    37,    33,    34,     9,     7,
      36,    36,    24,    25,    26,    27,    28,    29,    35,     6,
     152,    33,    34,    13,    14,    15,    16,    39,   126,   141,
     124,    55,    -1,    -1,    24,    25,    26,    27,    28,    29,
      -1,    -1,    -1,    33,    34,    -1,    -1,    37,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      25,    26,    27,    28,    29,    -1,    -1,    -1,    33,    34,
      -1,    36,    13,    14,    15,    16,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    25,    26,    27,    28,    29,    -1,
      -1,    -1,    33,    34,    -1,    36,    13,    14,    15,    16,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    26,
      27,    28,    29,    -1,    -1,    -1,    33,    34,    -1,    36,
      13,    14,    15,    16,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    25,    26,    27,    28,    29,    -1,    -1,    -1,
      33,    34,    -1,    36,    13,    14,    15,    16,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    25,    26,    27,    28,
      29,    -1,    -1,    32,    33,    34,    13,    14,    15,    16,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,    33,    34,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      25,    26,    27,    28,    29,    -1,    -1,    -1,    33,    34,
      13,    14,    15,    16,    -1,    -1,    -1,    13,    14,    15,
      16,    -1,    -1,    26,    27,    28,    29,    -1,    -1,    -1,
      33,    34,    28,    29,    -1,    -1,    -1,    33,    34
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,    43,    44,    45,    46,    50,    54,
      17,    17,    17,     0,    44,    31,    35,    38,    31,    35,
      38,    31,    35,    38,     3,     4,     5,    51,    52,    53,
      18,    19,    20,    17,    18,    19,    20,    30,    31,    62,
      63,    51,    18,    19,    20,    63,    51,    18,    19,    20,
      63,    17,    17,    17,    32,    37,    36,    36,    36,    31,
      38,    63,    63,    13,    14,    15,    16,    24,    25,    26,
      27,    28,    29,    33,    34,    39,    32,    36,    36,    36,
      39,    32,    36,    36,    36,    39,    40,    55,    52,    60,
      61,    63,    63,    32,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    35,    36,    55,    35,
      36,    55,    35,    36,     6,     8,     9,    10,    11,    12,
      17,    36,    55,    56,    59,    32,    37,    39,    18,    19,
      47,    48,    47,    20,    49,    31,    59,    63,    17,    21,
      57,    58,    63,    63,    35,    38,    41,    56,    61,    36,
      37,    36,    37,    36,    63,     9,     8,    36,    36,    57,
      36,    63,    63,    47,    49,    32,    63,    59,    36,    39,
      59,    36,    35,     7,    63,    59,    36
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    47,    47,    48,
      48,    49,    49,    50,    50,    50,    50,    50,    50,    51,
      51,    52,    52,    53,    53,    53,    54,    54,    54,    55,
      56,    56,    57,    57,    58,    58,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    60,    60,    61,
      61,    62,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     1,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     1,     3,     1,
       1,     1,     3,     8,     6,     8,     6,     8,     6,     0,
       1,     1,     3,     2,     2,     2,     6,     6,     6,     3,
       0,     2,     1,     2,     1,     1,     4,     7,     3,     3,
       3,     5,     7,     4,     5,     1,     1,     1,     0,     1,
       3,     4,     1,     4,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     3,     3,     3,
       3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
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
  case 2: /* program: ldecl  */
#line 94 "parser.ypp"
                        { (yyval.ast) = (yyvsp[0].ast);
                          TAC* code;
                          astPrint((yyval.ast),0); printf("\n");
                          
                          // DECLARACOES
                          checkAndSetDeclarations((yyval.ast));
                          checkUndeclared();
                          
                          //ATRIBUICOES E OPERACOES
                          checkOperands((yyval.ast));
                          checkAssignments((yyval.ast));
                          
                          // VARIAVEIS
                          checkVariables((yyval.ast));

                          // VETORES
                          checkVectors((yyval.ast));
                        
                          // FUNÇÕES
                          checkNumParFunc((yyval.ast));
                          checkTypeParFunc((yyval.ast));
                          checkReturn((yyval.ast));
                          
                          // CONSTRUÇÃO E PRINT DAS TACS
                          code = generateCode((yyval.ast));
                          tacPrintBackwards(code);

                          code = tacReverse(code);
                          generateAsm(code);


                          std::ofstream outFile(outputFile);
                          if (!outFile.is_open())
                          {
                                std::cerr << "Erro ao abrir o arquivo de saída.\n";
                                return 1;
                          }
                          descompile((yyval.ast), outFile);
                          outFile.close(); 
                        }
#line 1345 "parser.tab.cpp"
    break;

  case 3: /* ldecl: dec ldecl  */
#line 136 "parser.ypp"
                        { vector<AST*> children = {(yyvsp[-1].ast),(yyvsp[0].ast)}; (yyval.ast) = new AST(AST_LDECL, children); }
#line 1351 "parser.tab.cpp"
    break;

  case 4: /* ldecl: %empty  */
#line 137 "parser.ypp"
                        { (yyval.ast) = nullptr; }
#line 1357 "parser.tab.cpp"
    break;

  case 5: /* dec: vardec  */
#line 140 "parser.ypp"
                        { (yyval.ast) = (yyvsp[0].ast); }
#line 1363 "parser.tab.cpp"
    break;

  case 6: /* dec: vetdec  */
#line 141 "parser.ypp"
                        { (yyval.ast) = (yyvsp[0].ast); }
#line 1369 "parser.tab.cpp"
    break;

  case 7: /* dec: fundec  */
#line 142 "parser.ypp"
                        { (yyval.ast) = (yyvsp[0].ast); }
#line 1375 "parser.tab.cpp"
    break;

  case 8: /* vardec: KW_INT TK_IDENTIFIER '=' LIT_CHAR ';'  */
#line 149 "parser.ypp"
                                                { vector<AST*> children = {new AST(AST_SYMBOL, {}, (yyvsp[-1].symbol))}; (yyval.ast) = new AST(AST_INT_VARDEC, children, (yyvsp[-3].symbol));}
#line 1381 "parser.tab.cpp"
    break;

  case 9: /* vardec: KW_INT TK_IDENTIFIER '=' LIT_INT ';'  */
#line 150 "parser.ypp"
                                                { vector<AST*> children = {new AST(AST_SYMBOL, {}, (yyvsp[-1].symbol))}; (yyval.ast) = new AST(AST_INT_VARDEC, children, (yyvsp[-3].symbol));}
#line 1387 "parser.tab.cpp"
    break;

  case 10: /* vardec: KW_INT TK_IDENTIFIER '=' LIT_REAL ';'  */
#line 151 "parser.ypp"
                                                { vector<AST*> children = {new AST(AST_SYMBOL, {}, (yyvsp[-1].symbol))}; (yyval.ast) = new AST(AST_INT_VARDEC, children, (yyvsp[-3].symbol));}
#line 1393 "parser.tab.cpp"
    break;

  case 11: /* vardec: KW_BYTE TK_IDENTIFIER '=' LIT_CHAR ';'  */
#line 152 "parser.ypp"
                                                { vector<AST*> children = {new AST(AST_SYMBOL, {}, (yyvsp[-1].symbol))}; (yyval.ast) = new AST(AST_BYTE_VARDEC, children, (yyvsp[-3].symbol));}
#line 1399 "parser.tab.cpp"
    break;

  case 12: /* vardec: KW_BYTE TK_IDENTIFIER '=' LIT_INT ';'  */
#line 153 "parser.ypp"
                                                { vector<AST*> children = {new AST(AST_SYMBOL, {}, (yyvsp[-1].symbol))}; (yyval.ast) = new AST(AST_BYTE_VARDEC, children, (yyvsp[-3].symbol));}
#line 1405 "parser.tab.cpp"
    break;

  case 13: /* vardec: KW_BYTE TK_IDENTIFIER '=' LIT_REAL ';'  */
#line 154 "parser.ypp"
                                                { vector<AST*> children = {new AST(AST_SYMBOL, {}, (yyvsp[-1].symbol))}; (yyval.ast) = new AST(AST_BYTE_VARDEC, children, (yyvsp[-3].symbol));}
#line 1411 "parser.tab.cpp"
    break;

  case 14: /* vardec: KW_REAL TK_IDENTIFIER '=' LIT_INT ';'  */
#line 155 "parser.ypp"
                                                { vector<AST*> children = {new AST(AST_SYMBOL, {}, (yyvsp[-1].symbol))}; (yyval.ast) = new AST(AST_REAL_VARDEC, children, (yyvsp[-3].symbol));}
#line 1417 "parser.tab.cpp"
    break;

  case 15: /* vardec: KW_REAL TK_IDENTIFIER '=' LIT_CHAR ';'  */
#line 156 "parser.ypp"
                                                { vector<AST*> children = {new AST(AST_SYMBOL, {}, (yyvsp[-1].symbol))}; (yyval.ast) = new AST(AST_REAL_VARDEC, children, (yyvsp[-3].symbol));}
#line 1423 "parser.tab.cpp"
    break;

  case 16: /* vardec: KW_REAL TK_IDENTIFIER '=' LIT_REAL ';'  */
#line 157 "parser.ypp"
                                                { vector<AST*> children = {new AST(AST_SYMBOL, {}, (yyvsp[-1].symbol))}; (yyval.ast) = new AST(AST_REAL_VARDEC, children, (yyvsp[-3].symbol));}
#line 1429 "parser.tab.cpp"
    break;

  case 17: /* expr_vet_elem_list: expr_vet_elem  */
#line 164 "parser.ypp"
                                                                { (yyval.ast) = (yyvsp[0].ast); }
#line 1435 "parser.tab.cpp"
    break;

  case 18: /* expr_vet_elem_list: expr_vet_elem ',' expr_vet_elem_list  */
#line 165 "parser.ypp"
                                                                { vector<AST*> children = {(yyvsp[-2].ast), (yyvsp[0].ast)}; (yyval.ast) = new AST(AST_EXPR_VET_ELEM, children); }
#line 1441 "parser.tab.cpp"
    break;

  case 19: /* expr_vet_elem: LIT_CHAR  */
#line 168 "parser.ypp"
                                                                { vector<AST*> children; (yyval.ast) = new AST(AST_SYMBOL, children, (yyvsp[0].symbol)); }
#line 1447 "parser.tab.cpp"
    break;

  case 20: /* expr_vet_elem: LIT_INT  */
#line 169 "parser.ypp"
                                                                { vector<AST*> children; (yyval.ast) = new AST(AST_SYMBOL, children, (yyvsp[0].symbol)); }
#line 1453 "parser.tab.cpp"
    break;

  case 21: /* expr_vet_real_list: LIT_REAL  */
#line 171 "parser.ypp"
                                                                { vector<AST*> children; (yyval.ast) = new AST(AST_SYMBOL, children, (yyvsp[0].symbol)); }
#line 1459 "parser.tab.cpp"
    break;

  case 22: /* expr_vet_real_list: LIT_REAL ',' expr_vet_real_list  */
#line 172 "parser.ypp"
                                                                { vector<AST*> children = {(yyvsp[0].ast)}; (yyval.ast) = new AST(AST_SYMBOL, children, (yyvsp[-2].symbol)); }
#line 1465 "parser.tab.cpp"
    break;

  case 23: /* vetdec: KW_INT TK_IDENTIFIER '[' expr ']' '=' expr_vet_elem_list ';'  */
#line 175 "parser.ypp"
                                                                        { vector<AST*> children = {(yyvsp[-4].ast), (yyvsp[-1].ast)}; (yyval.ast) = new AST(AST_INT_VETDEC, children, (yyvsp[-6].symbol));}
#line 1471 "parser.tab.cpp"
    break;

  case 24: /* vetdec: KW_INT TK_IDENTIFIER '[' expr ']' ';'  */
#line 176 "parser.ypp"
                                                                        { vector<AST*> children = {(yyvsp[-2].ast)}; (yyval.ast) = new AST(AST_INT_VETDEC_VAZIO, children, (yyvsp[-4].symbol));}
#line 1477 "parser.tab.cpp"
    break;

  case 25: /* vetdec: KW_BYTE TK_IDENTIFIER '[' expr ']' '=' expr_vet_elem_list ';'  */
#line 177 "parser.ypp"
                                                                        { vector<AST*> children = {(yyvsp[-4].ast), (yyvsp[-1].ast)}; (yyval.ast) = new AST(AST_BYTE_VETDEC, children, (yyvsp[-6].symbol));}
#line 1483 "parser.tab.cpp"
    break;

  case 26: /* vetdec: KW_BYTE TK_IDENTIFIER '[' expr ']' ';'  */
#line 178 "parser.ypp"
                                                                        { vector<AST*> children = {(yyvsp[-2].ast)}; (yyval.ast) = new AST(AST_BYTE_VETDEC_VAZIO, children, (yyvsp[-4].symbol));}
#line 1489 "parser.tab.cpp"
    break;

  case 27: /* vetdec: KW_REAL TK_IDENTIFIER '[' expr ']' '=' expr_vet_real_list ';'  */
#line 179 "parser.ypp"
                                                                        { vector<AST*> children = {(yyvsp[-4].ast), (yyvsp[-1].ast)}; (yyval.ast) = new AST(AST_REAL_VETDEC, children, (yyvsp[-6].symbol));}
#line 1495 "parser.tab.cpp"
    break;

  case 28: /* vetdec: KW_REAL TK_IDENTIFIER '[' expr ']' ';'  */
#line 180 "parser.ypp"
                                                                        { vector<AST*> children = {(yyvsp[-2].ast)}; (yyval.ast) = new AST(AST_REAL_VETDEC_VAZIO, children, (yyvsp[-4].symbol));}
#line 1501 "parser.tab.cpp"
    break;

  case 29: /* parlist: %empty  */
#line 187 "parser.ypp"
                                        {(yyval.ast) = nullptr;}
#line 1507 "parser.tab.cpp"
    break;

  case 30: /* parlist: parlist_nvazio  */
#line 188 "parser.ypp"
                                        {(yyval.ast) = (yyvsp[0].ast);}
#line 1513 "parser.tab.cpp"
    break;

  case 31: /* parlist_nvazio: par_elem  */
#line 191 "parser.ypp"
                                        {(yyval.ast) = (yyvsp[0].ast);}
#line 1519 "parser.tab.cpp"
    break;

  case 32: /* parlist_nvazio: par_elem ',' parlist_nvazio  */
#line 192 "parser.ypp"
                                        {vector<AST*> children = {(yyvsp[-2].ast), (yyvsp[0].ast)}; (yyval.ast) = new AST(AST_PAR_LIST, children);}
#line 1525 "parser.tab.cpp"
    break;

  case 33: /* par_elem: KW_INT TK_IDENTIFIER  */
#line 195 "parser.ypp"
                                           {vector<AST*> children; (yyval.ast) = new AST(AST_PAR_INT_SYMBOL, children, (yyvsp[0].symbol)); }
#line 1531 "parser.tab.cpp"
    break;

  case 34: /* par_elem: KW_BYTE TK_IDENTIFIER  */
#line 196 "parser.ypp"
                                           {vector<AST*> children; (yyval.ast) = new AST(AST_PAR_BYTE_SYMBOL, children, (yyvsp[0].symbol));}
#line 1537 "parser.tab.cpp"
    break;

  case 35: /* par_elem: KW_REAL TK_IDENTIFIER  */
#line 197 "parser.ypp"
                                           {vector<AST*> children; (yyval.ast) = new AST(AST_PAR_REAL_SYMBOL, children, (yyvsp[0].symbol));}
#line 1543 "parser.tab.cpp"
    break;

  case 36: /* fundec: KW_INT TK_IDENTIFIER '(' parlist ')' cmd_blc  */
#line 200 "parser.ypp"
                                                    { vector<AST*> children = {(yyvsp[-2].ast),(yyvsp[0].ast)}; (yyval.ast) = new AST(AST_INT_FUNDEC, children, (yyvsp[-4].symbol));}
#line 1549 "parser.tab.cpp"
    break;

  case 37: /* fundec: KW_BYTE TK_IDENTIFIER '(' parlist ')' cmd_blc  */
#line 201 "parser.ypp"
                                                    { vector<AST*> children = {(yyvsp[-2].ast),(yyvsp[0].ast)}; (yyval.ast) = new AST(AST_BYTE_FUNDEC, children, (yyvsp[-4].symbol));}
#line 1555 "parser.tab.cpp"
    break;

  case 38: /* fundec: KW_REAL TK_IDENTIFIER '(' parlist ')' cmd_blc  */
#line 202 "parser.ypp"
                                                    { vector<AST*> children = {(yyvsp[-2].ast),(yyvsp[0].ast)}; (yyval.ast) = new AST(AST_REAL_FUNDEC, children, (yyvsp[-4].symbol));}
#line 1561 "parser.tab.cpp"
    break;

  case 39: /* cmd_blc: '{' cmd_lst '}'  */
#line 205 "parser.ypp"
                       { vector<AST*> children = {(yyvsp[-1].ast)}; (yyval.ast) = new AST(AST_CMD_BLOCK, children); }
#line 1567 "parser.tab.cpp"
    break;

  case 40: /* cmd_lst: %empty  */
#line 208 "parser.ypp"
         { (yyval.ast) = nullptr; }
#line 1573 "parser.tab.cpp"
    break;

  case 41: /* cmd_lst: cmd cmd_lst  */
#line 209 "parser.ypp"
                        { vector<AST*> children = {(yyvsp[-1].ast), (yyvsp[0].ast)}; (yyval.ast) = new AST(AST_CMD_LIST, children); }
#line 1579 "parser.tab.cpp"
    break;

  case 42: /* print_lst: print_elem  */
#line 216 "parser.ypp"
                                         { vector<AST*> children = {(yyvsp[0].ast), nullptr}; (yyval.ast) = new AST(AST_PRINT_LIST, children); }
#line 1585 "parser.tab.cpp"
    break;

  case 43: /* print_lst: print_elem print_lst  */
#line 217 "parser.ypp"
                                         { vector<AST*> children = {(yyvsp[-1].ast), (yyvsp[0].ast)}; (yyval.ast) = new AST(AST_PRINT_LIST, children); }
#line 1591 "parser.tab.cpp"
    break;

  case 44: /* print_elem: LIT_STRING  */
#line 220 "parser.ypp"
                                 { (yyval.ast) = new AST(AST_SYMBOL, {}, (yyvsp[0].symbol)); }
#line 1597 "parser.tab.cpp"
    break;

  case 45: /* print_elem: expr  */
#line 221 "parser.ypp"
                                 { (yyval.ast) = (yyvsp[0].ast); }
#line 1603 "parser.tab.cpp"
    break;

  case 46: /* cmd: TK_IDENTIFIER '=' expr ';'  */
#line 228 "parser.ypp"
                                                { vector<AST*> children = {(yyvsp[-1].ast)}; (yyval.ast) = new AST(AST_ASSIGNMENT, children, (yyvsp[-3].symbol));}
#line 1609 "parser.tab.cpp"
    break;

  case 47: /* cmd: TK_IDENTIFIER '[' expr ']' '=' expr ';'  */
#line 229 "parser.ypp"
                                                { vector<AST*> children = {(yyvsp[-4].ast), (yyvsp[-1].ast)}; (yyval.ast) = new AST(AST_VET_ASSIGNMENT, children, (yyvsp[-6].symbol));}
#line 1615 "parser.tab.cpp"
    break;

  case 48: /* cmd: KW_PRINT print_lst ';'  */
#line 230 "parser.ypp"
                                                { vector<AST*> children = {(yyvsp[-1].ast)}; (yyval.ast) = new AST(AST_PRINT, children);}
#line 1621 "parser.tab.cpp"
    break;

  case 49: /* cmd: KW_RETURN expr ';'  */
#line 231 "parser.ypp"
                                                { vector<AST*> children = {(yyvsp[-1].ast)}; (yyval.ast) = new AST(AST_RETURN, children);}
#line 1627 "parser.tab.cpp"
    break;

  case 50: /* cmd: KW_READ TK_IDENTIFIER ';'  */
#line 232 "parser.ypp"
                                                { vector<AST*> children; (yyval.ast) = new AST(AST_READ, children, (yyvsp[-1].symbol));}
#line 1633 "parser.tab.cpp"
    break;

  case 51: /* cmd: KW_IF '(' expr ')' cmd  */
#line 233 "parser.ypp"
                                                { vector<AST*> children = {(yyvsp[-2].ast), (yyvsp[0].ast)}; (yyval.ast) = new AST(AST_IF_THEN, children);}
#line 1639 "parser.tab.cpp"
    break;

  case 52: /* cmd: KW_IF '(' expr ')' cmd KW_ELSE cmd  */
#line 234 "parser.ypp"
                                                { vector<AST*> children = {(yyvsp[-4].ast), (yyvsp[-2].ast), (yyvsp[0].ast)}; (yyval.ast) = new AST(AST_IF_THEN_ELSE, children);}
#line 1645 "parser.tab.cpp"
    break;

  case 53: /* cmd: KW_WHILE expr KW_DO cmd  */
#line 235 "parser.ypp"
                                                { vector<AST*> children = {(yyvsp[-2].ast), (yyvsp[0].ast)}; (yyval.ast) = new AST(AST_WHILE, children);}
#line 1651 "parser.tab.cpp"
    break;

  case 54: /* cmd: KW_DO cmd KW_WHILE expr ';'  */
#line 236 "parser.ypp"
                                                { vector<AST*> children = {(yyvsp[-3].ast), (yyvsp[-1].ast)}; (yyval.ast) = new AST(AST_DO_WHILE, children);}
#line 1657 "parser.tab.cpp"
    break;

  case 55: /* cmd: cmd_blc  */
#line 237 "parser.ypp"
                                                { (yyval.ast) = (yyvsp[0].ast); }
#line 1663 "parser.tab.cpp"
    break;

  case 56: /* cmd: ';'  */
#line 238 "parser.ypp"
                                                { (yyval.ast) = nullptr; }
#line 1669 "parser.tab.cpp"
    break;

  case 57: /* par: par_nvazio  */
#line 243 "parser.ypp"
                                  { (yyval.ast) = (yyvsp[0].ast); }
#line 1675 "parser.tab.cpp"
    break;

  case 58: /* par: %empty  */
#line 244 "parser.ypp"
                                  { (yyval.ast) = nullptr; }
#line 1681 "parser.tab.cpp"
    break;

  case 59: /* par_nvazio: expr  */
#line 247 "parser.ypp"
                                  { vector<AST*> children = {(yyvsp[0].ast), nullptr}; (yyval.ast) = new AST(AST_EXP_LIST, children); }
#line 1687 "parser.tab.cpp"
    break;

  case 60: /* par_nvazio: expr ',' par_nvazio  */
#line 248 "parser.ypp"
                                  { vector<AST*> children = {(yyvsp[-2].ast), (yyvsp[0].ast)}; (yyval.ast) = new AST(AST_EXP_LIST, children); }
#line 1693 "parser.tab.cpp"
    break;

  case 61: /* func: TK_IDENTIFIER '(' par ')'  */
#line 253 "parser.ypp"
                                  { vector<AST*> children = {(yyvsp[-1].ast)}; (yyval.ast) = new AST(AST_SYMBOL_FUNC, children, (yyvsp[-3].symbol)); }
#line 1699 "parser.tab.cpp"
    break;

  case 62: /* expr: func  */
#line 255 "parser.ypp"
                                { (yyval.ast) = (yyvsp[0].ast); }
#line 1705 "parser.tab.cpp"
    break;

  case 63: /* expr: TK_IDENTIFIER '[' expr ']'  */
#line 256 "parser.ypp"
                                { vector<AST*> children = {(yyvsp[-1].ast)}; (yyval.ast) = new AST(AST_SYMBOL_VEC, children, (yyvsp[-3].symbol)); }
#line 1711 "parser.tab.cpp"
    break;

  case 64: /* expr: TK_IDENTIFIER  */
#line 257 "parser.ypp"
                                { vector<AST*> children; (yyval.ast) = new AST(AST_SYMBOL, children, (yyvsp[0].symbol)); }
#line 1717 "parser.tab.cpp"
    break;

  case 65: /* expr: LIT_INT  */
#line 258 "parser.ypp"
                                { vector<AST*> children; (yyval.ast) = new AST(AST_SYMBOL, children, (yyvsp[0].symbol)); }
#line 1723 "parser.tab.cpp"
    break;

  case 66: /* expr: LIT_CHAR  */
#line 259 "parser.ypp"
                                { vector<AST*> children; (yyval.ast) = new AST(AST_SYMBOL, children, (yyvsp[0].symbol)); }
#line 1729 "parser.tab.cpp"
    break;

  case 67: /* expr: LIT_REAL  */
#line 260 "parser.ypp"
                                { vector<AST*> children; (yyval.ast) = new AST(AST_SYMBOL, children, (yyvsp[0].symbol)); }
#line 1735 "parser.tab.cpp"
    break;

  case 68: /* expr: expr '+' expr  */
#line 262 "parser.ypp"
                                { vector<AST*> children = {(yyvsp[-2].ast), (yyvsp[0].ast)}; (yyval.ast) = new AST(AST_ADD, children); }
#line 1741 "parser.tab.cpp"
    break;

  case 69: /* expr: expr '-' expr  */
#line 263 "parser.ypp"
                                { vector<AST*> children = {(yyvsp[-2].ast), (yyvsp[0].ast)}; (yyval.ast) = new AST(AST_SUB, children); }
#line 1747 "parser.tab.cpp"
    break;

  case 70: /* expr: expr '*' expr  */
#line 264 "parser.ypp"
                                { vector<AST*> children = {(yyvsp[-2].ast), (yyvsp[0].ast)}; (yyval.ast) = new AST(AST_MUL, children); }
#line 1753 "parser.tab.cpp"
    break;

  case 71: /* expr: expr '/' expr  */
#line 265 "parser.ypp"
                                { vector<AST*> children = {(yyvsp[-2].ast), (yyvsp[0].ast)}; (yyval.ast) = new AST(AST_DIV, children); }
#line 1759 "parser.tab.cpp"
    break;

  case 72: /* expr: expr '&' expr  */
#line 266 "parser.ypp"
                                { vector<AST*> children = {(yyvsp[-2].ast), (yyvsp[0].ast)}; (yyval.ast) = new AST(AST_AND, children); }
#line 1765 "parser.tab.cpp"
    break;

  case 73: /* expr: expr '|' expr  */
#line 267 "parser.ypp"
                                { vector<AST*> children = {(yyvsp[-2].ast), (yyvsp[0].ast)}; (yyval.ast) = new AST(AST_OR, children); }
#line 1771 "parser.tab.cpp"
    break;

  case 74: /* expr: expr '<' expr  */
#line 268 "parser.ypp"
                                { vector<AST*> children = {(yyvsp[-2].ast), (yyvsp[0].ast)}; (yyval.ast) = new AST(AST_LESS, children); }
#line 1777 "parser.tab.cpp"
    break;

  case 75: /* expr: expr '>' expr  */
#line 269 "parser.ypp"
                                { vector<AST*> children = {(yyvsp[-2].ast), (yyvsp[0].ast)}; (yyval.ast) = new AST(AST_GRT, children); }
#line 1783 "parser.tab.cpp"
    break;

  case 76: /* expr: '~' expr  */
#line 270 "parser.ypp"
                                { vector<AST*> children = {(yyvsp[0].ast)}; (yyval.ast) = new AST(AST_NOT, children); }
#line 1789 "parser.tab.cpp"
    break;

  case 77: /* expr: expr OPERATOR_EQ expr  */
#line 271 "parser.ypp"
                                { vector<AST*> children = {(yyvsp[-2].ast), (yyvsp[0].ast)}; (yyval.ast) = new AST(AST_EQUAL, children); }
#line 1795 "parser.tab.cpp"
    break;

  case 78: /* expr: expr OPERATOR_DIF expr  */
#line 272 "parser.ypp"
                                { vector<AST*> children = {(yyvsp[-2].ast), (yyvsp[0].ast)}; (yyval.ast) = new AST(AST_DIF, children); }
#line 1801 "parser.tab.cpp"
    break;

  case 79: /* expr: expr OPERATOR_GE expr  */
#line 273 "parser.ypp"
                                { vector<AST*> children = {(yyvsp[-2].ast), (yyvsp[0].ast)}; (yyval.ast) = new AST(AST_GE, children); }
#line 1807 "parser.tab.cpp"
    break;

  case 80: /* expr: expr OPERATOR_LE expr  */
#line 274 "parser.ypp"
                                { vector<AST*> children = {(yyvsp[-2].ast), (yyvsp[0].ast)}; (yyval.ast) = new AST(AST_LE, children); }
#line 1813 "parser.tab.cpp"
    break;

  case 81: /* expr: '(' expr ')'  */
#line 275 "parser.ypp"
                                { (yyval.ast) = (yyvsp[-1].ast); }
#line 1819 "parser.tab.cpp"
    break;


#line 1823 "parser.tab.cpp"

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
  ++yynerrs;

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
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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

#line 278 "parser.ypp"


void yyerror(string msg)
{
    fprintf(stderr, "ERRO DE SINTAXE. ERRO NA linha %d", lineNumber);
    exit(3);
}
