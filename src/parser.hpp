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
    TOKEN_FLOAT = 259,
    TOKEN_PLUS = 260,
    TOKEN_MINUS = 261,
    TOKEN_MUL = 262,
    TOKEN_DIV = 263,
    LPAREN = 264,
    RPAREN = 265,
    LBRACKET = 266,
    RBRACKET = 267,
    LBRACE = 268,
    RBRACE = 269,
    TOKEN_RETURN = 270,
    TOKEN_IF = 271,
    TOKEN_ELSE = 272,
    TOKEN_WHILE = 273,
    TOKEN_FOR = 274,
    TOKEN_EXTERN = 275,
    TOKEN_EQUAL = 276,
    TOKEN_CEQ = 277,
    TOKEN_NEL = 278,
    TOKEN_NLT = 279,
    TOKEN_NLE = 280,
    TOKEN_NGT = 281,
    TOKEN_NGE = 282,
    TOKEN_XOR = 283,
    TOKEN_MOD = 284,
    TOKEN_SHL = 285,
    TOKEN_SHR = 286,
    TOKEN_AND = 287,
    TOKEN_OR = 288,
    TOKEN_NOT = 289,
    TOKEN_COMMA = 290,
    TOKEN_SEMICOLON = 291,
    TOKEN_DOT = 292,
    TOKEN_NEWLINE = 293,
    TOKEN_ID = 294,
    NUM = 295,
    TOKEN_STRING = 296,
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
    thlang::ExprAst *stmt;
    thlang::Type *type;
    std::string *values;

#line 113 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (thlang::NModule &root_program, thlang::CodeGenContext &context);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
