%define api.pure full
%define api.value.type {union sval}
%locations
%param { yyscan_t scanner }
%parse-param { ParserResult *parser_result }

%code top {
  #include <stdio.h>
}

%code requires {
  #include "SeriesExpr.h"
  #include <string>

  typedef std::vector<ExprPtr> ArgList;
  typedef std::unique_ptr<ArgList> ArgListPtr;

  union sval {
      Expr *e;
      double n;
      std::string *s;
      ArgList *a;
  };

  struct ParserResult {
      std::array<ExprPtr, 2> expr;
  };

  typedef void *yyscan_t;
}

%code {
  int yylex(YYSTYPE *yylvalp, YYLTYPE *yyllocp, yyscan_t scanner);
  void yyerror(YYLTYPE *yyllocp, yyscan_t unused, ParserResult *parser_result, const char *msg);

  static ExprPtr takeExpr(sval &sv)
  {
      ExprPtr e(sv.e);
      sv.e = nullptr;
      return e;
  }

  static std::string takeString(sval &sv)
  {
      std::string s = std::move(*sv.s);
      delete sv.s;
      sv.s = nullptr;
      return s;
  }

  static ArgListPtr takeArgListPtr(sval &sv)
  {
      ArgListPtr a(sv.a);
      sv.a = nullptr;
      return a;
  }

  static ArgList takeArgList(sval &sv)
  {
      ArgList a = std::move(*sv.a);
      sv.a = nullptr;
      return a;
  }
}

%destructor { delete $$.e; } expr
%destructor { delete $$.a; } maybe_args args_rest
%destructor { delete $$.s; } IDENTIFIER

%token SEMICOLON SHARP OPEN CLOSE COMMA NUMBER IDENTIFIER INVALID END UNOP
%left PLUS MINUS
%nonassoc EQUAL NOTEQUAL LT GT LE GE
%left TIMES DIVIDE MODULO
%left AND OR
%left POWER
%precedence UNOP

%%

input: expr input2exp END    { parser_result->expr[0].reset($1.e); $1.e = nullptr; }
input2exp: SEMICOLON expr    { parser_result->expr[1].reset($2.e); $2.e = nullptr; }
         | %empty            { }

expr : NUMBER                { $$.e = new Number($1.n); }
     | IDENTIFIER maybe_args { if (!$2.a) $$.e = new Var(takeString($1));
                               else $$.e = new Call(takeString($1), takeArgList($2)); }
     | SHARP                 { $$.e = new Random; }
     | OPEN expr CLOSE       { $$.e = $2.e; $2.e = nullptr; }
     | PLUS expr %prec UNOP  { $$.e = $2.e; $2.e = nullptr; }
     | MINUS expr %prec UNOP { $$.e = new Sub(ExprPtr(new Number(0)), takeExpr($2)); }
     | expr PLUS expr        { $$.e = new Add(takeExpr($1), takeExpr($3)); }
     | expr MINUS expr       { $$.e = new Sub(takeExpr($1), takeExpr($3)); }
     | expr TIMES expr       { $$.e = new Mul(takeExpr($1), takeExpr($3)); }
     | expr DIVIDE expr      { $$.e = new Div(takeExpr($1), takeExpr($3)); }
     | expr MODULO expr      { $$.e = new Mod(takeExpr($1), takeExpr($3)); }
     | expr POWER expr       { $$.e = new Pow(takeExpr($1), takeExpr($3)); }
     | expr EQUAL expr       { $$.e = new Eq(takeExpr($1), takeExpr($3)); }
     | expr NOTEQUAL expr    { $$.e = new Neq(takeExpr($1), takeExpr($3)); }
     | expr LT expr          { $$.e = new Lt(takeExpr($1), takeExpr($3)); }
     | expr GT expr          { $$.e = new Gt(takeExpr($1), takeExpr($3)); }
     | expr LE expr          { $$.e = new Le(takeExpr($1), takeExpr($3)); }
     | expr GE expr          { $$.e = new Ge(takeExpr($1), takeExpr($3)); }
     | expr AND expr         { $$.e = new And(takeExpr($1), takeExpr($3)); }
     | expr OR expr          { $$.e = new Or(takeExpr($1), takeExpr($3)); }

maybe_args : OPEN CLOSE { $$.a = new ArgList; }
           | OPEN expr args_rest { $$.a = takeArgListPtr($3).release();
                                   $$.a->insert($$.a->begin(), takeExpr($2)); }
           | %empty { $$.a = nullptr; }

args_rest : CLOSE { $$.a = new ArgList; }
          | COMMA expr args_rest { $$.a = takeArgListPtr($3).release();
                                   $$.a->insert($$.a->begin(), takeExpr($2)); }

%%

void yyerror(YYLTYPE *yyllocp, yyscan_t unused, ParserResult *parser_result, const char *msg)
{
    //fprintf(stderr, "[%d:%d]: %s\n", yyllocp->first_line, yyllocp->first_column, msg);
}
