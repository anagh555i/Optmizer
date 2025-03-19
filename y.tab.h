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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    PLUS = 258,                    /* PLUS  */
    MINUS = 259,                   /* MINUS  */
    MUL = 260,                     /* MUL  */
    DIV = 261,                     /* DIV  */
    PBEGIN = 262,                  /* PBEGIN  */
    END = 263,                     /* END  */
    READ = 264,                    /* READ  */
    WRITE = 265,                   /* WRITE  */
    IF = 266,                      /* IF  */
    ELSE = 267,                    /* ELSE  */
    THEN = 268,                    /* THEN  */
    ENDIF = 269,                   /* ENDIF  */
    ENDWHILE = 270,                /* ENDWHILE  */
    WHILE = 271,                   /* WHILE  */
    OR = 272,                      /* OR  */
    AND = 273,                     /* AND  */
    LT = 274,                      /* LT  */
    GT = 275,                      /* GT  */
    LTE = 276,                     /* LTE  */
    GTE = 277,                     /* GTE  */
    EQUALS = 278,                  /* EQUALS  */
    NOTEQUALS = 279,               /* NOTEQUALS  */
    DO = 280,                      /* DO  */
    BREAK = 281,                   /* BREAK  */
    CONTINUE = 282,                /* CONTINUE  */
    DECL = 283,                    /* DECL  */
    ENDDECL = 284,                 /* ENDDECL  */
    INT = 285,                     /* INT  */
    STR = 286,                     /* STR  */
    NUM = 287,                     /* NUM  */
    ID = 288,                      /* ID  */
    STRING = 289                   /* STRING  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define PLUS 258
#define MINUS 259
#define MUL 260
#define DIV 261
#define PBEGIN 262
#define END 263
#define READ 264
#define WRITE 265
#define IF 266
#define ELSE 267
#define THEN 268
#define ENDIF 269
#define ENDWHILE 270
#define WHILE 271
#define OR 272
#define AND 273
#define LT 274
#define GT 275
#define LTE 276
#define GTE 277
#define EQUALS 278
#define NOTEQUALS 279
#define DO 280
#define BREAK 281
#define CONTINUE 282
#define DECL 283
#define ENDDECL 284
#define INT 285
#define STR 286
#define NUM 287
#define ID 288
#define STRING 289

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 13 "parser.y"

 struct TokenAttr* ToAttr;
 int integer;

#line 140 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
