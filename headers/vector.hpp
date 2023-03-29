#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include <iostream>
#include "vector_iterator.hpp"
#include "reverse_iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"

namespace ft{
	template<class T, class Alloc = std::allocator<T> >
		class vector
		{
		public:
			/*Member types 12/12*/
			typedef T													value_type;
			typedef Alloc												allocator_type;
			typedef typename	allocator_type::reference				reference;
			typedef typename	allocator_type::const_reference			const_reference;
			typedef typename	allocator_type::pointer					pointer;
			typedef typename	allocator_type::const_pointer			const_pointer;
			typedef ft::vector_iterator<0, value_type>					iterator;
			typedef ft::vector_iterator<1, value_type>					const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
			typedef std::ptrdiff_t										difference_type;
			typedef typename allocator_type::size_type					size_type;





			/*Constructeur 4/4 */
			explicit vector(const allocator_type & alloc = allocator_type()):
				_alloc(alloc),
				_start(NULL),
				_size(0),
				_capacity(0)
			{
			}

			explicit vector(size_t n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type()):
				_alloc(alloc),
				_start(NULL)
			{
				_start = _alloc.allocate(n);
				_size = 0;
				_capacity = n;
				assign(n, val);
			}

			template <class InputIterator>
			vector (typename ft::enable_if<!is_integral<InputIterator>::value_type , InputIterator>::type first, InputIterator last, const allocator_type& alloc = allocator_type())
			{
				this->_alloc = alloc;
				this->_capacity = 0;
				this->_size = 0;
				this->_start = NULL;
				assign(first, last);
			}

			vector (const vector& x):
				_alloc(x._alloc),
				_start(NULL),
				_size(0), 
				_capacity(0)
			{
				*this = x;
			};



			/*Destructeur 1/1*/
			~vector(){
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.destroy(&_start[i]);
				_alloc.deallocate(this->_start, _capacity);
			};



			/*Capacity 6/6*/
			size_t size() const{
				return (_size);
			}

			size_t max_size() const {
				return (allocator_type().max_size());
			}

			void resize (size_type n, value_type val = value_type()){
				if (n < _size){
					this->pop_back();
					this->resize(n, val);
				}
				else if (n > _size){
					this->push_back(val);
					this->resize(n, val);
				}
			}

			size_t capacity() const{
				return(_capacity);
			}

			bool empty() const{
				return(size() > 0 ? false : true);
			}

			void reserve (size_type n){
				if (n <= this->_capacity)
					return ;
				if (n > max_size())
					throw std::length_error("vector::reserve");
				if (!this->_start)
				{
					this->_start = this->_alloc.allocate(n);
					_capacity = n;
					return ;
				}

				size_type new_containers_cap = 1;
				while (new_containers_cap < n)
					new_containers_cap *= 2;

				value_type* new_tab = this->_alloc.allocate(new_containers_cap);
				for (size_type i = 0; i < this->_size; i++)
				{
					this->_alloc.construct(&new_tab[i], this->_start[i]);
					this->_alloc.destroy(&this->_start[i]);
				}
				this->_alloc.deallocate(this->_start, this->_capacity);
				this->_capacity = new_containers_cap;
				this->_start = new_tab;
			};



			/*Iterator 12/12*/
			iterator begin()							{return (iterator(_start));};
			const_iterator begin() const				{return (const_iterator(_start));};
			const_iterator cbegin() const				{return (const_iterator(_start));};

			iterator end()								{return (iterator(_start + _size));};
			const_iterator end() const					{return (const_iterator(_start + _size));};
			const_iterator cend() const					{return (const_iterator(_start + _size));};

			reverse_iterator rbegin()					{return (reverse_iterator(this->end()));};
			const_reverse_iterator rbegin() const		{return (const_reverse_iterator(this->end()));};
			const_reverse_iterator crbegin() const		{return (const_reverse_iterator(this->end()));};

			reverse_iterator rend()						{return (reverse_iterator(this->begin()));};
			const_reverse_iterator rend() const			{return (const_reverse_iterator(this->begin()));};
			const_reverse_iterator crend() const		{return (const_reverse_iterator(this->begin()));};



			/*Element access 5/5*/ /*Exception a changer dans at*/
			reference operator[] (size_type n){
				return (this->_start[n]);
			}
			const_reference operator[] (size_type n) const{
				return (this->_start[n]);
			}

			reference at (size_type n){
				if (n >= _size || n < 0)
					throw std::out_of_range("Index out of range\n");
				return (this->_start[n]);
			}
			const_reference at (size_type n) const{
				if (n >= _size || n < 0)
					throw std::out_of_range("Index out of range\n");
				return (this->_start[n]);
			}

			reference front(){
				return (*(_start));
			}
			const_reference front() const{
				return (*(_start));
			}

			reference back(){
				return (*(_start + (_size - 1)));
			}
			const_reference back() const{
				return (*(_start + (_size - 1)));
			}

			value_type* data(){
				return (_start);
			}
			const value_type* data() const{
				return (_start);
			}



			/*Modifiers 6/7*/
			void push_back (const value_type& val){
				reserve(this->_size + 1);
				_alloc.construct(&this->_start[this->_size], val);
				_size++;
			}

			void pop_back(){
				_size--;
				_alloc.destroy(&this->_start[this->_size]);
			}

			void clear(){
				delete_elem(0);
			}
			
			void assign (size_type n, const value_type& val){
				delete_elem(0);
				reserve(n);
				for (size_t i = 0; i < n; i++){
					_alloc.construct(&this->_start[i], val);
				}
				_size = n;
			}
			template <class InputIterator>
			void assign (typename ft::enable_if<!is_integral<InputIterator>::value_type , InputIterator>::type first, InputIterator last){
				delete_elem(0);
				reserve(distance(first,last));
				int i = 0;
				for (; first != last; ++first){
					this->_alloc.construct(&this->_start[i], *first);
					i++;
				}
				_size = i;
			}

			iterator insert (iterator position, const T& val)
			{
				difference_type i = distance(begin(), position);
				reserve(_size + 1);
				position = begin() + i;
				iterator it = end();
				for (; it != position; it--)
				{
					_alloc.construct(&(*it), *(it - 1));
					_alloc.destroy(&(*(it - 1)));
				}
				_alloc.construct(&(*it), val);
				_size++;
				return position;
			}

			void insert( iterator position, size_type count, const T& val )
			{
				if (count == 0)
					return ;
				difference_type i = distance(begin(), position);
				reserve(_size + count);
				position = begin() + i;
				for (iterator it = end() - 1; it != position - 1; it--)
				{
					this->_alloc.construct(&(*(it + count)), *it);
					this->_alloc.destroy(&(*it));
				}
				for (size_type i = 0; i < count; i++)	{
					this->_alloc.construct(&(*position), val);
					position++;
				}
				_size += count;
			};
			template< class InputIterator >
			void insert( iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value_type, InputIterator>::type* = NULL )
			{
				typename iterator_traits<InputIterator>::difference_type n = distance(first, last);
				difference_type i = distance(begin(), position);
				reserve(_size + n);
				position = begin() + i;
				for (iterator it = end() - 1; it != position - 1; it--)
				{
					this->_alloc.construct(&(*(it + n)), *it);
					this->_alloc.destroy(&(*it));
				}
				for (;first != last; first++){
					this->_alloc.construct(&(*position++), *first);
				}
				_size += n;
			};
			iterator erase( iterator pos )
			{
				iterator ret = pos;
				_alloc.destroy(&(*pos));
				iterator end = this->end() - 1;
				for (; pos != end; pos++)	{
					_alloc.construct(&(*pos), *(pos + 1));
					_alloc.destroy(&(*(pos + 1)));
				}
				_size--;
				return ret;
			};

			iterator erase( iterator first, iterator last )
			{
				iterator ret = first;
				iterator tmp = first;
				difference_type i = distance(first, last);

				for (; tmp != last; tmp++)
					_alloc.destroy(&(*tmp));
				for (; tmp != end(); tmp++)	{
					_alloc.construct(&(*first), *tmp);
					_alloc.destroy(&(*tmp));
					first++;
				}
				_size -= i;
				return ret;
			};

			void swap (vector& x){
				ft::swap(this->_size, x._size);
				ft::swap(this->_capacity, x._capacity);
				ft::swap(this->_start, x._start);
				ft::swap(this->_alloc, x._alloc);
			}



			/*Utils*/
			void	delete_elem(size_type first)
			{
				for (size_type i = first; i < this->_size; i++)
					this->_alloc.destroy(&_start[i]);
				this->_size = first;
			};

			template< class InputIterator >
			difference_type distance(InputIterator first, InputIterator last){
				difference_type res = 0;
				for (; first != last; first++)
					res++;
				return (res);
			}

			void	affi(){
				pointer end = _start + _size;
				std::cout << "{";
				for (pointer start=_start; start < end; start++){
					std::cout << *start;
					if (start+1 < end)
						std::cout << " ";
				}
				std::cout << "}" << std::endl;
			}

			/*Allocator*/
			allocator_type get_allocator(){return (_alloc);}

			/*Operateurs*/
			vector &operator=(vector const & rhs)
			{
				delete_elem(0);
				reserve(rhs._size);
				for (size_type i = 0; i < rhs._size; i++)	{
					this->_alloc.construct(&this->_start[i], rhs._start[i]);
				}
				this->_size = rhs._size;
				return *this;
			};

			friend
			bool operator== (const vector& lhs, const vector& rhs)
			{
				if (lhs._size != rhs._size)
					return false;
				for (size_type i = 0; i < rhs._size; i++)
					if (lhs._start[i] != rhs._start[i])
						return false;
				return true;
			};

			friend
			bool operator<  (const vector& lhs, const vector& rhs)
			{
				for (size_type i = 0; i < rhs._size; i++)
				{
					if (i == lhs._size)
						return true;
					if (lhs._start[i] != rhs._start[i])
						return lhs._start[i] < rhs._start[i];
				}
				return false;
			};

		private:
			allocator_type	_alloc;
			pointer			_start;
			size_t			_size;
			size_t			_capacity;
		};

		template <class T>
		bool operator!=(const vector<T>lhs, const vector<T>rhs){
			return !(rhs == lhs);
		}
		template <class T>
		bool operator<=(const vector<T>lhs, const vector<T>rhs){
			return !(rhs < lhs);
		}
		template <class T>
		bool operator>=(const vector<T>lhs, const vector<T>rhs){
			return !(lhs < rhs);
		}
		template <class T>
		bool operator>(const vector<T>lhs, const vector<T>rhs){
			return (rhs < lhs);
		}
		template<class T>
		void swap (vector<T>& x, vector<T>& y)
		{
		x.swap(y);
		};

}
#endif
