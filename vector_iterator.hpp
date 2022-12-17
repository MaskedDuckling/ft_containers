#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <stddef.h>
#include <iterator>

namespace ft{
	template<class T>
		class vector_iterator
		{
		private:
			T *ptr;
		public:
		    typedef T         value_type;
			typedef ssize_t  difference_type;
			typedef T*   pointer;
			typedef T & reference;
			typedef std::random_access_iterator_tag  iterator_category;
			// vector_iterator();
			// vector_iterator(vector_iterator const & ref);

			// ~vector_iterator();

			// vector_iterator &operator=(vector_iterator const & rhs);
			bool operator== (const vector_iterator& rhs){
				return (this->ptr == rhs.ptr);
			};
			bool operator!= (const vector_iterator& rhs){
				return (this->ptr != rhs.ptr);
			};
			bool operator> (const vector_iterator& rhs){
				return (this->ptr > rhs.ptr);
			};
			bool operator< (const vector_iterator& rhs){
				return (this->ptr < rhs.ptr);
			};
			bool operator>= (const vector_iterator& rhs){
				return (this->ptr >= rhs.ptr);
			};
			bool operator<= (const vector_iterator& rhs){
				return (this->ptr <= rhs.ptr);
			};

			value_type & operator*(){
				return (*this->ptr);
			};
			value_type* operator->(){
				return (this->ptr);
			};

			vector_iterator & operator--(){
				this->ptr--;
				return (*this);
			};
			void operator--(int){
				vector_iterator copie(*this);
				this->ptr--;
				return (*this);
			};

			vector_iterator & operator++(){
				this->ptr++;
				return (*this);
			};
			void operator++(int){
				vector_iterator copie(*this);
				this->ptr++;
				return (*this);
			};

			vector_iterator operator+(const difference_type n){
				vector_iterator copie(*this);
				copie.ptr += n;
				return(copie);
			};
			vector_iterator operator-(const difference_type n){
				vector_iterator copie(*this);
				copie.ptr -= n;
				return(copie);
			};
			difference_type operator-(const vector_iterator & rhs){
				return(this->ptr - rhs.ptr);
			};
		};
	template<class T>
	vector_iterator<T> operator+(const typename vector_iterator<T>::difference_type n, vector_iterator<T> & rhs){
		return (rhs + n);
	}
}


#endif
