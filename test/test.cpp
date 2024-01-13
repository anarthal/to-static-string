#include <catch2/catch_test_macros.hpp>
#include <charconv>
#include <cstdint>
#include <type_traits>

#include "tostr/to_static_string.h"

using namespace tostr;

TEST_CASE("Integers without bases", "[to_static_string]")
{
    // Character types
    REQUIRE(to_static_string(static_cast<char>(10)).get() == "10");
    REQUIRE(to_static_string(static_cast<signed char>(-1)).get() == "-1");
    REQUIRE(to_static_string(static_cast<unsigned char>(12)).get() == "12");
    REQUIRE(to_static_string(static_cast<wchar_t>(12)).get() == "12");
    REQUIRE(to_static_string(static_cast<char16_t>(12)).get() == "12");
    REQUIRE(to_static_string(static_cast<char32_t>(12)).get() == "12");
    // TODO: char8_t

    // Shorts
    REQUIRE(to_static_string(static_cast<short>(10)).get() == "10");
    REQUIRE(to_static_string(static_cast<unsigned short>(10)).get() == "10");

    // Ints
    REQUIRE(to_static_string(static_cast<int>(10)).get() == "10");
    REQUIRE(to_static_string(static_cast<unsigned int>(10)).get() == "10");

    // Longs
    REQUIRE(to_static_string(static_cast<long>(10)).get() == "10");
    REQUIRE(to_static_string(static_cast<unsigned long>(10)).get() == "10");

    // Long long
    REQUIRE(to_static_string(static_cast<long long>(10)).get() == "10");
    REQUIRE(to_static_string(static_cast<unsigned long long>(10)).get() == "10");

    // TODO: extension types
}

TEST_CASE("Integers with bases", "[to_static_string]")
{
    // Character types
    REQUIRE(to_static_string(static_cast<char>(10), 16).get() == "a");
    REQUIRE(to_static_string(static_cast<signed char>(-1), 16).get() == "-1");
    REQUIRE(to_static_string(static_cast<unsigned char>(12), 16).get() == "c");
    REQUIRE(to_static_string(static_cast<wchar_t>(12), 16).get() == "c");
    REQUIRE(to_static_string(static_cast<char16_t>(12), 16).get() == "c");
    REQUIRE(to_static_string(static_cast<char32_t>(12), 16).get() == "c");
    // TODO: char8_t

    // Shorts
    REQUIRE(to_static_string(static_cast<short>(10), 16).get() == "a");
    REQUIRE(to_static_string(static_cast<unsigned short>(10), 16).get() == "a");

    // Ints
    REQUIRE(to_static_string(static_cast<int>(10), 16).get() == "a");
    REQUIRE(to_static_string(static_cast<unsigned int>(10), 16).get() == "a");

    // Longs
    REQUIRE(to_static_string(static_cast<long>(10), 16).get() == "a");
    REQUIRE(to_static_string(static_cast<unsigned long>(10), 16).get() == "a");

    // Long long
    REQUIRE(to_static_string(static_cast<long long>(10), 16).get() == "a");
    REQUIRE(to_static_string(static_cast<unsigned long long>(10), 16).get() == "a");

    // TODO: extension types
}

TEST_CASE("Floats with no args", "[to_static_string]")
{
    REQUIRE(to_static_string(4.2f).get() == "4.2");
    REQUIRE(to_static_string(4.2).get() == "4.2");
    // TODO: extension types
}

TEST_CASE("Floats with format", "[to_static_string]")
{
    REQUIRE(to_static_string(4.2f, std::chars_format::hex).get() == "1.0cccccp+2");
    REQUIRE(to_static_string(4.2, std::chars_format::hex).get() == "1.0cccccccccccdp+2");
    // TODO: extension types
}

TEST_CASE("Floats with format and precision", "[to_static_string]")
{
    REQUIRE(to_static_string(4.2f, std::chars_format::fixed, 4).get() == "4.2000");
    REQUIRE(to_static_string(4.2, std::chars_format::fixed, 4).get() == "4.2000");
    // TODO: extension types
}