/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
    TK_INT_TYPE = 258,
    TK_VOID_TYPE = 259,
    TK_LPAR = 260,
    TK_RPAR = 261,
    TK_COMMA = 262,
    TK_SEMI = 263,
    TK_LACC = 264,
    TK_RACC = 265,
    TK_GREATER = 266,
    TK_NEQ = 267,
    TK_EQ = 268,
    TK_PLUS = 269,
    TK_MINUS = 270,
    TK_MUL = 271,
    TK_PLUSPLUS = 272,
    TK_NUM = 273,
    TK_ID = 274,
    TK_CHAR = 275,
    TK_STRING = 276,
    TK_ASSIGN = 277,
    TK_IF = 278,
    TK_ELSE = 279,
    TK_WHILE = 280,
    TK_DO = 281,
    TK_FOR = 282,
    TK_RETURN = 283,
    TK_PRINT = 284,
    TK_INPUT = 285,
    TK_DIV = 286
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 39 "parser.ypp" /* yacc.c:1909  */

  int integer;
  char* id_string;

#line 91 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
