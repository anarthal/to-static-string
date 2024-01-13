//
// Copyright (c) 2023 Ruben Perez Hidalgo (rubenperez038 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef TO_STATIC_STRING_H
#define TO_STATIC_STRING_H

#include <cassert>
#include <charconv>
#include <cstddef>
#include <limits>
#include <string_view>
#include <system_error>
#include <type_traits>

// Config
#ifdef __cpp_lib_constexpr_charconv
#define TO_STATIC_STRING_CXX23_CONSTEXPR constexpr
#else
#define TO_STATIC_STRING_CXX23_CONSTEXPR constexpr
#endif

namespace tostr {

// Fwd decls
template <std::size_t N>
class cstatic_string;

namespace detail {

// Helpers
constexpr std::size_t round_buffer_size(std::size_t input) noexcept
{
    if (input <= 8u)
        return 8u;
    else if (input <= 16u)
        return 16u;
    else if (input <= 32u)
        return 32u;
    return input;
}

constexpr int log10ceil(int num) noexcept
{
    int res = 1;
    for (; num >= 10; num /= 10)
        ++res;
    return res;
}

template <class T>
constexpr std::size_t get_buffer_size() noexcept
{
    if constexpr (std::is_integral_v<T>)
    {
        return round_buffer_size(std::numeric_limits<T>::max_digits10 + 2);
    }
    else if constexpr (std::is_floating_point_v<T>)
    {
        // 4: radix point, sign, e+
        return round_buffer_size(
            4 + std::numeric_limits<T>::max_digits10 +
            (std::max)(2, log10ceil(std::numeric_limits<T>::max_exponent10))
        );
    }
    else
    {
        static_assert(false);
    }
}

struct access
{
    template <std::size_t N>
    static constexpr char* get_data(cstatic_string<N>& obj) noexcept
    {
        return obj.buff_;
    }

    template <std::size_t N>
    static constexpr void set_size(cstatic_string<N>& obj, std::size_t v) noexcept
    {
        obj.size_ = v;
    }
};

template <class T, class Invoker, class... Args>
constexpr auto to_static_string_impl(Invoker invoker, T value, Args... args)
{
    cstatic_string<get_buffer_size<T>()> buff;
    char* data = access::get_data(buff);
    std::to_chars_result result = invoker(data, data + buff.size(), value, args...);
    assert(result.ec == std::errc());
    access::set_size(buff, result.ptr - data);
    return buff;
}

}  // namespace detail

template <std::size_t N>
class cstatic_string
{
    char buff_[N];
    std::size_t size_{};

    friend struct detail::access;

public:
    constexpr cstatic_string() = default;
    constexpr std::string_view get() const noexcept { return std::string_view(buff_, size_); }
    constexpr operator std::string_view() const noexcept { return get(); }
};

template <class T, class = std::enable_if_t<std::is_integral_v<T> && !std::is_same_v<T, bool>>>
TO_STATIC_STRING_CXX23_CONSTEXPR auto to_static_string(T int_value, int base = 10) noexcept
{
    return to_static_string_impl(
        [](char* beg, char* end, T val, int base) { return std::to_chars(beg, end, val, base); },
        int_value,
        base
    );
}

template <class T, class = std::enable_if_t<std::is_floating_point_v<T>>>
TO_STATIC_STRING_CXX23_CONSTEXPR auto to_static_string(T float_value) noexcept
{
    return to_static_string_impl(
        [](char* beg, char* end, T val) { return std::to_chars(beg, end, val); },
        float_value
    );
}

template <class T, class = std::enable_if_t<std::is_floating_point_v<T>>>
TO_STATIC_STRING_CXX23_CONSTEXPR auto to_static_string(T float_value, std::chars_format fmt) noexcept
{
    return to_static_string_impl(
        [](char* beg, char* end, T val, std::chars_format fmt) { return std::to_chars(beg, end, val, fmt); },
        float_value,
        fmt
    );
}

template <class T, class = std::enable_if_t<std::is_floating_point_v<T>>>
TO_STATIC_STRING_CXX23_CONSTEXPR auto to_static_string(
    T float_value,
    std::chars_format fmt,
    int precision
) noexcept
{
    return to_static_string_impl(
        [](char* beg, char* end, T val, std::chars_format fmt, int prec) {
            return std::to_chars(beg, end, val, fmt, prec);
        },
        float_value,
        fmt,
        precision
    );
}

}  // namespace tostr

#endif
