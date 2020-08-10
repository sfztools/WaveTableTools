#include "Expr.h"
#include "Random.h"
#include "ExprGrammar.tab.h"
#include "ExprGrammar.yy.h"
#include <iostream>
#include <cmath>

///
ExprPtr Expr::parse(const char *text)
{
    yyscan_t scanner;
    YY_BUFFER_STATE buffer;
    ParserResult result;

    if (yylex_init(&scanner) != 0)
        goto end1;

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
float VarX::evalInterpreted(float x) const
{
    return x;
}

float Random::evalInterpreted(float x) const
{
    return random_next_float();
}

float Number::evalInterpreted(float x) const
{
    return number;
}

float Add::evalInterpreted(float x) const
{
    return lhs->evalInterpreted(x) + rhs->evalInterpreted(x);
}

float Sub::evalInterpreted(float x) const
{
    return lhs->evalInterpreted(x) - rhs->evalInterpreted(x);
}

float Mul::evalInterpreted(float x) const
{
    return lhs->evalInterpreted(x) * rhs->evalInterpreted(x);
}

float Div::evalInterpreted(float x) const
{
    return lhs->evalInterpreted(x) / rhs->evalInterpreted(x);
}

float Mod::evalInterpreted(float x) const
{
    return std::fmod(lhs->evalInterpreted(x), rhs->evalInterpreted(x));
}

float Pow::evalInterpreted(float x) const
{
    return std::pow(lhs->evalInterpreted(x), rhs->evalInterpreted(x));
}

float Eq::evalInterpreted(float x) const
{
    return lhs->evalInterpreted(x) == rhs->evalInterpreted(x);
}

float Neq::evalInterpreted(float x) const
{
    return lhs->evalInterpreted(x) != rhs->evalInterpreted(x);
}

float Lt::evalInterpreted(float x) const
{
    return lhs->evalInterpreted(x) < rhs->evalInterpreted(x);
}

float Gt::evalInterpreted(float x) const
{
    return lhs->evalInterpreted(x) > rhs->evalInterpreted(x);
}

float Le::evalInterpreted(float x) const
{
    return lhs->evalInterpreted(x) <= rhs->evalInterpreted(x);
}

float Ge::evalInterpreted(float x) const
{
    return lhs->evalInterpreted(x) >= rhs->evalInterpreted(x);
}

float And::evalInterpreted(float x) const
{
    return lhs->evalInterpreted(x) && rhs->evalInterpreted(x);
}

float Or::evalInterpreted(float x) const
{
    return lhs->evalInterpreted(x) || rhs->evalInterpreted(x);
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
