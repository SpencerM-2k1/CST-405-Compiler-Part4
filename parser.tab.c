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
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "AST.h"
#include "symbolTable.h"
#include "semantic.h"
#include "codeGenerator.h"
#include "optimizer.h"
#include "commons/types.h"

#define TABLE_SIZE 100
#define MAX_ID_LENGTH 10
#define VAR_SUFFIX_LENGTH 4

bool drawVertical[100] = { false }; // Adjust size as needed

extern int yylex();   // Declare yylex, the lexer function
extern int yyparse(); // Declare yyparse, the parser function
extern FILE* yyin;    // Declare yyin, the file pointer for the input file
extern int yylineno;  // Declare yylineno, the line number counter
extern TAC* tacHead;  // Declare the head of the linked list of TAC entries

void yyerror(const char* s);

extern int chars;
extern int lines;

ASTNode* root = NULL;
SymbolTable* symTab = NULL;
Symbol* symbol = NULL;

char* currentFunction = NULL; 	// Name of current function-- used for scope
								// NULL when not in a function

#line 108 "parser.tab.c"

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
  YYSYMBOL_TYPE = 3,                       /* TYPE  */
  YYSYMBOL_ID = 4,                         /* ID  */
  YYSYMBOL_SEMI = 5,                       /* SEMI  */
  YYSYMBOL_ASSIGN = 6,                     /* ASSIGN  */
  YYSYMBOL_INT_NUMBER = 7,                 /* INT_NUMBER  */
  YYSYMBOL_FLOAT_NUMBER = 8,               /* FLOAT_NUMBER  */
  YYSYMBOL_CHAR_VALUE = 9,                 /* CHAR_VALUE  */
  YYSYMBOL_CONST_TRUE = 10,                /* CONST_TRUE  */
  YYSYMBOL_CONST_FALSE = 11,               /* CONST_FALSE  */
  YYSYMBOL_WRITE = 12,                     /* WRITE  */
  YYSYMBOL_ARRAY = 13,                     /* ARRAY  */
  YYSYMBOL_RETURN = 14,                    /* RETURN  */
  YYSYMBOL_LPAREN = 15,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 16,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 17,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 18,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 19,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 20,                  /* RBRACKET  */
  YYSYMBOL_COMMA = 21,                     /* COMMA  */
  YYSYMBOL_IF = 22,                        /* IF  */
  YYSYMBOL_ELSE = 23,                      /* ELSE  */
  YYSYMBOL_ELIF = 24,                      /* ELIF  */
  YYSYMBOL_WHILE = 25,                     /* WHILE  */
  YYSYMBOL_BREAK = 26,                     /* BREAK  */
  YYSYMBOL_NOT = 27,                       /* NOT  */
  YYSYMBOL_AND = 28,                       /* AND  */
  YYSYMBOL_OR = 29,                        /* OR  */
  YYSYMBOL_GREATER_THAN = 30,              /* GREATER_THAN  */
  YYSYMBOL_LESS_THAN = 31,                 /* LESS_THAN  */
  YYSYMBOL_EQUAL_EQUAL = 32,               /* EQUAL_EQUAL  */
  YYSYMBOL_NOT_EQUAL = 33,                 /* NOT_EQUAL  */
  YYSYMBOL_GREATER_EQUAL = 34,             /* GREATER_EQUAL  */
  YYSYMBOL_LESS_EQUAL = 35,                /* LESS_EQUAL  */
  YYSYMBOL_PLUS = 36,                      /* PLUS  */
  YYSYMBOL_MINUS = 37,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 38,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 39,                    /* DIVIDE  */
  YYSYMBOL_MOD = 40,                       /* MOD  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_Program = 42,                   /* Program  */
  YYSYMBOL_DeclList = 43,                  /* DeclList  */
  YYSYMBOL_VarDeclList = 44,               /* VarDeclList  */
  YYSYMBOL_VarDecl = 45,                   /* VarDecl  */
  YYSYMBOL_VarDeclInit = 46,               /* VarDeclInit  */
  YYSYMBOL_FuncDecl = 47,                  /* FuncDecl  */
  YYSYMBOL_48_1 = 48,                      /* @1  */
  YYSYMBOL_ParamList = 49,                 /* ParamList  */
  YYSYMBOL_Param = 50,                     /* Param  */
  YYSYMBOL_StmtList = 51,                  /* StmtList  */
  YYSYMBOL_Stmt = 52,                      /* Stmt  */
  YYSYMBOL_IfStmt = 53,                    /* IfStmt  */
  YYSYMBOL_ElifList = 54,                  /* ElifList  */
  YYSYMBOL_Block = 55,                     /* Block  */
  YYSYMBOL_WhileStmt = 56,                 /* WhileStmt  */
  YYSYMBOL_BreakStmt = 57,                 /* BreakStmt  */
  YYSYMBOL_Expr = 58,                      /* Expr  */
  YYSYMBOL_FuncCall = 59,                  /* FuncCall  */
  YYSYMBOL_ArgList = 60,                   /* ArgList  */
  YYSYMBOL_Arg = 61,                       /* Arg  */
  YYSYMBOL_ReturnStmt = 62                 /* ReturnStmt  */
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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   359

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  146

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    76,    76,    87,    90,    97,   104,   115,   118,   128,
     192,   223,   263,   262,   303,   306,   312,   321,   338,   341,
     351,   361,   372,   377,   383,   387,   391,   395,   399,   406,
     414,   422,   433,   441,   449,   457,   465,   472,   482,   490,
     496,   502,   510,   518,   526,   534,   542,   550,   558,   566,
     574,   582,   590,   598,   606,   613,   621,   627,   633,   639,
     644,   649,   653,   660,   670,   673,   679,   688,   696,   701
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
  "\"end of file\"", "error", "\"invalid token\"", "TYPE", "ID", "SEMI",
  "ASSIGN", "INT_NUMBER", "FLOAT_NUMBER", "CHAR_VALUE", "CONST_TRUE",
  "CONST_FALSE", "WRITE", "ARRAY", "RETURN", "LPAREN", "RPAREN", "LBRACE",
  "RBRACE", "LBRACKET", "RBRACKET", "COMMA", "IF", "ELSE", "ELIF", "WHILE",
  "BREAK", "NOT", "AND", "OR", "GREATER_THAN", "LESS_THAN", "EQUAL_EQUAL",
  "NOT_EQUAL", "GREATER_EQUAL", "LESS_EQUAL", "PLUS", "MINUS", "MULTIPLY",
  "DIVIDE", "MOD", "$accept", "Program", "DeclList", "VarDeclList",
  "VarDecl", "VarDeclInit", "FuncDecl", "@1", "ParamList", "Param",
  "StmtList", "Stmt", "IfStmt", "ElifList", "Block", "WhileStmt",
  "BreakStmt", "Expr", "FuncCall", "ArgList", "Arg", "ReturnStmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-114)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       1,     4,    12,    21,   305,     1,     1,     1,    28,    40,
    -114,    47,     5,    82,    82,    34,    39,    53,  -114,  -114,
     305,  -114,  -114,  -114,    54,    83,  -114,  -114,  -114,  -114,
      82,    72,    75,    89,    82,    82,    82,     8,  -114,  -114,
    -114,  -114,  -114,    82,    82,    82,    45,  -114,   319,    82,
      82,  -114,  -114,  -114,  -114,   112,    93,    91,   125,   319,
      84,    78,   147,    82,   186,   173,     0,  -114,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,   211,   236,  -114,    97,    86,    87,    85,  -114,  -114,
      82,   104,   306,  -114,   173,   173,   198,   198,   198,   198,
     198,   198,     0,     0,  -114,  -114,  -114,   299,   299,  -114,
      94,    93,   108,  -114,    82,  -114,     6,  -114,    29,  -114,
       6,  -114,  -114,   161,   110,   305,     6,   299,   100,  -114,
     305,  -114,   111,   102,  -114,  -114,    82,   106,  -114,   261,
    -114,   299,    33,   299,  -114,  -114
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,     0,    18,     3,     3,     3,    12,     0,
       1,     0,     0,     0,    68,     0,     0,     0,    22,     2,
      18,    26,    27,    28,     0,     0,     4,     5,     6,     9,
       0,     0,     0,     0,     0,    64,     0,    54,    56,    57,
      58,    59,    60,     0,     0,     0,     0,    61,    69,     0,
       0,    38,    19,    24,    25,     0,    14,     0,     0,    67,
       0,    65,     0,     0,     0,    40,    39,    23,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    11,     0,     0,    15,     0,    20,    63,
      64,     0,     0,    62,    46,    47,    48,    49,    52,    53,
      50,    51,    41,    42,    43,    44,    45,     0,     0,    17,
       0,    14,     0,    66,     0,    55,     7,    36,    29,    37,
       7,    16,    10,     0,     0,    18,     7,     0,     0,    31,
      18,    21,     0,     0,     8,    30,     0,     0,    35,     0,
      13,     0,    32,     0,    33,    34
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -114,  -114,    41,  -108,  -113,    25,  -114,  -114,     7,  -114,
     -18,    -3,  -114,   -17,   -98,  -114,  -114,    -8,    -4,    42,
    -114,  -114
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,     4,   125,     5,    18,     7,    31,    85,    86,
      19,   117,    21,   129,   118,    22,    23,    59,    47,    60,
      61,    25
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      24,    20,    52,   126,     1,    46,    48,   126,     8,   124,
     119,    34,   130,   126,     2,     9,    24,    20,   134,     2,
      35,    10,    55,    35,    36,     6,    58,    63,    62,   135,
       6,     6,     6,    29,    30,    64,    65,    66,    78,    79,
      80,    81,    82,   142,    32,   145,    26,    27,    28,    49,
      67,    33,   127,   128,    50,    92,   143,   128,    51,    53,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    37,    56,    54,    38,
      39,    40,    41,    42,    57,    30,    84,    43,    87,    90,
      89,   109,   110,    24,    24,   112,   123,   133,   111,    44,
     114,   120,   137,   122,   132,   136,    29,    83,   121,    45,
     138,    24,    20,    24,   140,   144,    24,    20,   139,     0,
      88,     0,   113,     0,     0,     0,     0,    24,     0,    24,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,   131,    91,     0,     0,
       0,     0,     0,     0,     0,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,     0,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    93,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,   107,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    77,    78,    79,    80,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,   108,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,   141,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    11,    12,     0,     0,     0,     0,    11,    12,
       0,    13,     0,    14,     0,     0,   116,    13,     0,    14,
       0,    15,     0,     0,    16,    17,   115,    15,     0,     0,
      16,    17,     0,     0,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80
};

static const yytype_int16 yycheck[] =
{
       4,     4,    20,   116,     3,    13,    14,   120,     4,     3,
     108,     6,   120,   126,    13,     3,    20,    20,   126,    13,
      15,     0,    30,    15,    19,     0,    34,    19,    36,   127,
       5,     6,     7,     5,     6,    43,    44,    45,    38,    39,
      40,    49,    50,   141,     4,   143,     5,     6,     7,    15,
       5,     4,    23,    24,    15,    63,    23,    24,     5,     5,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,     4,    15,     5,     7,
       8,     9,    10,    11,    19,     6,     3,    15,     7,    21,
      16,     4,    16,   107,   108,    20,   114,   125,    21,    27,
       6,    17,   130,     5,     4,    15,     5,     5,   111,    37,
      18,   125,   125,   127,    18,   142,   130,   130,   136,    -1,
       5,    -1,    90,    -1,    -1,    -1,    -1,   141,    -1,   143,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,     5,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    -1,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    16,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    16,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    16,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,     3,     4,    -1,    -1,    -1,    -1,     3,     4,
      -1,    12,    -1,    14,    -1,    -1,    17,    12,    -1,    14,
      -1,    22,    -1,    -1,    25,    26,    20,    22,    -1,    -1,
      25,    26,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    13,    42,    43,    45,    46,    47,     4,     3,
       0,     3,     4,    12,    14,    22,    25,    26,    46,    51,
      52,    53,    56,    57,    59,    62,    43,    43,    43,     5,
       6,    48,     4,     4,     6,    15,    19,     4,     7,     8,
       9,    10,    11,    15,    27,    37,    58,    59,    58,    15,
      15,     5,    51,     5,     5,    58,    15,    19,    58,    58,
      60,    61,    58,    19,    58,    58,    58,     5,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    58,    58,     5,     3,    49,    50,     7,     5,    16,
      21,    20,    58,    16,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    16,    16,     4,
      16,    21,    20,    60,     6,    20,    17,    52,    55,    55,
      17,    49,     5,    58,     3,    44,    45,    23,    24,    54,
      44,     5,     4,    51,    44,    55,    15,    51,    18,    58,
      18,    16,    55,    23,    54,    55
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    43,    43,    44,    44,    45,
      45,    46,    48,    47,    49,    49,    49,    50,    51,    51,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    53,
      53,    53,    54,    54,    54,    55,    55,    56,    57,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    59,    60,    60,    60,    61,    62,    62
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     2,     2,     2,     0,     2,     3,
       7,     5,     0,    10,     0,     1,     3,     2,     0,     2,
       4,     7,     1,     3,     2,     2,     1,     1,     1,     5,
       7,     6,     5,     6,     2,     4,     1,     5,     2,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     4,     1,     1,     1,     1,
       1,     1,     3,     4,     0,     1,     3,     1,     1,     2
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
  case 2: /* Program: DeclList StmtList  */
#line 77 "parser.y"
    {
        printf("The PARSER has started\n");
        root = createNode(NodeType_Program);
        root->data.program.varDeclList = (yyvsp[-1].ast);
        root->data.program.stmtList = (yyvsp[0].ast);
    }
#line 1294 "parser.tab.c"
    break;

  case 3: /* DeclList: %empty  */
#line 87 "parser.y"
    {
        (yyval.ast) = NULL;
    }
#line 1302 "parser.tab.c"
    break;

  case 4: /* DeclList: VarDecl DeclList  */
#line 91 "parser.y"
    {
        printf("PARSER: Recognized declaration list (variable entry)\n");
        (yyval.ast) = createNode(NodeType_DeclList);
        (yyval.ast)->data.declList.decl = (yyvsp[-1].ast);
        (yyval.ast)->data.declList.next = (yyvsp[0].ast);
    }
#line 1313 "parser.tab.c"
    break;

  case 5: /* DeclList: VarDeclInit DeclList  */
#line 98 "parser.y"
    {
        printf("PARSER: Recognized declaration list (variable entry with initialization)\n");
        (yyval.ast) = createNode(NodeType_DeclList);
        (yyval.ast)->data.declList.decl = (yyvsp[-1].ast);
        (yyval.ast)->data.declList.next = (yyvsp[0].ast);
    }
#line 1324 "parser.tab.c"
    break;

  case 6: /* DeclList: FuncDecl DeclList  */
#line 105 "parser.y"
    {
        printf("PARSER: Recognized declaration list (function entry)\n");
        (yyval.ast) = createNode(NodeType_DeclList);
        (yyval.ast)->data.declList.decl = (yyvsp[-1].ast);
        (yyval.ast)->data.declList.next = (yyvsp[0].ast);
    }
#line 1335 "parser.tab.c"
    break;

  case 7: /* VarDeclList: %empty  */
#line 115 "parser.y"
    {
        (yyval.ast) = NULL;
    }
#line 1343 "parser.tab.c"
    break;

  case 8: /* VarDeclList: VarDecl VarDeclList  */
#line 119 "parser.y"
    {
        printf("PARSER: Recognized function-scoped variable declaration list\n");
        (yyval.ast) = createNode(NodeType_VarDeclList);
        (yyval.ast)->data.varDeclList.varDecl = (yyvsp[-1].ast);
        (yyval.ast)->data.varDeclList.next = (yyvsp[0].ast);
    }
#line 1354 "parser.tab.c"
    break;

  case 9: /* VarDecl: TYPE ID SEMI  */
#line 129 "parser.y"
    {
        printf("PARSER: Recognized variable declaration: %s\n", (yyvsp[-1].sval));
        printf("PARSER: Printing symbol table\n");
        printSymbolTable(symTab);
        printf("PARSER: Checking if variable has already been declared\n");

        char* varName = strdup((yyvsp[-1].sval));
        printf("Name with suffix: %s\n", varName);

        symbol = lookupSymbolInCurrentScope(symTab, varName);

        if (symbol != NULL)
        {
            printf("PARSER: Variable %s at line %d has already been declared - COMPILATION HALTED\n", (yyvsp[-1].sval), yylineno);
            exit(0);
        }
        else
        {
            (yyval.ast) = createNode(NodeType_VarDecl);
            (yyval.ast)->data.varDecl.varType = strdup((yyvsp[-2].sval));
            (yyval.ast)->data.varDecl.varName = strdup(varName);

            addSymbol(symTab, varName, (yyvsp[-2].sval));
            printSymbolTable(symTab);
        }
    }
#line 1385 "parser.tab.c"
    break;

  case 10: /* VarDecl: ARRAY TYPE ID LBRACKET INT_NUMBER RBRACKET SEMI  */
#line 193 "parser.y"
    {
        printf("PARSER: Printing symbol table\n");
        printSymbolTable(symTab);
        printf("PARSER: Checking if variable has already been declared\n");

        char* varName = strdup((yyvsp[-4].sval));
        printf("Name with suffix: %s\n", varName);

        symbol = lookupSymbolInCurrentScope(symTab, varName);

        if (symbol != NULL)
        {
            printf("PARSER: Variable %s at line %d has already been declared - COMPILATION HALTED\n", (yyvsp[-4].sval), yylineno);
            exit(0);
        }
        else
        {
            (yyval.ast) = createNode(NodeType_ArrDecl);
            (yyval.ast)->data.arrDecl.varType = strdup((yyvsp[-5].sval));
            (yyval.ast)->data.arrDecl.varName = strdup(varName);
            (yyval.ast)->data.arrDecl.arrSize = (yyvsp[-2].intVal);

            addArrSymbol(symTab, varName, (yyvsp[-5].sval), (yyvsp[-2].intVal));
            printSymbolTable(symTab);
        }
    }
#line 1416 "parser.tab.c"
    break;

  case 11: /* VarDeclInit: TYPE ID ASSIGN Expr SEMI  */
#line 224 "parser.y"
    {
        // printf("PARSER: Recognized variable declaration with initialization: %s\n", $2);

        // // Check if variable has already been declared
        // char* varName = strdup($2);
        // symbol = lookupSymbolInCurrentScope(symTab, varName);

        // if (symbol != NULL)
        // {
        //     printf("PARSER: Variable %s at line %d has already been declared - COMPILATION HALTED\n", $2, yylineno);
        //     exit(0);
        // }
        // else
        // {
        //     // Declare the variable
        //     ASTNode* varDeclNode = createNode(NodeType_VarDecl);
        //     varDeclNode->data.varDecl.varType = strdup($1);
        //     varDeclNode->data.varDecl.varName = strdup(varName);

        //     addSymbol(symTab, varName, $1);
        //     printSymbolTable(symTab);

        //     // Create an assignment statement for initialization
        //     ASTNode* assignStmtNode = createNode(NodeType_AssignStmt);
        //     assignStmtNode->data.assignStmt.varName = strdup(varName);
        //     assignStmtNode->data.assignStmt.operator = strdup($3);
        //     assignStmtNode->data.assignStmt.expr = $4;

        //     // Combine declaration and assignment into a VarDeclInit node
        //     $$ = createNode(NodeType_VarDeclInit);
        //     $$->data.varDeclInit.varDecl = varDeclNode;
        //     $$->data.varDeclInit.assignStmt = assignStmtNode;
        // }
    }
#line 1455 "parser.tab.c"
    break;

  case 12: /* @1: %empty  */
#line 263 "parser.y"
    {
        (yyval.ast) = createNode(NodeType_FuncDecl); //Partially generate a node to be passed to end rule
        
        currentFunction = (yyvsp[0].sval);
        
        // Check for redeclaration
        if (lookupSymbolInHierarchy(peekSubTable(symTab), (yyvsp[0].sval))) {
            fprintf(stderr, "PARSER: Function '%s' already declared\n", (yyvsp[0].sval));
            exit(1);
        }
        Symbol* sym = addFuncSymbol(symTab, (yyvsp[0].sval), (yyvsp[-1].sval));
        (yyval.ast)->data.funcDecl.name = strdup(sym->name);
        SubTable* newSubTab = enterNewScope(symTab, (yyvsp[0].sval));
        (yyval.ast)->data.funcDecl.funcSubTable = newSubTab;
    }
#line 1475 "parser.tab.c"
    break;

  case 13: /* FuncDecl: TYPE ID @1 LPAREN ParamList RPAREN LBRACE VarDeclList StmtList RBRACE  */
#line 279 "parser.y"
    {
        (yyval.ast) = (yyvsp[-7].ast); //Retrieve incomplete ASTNode from midrule
        (yyval.ast)->data.funcDecl.returnType = stringToVarType((yyvsp[-9].sval));
        printf("PARSER: Recognized function declaration: %s\n", (yyvsp[-8].sval));

        // addSymbol(symTab, $$->data.funcDecl.name, $1);

        (yyval.ast)->data.funcDecl.paramList = (yyvsp[-5].ast);       // Correct
        (yyval.ast)->data.funcDecl.varDeclList = (yyvsp[-2].ast);     // Adjusted from $7 to $8
        (yyval.ast)->data.funcDecl.stmtList = (yyvsp[-1].ast);        // Adjusted from $8 to $9

        currentFunction = NULL;

        //New implementation
        // $$ = createNode(NodeType_FuncDecl);
        // printf("PARSER: Recognized function declaration: %s\n", $2);
        // addFuncSymbol(symTab, $$->data.funcDecl.name, $1);

        exitScope(symTab);
    }
#line 1500 "parser.tab.c"
    break;

  case 14: /* ParamList: %empty  */
#line 303 "parser.y"
    {
        (yyval.ast) = NULL;
    }
#line 1508 "parser.tab.c"
    break;

  case 15: /* ParamList: Param  */
#line 307 "parser.y"
    {
        (yyval.ast) = createNode(NodeType_ParamList);
        (yyval.ast)->data.paramList.param = (yyvsp[0].ast);
        (yyval.ast)->data.paramList.next = NULL;
    }
#line 1518 "parser.tab.c"
    break;

  case 16: /* ParamList: Param COMMA ParamList  */
#line 313 "parser.y"
    {
        (yyval.ast) = createNode(NodeType_ParamList);
        (yyval.ast)->data.paramList.param = (yyvsp[-2].ast);
        (yyval.ast)->data.paramList.next = (yyvsp[0].ast);
    }
#line 1528 "parser.tab.c"
    break;

  case 17: /* Param: TYPE ID  */
#line 322 "parser.y"
    {
        (yyval.ast) = createNode(NodeType_Param);
        (yyval.ast)->data.param.type = stringToVarType((yyvsp[-1].sval));

        (yyval.ast)->data.param.name = strdup((yyvsp[0].sval));
        // Check if the parameter is already declared (though unlikely)
        if (lookupSymbolInCurrentScope(symTab, (yyvsp[0].sval))) {
            fprintf(stderr, "Parameter '%s' already declared in current scope\n", (yyvsp[0].sval));
            exit(1);
        }
        addSymbol(symTab, (yyval.ast)->data.param.name, (yyvsp[-1].sval));
    }
#line 1545 "parser.tab.c"
    break;

  case 18: /* StmtList: %empty  */
#line 338 "parser.y"
    {
        (yyval.ast) = NULL;
    }
#line 1553 "parser.tab.c"
    break;

  case 19: /* StmtList: Stmt StmtList  */
#line 342 "parser.y"
    {
        printf("PARSER: Recognized statement list\n");
        (yyval.ast) = createNode(NodeType_StmtList);
        (yyval.ast)->data.stmtList.stmt = (yyvsp[-1].ast);
        (yyval.ast)->data.stmtList.stmtList = (yyvsp[0].ast);
    }
#line 1564 "parser.tab.c"
    break;

  case 20: /* Stmt: ID ASSIGN Expr SEMI  */
#line 352 "parser.y"
    {
        printf("PARSER: Recognized assignment statement\n");
        (yyval.ast) = createNode(NodeType_AssignStmt);
        char* varName = (yyvsp[-3].sval);

        (yyval.ast)->data.assignStmt.varName = strdup(varName);
        (yyval.ast)->data.assignStmt.operator = strdup((yyvsp[-2].sval));
        (yyval.ast)->data.assignStmt.expr = (yyvsp[-1].ast);
    }
#line 1578 "parser.tab.c"
    break;

  case 21: /* Stmt: ID LBRACKET Expr RBRACKET ASSIGN Expr SEMI  */
#line 362 "parser.y"
    {
        printf("PARSER: Recognized array assignment statement\n");
        (yyval.ast) = createNode(NodeType_AssignArrStmt);
        char* varName = strdup((yyvsp[-6].sval));

        (yyval.ast)->data.assignArrStmt.varName = strdup(varName);
        (yyval.ast)->data.assignArrStmt.operator = strdup((yyvsp[-2].sval));
        (yyval.ast)->data.assignArrStmt.expr = (yyvsp[-1].ast);
        (yyval.ast)->data.assignArrStmt.indexExpr = (yyvsp[-4].ast);
    }
#line 1593 "parser.tab.c"
    break;

  case 22: /* Stmt: VarDeclInit  */
#line 373 "parser.y"
    {
        // Since VarDeclInit contains both declaration and assignment
        (yyval.ast) = (yyvsp[0].ast);
    }
#line 1602 "parser.tab.c"
    break;

  case 23: /* Stmt: WRITE Expr SEMI  */
#line 378 "parser.y"
    {
        printf("PARSER: Recognized write statement\n");
        (yyval.ast) = createNode(NodeType_WriteStmt);
        (yyval.ast)->data.writeStmt.expr = (yyvsp[-1].ast);
    }
#line 1612 "parser.tab.c"
    break;

  case 24: /* Stmt: FuncCall SEMI  */
#line 384 "parser.y"
    {
        (yyval.ast) = (yyvsp[-1].ast);
    }
#line 1620 "parser.tab.c"
    break;

  case 25: /* Stmt: ReturnStmt SEMI  */
#line 388 "parser.y"
    {
        (yyval.ast) = (yyvsp[-1].ast);
    }
#line 1628 "parser.tab.c"
    break;

  case 26: /* Stmt: IfStmt  */
#line 392 "parser.y"
    {
        (yyval.ast) = (yyvsp[0].ast);
    }
#line 1636 "parser.tab.c"
    break;

  case 27: /* Stmt: WhileStmt  */
#line 396 "parser.y"
    {
        (yyval.ast) = (yyvsp[0].ast);
    }
#line 1644 "parser.tab.c"
    break;

  case 28: /* Stmt: BreakStmt  */
#line 400 "parser.y"
    {
        (yyval.ast) = (yyvsp[0].ast);
    }
#line 1652 "parser.tab.c"
    break;

  case 29: /* IfStmt: IF LPAREN Expr RPAREN Block  */
#line 407 "parser.y"
    {
        printf("PARSER: Recognized 'if' statement\n");
        (yyval.ast) = createNode(NodeType_IfStmt);
        (yyval.ast)->data.ifStmt.condition = (yyvsp[-2].ast);
        (yyval.ast)->data.ifStmt.thenStmt = (yyvsp[0].ast);
        (yyval.ast)->data.ifStmt.elseStmt = NULL;
    }
#line 1664 "parser.tab.c"
    break;

  case 30: /* IfStmt: IF LPAREN Expr RPAREN Block ELSE Block  */
#line 415 "parser.y"
    {
        printf("PARSER: Recognized 'if-else' statement\n");
        (yyval.ast) = createNode(NodeType_IfStmt);
        (yyval.ast)->data.ifStmt.condition = (yyvsp[-4].ast);
        (yyval.ast)->data.ifStmt.thenStmt = (yyvsp[-2].ast);
        (yyval.ast)->data.ifStmt.elseStmt = (yyvsp[0].ast);
    }
#line 1676 "parser.tab.c"
    break;

  case 31: /* IfStmt: IF LPAREN Expr RPAREN Block ElifList  */
#line 423 "parser.y"
    {
        printf("PARSER: Recognized 'if-elif' statement\n");
        (yyval.ast) = createNode(NodeType_IfStmt);
        (yyval.ast)->data.ifStmt.condition = (yyvsp[-3].ast);
        (yyval.ast)->data.ifStmt.thenStmt = (yyvsp[-1].ast);
        (yyval.ast)->data.ifStmt.elseStmt = (yyvsp[0].ast);  // ElifList is assigned to elseStmt
    }
#line 1688 "parser.tab.c"
    break;

  case 32: /* ElifList: ELIF LPAREN Expr RPAREN Block  */
#line 434 "parser.y"
    {
        printf("PARSER: Recognized 'elif' statement\n");
        (yyval.ast) = createNode(NodeType_IfStmt);
        (yyval.ast)->data.ifStmt.condition = (yyvsp[-2].ast);
        (yyval.ast)->data.ifStmt.elseStmt = NULL;
        (yyval.ast)->data.ifStmt.thenStmt = (yyvsp[0].ast);
    }
#line 1700 "parser.tab.c"
    break;

  case 33: /* ElifList: ELIF LPAREN Expr RPAREN Block ElifList  */
#line 442 "parser.y"
    {
        printf("PARSER: Recognized 'elif' with additional 'elif' or 'else'\n");
        (yyval.ast) = createNode(NodeType_IfStmt);
        (yyval.ast)->data.ifStmt.condition = (yyvsp[-3].ast);
        (yyval.ast)->data.ifStmt.thenStmt = (yyvsp[-1].ast);
        (yyval.ast)->data.ifStmt.elseStmt = (yyvsp[0].ast);  // ElifList is assigned to elseStmt
    }
#line 1712 "parser.tab.c"
    break;

  case 34: /* ElifList: ELSE Block  */
#line 450 "parser.y"
    {
        printf("PARSER: Recognized 'else' statement\n");
        (yyval.ast) = (yyvsp[0].ast); // Directly assign the else Block
    }
#line 1721 "parser.tab.c"
    break;

  case 35: /* Block: LBRACE VarDeclList StmtList RBRACE  */
#line 458 "parser.y"
    {
        // Scope creation/exit is handled by FuncDecl/If/etc.
        //  This is because scope creation requires unique data
        //  based on the type of scope (e.g. name). Unfortunate.
        (yyval.ast) = (yyvsp[-2].ast);             
        (yyval.ast) = (yyvsp[-1].ast);             
    }
#line 1733 "parser.tab.c"
    break;

  case 36: /* Block: Stmt  */
#line 466 "parser.y"
    {
        (yyval.ast) = (yyvsp[0].ast);  // Single statements do not introduce a new scope
    }
#line 1741 "parser.tab.c"
    break;

  case 37: /* WhileStmt: WHILE LPAREN Expr RPAREN Block  */
#line 473 "parser.y"
    {
        printf("PARSER: Recognized 'while' statement\n");
        (yyval.ast) = createNode(NodeType_WhileStmt);
        (yyval.ast)->data.whileStmt.condition = (yyvsp[-2].ast);
        (yyval.ast)->data.whileStmt.block = (yyvsp[0].ast);
    }
#line 1752 "parser.tab.c"
    break;

  case 38: /* BreakStmt: BREAK SEMI  */
#line 483 "parser.y"
    {
        printf("PARSER: Recognized 'break' statement\n");
        (yyval.ast) = createNode(NodeType_BreakStmt);
    }
#line 1761 "parser.tab.c"
    break;

  case 39: /* Expr: MINUS Expr  */
#line 491 "parser.y"
    {
        (yyval.ast) = createNode(NodeType_UnaryOp);
        (yyval.ast)->data.unaryOp.expr = (yyvsp[0].ast);
        (yyval.ast)->data.unaryOp.operator = strdup("neg"); //Best to use a unique operator; '-' is used for binOp subtraction
    }
#line 1771 "parser.tab.c"
    break;

  case 40: /* Expr: NOT Expr  */
#line 497 "parser.y"
    {
        (yyval.ast) = createNode(NodeType_UnaryOp);
        (yyval.ast)->data.unaryOp.expr = (yyvsp[0].ast);
        (yyval.ast)->data.unaryOp.operator = strdup((yyvsp[-1].sval));
    }
#line 1781 "parser.tab.c"
    break;

  case 41: /* Expr: Expr PLUS Expr  */
#line 503 "parser.y"
    {
        printf("PARSER: Recognized addition expression\n");
        (yyval.ast) = createNode(NodeType_BinOp);
        (yyval.ast)->data.binOp.left = (yyvsp[-2].ast);
        (yyval.ast)->data.binOp.right = (yyvsp[0].ast);
        (yyval.ast)->data.binOp.operator = strdup((yyvsp[-1].sval));
    }
#line 1793 "parser.tab.c"
    break;

  case 42: /* Expr: Expr MINUS Expr  */
#line 511 "parser.y"
    {
        printf("PARSER: Recognized subtraction expression\n");
        (yyval.ast) = createNode(NodeType_BinOp);
        (yyval.ast)->data.binOp.left = (yyvsp[-2].ast);
        (yyval.ast)->data.binOp.right = (yyvsp[0].ast);
        (yyval.ast)->data.binOp.operator = strdup((yyvsp[-1].sval));
    }
#line 1805 "parser.tab.c"
    break;

  case 43: /* Expr: Expr MULTIPLY Expr  */
#line 519 "parser.y"
    {
        printf("PARSER: Recognized multiplication expression\n");
        (yyval.ast) = createNode(NodeType_BinOp);
        (yyval.ast)->data.binOp.left = (yyvsp[-2].ast);
        (yyval.ast)->data.binOp.right = (yyvsp[0].ast);
        (yyval.ast)->data.binOp.operator = strdup((yyvsp[-1].sval));
    }
#line 1817 "parser.tab.c"
    break;

  case 44: /* Expr: Expr DIVIDE Expr  */
#line 527 "parser.y"
    {
        printf("PARSER: Recognized division expression\n");
        (yyval.ast) = createNode(NodeType_BinOp);
        (yyval.ast)->data.binOp.left = (yyvsp[-2].ast);
        (yyval.ast)->data.binOp.right = (yyvsp[0].ast);
        (yyval.ast)->data.binOp.operator = strdup((yyvsp[-1].sval));
    }
#line 1829 "parser.tab.c"
    break;

  case 45: /* Expr: Expr MOD Expr  */
#line 535 "parser.y"
    {
        printf("PARSER: Recognized modulus expression\n");
        (yyval.ast) = createNode(NodeType_BinOp);
        (yyval.ast)->data.binOp.left = (yyvsp[-2].ast);
        (yyval.ast)->data.binOp.right = (yyvsp[0].ast);
        (yyval.ast)->data.binOp.operator = strdup((yyvsp[-1].sval));
    }
#line 1841 "parser.tab.c"
    break;

  case 46: /* Expr: Expr AND Expr  */
#line 543 "parser.y"
    {
        printf("PARSER: Recognized inequality expression\n");
        (yyval.ast) = createNode(NodeType_RelOp);
        (yyval.ast)->data.binOp.left = (yyvsp[-2].ast);
        (yyval.ast)->data.binOp.right = (yyvsp[0].ast);
        (yyval.ast)->data.binOp.operator = strdup((yyvsp[-1].sval));
    }
#line 1853 "parser.tab.c"
    break;

  case 47: /* Expr: Expr OR Expr  */
#line 551 "parser.y"
    {
        printf("PARSER: Recognized inequality expression\n");
        (yyval.ast) = createNode(NodeType_RelOp);
        (yyval.ast)->data.binOp.left = (yyvsp[-2].ast);
        (yyval.ast)->data.binOp.right = (yyvsp[0].ast);
        (yyval.ast)->data.binOp.operator = strdup((yyvsp[-1].sval));
    }
#line 1865 "parser.tab.c"
    break;

  case 48: /* Expr: Expr GREATER_THAN Expr  */
#line 559 "parser.y"
    {
        printf("PARSER: Recognized greater-than expression\n");
        (yyval.ast) = createNode(NodeType_RelOp);
        (yyval.ast)->data.binOp.left = (yyvsp[-2].ast);
        (yyval.ast)->data.binOp.right = (yyvsp[0].ast);
        (yyval.ast)->data.binOp.operator = strdup((yyvsp[-1].sval));
    }
#line 1877 "parser.tab.c"
    break;

  case 49: /* Expr: Expr LESS_THAN Expr  */
#line 567 "parser.y"
    {
        printf("PARSER: Recognized less-than expression\n");
        (yyval.ast) = createNode(NodeType_RelOp);
        (yyval.ast)->data.binOp.left = (yyvsp[-2].ast);
        (yyval.ast)->data.binOp.right = (yyvsp[0].ast);
        (yyval.ast)->data.binOp.operator = strdup((yyvsp[-1].sval));
    }
#line 1889 "parser.tab.c"
    break;

  case 50: /* Expr: Expr GREATER_EQUAL Expr  */
#line 575 "parser.y"
    {
        printf("PARSER: Recognized greater-than-or-equal expression\n");
        (yyval.ast) = createNode(NodeType_RelOp);
        (yyval.ast)->data.binOp.left = (yyvsp[-2].ast);
        (yyval.ast)->data.binOp.right = (yyvsp[0].ast);
        (yyval.ast)->data.binOp.operator = strdup((yyvsp[-1].sval));
    }
#line 1901 "parser.tab.c"
    break;

  case 51: /* Expr: Expr LESS_EQUAL Expr  */
#line 583 "parser.y"
    {
        printf("PARSER: Recognized less-than-or-equal expression\n");
        (yyval.ast) = createNode(NodeType_RelOp);
        (yyval.ast)->data.binOp.left = (yyvsp[-2].ast);
        (yyval.ast)->data.binOp.right = (yyvsp[0].ast);
        (yyval.ast)->data.binOp.operator = strdup((yyvsp[-1].sval));
    }
#line 1913 "parser.tab.c"
    break;

  case 52: /* Expr: Expr EQUAL_EQUAL Expr  */
#line 591 "parser.y"
    {
        printf("PARSER: Recognized equality expression\n");
        (yyval.ast) = createNode(NodeType_RelOp);
        (yyval.ast)->data.binOp.left = (yyvsp[-2].ast);
        (yyval.ast)->data.binOp.right = (yyvsp[0].ast);
        (yyval.ast)->data.binOp.operator = strdup((yyvsp[-1].sval));
    }
#line 1925 "parser.tab.c"
    break;

  case 53: /* Expr: Expr NOT_EQUAL Expr  */
#line 599 "parser.y"
    {
        printf("PARSER: Recognized inequality expression\n");
        (yyval.ast) = createNode(NodeType_RelOp);
        (yyval.ast)->data.binOp.left = (yyvsp[-2].ast);
        (yyval.ast)->data.binOp.right = (yyvsp[0].ast);
        (yyval.ast)->data.binOp.operator = strdup((yyvsp[-1].sval));
    }
#line 1937 "parser.tab.c"
    break;

  case 54: /* Expr: ID  */
#line 607 "parser.y"
    {
        printf("PARSER: Recognized identifier\n");
        (yyval.ast) = createNode(NodeType_SimpleID);
        char* varName = (yyvsp[0].sval);
        (yyval.ast)->data.simpleID.name = varName;
    }
#line 1948 "parser.tab.c"
    break;

  case 55: /* Expr: ID LBRACKET Expr RBRACKET  */
#line 614 "parser.y"
    {
        printf("PARSER: Recognized array access\n");
        (yyval.ast) = createNode(NodeType_ArrAccess);
        char* varName = strdup((yyvsp[-3].sval));
        (yyval.ast)->data.arrAccess.name = varName;
        (yyval.ast)->data.arrAccess.indexExpr = (yyvsp[-1].ast);
    }
#line 1960 "parser.tab.c"
    break;

  case 56: /* Expr: INT_NUMBER  */
#line 622 "parser.y"
    {
        printf("PARSER: Recognized int number\n");
        (yyval.ast) = createNode(NodeType_IntExpr);
        (yyval.ast)->data.intExpr.number = (yyvsp[0].intVal);
    }
#line 1970 "parser.tab.c"
    break;

  case 57: /* Expr: FLOAT_NUMBER  */
#line 628 "parser.y"
    {
        printf("PARSER: Recognized float number\n");
        (yyval.ast) = createNode(NodeType_FloatExpr);
        (yyval.ast)->data.floatExpr.number = (yyvsp[0].floatVal);
    }
#line 1980 "parser.tab.c"
    break;

  case 58: /* Expr: CHAR_VALUE  */
#line 633 "parser.y"
                 { 
        printf("PARSER: Recognized character\n");
        (yyval.ast) = createNode(NodeType_CharExpr);
        (yyval.ast)->data.charExpr.character = (yyvsp[0].charVal);
        // Set other fields as necessary
    }
#line 1991 "parser.tab.c"
    break;

  case 59: /* Expr: CONST_TRUE  */
#line 639 "parser.y"
                 {
        printf("PARSER: Recognized boolean constant\n");
        (yyval.ast) = createNode(NodeType_IntExpr);
        (yyval.ast)->data.intExpr.number = 1;    //Boolean stored as an integer (non-zero = true)
    }
#line 2001 "parser.tab.c"
    break;

  case 60: /* Expr: CONST_FALSE  */
#line 644 "parser.y"
                  {
        printf("PARSER: Recognized boolean constant\n");
        (yyval.ast) = createNode(NodeType_IntExpr);
        (yyval.ast)->data.intExpr.number = 0;    //Boolean stored as an integer (0 = false)
    }
#line 2011 "parser.tab.c"
    break;

  case 61: /* Expr: FuncCall  */
#line 650 "parser.y"
    {
        (yyval.ast) = (yyvsp[0].ast);
    }
#line 2019 "parser.tab.c"
    break;

  case 62: /* Expr: LPAREN Expr RPAREN  */
#line 654 "parser.y"
    {
        (yyval.ast) = (yyvsp[-1].ast);
    }
#line 2027 "parser.tab.c"
    break;

  case 63: /* FuncCall: ID LPAREN ArgList RPAREN  */
#line 661 "parser.y"
    {
        (yyval.ast) = createNode(NodeType_FuncCall);
        (yyval.ast)->data.funcCall.name = strdup((yyvsp[-3].sval));
        (yyval.ast)->data.funcCall.argList = (yyvsp[-1].ast);
    }
#line 2037 "parser.tab.c"
    break;

  case 64: /* ArgList: %empty  */
#line 670 "parser.y"
    {
        (yyval.ast) = NULL;
    }
#line 2045 "parser.tab.c"
    break;

  case 65: /* ArgList: Arg  */
#line 674 "parser.y"
    {
        (yyval.ast) = createNode(NodeType_ArgList);
        (yyval.ast)->data.argList.arg = (yyvsp[0].ast);
        (yyval.ast)->data.argList.next = NULL;
    }
#line 2055 "parser.tab.c"
    break;

  case 66: /* ArgList: Arg COMMA ArgList  */
#line 680 "parser.y"
    {
        (yyval.ast) = createNode(NodeType_ArgList);
        (yyval.ast)->data.argList.arg = (yyvsp[-2].ast);
        (yyval.ast)->data.argList.next = (yyvsp[0].ast);
    }
#line 2065 "parser.tab.c"
    break;

  case 67: /* Arg: Expr  */
#line 689 "parser.y"
    {
        (yyval.ast) = createNode(NodeType_Arg);
        (yyval.ast)->data.arg.expr = (yyvsp[0].ast);
    }
#line 2074 "parser.tab.c"
    break;

  case 68: /* ReturnStmt: RETURN  */
#line 697 "parser.y"
    {
        (yyval.ast) = createNode(NodeType_ReturnStmt);
        (yyval.ast)->data.returnStmt.returnExpr = NULL;
    }
#line 2083 "parser.tab.c"
    break;

  case 69: /* ReturnStmt: RETURN Expr  */
#line 702 "parser.y"
    {
        (yyval.ast) = createNode(NodeType_ReturnStmt);
        (yyval.ast)->data.returnStmt.returnExpr = (yyvsp[0].ast);
    }
#line 2092 "parser.tab.c"
    break;


#line 2096 "parser.tab.c"

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

#line 711 "parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Error: %s at (line %d:%d)\n", s, lines, chars);
}

int main(int argc, char **argv) {
    ++argv, --argc;  /* Skip over program name */
    if (argc > 0)
        yyin = fopen(argv[0], "r");
    else
        yyin = stdin;

        // Record start time
    clock_t start_time = clock();

    // Call the main compilation function
    /* compile(argv[1]); */

    // Initialize symbol table
    symTab = createSymbolTable(TABLE_SIZE);
    if (symTab == NULL) {
        // Handle error
        return EXIT_FAILURE;
    }

    int parseCode = yyparse();
    if (parseCode == 0)
    {
        // Successfully parsed
        printf("Parsing successful!\n");
        traverseAST(root, 0, drawVertical, false);
        // Print symbol table for debugging
        printSymbolTable(symTab);
        // Semantic analysis
        printf("\n=== SEMANTIC ANALYSIS ===\n\n");
        initSemantic(symTab);
        semanticAnalysis(root);
        printf("\n=== TAC GENERATION ===\n");
        printTACToFile("output/TAC.ir", tacHead);
        printFuncTACsToFile();

        // Code generation
        printf("\n=== CODE GENERATION ===\n");
        initCodeGenerator("output/output.asm");
        generateMIPS(tacHead, symTab);
        finalizeCodeGenerator("output/output.asm");

        freeAST(root);
        freeSymbolTable(symTab);

        // Record end time
        clock_t end_time = clock();

        // Calculate and display elapsed time
        double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("Compilation time: %.4f seconds\n", elapsed_time);
    }
    else
        printf("Parsing failed. (error code: %d)\n", parseCode);

    return 0;
}

