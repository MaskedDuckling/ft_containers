#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "utils.hpp"

namespace ft
{

template <bool isConst, class T>
class vector_iterator
{
	public :

		typedef typename choose<isConst, const T, T>::type value_type;
		typedef value_type* pointer;
		typedef value_type& reference;
		typedef std::ptrdiff_t difference_type;
		typedef std::random_access_iterator_tag iterator_category;
	private :
		pointer _ptr;
	public :

		vector_iterator() : _ptr(NULL)
		{};

		vector_iterator(const vector_iterator &other)
		{*this = other;}

		vector_iterator(pointer ptr): _ptr(ptr)
		{};

		~vector_iterator()
		{};

			/* assigne operator */

		operator vector_iterator<true, T> () const {return (vector_iterator<true, T>(this->_ptr)); }
	;	
		vector_iterator &operator=(const vector_iterator &rhs)
		{
			this->_ptr = rhs._ptr;
			return (*this);
		}

			/* equality/inequality operators */

		bool operator==(const vector_iterator &rhs)
		{return ((this->_ptr == rhs._ptr));};

		bool operator!=(const vector_iterator &rhs)
		{return ((this->_ptr != rhs._ptr));};

			/* dereferance operators */
		
		reference	operator*() const
		{return(*_ptr);};

		pointer operator->() const
		{return(_ptr);};


			/* incremente and decremante operators */

		vector_iterator &operator++()
		{
			this->_ptr++;
			return (*this);
		};

		vector_iterator &operator--()
		{
			this->_ptr--;
			return (*this);
		};

		vector_iterator operator++(int)
		{
			vector_iterator tmp(*this);
			operator++();
			return (tmp);
		};
		
		vector_iterator operator--(int)
		{
			vector_iterator tmp(*this);
			operator--();
			return (tmp);
		};

			/* aritmetic operators */

		vector_iterator operator+(int i)
		{
			vector_iterator tmp(*this);

			tmp += i;
			return (tmp);
		};

		vector_iterator operator-(int i)
		{
			vector_iterator tmp(*this);

			tmp -= i;
			return (tmp);
		};

	//Supports the arithmetic operators + and - between an iterator and an integer value, or subtracting an iterator from another???????????
		vector_iterator operator+(int i) const
		{
			vector_iterator tmp(*this);

			tmp._ptr += i;
			return (tmp);
		};

		vector_iterator operator-(int i) const
		{
			vector_iterator tmp(*this);

			tmp._ptr -= i;
			return (tmp);
		};

		//friend
		//difference_type 

			/* inequality relational operators */
		
		bool	operator<(vector_iterator &rsh)
		{return (this->_ptr < rsh._ptr);};

		bool	operator>(vector_iterator &rsh)
		{return (this->_ptr > rsh._ptr);};

		bool	operator<=(vector_iterator &rsh)
		{return (!operator>(rsh));};

		bool	operator>=(vector_iterator &rsh)
		{return (!operator<(rsh));};

			/* compound assignment operators */

		vector_iterator &operator+=(int n)
		{
			this->_ptr += n;
			return (*this);
		};

		vector_iterator &operator-=(int n)
		{
			this->_ptr -= n;
			return (*this);
		};

			/* offset dereference operator */

		value_type &operator[](int i) const
		{return(_ptr[i]);};


		friend
		vector_iterator	operator+(int n, vector_iterator &rit)	{
			return rit + n;
		}

		friend
		difference_type		operator-(const vector_iterator &lhs, const vector_iterator &rhs)	{
			return &(*lhs) - &(*rhs);
		}

		friend
		bool	operator==(const vector_iterator &lhs, const vector_iterator &rhs)	{
			return lhs._ptr == rhs._ptr;
		}
		friend
		bool	operator!=(const vector_iterator &lhs, const vector_iterator &rhs)	{
			return lhs._ptr != rhs._ptr;
		}
		friend
		bool	operator<(const vector_iterator &lhs, const vector_iterator &rhs)	{
			return lhs._ptr < rhs._ptr;
		}
		friend
		bool	operator<=(const vector_iterator &lhs, const vector_iterator &rhs)	{
			return lhs._ptr <= rhs._ptr;
		}
		friend
		bool	operator>(const vector_iterator &lhs, const vector_iterator &rhs)	{
			return lhs._ptr > rhs._ptr;
		}
		friend
		bool	operator>=(const vector_iterator &lhs, const vector_iterator &rhs)	{
			return lhs._ptr >= rhs._ptr;
		}

		friend
		difference_type	distance(const vector_iterator& first, const vector_iterator& last)	{
			return last - first;
		}

};

}


#endif