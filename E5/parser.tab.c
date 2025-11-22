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
#line 4 "parser.y"

#include <stdio.h>
#include <string.h>
#include "asd.h"
#include "tabela.h" 
#include "errors.h"   

int yylex(void);
void yyerror (char const *mensagem);
int get_line_number();

// Funções auxiliares para criar nós da AST
static asd_tree_t* asd_new_binary_op(const char* label, asd_tree_t* child1, asd_tree_t* child2);
static asd_tree_t* asd_new_unary_op(const char* label, asd_tree_t* child);

// Função auxiliar para verificação de tipos em operações binárias
void check_types(asd_tree_t* node, asd_tree_t* child1, asd_tree_t* child2);
void check_function_call_args(symbol_t* func_symbol, asd_tree_t* args_node, int line);
static symbol_t* current_function = NULL;

#line 92 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TK_TIPO = 3,                    /* TK_TIPO  */
  YYSYMBOL_TK_VAR = 4,                     /* TK_VAR  */
  YYSYMBOL_TK_SENAO = 5,                   /* TK_SENAO  */
  YYSYMBOL_TK_DECIMAL = 6,                 /* TK_DECIMAL  */
  YYSYMBOL_TK_SE = 7,                      /* TK_SE  */
  YYSYMBOL_TK_INTEIRO = 8,                 /* TK_INTEIRO  */
  YYSYMBOL_TK_ATRIB = 9,                   /* TK_ATRIB  */
  YYSYMBOL_TK_RETORNA = 10,                /* TK_RETORNA  */
  YYSYMBOL_TK_SETA = 11,                   /* TK_SETA  */
  YYSYMBOL_TK_ENQUANTO = 12,               /* TK_ENQUANTO  */
  YYSYMBOL_TK_COM = 13,                    /* TK_COM  */
  YYSYMBOL_TK_OC_LE = 14,                  /* TK_OC_LE  */
  YYSYMBOL_TK_OC_GE = 15,                  /* TK_OC_GE  */
  YYSYMBOL_TK_OC_EQ = 16,                  /* TK_OC_EQ  */
  YYSYMBOL_TK_OC_NE = 17,                  /* TK_OC_NE  */
  YYSYMBOL_TK_ID = 18,                     /* TK_ID  */
  YYSYMBOL_TK_LI_INTEIRO = 19,             /* TK_LI_INTEIRO  */
  YYSYMBOL_TK_LI_DECIMAL = 20,             /* TK_LI_DECIMAL  */
  YYSYMBOL_TK_ER = 21,                     /* TK_ER  */
  YYSYMBOL_22_ = 22,                       /* ';'  */
  YYSYMBOL_23_ = 23,                       /* ','  */
  YYSYMBOL_24_ = 24,                       /* '['  */
  YYSYMBOL_25_ = 25,                       /* ']'  */
  YYSYMBOL_26_ = 26,                       /* '('  */
  YYSYMBOL_27_ = 27,                       /* ')'  */
  YYSYMBOL_28_ = 28,                       /* '|'  */
  YYSYMBOL_29_ = 29,                       /* '&'  */
  YYSYMBOL_30_ = 30,                       /* '<'  */
  YYSYMBOL_31_ = 31,                       /* '>'  */
  YYSYMBOL_32_ = 32,                       /* '+'  */
  YYSYMBOL_33_ = 33,                       /* '-'  */
  YYSYMBOL_34_ = 34,                       /* '*'  */
  YYSYMBOL_35_ = 35,                       /* '/'  */
  YYSYMBOL_36_ = 36,                       /* '%'  */
  YYSYMBOL_37_ = 37,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 38,                  /* $accept  */
  YYSYMBOL_programa = 39,                  /* programa  */
  YYSYMBOL_lista = 40,                     /* lista  */
  YYSYMBOL_elemento = 41,                  /* elemento  */
  YYSYMBOL_declaracao_variavel = 42,       /* declaracao_variavel  */
  YYSYMBOL_declaracao_funcao = 43,         /* declaracao_funcao  */
  YYSYMBOL_cabecalho_funcao = 44,          /* cabecalho_funcao  */
  YYSYMBOL_45_1 = 45,                      /* $@1  */
  YYSYMBOL_lista_parametros_opcional = 46, /* lista_parametros_opcional  */
  YYSYMBOL_lista_parametros = 47,          /* lista_parametros  */
  YYSYMBOL_parametros = 48,                /* parametros  */
  YYSYMBOL_parametro = 49,                 /* parametro  */
  YYSYMBOL_bloco_de_comandos = 50,         /* bloco_de_comandos  */
  YYSYMBOL_51_2 = 51,                      /* $@2  */
  YYSYMBOL_52_3 = 52,                      /* $@3  */
  YYSYMBOL_sequencia_comandos = 53,        /* sequencia_comandos  */
  YYSYMBOL_comando = 54,                   /* comando  */
  YYSYMBOL_matched_statement = 55,         /* matched_statement  */
  YYSYMBOL_unmatched_statement = 56,       /* unmatched_statement  */
  YYSYMBOL_outro_comando = 57,             /* outro_comando  */
  YYSYMBOL_literal = 58,                   /* literal  */
  YYSYMBOL_atribuicao = 59,                /* atribuicao  */
  YYSYMBOL_chamada_funcao = 60,            /* chamada_funcao  */
  YYSYMBOL_argumentos = 61,                /* argumentos  */
  YYSYMBOL_retorno = 62,                   /* retorno  */
  YYSYMBOL_repeticao = 63,                 /* repeticao  */
  YYSYMBOL_tipo_num = 64,                  /* tipo_num  */
  YYSYMBOL_expressao = 65,                 /* expressao  */
  YYSYMBOL_expr_logica_ou = 66,            /* expr_logica_ou  */
  YYSYMBOL_expr_logica_e = 67,             /* expr_logica_e  */
  YYSYMBOL_expr_igualdade = 68,            /* expr_igualdade  */
  YYSYMBOL_expr_relacional = 69,           /* expr_relacional  */
  YYSYMBOL_expr_aditiva = 70,              /* expr_aditiva  */
  YYSYMBOL_expr_multiplicativa = 71,       /* expr_multiplicativa  */
  YYSYMBOL_expr_unaria = 72,               /* expr_unaria  */
  YYSYMBOL_fator = 73                      /* fator  */
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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   119

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  129

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   276


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
       2,     2,     2,    37,     2,     2,     2,    36,    29,     2,
      26,    27,    34,    32,    23,    33,     2,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    22,
      30,     2,    31,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    24,     2,    25,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    28,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    81,    81,    82,    85,    86,    98,    99,   102,   107,
     123,   133,   132,   155,   156,   159,   160,   163,   164,   167,
     177,   177,   178,   178,   181,   182,   192,   193,   196,   224,
     227,   236,   248,   249,   250,   251,   252,   253,   256,   257,
     260,   282,   299,   319,   320,   323,   338,   348,   349,   352,
     354,   355,   358,   359,   362,   363,   364,   367,   368,   369,
     370,   371,   374,   375,   376,   379,   380,   381,   382,   385,
     386,   387,   388,   391,   404,   405,   406
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TK_TIPO", "TK_VAR",
  "TK_SENAO", "TK_DECIMAL", "TK_SE", "TK_INTEIRO", "TK_ATRIB",
  "TK_RETORNA", "TK_SETA", "TK_ENQUANTO", "TK_COM", "TK_OC_LE", "TK_OC_GE",
  "TK_OC_EQ", "TK_OC_NE", "TK_ID", "TK_LI_INTEIRO", "TK_LI_DECIMAL",
  "TK_ER", "';'", "','", "'['", "']'", "'('", "')'", "'|'", "'&'", "'<'",
  "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "$accept", "programa",
  "lista", "elemento", "declaracao_variavel", "declaracao_funcao",
  "cabecalho_funcao", "$@1", "lista_parametros_opcional",
  "lista_parametros", "parametros", "parametro", "bloco_de_comandos",
  "$@2", "$@3", "sequencia_comandos", "comando", "matched_statement",
  "unmatched_statement", "outro_comando", "literal", "atribuicao",
  "chamada_funcao", "argumentos", "retorno", "repeticao", "tipo_num",
  "expressao", "expr_logica_ou", "expr_logica_e", "expr_igualdade",
  "expr_relacional", "expr_aditiva", "expr_multiplicativa", "expr_unaria",
  "fator", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-98)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-21)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       3,    -1,    26,    30,     5,    18,   -98,   -98,    43,    42,
      12,   -98,   -98,     3,    44,   -98,    12,   -98,   -98,   -98,
     -98,    62,     1,    68,    34,   -98,    63,    16,    64,     0,
     -98,   -98,    66,     1,   -98,   -98,   -98,   -98,   -98,   -98,
     -98,    56,    70,    83,    84,   -98,   -98,    71,    16,    69,
     -98,   -98,    16,    -4,    -4,    -4,   -98,   -98,    87,    72,
      73,    61,    40,    47,    27,   -98,   -98,    16,    16,    13,
     -98,   -98,   -98,   -98,    12,   -98,    70,    74,    76,   -98,
     -98,   -98,    12,    16,    16,    16,    16,    16,    16,    16,
      16,    16,    16,    16,    16,    16,    77,   -98,   -98,    79,
      75,   -98,   -98,     1,   -98,   -98,    73,    61,    40,    40,
      47,    47,    47,    47,    27,    27,   -98,   -98,   -98,    43,
     -98,    16,   -98,    92,   -98,   -98,     1,   -98,   -98
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,     0,     0,     4,     6,     7,     0,     0,
       0,     1,     2,     0,    22,    10,     0,    47,    48,    11,
       5,     0,     0,     8,    14,    21,     0,     0,     0,     0,
      33,    32,     0,    24,    26,    27,    29,    34,    35,    36,
      37,     0,     0,     0,     0,    13,    16,    17,     0,    73,
      38,    39,     0,     0,     0,     0,    74,    75,     0,    49,
      51,    53,    56,    61,    64,    68,    72,     0,     0,     0,
      23,    25,     9,    15,     0,    12,     0,     0,     0,    69,
      70,    71,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    40,    41,     0,
      43,    19,    18,     0,    76,    45,    50,    52,    54,    55,
      59,    60,    57,    58,    62,    63,    65,    66,    67,     0,
      42,     0,    30,    26,    46,    44,     0,    28,    31
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -98,   -98,    86,   -98,    10,   -98,   -98,   -98,   -98,   -98,
     -38,   -98,    -8,   -98,   -98,    80,     4,   -97,   -18,   -98,
      78,   -98,   -21,   -12,   -98,   -98,   -14,   -24,   -98,    29,
      31,    -2,   -31,    -6,   -29,    19
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,    30,     7,     8,    24,    44,    45,
      46,    47,    31,    21,    22,    32,    33,    34,    35,    36,
      56,    37,    57,    99,    39,    40,    19,   100,    59,    60,
      61,    62,    63,    64,    65,    66
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      15,    38,    23,    58,    73,     1,   123,     1,    26,    68,
       6,    27,    38,    28,    49,    50,    51,     9,    17,    29,
      18,     2,    52,     6,    77,    14,    69,    12,    78,   127,
      11,    49,    50,    51,    49,    50,    51,    10,   102,    52,
      98,    13,    52,    96,    97,    53,    54,    42,    53,    54,
      55,    16,    43,    55,    87,    88,   110,   111,   112,   113,
     101,    93,    94,    95,   116,   117,   118,    14,   105,   -20,
      89,    90,    79,    80,    81,    50,    51,    85,    86,    91,
      92,    41,    38,   108,   109,   114,   115,    25,    43,    48,
      67,    70,    74,    75,    76,    69,    82,   126,   121,    20,
      83,   103,    84,   104,   119,    38,   120,   122,   128,   125,
       0,   124,   106,    71,     0,   107,     0,     0,     0,    72
};

static const yytype_int8 yycheck[] =
{
       8,    22,    16,    27,    42,     4,   103,     4,     7,     9,
       0,    10,    33,    12,    18,    19,    20,    18,     6,    18,
       8,    18,    26,    13,    48,    24,    26,    22,    52,   126,
       0,    18,    19,    20,    18,    19,    20,    11,    76,    26,
      27,    23,    26,    67,    68,    32,    33,    13,    32,    33,
      37,     9,    18,    37,    14,    15,    87,    88,    89,    90,
      74,    34,    35,    36,    93,    94,    95,    24,    82,    25,
      30,    31,    53,    54,    55,    19,    20,    16,    17,    32,
      33,    13,   103,    85,    86,    91,    92,    25,    18,    26,
      26,    25,     9,     9,    23,    26,     9,     5,    23,    13,
      28,    27,    29,    27,    27,   126,    27,   103,   126,   121,
      -1,   119,    83,    33,    -1,    84,    -1,    -1,    -1,    41
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,    18,    39,    40,    41,    42,    43,    44,    18,
      11,     0,    22,    23,    24,    50,     9,     6,     8,    64,
      40,    51,    52,    64,    45,    25,     7,    10,    12,    18,
      42,    50,    53,    54,    55,    56,    57,    59,    60,    62,
      63,    13,    13,    18,    46,    47,    48,    49,    26,    18,
      19,    20,    26,    32,    33,    37,    58,    60,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    26,     9,    26,
      25,    53,    58,    48,     9,     9,    23,    65,    65,    73,
      73,    73,     9,    28,    29,    16,    17,    14,    15,    30,
      31,    32,    33,    34,    35,    36,    65,    65,    27,    61,
      65,    64,    48,    27,    27,    64,    67,    68,    69,    69,
      70,    70,    70,    70,    71,    71,    72,    72,    72,    27,
      27,    23,    54,    55,    50,    61,     5,    55,    56
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    39,    39,    40,    40,    41,    41,    42,    42,
      43,    45,    44,    46,    46,    47,    47,    48,    48,    49,
      51,    50,    52,    50,    53,    53,    54,    54,    55,    55,
      56,    56,    57,    57,    57,    57,    57,    57,    58,    58,
      59,    60,    60,    61,    61,    62,    63,    64,    64,    65,
      66,    66,    67,    67,    68,    68,    68,    69,    69,    69,
      69,    69,    70,    70,    70,    71,    71,    71,    71,    72,
      72,    72,    72,    73,    73,    73,    73
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     1,     3,     1,     1,     4,     6,
       2,     0,     6,     1,     0,     2,     1,     1,     3,     3,
       0,     3,     0,     4,     1,     2,     1,     1,     7,     1,
       5,     7,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     4,     1,     3,     4,     5,     1,     1,     1,
       3,     1,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     2,
       2,     2,     1,     1,     1,     1,     3
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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
  case 2: /* programa: lista ';'  */
#line 81 "parser.y"
                    { arvore = (yyvsp[-1].nodo_arvore); }
#line 1508 "parser.tab.c"
    break;

  case 3: /* programa: %empty  */
#line 82 "parser.y"
                    { arvore = NULL; }
#line 1514 "parser.tab.c"
    break;

  case 4: /* lista: elemento  */
#line 85 "parser.y"
                                { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 1520 "parser.tab.c"
    break;

  case 5: /* lista: elemento ',' lista  */
#line 86 "parser.y"
                                { 
                                    if ((yyvsp[-2].nodo_arvore) != NULL) {
                                        if ((yyvsp[0].nodo_arvore) != NULL) {
                                            asd_add_child((yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore));
                                        }
                                        (yyval.nodo_arvore) = (yyvsp[-2].nodo_arvore);
                                    } else {
                                        (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore);
                                    }
                                }
#line 1535 "parser.tab.c"
    break;

  case 6: /* elemento: declaracao_variavel  */
#line 98 "parser.y"
                                { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 1541 "parser.tab.c"
    break;

  case 7: /* elemento: declaracao_funcao  */
#line 99 "parser.y"
                                { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 1547 "parser.tab.c"
    break;

  case 8: /* declaracao_variavel: TK_VAR TK_ID TK_ATRIB tipo_num  */
#line 102 "parser.y"
                                                    {
                         add_symbol((yyvsp[-2].valor_lexico).valor, (yyvsp[-2].valor_lexico).numero_linha, NATURE_VARIABLE, (yyvsp[0].tipo_dado));
                         free((yyvsp[-2].valor_lexico).valor);
                         (yyval.nodo_arvore) = NULL; // Declaração simples não gera nó na AST
                    }
#line 1557 "parser.tab.c"
    break;

  case 9: /* declaracao_variavel: TK_VAR TK_ID TK_ATRIB tipo_num TK_COM literal  */
#line 107 "parser.y"
                                                                   {
                         add_symbol((yyvsp[-4].valor_lexico).valor, (yyvsp[-4].valor_lexico).numero_linha, NATURE_VARIABLE, (yyvsp[-2].tipo_dado));
                         
                         if ((yyvsp[-2].tipo_dado) != (yyvsp[0].nodo_arvore)->data_type) {
                            semantic_error(ERR_WRONG_TYPE, (yyvsp[-4].valor_lexico).numero_linha, "Tipo do literal de inicialização é incompatível com a variável.");
                         }
                         
                         (yyval.nodo_arvore) = asd_new(":=");
                         (yyval.nodo_arvore)->data_type = (yyvsp[-2].tipo_dado);
                         asd_tree_t* id_node = asd_new((yyvsp[-4].valor_lexico).valor);
                         id_node->data_type = (yyvsp[-2].tipo_dado);
                         asd_add_child((yyval.nodo_arvore), id_node);
                         asd_add_child((yyval.nodo_arvore), (yyvsp[0].nodo_arvore));
                         free((yyvsp[-4].valor_lexico).valor);
                   }
#line 1577 "parser.tab.c"
    break;

  case 10: /* declaracao_funcao: cabecalho_funcao bloco_de_comandos  */
#line 123 "parser.y"
                                                      {
                        (yyval.nodo_arvore) = (yyvsp[-1].nodo_arvore);
                        if ((yyvsp[0].nodo_arvore) != NULL){
                              asd_add_child((yyval.nodo_arvore), (yyvsp[0].nodo_arvore));
                        }
                        pop_scope();
                        current_function = NULL;
                   }
#line 1590 "parser.tab.c"
    break;

  case 11: /* $@1: %empty  */
#line 133 "parser.y"
                  {
                      current_function = add_symbol((yyvsp[-2].valor_lexico).valor, (yyvsp[-2].valor_lexico).numero_linha, NATURE_FUNCTION, (yyvsp[0].tipo_dado));
                      push_scope();
                  }
#line 1599 "parser.tab.c"
    break;

  case 12: /* cabecalho_funcao: TK_ID TK_SETA tipo_num $@1 lista_parametros_opcional TK_ATRIB  */
#line 138 "parser.y"
                  {
                      (yyval.nodo_arvore) = asd_new((yyvsp[-5].valor_lexico).valor);
                      (yyval.nodo_arvore)->data_type = (yyvsp[-3].tipo_dado);
                      
                      if((yyvsp[-1].nodo_arvore) != NULL) {
                         asd_add_child((yyval.nodo_arvore), (yyvsp[-1].nodo_arvore));
                         if(current_function)
                         {    
                             current_function->params = (yyvsp[-1].nodo_arvore); 
                         }

                      }
                      free((yyvsp[-5].valor_lexico).valor);
                  }
#line 1618 "parser.tab.c"
    break;

  case 13: /* lista_parametros_opcional: lista_parametros  */
#line 155 "parser.y"
                                            { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 1624 "parser.tab.c"
    break;

  case 14: /* lista_parametros_opcional: %empty  */
#line 156 "parser.y"
                                                    { (yyval.nodo_arvore) = NULL; }
#line 1630 "parser.tab.c"
    break;

  case 15: /* lista_parametros: TK_COM parametros  */
#line 159 "parser.y"
                                    { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 1636 "parser.tab.c"
    break;

  case 16: /* lista_parametros: parametros  */
#line 160 "parser.y"
                                        { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 1642 "parser.tab.c"
    break;

  case 17: /* parametros: parametro  */
#line 163 "parser.y"
                                     { (yyval.nodo_arvore) = asd_new("params"); asd_add_child((yyval.nodo_arvore), (yyvsp[0].nodo_arvore)); }
#line 1648 "parser.tab.c"
    break;

  case 18: /* parametros: parametro ',' parametros  */
#line 164 "parser.y"
                                     { asd_add_child((yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); (yyval.nodo_arvore) = (yyvsp[-2].nodo_arvore); }
#line 1654 "parser.tab.c"
    break;

  case 19: /* parametro: TK_ID TK_ATRIB tipo_num  */
#line 167 "parser.y"
                                   {
               // Adiciona o parâmetro à tabela de símbolos do escopo atual
               add_symbol((yyvsp[-2].valor_lexico).valor, (yyvsp[-2].valor_lexico).numero_linha, NATURE_VARIABLE, (yyvsp[0].tipo_dado));
               
               (yyval.nodo_arvore) = asd_new((yyvsp[-2].valor_lexico).valor);
               (yyval.nodo_arvore)->data_type = (yyvsp[0].tipo_dado);
               free((yyvsp[-2].valor_lexico).valor);
           }
#line 1667 "parser.tab.c"
    break;

  case 20: /* $@2: %empty  */
#line 177 "parser.y"
                       { push_scope(); }
#line 1673 "parser.tab.c"
    break;

  case 21: /* bloco_de_comandos: '[' $@2 ']'  */
#line 177 "parser.y"
                                                        { pop_scope(); (yyval.nodo_arvore) = NULL; }
#line 1679 "parser.tab.c"
    break;

  case 22: /* $@3: %empty  */
#line 178 "parser.y"
                       { push_scope(); }
#line 1685 "parser.tab.c"
    break;

  case 23: /* bloco_de_comandos: '[' $@3 sequencia_comandos ']'  */
#line 178 "parser.y"
                                                                { pop_scope(); (yyval.nodo_arvore) = (yyvsp[-1].nodo_arvore); }
#line 1691 "parser.tab.c"
    break;

  case 24: /* sequencia_comandos: comando  */
#line 181 "parser.y"
                                                    { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 1697 "parser.tab.c"
    break;

  case 25: /* sequencia_comandos: comando sequencia_comandos  */
#line 182 "parser.y"
                                                    { 
                                    if ((yyvsp[-1].nodo_arvore) != NULL) {
                                        if ((yyvsp[0].nodo_arvore) != NULL) asd_add_child((yyvsp[-1].nodo_arvore), (yyvsp[0].nodo_arvore));
                                        (yyval.nodo_arvore) = (yyvsp[-1].nodo_arvore);
                                    } else {
                                        (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore);
                                    }
                                }
#line 1710 "parser.tab.c"
    break;

  case 26: /* comando: matched_statement  */
#line 192 "parser.y"
                             { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 1716 "parser.tab.c"
    break;

  case 27: /* comando: unmatched_statement  */
#line 193 "parser.y"
                             { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 1722 "parser.tab.c"
    break;

  case 28: /* matched_statement: TK_SE '(' expressao ')' matched_statement TK_SENAO matched_statement  */
#line 196 "parser.y"
                                                                                        {
                        if ((yyvsp[-4].nodo_arvore)->data_type != TYPE_INTEGER) {
                            semantic_error(ERR_WRONG_TYPE, get_line_number(), "Expressão de teste do 'se' deve ser do tipo 'inteiro'.");
                        }
                        int then_type;
                        int else_type;
                        if ((yyvsp[-2].nodo_arvore) == NULL) {
                            then_type = TYPE_INTEGER;
                        } else {
                            // Tipo do bloco é o tipo do primeiro comando.
                            then_type = (yyvsp[-2].nodo_arvore)->data_type;
                        }
                        if ((yyvsp[0].nodo_arvore) == NULL) {
                            else_type = TYPE_INTEGER;
                        } else {
                            else_type = (yyvsp[0].nodo_arvore)->data_type;
                        }
                        if (then_type != TYPE_UNDEFINED && 
                            else_type != TYPE_UNDEFINED &&
                            then_type != else_type) {
                            semantic_error(ERR_WRONG_TYPE, get_line_number(), "Tipos dos blocos 'se' e 'senao' são incompatíveis.");
                        }
                        (yyval.nodo_arvore) = asd_new("se");
                        (yyval.nodo_arvore)->data_type = (yyvsp[-4].nodo_arvore)->data_type;
                        asd_add_child((yyval.nodo_arvore), (yyvsp[-4].nodo_arvore)); 
                        if ((yyvsp[-2].nodo_arvore) != NULL) asd_add_child((yyval.nodo_arvore), (yyvsp[-2].nodo_arvore));
                        if ((yyvsp[0].nodo_arvore) != NULL) asd_add_child((yyval.nodo_arvore), (yyvsp[0].nodo_arvore));
                   }
#line 1755 "parser.tab.c"
    break;

  case 29: /* matched_statement: outro_comando  */
#line 224 "parser.y"
                                 { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 1761 "parser.tab.c"
    break;

  case 30: /* unmatched_statement: TK_SE '(' expressao ')' comando  */
#line 227 "parser.y"
                                                     {
                        if ((yyvsp[-2].nodo_arvore)->data_type != TYPE_INTEGER) {
                            semantic_error(ERR_WRONG_TYPE, get_line_number(), "Expressão de teste do 'se' deve ser do tipo 'inteiro'.");
                        }
                        (yyval.nodo_arvore) = asd_new("se");
                        (yyval.nodo_arvore)->data_type = (yyvsp[-2].nodo_arvore)->data_type;
                        asd_add_child((yyval.nodo_arvore), (yyvsp[-2].nodo_arvore)); 
                        if ((yyvsp[0].nodo_arvore) != NULL) asd_add_child((yyval.nodo_arvore), (yyvsp[0].nodo_arvore));
                   }
#line 1775 "parser.tab.c"
    break;

  case 31: /* unmatched_statement: TK_SE '(' expressao ')' matched_statement TK_SENAO unmatched_statement  */
#line 236 "parser.y"
                                                                                            {
                        if ((yyvsp[-4].nodo_arvore)->data_type != TYPE_INTEGER) {
                            semantic_error(ERR_WRONG_TYPE, get_line_number(), "Expressão de teste do 'se' deve ser do tipo 'inteiro'.");
                        }
                        (yyval.nodo_arvore) = asd_new("se");
                        (yyval.nodo_arvore)->data_type = (yyvsp[-4].nodo_arvore)->data_type;
                        asd_add_child((yyval.nodo_arvore), (yyvsp[-4].nodo_arvore));
                        if ((yyvsp[-2].nodo_arvore) != NULL) asd_add_child((yyval.nodo_arvore), (yyvsp[-2].nodo_arvore));
                        if ((yyvsp[0].nodo_arvore) != NULL) asd_add_child((yyval.nodo_arvore), (yyvsp[0].nodo_arvore));
                   }
#line 1790 "parser.tab.c"
    break;

  case 32: /* outro_comando: bloco_de_comandos  */
#line 248 "parser.y"
                                 { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 1796 "parser.tab.c"
    break;

  case 33: /* outro_comando: declaracao_variavel  */
#line 249 "parser.y"
                                   { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 1802 "parser.tab.c"
    break;

  case 34: /* outro_comando: atribuicao  */
#line 250 "parser.y"
                          { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 1808 "parser.tab.c"
    break;

  case 35: /* outro_comando: chamada_funcao  */
#line 251 "parser.y"
                              { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 1814 "parser.tab.c"
    break;

  case 36: /* outro_comando: retorno  */
#line 252 "parser.y"
                       { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 1820 "parser.tab.c"
    break;

  case 37: /* outro_comando: repeticao  */
#line 253 "parser.y"
                         { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 1826 "parser.tab.c"
    break;

  case 38: /* literal: TK_LI_INTEIRO  */
#line 256 "parser.y"
                       { (yyval.nodo_arvore) = asd_new((yyvsp[0].valor_lexico).valor); (yyval.nodo_arvore)->data_type = TYPE_INTEGER; add_symbol((yyvsp[0].valor_lexico).valor, (yyvsp[0].valor_lexico).numero_linha, NATURE_LITERAL, TYPE_INTEGER); free((yyvsp[0].valor_lexico).valor); }
#line 1832 "parser.tab.c"
    break;

  case 39: /* literal: TK_LI_DECIMAL  */
#line 257 "parser.y"
                           { (yyval.nodo_arvore) = asd_new((yyvsp[0].valor_lexico).valor); (yyval.nodo_arvore)->data_type = TYPE_FLOAT; add_symbol((yyvsp[0].valor_lexico).valor, (yyvsp[0].valor_lexico).numero_linha, NATURE_LITERAL, TYPE_FLOAT); free((yyvsp[0].valor_lexico).valor); }
#line 1838 "parser.tab.c"
    break;

  case 40: /* atribuicao: TK_ID TK_ATRIB expressao  */
#line 260 "parser.y"
                                     { 
                // Verifica declaração e tipos da atribuição
                symbol_t* symbol = find_symbol((yyvsp[-2].valor_lexico).valor);
                if (symbol == NULL) {
                    semantic_error(ERR_UNDECLARED, (yyvsp[-2].valor_lexico).numero_linha, (yyvsp[-2].valor_lexico).valor);
                }
                if (symbol->nature != NATURE_VARIABLE) {
                    semantic_error(ERR_FUNCTION, (yyvsp[-2].valor_lexico).numero_linha, (yyvsp[-2].valor_lexico).valor);
                }
                if (symbol->type != (yyvsp[0].nodo_arvore)->data_type) {
                    semantic_error(ERR_WRONG_TYPE, (yyvsp[-2].valor_lexico).numero_linha, "Tipo da expressão incompatível com a variável.");
                }

                (yyval.nodo_arvore) = asd_new(":=");
                (yyval.nodo_arvore)->data_type = symbol->type;
                asd_tree_t* id_node = asd_new((yyvsp[-2].valor_lexico).valor);
                id_node->data_type = symbol->type;
                asd_add_child((yyval.nodo_arvore), id_node); 
                asd_add_child((yyval.nodo_arvore), (yyvsp[0].nodo_arvore));     
                free((yyvsp[-2].valor_lexico).valor);
            }
#line 1864 "parser.tab.c"
    break;

  case 41: /* chamada_funcao: TK_ID '(' ')'  */
#line 282 "parser.y"
                              {
                    // Verifica a chamada de função sem argumentos
                    symbol_t* symbol = find_symbol((yyvsp[-2].valor_lexico).valor);
                    if (symbol == NULL) semantic_error(ERR_UNDECLARED, (yyvsp[-2].valor_lexico).numero_linha, (yyvsp[-2].valor_lexico).valor);
                    if (symbol->nature != NATURE_FUNCTION) semantic_error(ERR_VARIABLE, (yyvsp[-2].valor_lexico).numero_linha, (yyvsp[-2].valor_lexico).valor);
                    
                    // Se a função esperava parâmetros, lança erro.
                    if (symbol->params != NULL && symbol->params->number_of_children > 0) {
                        semantic_error(ERR_MISSING_ARGS, (yyvsp[-2].valor_lexico).numero_linha, (yyvsp[-2].valor_lexico).valor);
                    }
                    
                    char label[256];
                    sprintf(label, "call %s", (yyvsp[-2].valor_lexico).valor);
                    (yyval.nodo_arvore) = asd_new(label);
                    (yyval.nodo_arvore)->data_type = symbol->type;
                    free((yyvsp[-2].valor_lexico).valor);
                }
#line 1886 "parser.tab.c"
    break;

  case 42: /* chamada_funcao: TK_ID '(' argumentos ')'  */
#line 299 "parser.y"
                                         {
                    symbol_t* symbol = find_symbol((yyvsp[-3].valor_lexico).valor);
                    if (symbol == NULL) semantic_error(ERR_UNDECLARED, (yyvsp[-3].valor_lexico).numero_linha, (yyvsp[-3].valor_lexico).valor);
                    if (symbol->nature != NATURE_FUNCTION) semantic_error(ERR_VARIABLE, (yyvsp[-3].valor_lexico).numero_linha, (yyvsp[-3].valor_lexico).valor);
                    
                    if (symbol->params == NULL || symbol->params->number_of_children == 0) {
                        semantic_error(ERR_EXCESS_ARGS, (yyvsp[-3].valor_lexico).numero_linha, (yyvsp[-3].valor_lexico).valor);
                    } else {
                        check_function_call_args(symbol, (yyvsp[-1].nodo_arvore), (yyvsp[-3].valor_lexico).numero_linha);
                    }
                    
                    char label[256];
                    sprintf(label, "call %s", (yyvsp[-3].valor_lexico).valor);
                    (yyval.nodo_arvore) = asd_new(label);
                    (yyval.nodo_arvore)->data_type = symbol->type;
                    asd_add_child((yyval.nodo_arvore), (yyvsp[-1].nodo_arvore)); 
                    free((yyvsp[-3].valor_lexico).valor);
                }
#line 1909 "parser.tab.c"
    break;

  case 43: /* argumentos: expressao  */
#line 319 "parser.y"
                                     { (yyval.nodo_arvore) = asd_new("args"); asd_add_child((yyval.nodo_arvore), (yyvsp[0].nodo_arvore)); }
#line 1915 "parser.tab.c"
    break;

  case 44: /* argumentos: expressao ',' argumentos  */
#line 320 "parser.y"
                                     { asd_add_child((yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); (yyval.nodo_arvore) = (yyvsp[-2].nodo_arvore); }
#line 1921 "parser.tab.c"
    break;

  case 45: /* retorno: TK_RETORNA expressao TK_ATRIB tipo_num  */
#line 323 "parser.y"
                                                { 
            // Verifica se o tipo do retorno é compatível com o tipo da expressão
            if ((yyvsp[0].tipo_dado) != (yyvsp[-2].nodo_arvore)->data_type) {
                semantic_error(ERR_WRONG_TYPE, get_line_number(), "Tipo de retorno incompatível com a expressão retornada.");
            }
            if (current_function == NULL) {
                semantic_error(ERR_WRONG_TYPE, get_line_number(), "Comando 'retorna' fora do escopo de uma função.");
            } else if (current_function->type != (yyvsp[0].tipo_dado)) {
                semantic_error(ERR_WRONG_TYPE, get_line_number(), "Tipo de retorno declarado ('retorna ... := tipo') incompatível com o tipo da função.");
            }
            (yyval.nodo_arvore) = asd_new("retorna");
            (yyval.nodo_arvore)->data_type = (yyvsp[-2].nodo_arvore)->data_type;
            asd_add_child((yyval.nodo_arvore), (yyvsp[-2].nodo_arvore));
         }
#line 1940 "parser.tab.c"
    break;

  case 46: /* repeticao: TK_ENQUANTO '(' expressao ')' bloco_de_comandos  */
#line 338 "parser.y"
                                                           {	
                if ((yyvsp[-2].nodo_arvore)->data_type != TYPE_INTEGER) {
                    semantic_error(ERR_WRONG_TYPE, get_line_number(), "Expressão de teste do 'enquanto' deve ser do tipo 'inteiro'.");
                }
                (yyval.nodo_arvore) = asd_new("enquanto");
                (yyval.nodo_arvore)->data_type = (yyvsp[-2].nodo_arvore)->data_type;
                asd_add_child((yyval.nodo_arvore), (yyvsp[-2].nodo_arvore));
                if ((yyvsp[0].nodo_arvore) != NULL) asd_add_child((yyval.nodo_arvore), (yyvsp[0].nodo_arvore));
           }
#line 1954 "parser.tab.c"
    break;

  case 47: /* tipo_num: TK_DECIMAL  */
#line 348 "parser.y"
                     { (yyval.tipo_dado) = TYPE_FLOAT; }
#line 1960 "parser.tab.c"
    break;

  case 48: /* tipo_num: TK_INTEIRO  */
#line 349 "parser.y"
                     { (yyval.tipo_dado) = TYPE_INTEGER; }
#line 1966 "parser.tab.c"
    break;

  case 49: /* expressao: expr_logica_ou  */
#line 352 "parser.y"
                          { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 1972 "parser.tab.c"
    break;

  case 50: /* expr_logica_ou: expr_logica_ou '|' expr_logica_e  */
#line 354 "parser.y"
                                                 { (yyval.nodo_arvore) = asd_new_binary_op("|", (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); check_types((yyval.nodo_arvore), (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); }
#line 1978 "parser.tab.c"
    break;

  case 51: /* expr_logica_ou: expr_logica_e  */
#line 355 "parser.y"
                                                { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 1984 "parser.tab.c"
    break;

  case 52: /* expr_logica_e: expr_logica_e '&' expr_igualdade  */
#line 358 "parser.y"
                                                { (yyval.nodo_arvore) = asd_new_binary_op("&", (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); check_types((yyval.nodo_arvore), (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); }
#line 1990 "parser.tab.c"
    break;

  case 53: /* expr_logica_e: expr_igualdade  */
#line 359 "parser.y"
                                               { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 1996 "parser.tab.c"
    break;

  case 54: /* expr_igualdade: expr_igualdade TK_OC_EQ expr_relacional  */
#line 362 "parser.y"
                                                        { (yyval.nodo_arvore) = asd_new_binary_op("==", (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); check_types((yyval.nodo_arvore), (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); }
#line 2002 "parser.tab.c"
    break;

  case 55: /* expr_igualdade: expr_igualdade TK_OC_NE expr_relacional  */
#line 363 "parser.y"
                                                        { (yyval.nodo_arvore) = asd_new_binary_op("!=", (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); check_types((yyval.nodo_arvore), (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); }
#line 2008 "parser.tab.c"
    break;

  case 56: /* expr_igualdade: expr_relacional  */
#line 364 "parser.y"
                                                        { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 2014 "parser.tab.c"
    break;

  case 57: /* expr_relacional: expr_relacional '<' expr_aditiva  */
#line 367 "parser.y"
                                                       { (yyval.nodo_arvore) = asd_new_binary_op("<", (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); check_types((yyval.nodo_arvore), (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); }
#line 2020 "parser.tab.c"
    break;

  case 58: /* expr_relacional: expr_relacional '>' expr_aditiva  */
#line 368 "parser.y"
                                                       { (yyval.nodo_arvore) = asd_new_binary_op(">", (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); check_types((yyval.nodo_arvore), (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); }
#line 2026 "parser.tab.c"
    break;

  case 59: /* expr_relacional: expr_relacional TK_OC_LE expr_aditiva  */
#line 369 "parser.y"
                                                       { (yyval.nodo_arvore) = asd_new_binary_op("<=", (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); check_types((yyval.nodo_arvore), (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); }
#line 2032 "parser.tab.c"
    break;

  case 60: /* expr_relacional: expr_relacional TK_OC_GE expr_aditiva  */
#line 370 "parser.y"
                                                       { (yyval.nodo_arvore) = asd_new_binary_op(">=", (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); check_types((yyval.nodo_arvore), (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); }
#line 2038 "parser.tab.c"
    break;

  case 61: /* expr_relacional: expr_aditiva  */
#line 371 "parser.y"
                                                       { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore);}
#line 2044 "parser.tab.c"
    break;

  case 62: /* expr_aditiva: expr_aditiva '+' expr_multiplicativa  */
#line 374 "parser.y"
                                                   { (yyval.nodo_arvore) = asd_new_binary_op("+", (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); check_types((yyval.nodo_arvore), (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); }
#line 2050 "parser.tab.c"
    break;

  case 63: /* expr_aditiva: expr_aditiva '-' expr_multiplicativa  */
#line 375 "parser.y"
                                                   { (yyval.nodo_arvore) = asd_new_binary_op("-", (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); check_types((yyval.nodo_arvore), (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); }
#line 2056 "parser.tab.c"
    break;

  case 64: /* expr_aditiva: expr_multiplicativa  */
#line 376 "parser.y"
                                                   { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 2062 "parser.tab.c"
    break;

  case 65: /* expr_multiplicativa: expr_multiplicativa '*' expr_unaria  */
#line 379 "parser.y"
                                                         { (yyval.nodo_arvore) = asd_new_binary_op("*", (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); check_types((yyval.nodo_arvore), (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); }
#line 2068 "parser.tab.c"
    break;

  case 66: /* expr_multiplicativa: expr_multiplicativa '/' expr_unaria  */
#line 380 "parser.y"
                                                         { (yyval.nodo_arvore) = asd_new_binary_op("/", (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); check_types((yyval.nodo_arvore), (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); }
#line 2074 "parser.tab.c"
    break;

  case 67: /* expr_multiplicativa: expr_multiplicativa '%' expr_unaria  */
#line 381 "parser.y"
                                                         { (yyval.nodo_arvore) = asd_new_binary_op("%", (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); check_types((yyval.nodo_arvore), (yyvsp[-2].nodo_arvore), (yyvsp[0].nodo_arvore)); }
#line 2080 "parser.tab.c"
    break;

  case 68: /* expr_multiplicativa: expr_unaria  */
#line 382 "parser.y"
                                                         { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 2086 "parser.tab.c"
    break;

  case 69: /* expr_unaria: '+' fator  */
#line 385 "parser.y"
                       { (yyval.nodo_arvore) = asd_new_unary_op("+", (yyvsp[0].nodo_arvore)); (yyval.nodo_arvore)->data_type = (yyvsp[0].nodo_arvore)->data_type; }
#line 2092 "parser.tab.c"
    break;

  case 70: /* expr_unaria: '-' fator  */
#line 386 "parser.y"
                       { (yyval.nodo_arvore) = asd_new_unary_op("-", (yyvsp[0].nodo_arvore)); (yyval.nodo_arvore)->data_type = (yyvsp[0].nodo_arvore)->data_type; }
#line 2098 "parser.tab.c"
    break;

  case 71: /* expr_unaria: '!' fator  */
#line 387 "parser.y"
                       { (yyval.nodo_arvore) = asd_new_unary_op("!", (yyvsp[0].nodo_arvore)); (yyval.nodo_arvore)->data_type = (yyvsp[0].nodo_arvore)->data_type; }
#line 2104 "parser.tab.c"
    break;

  case 72: /* expr_unaria: fator  */
#line 388 "parser.y"
                       { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 2110 "parser.tab.c"
    break;

  case 73: /* fator: TK_ID  */
#line 391 "parser.y"
             {
           //  Busca o identificador e anota seu tipo no nó
           symbol_t* symbol = find_symbol((yyvsp[0].valor_lexico).valor);
           if (symbol == NULL) {
               semantic_error(ERR_UNDECLARED, (yyvsp[0].valor_lexico).numero_linha, (yyvsp[0].valor_lexico).valor);
           }
           if (symbol->nature != NATURE_VARIABLE) {
               semantic_error(ERR_FUNCTION, (yyvsp[0].valor_lexico).numero_linha, (yyvsp[0].valor_lexico).valor);
           }
           (yyval.nodo_arvore) = asd_new((yyvsp[0].valor_lexico).valor);
           (yyval.nodo_arvore)->data_type = symbol->type;
           free((yyvsp[0].valor_lexico).valor);
       }
#line 2128 "parser.tab.c"
    break;

  case 74: /* fator: literal  */
#line 404 "parser.y"
                      { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 2134 "parser.tab.c"
    break;

  case 75: /* fator: chamada_funcao  */
#line 405 "parser.y"
                      { (yyval.nodo_arvore) = (yyvsp[0].nodo_arvore); }
#line 2140 "parser.tab.c"
    break;

  case 76: /* fator: '(' expressao ')'  */
#line 406 "parser.y"
                         { (yyval.nodo_arvore) = (yyvsp[-1].nodo_arvore); }
#line 2146 "parser.tab.c"
    break;


#line 2150 "parser.tab.c"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 408 "parser.y"



void check_function_call_args(symbol_t* func_symbol, asd_tree_t* args_node, int line) {
    asd_tree_t* param_list = func_symbol->params;    
    int num_params = param_list->number_of_children;
    int num_args = args_node->number_of_children;

    // Verifica contagem de argumentos
    if (num_args < num_params) {
        semantic_error(ERR_MISSING_ARGS, line, func_symbol->key);
    }
    if (num_args > num_params) {
        semantic_error(ERR_EXCESS_ARGS, line, func_symbol->key);
    }

    // Verifica os tipos 
    for (int i = 0; i < num_params; i++) {
        asd_tree_t* current_param = param_list->children[i];
        asd_tree_t* current_arg = args_node->children[i];

        if (current_param->data_type != current_arg->data_type) {
            // Reporta erro especificando o argumento
            char error_msg[256];
            sprintf(error_msg, "Argumento %d na chamada da função '%s' está com tipo errado.", i+1, func_symbol->key);
            semantic_error(ERR_WRONG_TYPE_ARGS, line, error_msg);
        }
    }
}

// Implementação das funções auxiliares
void yyerror (char const *mensagem) {
    fprintf (stderr, "Erro sintático na Linha %i: %s\n", get_line_number(), mensagem);
}

static asd_tree_t* asd_new_binary_op(const char* label, asd_tree_t* child1, asd_tree_t* child2) {
     asd_tree_t* node = asd_new(label);
     asd_add_child(node, child1);
     asd_add_child(node, child2);
     return node;
}

static asd_tree_t* asd_new_unary_op(const char* label, asd_tree_t* child) {
     asd_tree_t* node = asd_new(label);
     asd_add_child(node, child);
     return node;
}

// Implementação da verificação de tipos para expressões binárias
void check_types(asd_tree_t* node, asd_tree_t* child1, asd_tree_t* child2) {
    if (child1->data_type == TYPE_UNDEFINED || child2->data_type == TYPE_UNDEFINED) {
        node->data_type = TYPE_UNDEFINED;
        return;
    }
    // float e int não podem ser misturados
    if (child1->data_type != child2->data_type) {
        semantic_error(ERR_WRONG_TYPE, get_line_number(), "Operação com tipos incompatíveis (int e float).");
    }
    node->data_type = child1->data_type;
}
