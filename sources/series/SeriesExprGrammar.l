%top{
  #if defined(_WIN32)
     #define YY_NO_UNISTD_H 1
     #include <io.h>
  #endif

  #define FLEXINT_H 1
  #include <cstdint>
  typedef int8_t flex_int8_t;
  typedef uint8_t flex_uint8_t;
  typedef int16_t flex_int16_t;
  typedef uint16_t flex_uint16_t;
  typedef int32_t flex_int32_t;
  typedef uint32_t flex_uint32_t;
}

%option noinput nounput noyywrap 8bit nodefault
%option yylineno
%option reentrant bison-bridge bison-locations
%option extra-type="struct SeriesExprGrammarExtra *"
/* %option debug */

%{
  #include <stdlib.h>
  #include <string.h>
  #include "SeriesExprGrammar.tab.h"
  #include "SeriesExprGrammarExtra.h"

  static double to_number(const char *text, Locale::handle_type loc)
  {
    double number;
#if !defined(_WIN32)
    loc = uselocale(loc);
    number = atof(text);
    uselocale(loc);
#else
    return _atof_l(text, loc);
#endif
    return number;
  }
%}

DECIMAL [0-9]+
REAL ([0-9]+)?\.[0-9]*
EXPONENT [eE][-\+]?[0-9]+
NUMBER ({DECIMAL}{EXPONENT}?)|({REAL}{EXPONENT}?)

%%

[ \t\r\n]+            ;
";"                   return SEMICOLON;
"#"                   return SHARP;
"("                   return OPEN;
")"                   return CLOSE;
"x"                   return VARX;
{NUMBER}              yylval->n = to_number(yytext, yyextra->c_locale); return NUMBER;
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
