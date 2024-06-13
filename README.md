# Argument binding

Prototype a concise syntax for argument binding, using operator overloading.

## Getting started

1. Install dependencies
```bash
sudo apt get install libgtest-dev cmake g++
```

2. Clone the repo

3. Build and run:
```bash
cd cpp_bind
mkdir out
cd out
cmake ..
cd ..
cmake --build out/ # out-of-source build
./out/unit_tests
```

## Simple example

Create function objects where one argument of a binary function has been bound:

```cpp
    auto twoMinus = 2 >>= std::minus<int>{};  // bind left argument to 2
    auto minusTwo = std::minus<int>{} <<= 2;  // bind right argument to 2
```

## Usage example: subtract one from each element

Given:
```cpp
const std::vector<int> v{1, 2, 4, 8};
std::vector<int> result(v.size());
```

This is how we would normally subtract one from each element in a sequence:
```cpp
std::transform(v.cbegin(),
               v.cend(),
               0,
               [](int i){ return i-1; });
```

With the argument binding enabled, we can instead write it like this:
```cpp
using namespace bind; // make the overloads for operator>>= and operator<<= available

std::transform(v.cbegin(),
               v.cend(),
               0,
               std::minus<int>{} <<= 1); // bind right argument of 'minus' to equal 1
```

For binary functions which have their own operator symbol, such as + - * / ect, a lambda expression is shorter, but for
function-like objects without its own special symbol, the overload syntax is shorter and simpler.
