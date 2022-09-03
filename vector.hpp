#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include <iostream>

namespace ft{
	template<class T, class Alloc = std::allocator<T> >
		class vector
		{
		public:
			/*Member types 9/12*/
			typedef T													value_type;
			typedef Alloc												allocator_type;
			typedef typename	allocator_type::reference				reference;
			typedef typename	allocator_type::const_reference			const_reference;
			typedef typename	allocator_type::pointer					pointer;
			typedef typename	allocator_type::const_pointer			const_pointer;
			//typedef std::random_access_iterator<value_type>							iterator;
			//typedef std::random<const value_type>						const_iterator;
			typedef std::reverse_iterator<value_type>					reverse_iterator;
			typedef std::reverse_iterator<const value_type>				const_reverse_iterator;
			typedef typename allocator_type::size_type							size_type;





			/*Constructeur 2/4 */
			explicit vector(const allocator_type & alloc = allocator_type()):
				_alloc(alloc),
				_start(NULL),
				_size(0),
				_capacity(0)
			{}

			explicit vector(size_t n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type()):
				_alloc(alloc),
				_start(NULL),
				_size(0),
				_capacity(0)
			{
				_start = _alloc.allocate(n);
				_capacity = n;
				_size = n;
				for (size_t i = 0; i < n; i++){
					_alloc.construct(_start + i, val);
				}
			}





			/*Destructeur 1/1*/
			~vector(){
				_alloc.destroy(_start);
				_alloc.deallocate(_start, this->capacity());
			}





			/*Iterators 0/4*/





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
				while (n > _capacity){
					double_capacity();
				}
			}





			/*Element access 5/5*/ /*Exception a changer dans at*/
			reference operator[] (size_type n){
				return (*(_start + n));
			}
			const_reference operator[] (size_type n) const{
				return (*(_start + n));
			}

			reference at (size_type n){
				if (n >= _size || n < 0)
					throw std::out_of_range("Index out of range");
				return (*(_start + n));
			}
			const_reference at (size_type n) const{
				if (n >= _size || n < 0)
					throw std::out_of_range("Index out of range");
				return (*(_start + n));
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





			/*Modifiers 3/7*/
			void push_back (const value_type& val){
				if (_size == _capacity)
					double_capacity();
				_alloc.construct(_start + _size, val);
				_size++;
			}

			void pop_back(){
				_size--;
				_alloc.destroy(_start + _size);
			}

			void clear(){
				while (_size > 0){
					_size--;
					_alloc.destroy(_start + _size);
				}
			}
			
			/*1/2*/void assign (size_type n, const value_type& val){
				clear();
				while (n > 0){
					push_back(val);
					n--;
				}
			}

			void swap (vector& x){
				ft::vector<value_type> tmp((x.size() > _size ? x.size() : _size));
			}





			/*Utils*/
			void double_capacity(){
				pointer	ostart = _start;
				pointer oend = _start + _size;
				_capacity = _capacity * 2;
				_start = _alloc.allocate(this->capacity());
				size_t i = 0;
				while (ostart < oend){
					_alloc.construct(_start + i, *ostart);
					i++;
					ostart++;
				}
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

			/*Operateur=*/
			vector &operator=(vector const & rhs);

		private:
			allocator_type	_alloc;
			pointer			_start;
			size_t			_size;
			size_t			_capacity;
		};

}
#endif
