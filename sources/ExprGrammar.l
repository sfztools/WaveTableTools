%option noinput nounput noyywrap 8bit nodefault
%option yylineno
%option reentrant bison-bridge bison-locations
/* %option debug */

%{
  #include <stdlib.h>
  #include <string.h>
  #include "ExprGrammar.tab.h"
%}

%%

[ \t]+                ;
";"                   return SEMICOLON;
"#"                   return SHARP;
"("                   return OPEN;
")"                   return CLOSE;
"x"                   return VARX;
-?[0-9]+(\.[0-9]*)?   yylval->n = atof(yytext); return NUMBER;
"+"                   return PLUS;
"-"                   return MINUS;
"*"                   return TIMES;
"/"                   return DIVIDE;
"%"                   return MODULO;
"^"                   return POWER;
"="                   return EQUAL;
"!="                  return NOTEQUAL;
"<"                   return LT;
">"                   return GT;
"<="                  return LE;
">="                  return GE;
"||"                  return OR;
"&&"                  return AND;
<<EOF>>               return END;
.|\n                  return INVALID;
