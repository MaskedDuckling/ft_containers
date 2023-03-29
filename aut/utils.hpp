#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
    template <bool flag, class IsTrue, class IsFalse>
    struct choose;

    template <class IsTrue, class IsFalse>
    struct choose<true, IsTrue, IsFalse>
    {
        typedef IsTrue type;
    };

    template <class IsTrue, class IsFalse>
    struct choose<false, IsTrue, IsFalse>
    {
        typedef IsFalse type;
    };

    
    template <typename T>
    void	swap(T& a, T& b)
    {
        T tmp;

        tmp = a;
        a = b;
        b = tmp;
    };
}

#endif