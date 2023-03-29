
#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include <memory>
# include "iterator_traits.hpp"
namespace ft
{

template <class Iterator>
class reverse_iterator
{
	public :
	
	typedef Iterator												iterator_type;
	typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename iterator_traits<Iterator>::value_type			value_type;
	typedef typename iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename iterator_traits<Iterator>::pointer				pointer;
	typedef typename iterator_traits<Iterator>::reference			reference;


	private :
		iterator_type _it;

	public :
	reverse_iterator() {};
	explicit reverse_iterator( iterator_type it): _it(--it) {};
	template <class It>
	reverse_iterator(const reverse_iterator<It>& other) : _it(--other.base()) {};
	~reverse_iterator() {};

	reverse_iterator& operator=(reverse_iterator const &other)
	{
		this->_it = other._it;
		return (*this);
	}

	Iterator base() const
	{
		iterator_type tmp = this->_it;
		return(++tmp);
	};

	reference operator*() const
	{return (*(this->_it));};

	pointer operator->() const
	{	return (&(operator*()));		};

	reference operator[]( int n ) const
	{return (_it[-n]);};

	reverse_iterator& operator++()
	{
		this->_it--;
		return (*this);
	};

	reverse_iterator& operator--()
	{
		this->_it++;
		return (*this);
	};

	reverse_iterator operator++( int )
	{
		reverse_iterator tmp(*this);
		_it--;
		return (tmp);
	};

	reverse_iterator operator--( int )
	{
		reverse_iterator tmp(*this);
		_it++;
		return (tmp);
	};

	reverse_iterator operator+( difference_type n ) const
	{
		return (reverse_iterator(base() - n));
	};

	reverse_iterator operator-( difference_type n ) const
	{
		return (reverse_iterator(base() + n));
	};

	reverse_iterator& operator+=( difference_type n )
	{
		_it -= n;
		return (*this);
	};

	reverse_iterator& operator-=( difference_type n )
	{
		_it += n;
		return (*this);
	};
	
friend
reverse_iterator	operator+(difference_type n, const reverse_iterator& rit)	{
		return rit + n;
	}

};


template <typename I_L, typename I_R>
bool operator== (const reverse_iterator<I_L>& lhs, const reverse_iterator<I_R>& rhs)	{
	return lhs.base() == rhs.base();
};

template <typename I_L, typename I_R>
bool operator!= (const reverse_iterator<I_L>& lhs, const reverse_iterator<I_R>& rhs)	{
	return lhs.base() != rhs.base();
};

template <typename I_L, typename I_R>
bool operator<  (const reverse_iterator<I_L>& lhs, const reverse_iterator<I_R>& rhs)	{
	return lhs.base() > rhs.base();
};

template <typename I_L, typename I_R>
bool operator<= (const reverse_iterator<I_L>& lhs, const reverse_iterator<I_R>& rhs)	{
	return lhs.base() >= rhs.base();
};

template <typename I_L, typename I_R>
bool operator>  (const reverse_iterator<I_L>& lhs, const reverse_iterator<I_R>& rhs)	{
	return lhs.base() < rhs.base();
};

template <typename I_L, typename I_R>
bool operator>= (const reverse_iterator<I_L>& lhs, const reverse_iterator<I_R>& rhs)	{
	return lhs.base() <= rhs.base();
};

template <typename I_L, typename I_R>
typename reverse_iterator<I_L>::difference_type		operator-(const reverse_iterator<I_L>& lhs, const reverse_iterator<I_R> &rhs)	{
	return rhs.base() - lhs.base();
};

}


#endif