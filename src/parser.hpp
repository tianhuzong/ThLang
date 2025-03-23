/* A Bison parser, made by GNU Bison 3.8.2.  */

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

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_INT = 258,               /* TOKEN_INT  */
    TOKEN_FLOAT = 259,             /* TOKEN_FLOAT  */
    TOKEN_PLUS = 260,              /* TOKEN_PLUS  */
    TOKEN_MINUS = 261,             /* TOKEN_MINUS  */
    TOKEN_MUL = 262,               /* TOKEN_MUL  */
    TOKEN_DIV = 263,               /* TOKEN_DIV  */
    LPAREN = 264,                  /* LPAREN  */
    RPAREN = 265,                  /* RPAREN  */
    LBRACKET = 266,                /* LBRACKET  */
    RBRACKET = 267,                /* RBRACKET  */
    LBRACE = 268,                  /* LBRACE  */
    RBRACE = 269,                  /* RBRACE  */
    TOKEN_RETURN = 270,            /* TOKEN_RETURN  */
    TOKEN_IF = 271,                /* TOKEN_IF  */
    TOKEN_ELSE = 272,              /* TOKEN_ELSE  */
    TOKEN_WHILE = 273,             /* TOKEN_WHILE  */
    TOKEN_FOR = 274,               /* TOKEN_FOR  */
    TOKEN_EXTERN = 275,            /* TOKEN_EXTERN  */
    TOKEN_EQUAL = 276,             /* TOKEN_EQUAL  */
    TOKEN_CEQ = 277,               /* TOKEN_CEQ  */
    TOKEN_NEL = 278,               /* TOKEN_NEL  */
    TOKEN_NLT = 279,               /* TOKEN_NLT  */
    TOKEN_NLE = 280,               /* TOKEN_NLE  */
    TOKEN_NGT = 281,               /* TOKEN_NGT  */
    TOKEN_NGE = 282,               /* TOKEN_NGE  */
    TOKEN_XOR = 283,               /* TOKEN_XOR  */
    TOKEN_MOD = 284,               /* TOKEN_MOD  */
    TOKEN_SHL = 285,               /* TOKEN_SHL  */
    TOKEN_SHR = 286,               /* TOKEN_SHR  */
    TOKEN_AND = 287,               /* TOKEN_AND  */
    TOKEN_OR = 288,                /* TOKEN_OR  */
    TOKEN_NOT = 289,               /* TOKEN_NOT  */
    TOKEN_COMMA = 290,             /* TOKEN_COMMA  */
    TOKEN_SEMICOLON = 291,         /* TOKEN_SEMICOLON  */
    TOKEN_DOT = 292,               /* TOKEN_DOT  */
    TOKEN_NEWLINE = 293,           /* TOKEN_NEWLINE  */
    TOKEN_ID = 294,                /* TOKEN_ID  */
    NUM = 295,                     /* NUM  */
    TOKEN_STRING = 296,            /* TOKEN_STRING  */
    UMINUS = 297,                  /* UMINUS  */
    UPLUS = 298,                   /* UPLUS  */
    UFACT = 299                    /* UFACT  */
  };
  typedef enum yytokentype yytoken_kind_t;
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
    thlang::ExprAst *stmt;
    thlang::Type *type;
    std::string *values;

#line 119 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (thlang::NModule &root_program, thlang::CodeGenContext &context);


#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
