# to_static_string: like std::to_string, but without surprises

This is a tiny, header-only library that implements `to_static_string`:
a C++17 drop-in replacement for `std::to_string`, based on `std::to_chars`.

For instance:

```cpp
#include "tostr/to_static_string.h"
#include <iostream>

int main()
{
    // We have an integer value to convert to string
    int value = 42;

    // Converting it returns a cstatic_string<N>, a stack-based
    // string holding the result of the conversion. N is selected
    // at compile-time, depending on the type
    auto str = tostr::to_static_string(value);

    // We can use .get() to retrieve a std::string_view for that buffer
    std::cout << "The answer is: " << str.get() << std::endl;
}

```

## Comparison

When compared to `std::to_string`, it has the following advantages:

- It is faster. See the benchmark section (TODO: link) below.
- It is non-allocating. All operations use stack memory.
- It is non-throwing. It is guaranteed that `to_static_string` will never throw exceptions.
- It is locale-independant. This is specially important for floating-point values,
  where the decimal point can be affected by locale configuration.

When compared to just using `std::to_chars`:

- It is a level of abstraction above. This means it is safer, since you do not need to
  think of buffer size - we do it for you.
- It has comparable performance (see below).

## Banchmarks

These benchmarks have been obtained under an i7-10510U CPU @ 1.80GHz,
using clang-18, under CMake Release variant, using libstdc++ (Ubuntu 22.04) and C++20.

## Tested under

Testing is still an ongoing effort. It has only been tested locally
with the compiler/setup mentioned above.

## Benchmark

| Benchmark                             | Time    | Iterations |
| ------------------------------------- | ------- | ---------- |
| `std::to_string(long)`                | 45.3 ns | 11844179   |
| `to_static_string(long)`              | 27.7 ns | 30023151   |
| `std::to_chars(char*, char*, long)`   | 27.4 ns | 25507148   |
| `std::to_string(double)`              | 1245 ns | 480956     |
| `to_static_string(double)`            | 95.6 ns | 6366312    |
| `std::to_chars(char*, char*, double)` | 98.4 ns | 7338231    |
