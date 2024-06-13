# Argument binding

Prototype a concise syntax for argument binding, using operator overloading.
This can be used instead of lambda expressions in some contexts such as:

```cpp
const std::vector<int> v{1, 2, 4, 8};

const int sum_squares = std::transform_reduce(v.cbegin(), v.cend(),
                                              0,
                                              std::Plus<int>{},
                                              [](int i){ return i*i; }); // lambda expression to square a number
```

A simple syntax to bind the left and right arguments of a binary function could be:

```cpp
    2 >>= power()  // bind left argument to 2
    power() <<= 2  // bind right argument to 2
```

Ideally, this would work for any function-like object, while rejecting booleans and integers as potential template arguments, to avoid collision with the usual operator<<= and operator>>= on primitive types.
Perhaps std::enable_if could and should be used to enable it for function-like objects only?

A usage example could look like this:

```cpp
const std::vector<int> v{1, 2, 4, 8};

const int sum_squares = std::transform_reduce(v.cbegin(), v.cend(),
                                              0,
                                              std::Plus<int>{},
                                              std::pow <<= 2.0); // bind right argument of 'pow' to equal 2.0
```

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
