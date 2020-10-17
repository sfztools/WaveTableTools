#include "SeriesExpr.h"
#include "Random.h"
#include "SeriesExprGrammar.tab.h"
#include "SeriesExprGrammar.yy.h"
#include "SeriesExprGrammarExtra.h"
#include <iostream>
#include <cmath>
#include <cassert>

///
std::array<ExprPtr, 2> Expr::parse(const char *text)
{
    yyscan_t scanner;
    YY_BUFFER_STATE buffer;
    ParserResult result;

#if !defined(_WIN32)
    Locale c_locale(newlocale(LC_ALL_MASK, "C", (locale_t)0));
#else
    Locale c_locale(_create_locale(LC_ALL, "C"));
#endif
    if (!c_locale)
        throw std::system_error(errno, std::generic_category());

    if (yylex_init(&scanner) != 0)
        goto end1;

    SeriesExprGrammarExtra extra;
    extra.c_locale = *c_locale;
    yyset_extra(&extra, scanner);

#if YYDEBUG
    yydebug = 1;
    yyset_debug(1 , scanner);
#endif

    buffer = yy_scan_string(text, scanner);
    if (!buffer)
        goto end2;

    if (yyparse(scanner, &result) != 0)
        goto end3;

end3:
    yy_delete_buffer(buffer, scanner);
end2:
    yylex_destroy(scanner);
end1:
    return result.expr;
}

///
float VarX::evalInterpreted(ExprContext& ctx) const
{
    return ctx.x;
}

float Random::evalInterpreted(ExprContext& ctx) const
{
    assert(ctx.prng);
    return ctx.prng->next_float();
}

float Number::evalInterpreted(ExprContext& ctx) const
{
    return number;
}

float Add::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) + rhs->evalInterpreted(ctx);
}

float Sub::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) - rhs->evalInterpreted(ctx);
}

float Mul::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) * rhs->evalInterpreted(ctx);
}

float Div::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) / rhs->evalInterpreted(ctx);
}

float Mod::evalInterpreted(ExprContext& ctx) const
{
    return std::fmod(lhs->evalInterpreted(ctx), rhs->evalInterpreted(ctx));
}

float Pow::evalInterpreted(ExprContext& ctx) const
{
    return std::pow(lhs->evalInterpreted(ctx), rhs->evalInterpreted(ctx));
}

float Eq::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) == rhs->evalInterpreted(ctx);
}

float Neq::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) != rhs->evalInterpreted(ctx);
}

float Lt::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) < rhs->evalInterpreted(ctx);
}

float Gt::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) > rhs->evalInterpreted(ctx);
}

float Le::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) <= rhs->evalInterpreted(ctx);
}

float Ge::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) >= rhs->evalInterpreted(ctx);
}

float And::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) && rhs->evalInterpreted(ctx);
}

float Or::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) || rhs->evalInterpreted(ctx);
}

///
void VarX::repr(std::ostream &out) const
{
    out << 'x';
}

void Random::repr(std::ostream &out) const
{
    out << '#';
}

void Number::repr(std::ostream &out) const
{
    out << number;
}

void Binop::genericRepr(std::ostream &out, const char *sym) const
{
    out << '(' << *lhs << sym << *rhs << ')';
}

///
std::ostream &operator<<(std::ostream &out, const Expr &expr)
{
    expr.repr(out);
    return out;
}
