#pragma once

namespace bd {

// essentially an implementation of 'bind1st' which was deprecated in C++11 and removed in C++17 in favor of 'bind'
template <typename F, typename L>
struct bind_left
{
    bind_left(F binaryFunction, L const& left) : _f{binaryFunction}, _left{left} {}

    template <typename U>
    auto operator()(U const& right) const { return _f(_left, right); }

    F const _f;
    L const _left;
};

// essentially an implementation of 'bind2nd' which was deprecated in C++11 and removed in C++17 in favor of 'bind'
template <typename F, typename R>
struct bind_right
{
    bind_right(F binaryFunction, R const& right) : _f{binaryFunction}, _right{right} {}

    template <typename U>
    auto operator()(U const& left) const { return _f(left, _right); }

    F const _f;
    R const _right;
};

template <typename F, typename L, typename R>
struct bind_both
{
    bind_both(F binaryFunction, L const& left, R const& right) : _f{binaryFunction}, _left{left}, _right{right} {}
    auto operator()() const { return _f(_left, _right); }

    F const _f;
    L const _left;
    R const _right;
};

template <typename F, typename T>
bind_right<F, T> operator<<=(F binaryFunction, T const& rightArg)
{
    return bind_right<F, T>(binaryFunction, rightArg);
}

template <typename T, typename F>
bind_left<F, T> operator>>=(T const& leftArg, F binaryFunction)
{
    return bind_left<F, T>(binaryFunction, leftArg);
}

template <typename F, typename L, typename R>
bind_both<F, L, R> operator<<=(bind_left<F,L> const& f_partial, R const& right)
{
    return bind_both<F, L, R>{f_partial._f, f_partial._left, right};
}

template <typename F, typename L, typename R>
bind_both<F, L, R> operator>>=(L const& left, bind_right<F,R> const& f_partial)
{
    return bind_both<F, L, R>{f_partial._f, left, f_partial._right};
}

}
