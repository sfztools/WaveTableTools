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

%%

[ \t]+                ;
";"                   return SEMICOLON;
"#"                   return SHARP;
"("                   return OPEN;
")"                   return CLOSE;
"x"                   return VARX;
[0-9]+(\.[0-9]*)?     yylval->n = to_number(yytext, yyextra->c_locale); return NUMBER;
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
