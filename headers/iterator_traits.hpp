#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

#include <iterator>

template <typename _Iterator>
struct iterator_traits{
	typedef typename _Iterator::difference_type		difference_type;
	typedef typename _Iterator::value_type			value_type;
	typedef typename _Iterator::pointer				pointer;
	typedef typename _Iterator::reference			reference;
	typedef typename _Iterator::iterator_category	iterator_category;
};

template <class T>
struct iterator_traits<T*>{
	typedef std::random_access_iterator_tag			iterator_category;
	typedef T										value_type;
	typedef T*										pointer;
	typedef T&										reference;
	typedef std::ptrdiff_t								difference_type;
};

template <class T>
struct iterator_traits<const T*>{
	typedef std::random_access_iterator_tag			iterator_category;
	typedef T										value_type;
	typedef const T*										pointer;
	typedef const T&										reference;
	typedef std::ptrdiff_t								difference_type;
};

#endif