#include "SeriesExpr.h"
#include "Random.h"
#include "SeriesExprGrammar.tab.h"
#include "SeriesExprGrammar.yy.h"
#include "SeriesExprGrammarExtra.h"
#include <iostream>
#include <cmath>
#include <cassert>

bool ExprFunctionId::operator==(const ExprFunctionId &other) const
{
    return name == other.name && arity == other.arity;
}

bool ExprFunctionId::operator!=(const ExprFunctionId &other) const
{
    return !operator==(other);
}

size_t std::hash<ExprFunctionId>::operator()(const ExprFunctionId& id) const noexcept
{
    return std::hash<std::string>()(id.name) ^ std::hash<size_t>()(id.arity);
}

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
expr_float_t Var::evalInterpreted(ExprContext& ctx) const
{
    auto it = ctx.vars.find(id);
    if (it == ctx.vars.end())
        return 0; // inexistent variable
    return it->second;
}

expr_float_t Call::evalInterpreted(ExprContext& ctx) const
{
    auto it = ctx.funcs.find(id);
    if (it == ctx.funcs.end())
        return 0; // inexistent function

    size_t arity = id.arity;
    std::unique_ptr<expr_float_t[]> values(new expr_float_t[arity]);

    for (size_t i = 0; i < arity; ++i)
        values[i] = args[i]->evalInterpreted(ctx);

    return it->second(values.get());
}

expr_float_t Random::evalInterpreted(ExprContext& ctx) const
{
    assert(ctx.prng);
    return ctx.prng->next_float();
}

expr_float_t Number::evalInterpreted(ExprContext& ctx) const
{
    return static_cast<expr_float_t>(number);
}

expr_float_t Add::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) + rhs->evalInterpreted(ctx);
}

expr_float_t Sub::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) - rhs->evalInterpreted(ctx);
}

expr_float_t Mul::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) * rhs->evalInterpreted(ctx);
}

expr_float_t Div::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) / rhs->evalInterpreted(ctx);
}

expr_float_t Mod::evalInterpreted(ExprContext& ctx) const
{
    return std::fmod(lhs->evalInterpreted(ctx), rhs->evalInterpreted(ctx));
}

expr_float_t Pow::evalInterpreted(ExprContext& ctx) const
{
    return std::pow(lhs->evalInterpreted(ctx), rhs->evalInterpreted(ctx));
}

expr_float_t Eq::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) == rhs->evalInterpreted(ctx);
}

expr_float_t Neq::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) != rhs->evalInterpreted(ctx);
}

expr_float_t Lt::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) < rhs->evalInterpreted(ctx);
}

expr_float_t Gt::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) > rhs->evalInterpreted(ctx);
}

expr_float_t Le::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) <= rhs->evalInterpreted(ctx);
}

expr_float_t Ge::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) >= rhs->evalInterpreted(ctx);
}

expr_float_t And::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) && rhs->evalInterpreted(ctx);
}

expr_float_t Or::evalInterpreted(ExprContext& ctx) const
{
    return lhs->evalInterpreted(ctx) || rhs->evalInterpreted(ctx);
}

///
void Var::repr(std::ostream &out) const
{
    out << id;
}

void Call::repr(std::ostream &out) const
{
    out << id.name << '(';
    for (size_t i = 0, n = args.size(); i < n; ++i) {
        if (i > 0)
            out << ", ";
        out << *args[i];
    }
    out << ')';
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
