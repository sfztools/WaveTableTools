#pragma once
#include <vector>
#include <array>
#include <memory>
#include <string>
#include <unordered_map>
#include <iosfwd>
class RandomGenerator;

typedef double expr_float_t;

///
class Expr;
typedef std::shared_ptr<Expr> ExprPtr;

///
struct ExprContext {
    RandomGenerator* prng = nullptr;
    std::unordered_map<std::string, expr_float_t> vars;
};

///
class Expr : public std::enable_shared_from_this<Expr> {
public:
    enum class Type {
        Var,
        Call,
        Number,
        Random,
        Add,
        Sub,
        Mul,
        Div,
        Mod,
        Pow,
        Eq,
        Neq,
        Lt,
        Gt,
        Le,
        Ge,
        And,
        Or,
    };

protected:
    explicit Expr(Type t) : type(t) {}

public:
    virtual ~Expr() {}
    virtual void repr(std::ostream &out) const = 0;
    static std::array<ExprPtr, 2> parse(const char *text);
    virtual expr_float_t evalInterpreted(ExprContext& ctx) const = 0;
    Type type;
};

///
class Var : public Expr {
public:
    explicit Var(std::string id) : Expr(Type::Var), id(std::move(id)) {}
    void repr(std::ostream &out) const override;
    expr_float_t evalInterpreted(ExprContext& ctx) const override;
    std::string id;
};

///
class Call : public Expr {
public:
    Call(std::string id, std::vector<ExprPtr> args) : Expr(Type::Call), id(std::move(id)), args(std::move(args)) {}
    void repr(std::ostream &out) const override;
    expr_float_t evalInterpreted(ExprContext& ctx) const override;
    std::string id;
    std::vector<ExprPtr> args;
};

///
class Random : public Expr {
public:
    Random() : Expr(Type::Random) {}
    void repr(std::ostream &out) const override;
    expr_float_t evalInterpreted(ExprContext& ctx) const override;
};

///
class Number : public Expr {
public:
    explicit Number(double n) : Expr(Type::Number), number(n) {}
    void repr(std::ostream &out) const override;
    expr_float_t evalInterpreted(ExprContext& ctx) const override;
    double number;
};

///
class Binop : public Expr {
protected:
    Binop(Type t, ExprPtr lhs, ExprPtr rhs) : Expr(t), lhs(lhs), rhs(rhs) {}
    void genericRepr(std::ostream &out, const char *sym) const;

public:
    virtual ~Binop() {}
    ExprPtr lhs, rhs;
};

///
template <Expr::Type T> class BinopT : public Binop {
public:
    BinopT(ExprPtr lhs, ExprPtr rhs) : Binop(T, lhs, rhs) {}
    virtual ~BinopT() {}
};

///
#define DefBinop(id, sym)                                                      \
    class id : public BinopT<Expr::Type::id> {                                 \
    public:                                                                    \
        using BinopT::BinopT;                                                  \
        void repr(std::ostream &out) const override { genericRepr(out, sym); } \
        expr_float_t evalInterpreted(ExprContext& ctx) const override;         \
    }

DefBinop(Add, "+");
DefBinop(Sub, "-");
DefBinop(Mul, "*");
DefBinop(Div, "/");
DefBinop(Mod, "%");
DefBinop(Pow, "^");
DefBinop(Eq, "=");
DefBinop(Neq, "!=");
DefBinop(Lt, "<");
DefBinop(Gt, ">");
DefBinop(Le, "<=");
DefBinop(Ge, ">=");
DefBinop(And, "&&");
DefBinop(Or, "||");

///
std::ostream &operator<<(std::ostream &out, const Expr &expr);
