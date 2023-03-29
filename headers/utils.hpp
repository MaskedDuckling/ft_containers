#ifndef UTILS_HPP
# define UTILS_HPP

# include "iterator_traits.hpp"
# include "is_integral.hpp"

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

template <typename it>
typename iterator_traits<it>::difference_type distance(it first, it last)
{
	typename iterator_traits<it>::difference_type dist = 0;

	while (first != last)
	{
		first++;
		dist++;
	}
	return (dist);
};

}

#endif