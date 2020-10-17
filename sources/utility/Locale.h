#pragma once
#include <clocale>

class Locale {
public:
#if !defined(_WIN32)
    typedef locale_t handle_type;
#else
    typedef _locale_t handle_type;
#endif

    explicit Locale(handle_type handle = (handle_type)0) noexcept;
    ~Locale() noexcept;
    explicit operator bool() const noexcept;
    handle_type operator*() const noexcept;

private:
    handle_type handle_ = (handle_type)0;
};

//------------------------------------------------------------------------------
inline Locale::Locale(handle_type handle) noexcept
    : handle_(handle)
{
}

inline Locale::~Locale() noexcept
{
#if !defined(_WIN32)
    if (*this) freelocale(handle_);
#else
    if (*this) _free_locale(handle_);
#endif
}

inline Locale::operator bool() const noexcept
{
    return handle_ != (handle_type)0;
}

inline Locale::handle_type Locale::operator*() const noexcept
{
    return handle_;
}
