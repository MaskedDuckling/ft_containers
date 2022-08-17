#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <iostream>

namespace ft{
	template<class T, class Alloc = std::allocator<T> >
		class vector
		{
		public:
			/*Member types*/
			typedef T													value_type;
			typedef Alloc												allocator_type;

			typedef typename	allocator_type::reference				reference;
			typedef typename	allocator_type::const_reference			const_reference;
			typedef typename	allocator_type::pointer					pointer;
			typedef typename	allocator_type::const_pointer			const_pointer;
			/*VOIR SI LES 4 SUIVANTS SONT A CHANGER*/
			//typedef	std::random_access_iterator_tag<value_type>			iterator;
			//typedef	std::random_access_iterator_tag<const value_type>	const_iterator;
			typedef std::reverse_iterator<value_type>					reverse_iterator;
			typedef std::reverse_iterator<const value_type>				const_reverse_iterator;

			//typedef std::iterator_traits<iterator>::difference_type		difference_type;
			typedef typename allocator_type::size_type							size_type;

			/*Constructeur*/
			explicit vector(const allocator_type & alloc = allocator_type()):
				_alloc(alloc),
				_start(NULL),
				_end(NULL),
				_capacity(NULL)
			{}

			explicit vector(size_t n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type()):
				_alloc(alloc),
				_start(NULL),
				_end(NULL),
				_capacity(NULL)
			{
				_start = _alloc.allocate(n);
				_capacity = _start + n;
				_end = _start;
				for (size_t i = 0; i < n; i++){
					_alloc.construct(_end, val);
					_end++;
				}
			}

			/*template<class InputIterator> vector(InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type());
				vector(const vector & X):
				_alloc(alloc),
			{}*/
			vector(vector const & ref);

			~vector(){_alloc.deallocate(_start, this->max_size());}

			/*Fonctions membres*/
			void	affi(){
				pointer end = _end;
				for (pointer start=_start; start < end; start++){
					std::cout << *start << " ";
				}
				std::cout << std::endl;
			}

			size_t size() const{
				pointer end = _end;
				size_t i = 0;
				for (pointer start=_start; start < end; start++){
					i++;
				}
				return (i);
			}

			size_t capacity() const{
				pointer capacity = _capacity;
				size_t i = 0;
				for (pointer start=_start; start < capacity; start++){
					i++;
				}
				return (i);
			}

			size_t max_size() const {return (allocator_type().max_size());}

			bool empty() const{return(size() > 0 ? false : true);}

			/*Accesseur*/
			allocator_type get_allocator(){return (_alloc);}

			/*Operateurs*/
			vector &operator=(vector const & rhs);

		private:
			allocator_type	_alloc;
			pointer			_start;
			pointer			_end;
			pointer			_capacity;
		};

}
#endif
