/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

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

    #include <iostream>
    #include <stdio.h>
    #include <stdlib.h>
    #include <cstdio>
    #include <string>
    #include <thlang/node.h>
    #include <thlang/codegen.h>
    extern int yylineno;
    int yylex();
    int findMapping(const char *type);
    void addMapping(const char *type, int token);
    void yyerror(thlang::NModule &root_program, thlang::CodeGenContext& context, const char *s) { 
        printf("Error: %s, lineno: %d\n", s, yylineno);
        exit(1); 
    }
    int nums;

#line 89 "parser.cpp"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOKEN_INT = 258,
    TOKEN_PLUS = 259,
    TOKEN_MINUS = 260,
    TOKEN_MUL = 261,
    TOKEN_DIV = 262,
    LPAREN = 263,
    RPAREN = 264,
    LBRACKET = 265,
    RBRACKET = 266,
    LBRACE = 267,
    RBRACE = 268,
    TOKEN_RETURN = 269,
    TOKEN_IF = 270,
    TOKEN_ELSE = 271,
    TOKEN_WHILE = 272,
    TOKEN_FOR = 273,
    TOKEN_EXTERN = 274,
    TOKEN_EQUAL = 275,
    TOKEN_CEQ = 276,
    TOKEN_NEL = 277,
    TOKEN_NLT = 278,
    TOKEN_NLE = 279,
    TOKEN_NGT = 280,
    TOKEN_NGE = 281,
    TOKEN_XOR = 282,
    TOKEN_MOD = 283,
    TOKEN_SHL = 284,
    TOKEN_SHR = 285,
    TOKEN_AND = 286,
    TOKEN_OR = 287,
    TOKEN_NOT = 288,
    TOKEN_COMMA = 289,
    TOKEN_SEMICOLON = 290,
    TOKEN_DOT = 291,
    TOKEN_NEWLINE = 292,
    TOKEN_ID = 293,
    NUM = 294,
    STRING = 295,
    FLOAT = 296,
    UMINUS = 297,
    UPLUS = 298,
    UFACT = 299
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "parser.y"

    std::string *string;
    std::string *str; 
    int token;
    thlang::Node *node;
    thlang::NBlock *block;
    thlang::ExprAst *expr;
    thlang::VarStmtAst *var_decl;
    thlang::Type *type;
    std::string *values;
    thlang::VarList* varvec;
    thlang::ExprList* exprvec;

#line 200 "parser.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (thlang::NModule &root_program, thlang::CodeGenContext &context);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  39
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   432

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  112

#define YYUNDEFTOK  2
#define YYMAXUTOK   299


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    65,    65,    70,    71,    73,    74,    75,    76,    78,
      79,    80,    81,    82,    83,    84,    86,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   119,   124,   131,   136,   140,   145,
     153,   156,   162,   163,   164,   167,   173,   180,   181,   182,
     185,   186,   189,   198
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_INT", "TOKEN_PLUS", "TOKEN_MINUS",
  "TOKEN_MUL", "TOKEN_DIV", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET",
  "LBRACE", "RBRACE", "TOKEN_RETURN", "TOKEN_IF", "TOKEN_ELSE",
  "TOKEN_WHILE", "TOKEN_FOR", "TOKEN_EXTERN", "TOKEN_EQUAL", "TOKEN_CEQ",
  "TOKEN_NEL", "TOKEN_NLT", "TOKEN_NLE", "TOKEN_NGT", "TOKEN_NGE",
  "TOKEN_XOR", "TOKEN_MOD", "TOKEN_SHL", "TOKEN_SHR", "TOKEN_AND",
  "TOKEN_OR", "TOKEN_NOT", "TOKEN_COMMA", "TOKEN_SEMICOLON", "TOKEN_DOT",
  "TOKEN_NEWLINE", "TOKEN_ID", "NUM", "STRING", "FLOAT", "UMINUS", "UPLUS",
  "UFACT", "$accept", "program", "block", "stmts", "stmt", "expr", "op",
  "assign", "for_stmt", "while_stmt", "if_stmt", "var_decl", "func_args",
  "func_decl", "call_args", "types", "type_id", "var_id", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299
};
# endif

#define YYPACT_NINF (-47)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-63)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     158,   -47,    68,    68,    68,    68,    -1,     8,     9,    10,
      68,    -8,   -47,   -47,   -47,    36,   119,   -47,   360,   -47,
     -47,   -47,   -47,   -47,   -47,     0,   -47,     7,   -47,   400,
     400,   244,   360,    68,    68,    68,   -47,     0,   400,   -47,
     158,   -47,    68,    68,    68,    68,   -47,   -47,   -47,   -47,
     -47,   -47,   -47,   -47,    68,   -47,   -47,   -47,   -47,    68,
      14,    68,    68,   -47,   273,   302,   180,    46,   -47,   387,
     387,   400,   400,   400,   360,    10,    68,   360,     3,   360,
      44,    44,    68,    10,   -47,    17,     0,   360,   -47,    68,
       6,    45,   -47,   212,    19,    44,    10,    43,   360,   -47,
      80,    50,    68,   -47,   -47,   -47,   -47,   -47,   -47,   331,
      44,   -47
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    60,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    63,    16,    17,    18,     0,     2,     8,    15,    19,
      11,    10,     9,    12,    13,     0,    61,    20,    63,    29,
      28,     0,    14,     0,     0,     0,    62,     0,    30,     1,
       6,     5,     0,     0,     0,     0,    32,    33,    34,    35,
      36,    37,    38,    39,     0,    40,    41,    42,    43,     0,
      50,    57,     0,    21,     0,     0,     0,     0,     7,    26,
      27,    24,    25,    23,    22,    52,     0,    58,     0,    44,
       0,     0,     0,    52,    53,     0,     0,    51,    31,     0,
       0,    47,    46,     0,     0,     0,     0,    50,    59,     4,
       0,     0,     0,    56,    55,    54,     3,    48,    49,     0,
       0,    45
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -47,   -47,   -46,   -24,   -11,    -2,   -47,   -47,   -47,   -47,
     -33,   -25,   -14,   -47,   -47,    -5,   -47,   -19
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    15,    91,    16,    17,    18,    59,    19,    20,    21,
      22,    23,    85,    24,    78,    25,    26,    27
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      29,    30,    31,    32,    37,    41,    60,    33,    38,     1,
       2,     3,    88,     1,     4,    61,    34,    35,    67,    99,
       5,     6,    75,     7,     8,     9,    95,    62,   103,    68,
     -62,    64,    65,    66,    76,    92,    39,    89,    28,    10,
      69,    70,    71,    72,    11,    12,    13,    14,    36,   104,
      84,    96,    73,    96,    83,   107,    90,    74,    84,    77,
      79,   101,    90,    76,   111,     6,   100,    97,   108,    94,
      86,   105,     2,     3,    87,     0,     4,     0,    86,     0,
      93,     0,     0,     1,     2,     3,     0,    98,     4,    41,
       0,    86,     0,   106,     5,     6,     0,     7,     8,     9,
     109,    10,     0,     0,     0,     0,    28,    12,    13,    14,
       0,     0,     0,    10,     0,    40,     0,     0,    11,    12,
      13,    14,     1,     2,     3,     0,     0,     4,     0,     0,
       0,     0,     0,     5,     6,     0,     7,     8,     9,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    10,     0,    40,     0,     0,    11,    12,    13,
      14,     1,     2,     3,     0,     0,     4,     0,     0,     0,
       0,     0,     5,     6,     0,     7,     8,     9,     0,     0,
       0,     0,     0,     0,    42,    43,    44,    45,     0,     0,
       0,    10,     0,     0,     0,     0,    11,    12,    13,    14,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,     0,     0,    82,    42,    43,    44,    45,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,     0,     0,   102,    42,    43,
      44,    45,     0,    63,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    42,    43,    44,
      45,     0,    80,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    42,    43,    44,    45,
       0,    81,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    42,    43,    44,    45,     0,
     110,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    42,    43,    44,    45,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    44,    45,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      46,    47,    48,    49,    50,    51,    52,    53,     0,    55,
      56,    57,    58
};

static const yytype_int8 yycheck[] =
{
       2,     3,     4,     5,     9,    16,    25,     8,    10,     3,
       4,     5,     9,     3,     8,     8,     8,     8,    37,    13,
      14,    15,     8,    17,    18,    19,     9,    20,     9,    40,
      38,    33,    34,    35,    20,    81,     0,    34,    38,    33,
      42,    43,    44,    45,    38,    39,    40,    41,    38,    95,
      75,    34,    54,    34,     8,   101,    12,    59,    83,    61,
      62,    16,    12,    20,   110,    15,    90,    86,   101,    83,
      75,    96,     4,     5,    76,    -1,     8,    -1,    83,    -1,
      82,    -1,    -1,     3,     4,     5,    -1,    89,     8,   100,
      -1,    96,    -1,    13,    14,    15,    -1,    17,    18,    19,
     102,    33,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      -1,    -1,    -1,    33,    -1,    35,    -1,    -1,    38,    39,
      40,    41,     3,     4,     5,    -1,    -1,     8,    -1,    -1,
      -1,    -1,    -1,    14,    15,    -1,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    -1,    35,    -1,    -1,    38,    39,    40,
      41,     3,     4,     5,    -1,    -1,     8,    -1,    -1,    -1,
      -1,    -1,    14,    15,    -1,    17,    18,    19,    -1,    -1,
      -1,    -1,    -1,    -1,     4,     5,     6,     7,    -1,    -1,
      -1,    33,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    -1,    35,     4,     5,     6,     7,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    -1,    35,     4,     5,
       6,     7,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,     4,     5,     6,
       7,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,     4,     5,     6,     7,
      -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,     4,     5,     6,     7,    -1,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,     6,     7,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      20,    21,    22,    23,    24,    25,    26,    27,    -1,    29,
      30,    31,    32
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     8,    14,    15,    17,    18,    19,
      33,    38,    39,    40,    41,    46,    48,    49,    50,    52,
      53,    54,    55,    56,    58,    60,    61,    62,    38,    50,
      50,    50,    50,     8,     8,     8,    38,    60,    50,     0,
      35,    49,     4,     5,     6,     7,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    51,
      62,     8,    20,     9,    50,    50,    50,    62,    49,    50,
      50,    50,    50,    50,    50,     8,    20,    50,    59,    50,
       9,     9,    35,     8,    56,    57,    60,    50,     9,    34,
      12,    47,    47,    50,    57,     9,    34,    62,    50,    13,
      48,    16,    35,     9,    47,    56,    13,    47,    55,    50,
       9,    47
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    48,    48,    49,
      49,    49,    49,    49,    49,    49,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    52,    53,    54,    55,    55,    55,
      56,    56,    57,    57,    57,    58,    58,    59,    59,    59,
      60,    60,    61,    62
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     3,     2,     2,     2,     3,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     9,     5,     5,     7,     7,
       2,     4,     0,     1,     3,     6,     6,     0,     1,     3,
       1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

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
        yyerror (root_program, context, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, root_program, context); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, thlang::NModule &root_program, thlang::CodeGenContext &context)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (root_program);
  YYUSE (context);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, thlang::NModule &root_program, thlang::CodeGenContext &context)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, root_program, context);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule, thlang::NModule &root_program, thlang::CodeGenContext &context)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              , root_program, context);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, root_program, context); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
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
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
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
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
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
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, thlang::NModule &root_program, thlang::CodeGenContext &context)
{
  YYUSE (yyvaluep);
  YYUSE (root_program);
  YYUSE (context);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (thlang::NModule &root_program, thlang::CodeGenContext &context)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 2:
#line 65 "parser.y"
                {
    root_program = thlang::NModule();
    root_program.block = std::unique_ptr<thlang::Node>((yyvsp[0].block));
}
#line 1525 "parser.cpp"
    break;

  case 3:
#line 70 "parser.y"
                            { (yyval.block) = (yyvsp[-1].block); }
#line 1531 "parser.cpp"
    break;

  case 4:
#line 71 "parser.y"
                     { (yyval.block) = new thlang::NBlock(); }
#line 1537 "parser.cpp"
    break;

  case 5:
#line 73 "parser.y"
                   { (yyvsp[-1].block)->stmts->push_back(std::unique_ptr<thlang::Node>((yyvsp[0].node))); (yyval.block) = (yyvsp[-1].block); }
#line 1543 "parser.cpp"
    break;

  case 6:
#line 74 "parser.y"
                             { (yyval.block) = (yyvsp[-1].block); }
#line 1549 "parser.cpp"
    break;

  case 7:
#line 75 "parser.y"
                                  { (yyvsp[-2].block)->stmts->push_back(std::unique_ptr<thlang::Node>((yyvsp[0].node))); (yyval.block) = (yyvsp[-2].block); }
#line 1555 "parser.cpp"
    break;

  case 8:
#line 76 "parser.y"
            { auto ast = new thlang::NBlock(); ast->stmts->push_back(std::unique_ptr<thlang::Node>((yyvsp[0].node))); (yyval.block) = ast; }
#line 1561 "parser.cpp"
    break;

  case 9:
#line 78 "parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 1567 "parser.cpp"
    break;

  case 10:
#line 79 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1573 "parser.cpp"
    break;

  case 11:
#line 80 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1579 "parser.cpp"
    break;

  case 12:
#line 81 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1585 "parser.cpp"
    break;

  case 13:
#line 82 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1591 "parser.cpp"
    break;

  case 14:
#line 83 "parser.y"
                         { (yyval.node) = new thlang::ReturnStmtAst(std::unique_ptr<thlang::Node>((yyvsp[0].node))); }
#line 1597 "parser.cpp"
    break;

  case 15:
#line 84 "parser.y"
            { (yyval.node) = new thlang::ExprStmtAst(std::move(std::unique_ptr<thlang::Node>((yyvsp[0].node)))); }
#line 1603 "parser.cpp"
    break;

  case 16:
#line 86 "parser.y"
           {
    (yyval.node) = new thlang::IntAst(std::atol((yyvsp[0].string)->c_str()));
    delete (yyvsp[0].string);
    }
#line 1612 "parser.cpp"
    break;

  case 17:
#line 90 "parser.y"
             { (yyval.node) = new thlang::StringAst(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1618 "parser.cpp"
    break;

  case 18:
#line 91 "parser.y"
            { (yyval.node) = new thlang::FloatAst(std::stod((yyvsp[0].string)->c_str())); delete (yyvsp[0].string); }
#line 1624 "parser.cpp"
    break;

  case 19:
#line 92 "parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 1630 "parser.cpp"
    break;

  case 20:
#line 93 "parser.y"
             { (yyval.node) = (yyvsp[0].expr); }
#line 1636 "parser.cpp"
    break;

  case 21:
#line 94 "parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 1642 "parser.cpp"
    break;

  case 22:
#line 95 "parser.y"
                   { (yyval.node) = new thlang::BinOpAst(*(yyvsp[-1].str), std::unique_ptr<thlang::Node>((yyvsp[-2].node)), std::unique_ptr<thlang::Node>((yyvsp[0].node))); delete (yyvsp[-1].str); }
#line 1648 "parser.cpp"
    break;

  case 23:
#line 96 "parser.y"
                          { (yyval.node) = new thlang::BinOpAst("%", std::unique_ptr<thlang::Node>((yyvsp[-2].node)), std::unique_ptr<thlang::Node>((yyvsp[0].node))); }
#line 1654 "parser.cpp"
    break;

  case 24:
#line 97 "parser.y"
                          { (yyval.node) = new thlang::BinOpAst("*", std::unique_ptr<thlang::Node>((yyvsp[-2].node)), std::unique_ptr<thlang::Node>((yyvsp[0].node))); }
#line 1660 "parser.cpp"
    break;

  case 25:
#line 98 "parser.y"
                          { (yyval.node) = new thlang::BinOpAst("/", std::unique_ptr<thlang::Node>((yyvsp[-2].node)), std::unique_ptr<thlang::Node>((yyvsp[0].node))); }
#line 1666 "parser.cpp"
    break;

  case 26:
#line 99 "parser.y"
                           { (yyval.node) = new thlang::BinOpAst("+", std::unique_ptr<thlang::Node>((yyvsp[-2].node)), std::unique_ptr<thlang::Node>((yyvsp[0].node))); }
#line 1672 "parser.cpp"
    break;

  case 27:
#line 100 "parser.y"
                            { (yyval.node) = new thlang::BinOpAst("-", std::unique_ptr<thlang::Node>((yyvsp[-2].node)), std::unique_ptr<thlang::Node>((yyvsp[0].node))); }
#line 1678 "parser.cpp"
    break;

  case 28:
#line 101 "parser.y"
                                    { (yyval.node) = new thlang::UnOpAst("-", std::unique_ptr<thlang::Node>((yyvsp[0].node))); }
#line 1684 "parser.cpp"
    break;

  case 29:
#line 102 "parser.y"
                                  { (yyval.node) = new thlang::UnOpAst("+", std::unique_ptr<thlang::Node>((yyvsp[0].node))); }
#line 1690 "parser.cpp"
    break;

  case 30:
#line 103 "parser.y"
                                 { (yyval.node) = new thlang::UnOpAst("!", std::unique_ptr<thlang::Node>((yyvsp[0].node))); }
#line 1696 "parser.cpp"
    break;

  case 31:
#line 104 "parser.y"
                                     { (yyval.node) = new thlang::CallExprAst(std::unique_ptr<thlang::ExprAst>((yyvsp[-3].expr)), std::unique_ptr<thlang::ExprList>((yyvsp[-1].exprvec))); }
#line 1702 "parser.cpp"
    break;

  case 32:
#line 106 "parser.y"
                 { (yyval.str) = new std::string("="); }
#line 1708 "parser.cpp"
    break;

  case 33:
#line 107 "parser.y"
                 { (yyval.str) = new std::string("=="); }
#line 1714 "parser.cpp"
    break;

  case 34:
#line 108 "parser.y"
                 { (yyval.str) = new std::string("!="); }
#line 1720 "parser.cpp"
    break;

  case 35:
#line 109 "parser.y"
                 { (yyval.str) = new std::string("<"); }
#line 1726 "parser.cpp"
    break;

  case 36:
#line 110 "parser.y"
                 { (yyval.str) = new std::string("<="); }
#line 1732 "parser.cpp"
    break;

  case 37:
#line 111 "parser.y"
                 { (yyval.str) = new std::string(">"); }
#line 1738 "parser.cpp"
    break;

  case 38:
#line 112 "parser.y"
                 { (yyval.str) = new std::string(">="); }
#line 1744 "parser.cpp"
    break;

  case 39:
#line 113 "parser.y"
                 { (yyval.str) = new std::string("^"); }
#line 1750 "parser.cpp"
    break;

  case 40:
#line 114 "parser.y"
                 { (yyval.str) = new std::string("<<"); }
#line 1756 "parser.cpp"
    break;

  case 41:
#line 115 "parser.y"
                 { (yyval.str) = new std::string(">>"); }
#line 1762 "parser.cpp"
    break;

  case 42:
#line 116 "parser.y"
                 { (yyval.str) = new std::string("&&"); }
#line 1768 "parser.cpp"
    break;

  case 43:
#line 117 "parser.y"
                 { (yyval.str) = new std::string("||"); }
#line 1774 "parser.cpp"
    break;

  case 44:
#line 119 "parser.y"
                                 { 
    (yyval.node) = new thlang::AssignAst(std::unique_ptr<thlang::ExprAst>((yyvsp[-2].expr)), 
                              std::move(std::unique_ptr<thlang::Node>((yyvsp[0].node)))); 
}
#line 1783 "parser.cpp"
    break;

  case 45:
#line 124 "parser.y"
                                                                                        { 
    (yyval.node) = new thlang::ForStmtAst(std::unique_ptr<thlang::Node>((yyvsp[-6].node)), 
                               std::unique_ptr<thlang::Node>((yyvsp[-4].node)), 
                               std::unique_ptr<thlang::Node>((yyvsp[-2].node)), 
                               std::unique_ptr<thlang::Node>((yyvsp[0].block))); 
}
#line 1794 "parser.cpp"
    break;

  case 46:
#line 131 "parser.y"
                                                  { 
    (yyval.node) = new thlang::WhileStmtAst(std::unique_ptr<thlang::Node>((yyvsp[-2].node)), 
                                 std::unique_ptr<thlang::Node>((yyvsp[0].block))); 
}
#line 1803 "parser.cpp"
    break;

  case 47:
#line 136 "parser.y"
                                            { 
    (yyval.node) = new thlang::IfStmtAst(std::unique_ptr<thlang::Node>((yyvsp[-2].node)), 
                              std::unique_ptr<thlang::Node>((yyvsp[0].block))); 
}
#line 1812 "parser.cpp"
    break;

  case 48:
#line 140 "parser.y"
                                                         { 
        (yyval.node) = new thlang::IfStmtAst(std::unique_ptr<thlang::Node>((yyvsp[-4].node)), 
                                  std::unique_ptr<thlang::Node>((yyvsp[-2].block)), 
                                  std::unique_ptr<thlang::Node>((yyvsp[0].block))); 
    }
#line 1822 "parser.cpp"
    break;

  case 49:
#line 145 "parser.y"
                                                           { 
        auto blk = new thlang::NBlock(); 
        blk->stmts->push_back(std::unique_ptr<thlang::Node>((yyvsp[0].node))); 
        (yyval.node) = new thlang::IfStmtAst(std::unique_ptr<thlang::Node>((yyvsp[-4].node)), 
                                  std::unique_ptr<thlang::Node>((yyvsp[-2].block)), 
                                  std::unique_ptr<thlang::Node>(blk)); 
    }
#line 1834 "parser.cpp"
    break;

  case 50:
#line 153 "parser.y"
                        { 
    (yyval.node) = new thlang::VarStmtAst((yyvsp[-1].type), std::unique_ptr<thlang::ExprAst>((yyvsp[0].expr))); 
}
#line 1842 "parser.cpp"
    break;

  case 51:
#line 156 "parser.y"
                                    {
        (yyval.node) = new thlang::VarStmtAst((yyvsp[-3].type), 
                                   std::unique_ptr<thlang::Node>((yyvsp[-2].expr)), 
                                   std::unique_ptr<thlang::Node>((yyvsp[0].node))); 
    }
#line 1852 "parser.cpp"
    break;

  case 52:
#line 162 "parser.y"
                               { (yyval.varvec) = new thlang::VarList(); }
#line 1858 "parser.cpp"
    break;

  case 53:
#line 163 "parser.y"
               { (yyval.varvec) = new thlang::VarList(); (yyval.varvec)->push_back(std::unique_ptr<thlang::VarStmtAst>((yyvsp[0].var_decl))); }
#line 1864 "parser.cpp"
    break;

  case 54:
#line 164 "parser.y"
                                     { (yyvsp[-2].varvec)->push_back(std::unique_ptr<thlang::VarStmtAst>((yyvsp[0].var_decl))); }
#line 1870 "parser.cpp"
    break;

  case 55:
#line 167 "parser.y"
                                                       { 
    (yyval.node) = new thlang::FunctionStmtAst((yyvsp[-5].type), 
                                    std::unique_ptr<thlang::ExprAst>((yyvsp[-4].expr)), 
                                    std::unique_ptr<thlang::VarList>((yyvsp[-2].varvec)), 
                                    std::unique_ptr<thlang::Node>((yyvsp[0].block))); 
    }
#line 1881 "parser.cpp"
    break;

  case 56:
#line 173 "parser.y"
                                                        {
        (yyval.node) = new thlang::FunctionStmtAst((yyvsp[-4].type), 
                                    std::unique_ptr<thlang::ExprAst>((yyvsp[-3].expr)), 
                                    std::unique_ptr<thlang::VarList>((yyvsp[-1].varvec)), 
                                    nullptr, true); 
    }
#line 1892 "parser.cpp"
    break;

  case 57:
#line 180 "parser.y"
                                  { (yyval.exprvec) = new thlang::ExprList(); }
#line 1898 "parser.cpp"
    break;

  case 58:
#line 181 "parser.y"
           { (yyval.exprvec) = new thlang::ExprList(); (yyval.exprvec)->push_back(std::unique_ptr<thlang::ExprAst>((yyvsp[0].expr))); }
#line 1904 "parser.cpp"
    break;

  case 59:
#line 182 "parser.y"
                                 { (yyvsp[-2].exprvec)->push_back(std::unique_ptr<thlang::ExprAst>((yyvsp[0].expr))); }
#line 1910 "parser.cpp"
    break;

  case 60:
#line 185 "parser.y"
                  { (yyval.type) = context.typeSystem.get_type("整数型"); }
#line 1916 "parser.cpp"
    break;

  case 61:
#line 186 "parser.y"
              { (yyval.type) = (yyvsp[0].type); }
#line 1922 "parser.cpp"
    break;

  case 62:
#line 189 "parser.y"
                   { 
    thlang::Type* t = context.typeSystem.get_type(*(yyvsp[0].string)) ;
    if (t == context.typeSystem.get_type("空类型")) {
        LogError("未知的数据类型" +  *(yyvsp[0].string));
    }
    (yyval.type) = t;
    delete (yyvsp[0].string);
}
#line 1935 "parser.cpp"
    break;

  case 63:
#line 198 "parser.y"
                  { 
    (yyval.expr) = new thlang::NameAst(*(yyvsp[0].string));
    delete (yyvsp[0].string);
}
#line 1944 "parser.cpp"
    break;


#line 1948 "parser.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (root_program, context, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (root_program, context, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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
                      yytoken, &yylval, root_program, context);
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp, root_program, context);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (root_program, context, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, root_program, context);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, root_program, context);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 203 "parser.y"
