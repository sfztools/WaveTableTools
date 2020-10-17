#pragma once
#include <vector>
#include <array>
#include <memory>
#include <iosfwd>
class RandomGenerator;

class Expr;
typedef std::shared_ptr<Expr> ExprPtr;

///
struct ExprContext {
    RandomGenerator* prng = nullptr;
    float x = 0;
};

///
class Expr : public std::enable_shared_from_this<Expr> {
public:
    enum class Type {
        VarX,
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
    virtual float evalInterpreted(ExprContext& ctx) const = 0;
    Type type;
};

///
class VarX : public Expr {
public:
    VarX() : Expr(Type::VarX) {}
    void repr(std::ostream &out) const override;
    float evalInterpreted(ExprContext& ctx) const override;
};

///
class Random : public Expr {
public:
    Random() : Expr(Type::Random) {}
    void repr(std::ostream &out) const override;
    float evalInterpreted(ExprContext& ctx) const override;
};

///
class Number : public Expr {
public:
    explicit Number(double n) : Expr(Type::Number), number(n) {}
    void repr(std::ostream &out) const override;
    float evalInterpreted(ExprContext& ctx) const override;
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
        float evalInterpreted(ExprContext& ctx) const override;                \
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
