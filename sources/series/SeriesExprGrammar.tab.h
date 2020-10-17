/* A Bison parser, made by GNU Bison 3.7.2.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SERIESEXPRGRAMMAR_TAB_H_INCLUDED
# define YY_YY_SERIESEXPRGRAMMAR_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 11 "SeriesExprGrammar.y"

  #include "SeriesExpr.h"

  union sval {
      Expr *e;
      double n;
  };

  struct ParserResult {
      std::array<ExprPtr, 2> expr;
  };

  typedef void *yyscan_t;

#line 64 "SeriesExprGrammar.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    SHARP = 259,                   /* SHARP  */
    OPEN = 260,                    /* OPEN  */
    CLOSE = 261,                   /* CLOSE  */
    NUMBER = 262,                  /* NUMBER  */
    VARX = 263,                    /* VARX  */
    INVALID = 264,                 /* INVALID  */
    END = 265,                     /* END  */
    UNOP = 266,                    /* UNOP  */
    PLUS = 267,                    /* PLUS  */
    MINUS = 268,                   /* MINUS  */
    EQUAL = 269,                   /* EQUAL  */
    NOTEQUAL = 270,                /* NOTEQUAL  */
    LT = 271,                      /* LT  */
    GT = 272,                      /* GT  */
    LE = 273,                      /* LE  */
    GE = 274,                      /* GE  */
    TIMES = 275,                   /* TIMES  */
    DIVIDE = 276,                  /* DIVIDE  */
    MODULO = 277,                  /* MODULO  */
    AND = 278,                     /* AND  */
    OR = 279,                      /* OR  */
    POWER = 280                    /* POWER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union sval YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (yyscan_t scanner, ParserResult *parser_result);

#endif /* !YY_YY_SERIESEXPRGRAMMAR_TAB_H_INCLUDED  */
