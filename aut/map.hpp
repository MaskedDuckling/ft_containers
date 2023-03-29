#ifndef MAP_HPP
# define MAP_HPP

#include "RBtree.hpp"
#include "RBnode.hpp"
#include "pair.hpp"
#include "map_iterator.hpp"
#include "reverse_iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"

#include <memory>
#include <functional>

namespace ft{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map
	{
		public:
			/*Member types*/
			typedef Key                                     key_type;
			typedef T                                       mapped_type;
			typedef ft::pair<const key_type, mapped_type>   value_type;
			typedef Compare                                 key_compare;
			typedef Alloc                                   allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef ft::map_iterator<0,value_type> iterator;
			typedef ft::map_iterator<1,value_type> const_iterator;
			typedef ft::reverse_iterator<iterator>	 reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	 const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type difference_type;
			typedef typename std::size_t size_type;

			typedef ft::RBtree<value_type>	tree_type;
			typedef ft::Node<value_type>	node_type;

		private:

		public:
			tree_type		*_tree;
			allocator_type	_allocator;
			size_type		_size;
			key_compare		_comp;
			std::allocator<node_type>	_node_allocator;
			/*CLASSE INTEGRE*/

			class value_compare
			{
				friend class map;
				protected:
					key_compare _comp;
					value_compare (key_compare c) : _comp(c) {}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return _comp(x.first, y.first);
					}
			};

			/*CONSTRUCTEURS*/

			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
				_tree(new tree_type()),
				_allocator(alloc),
				_size(0),
				_comp(comp)
			{};

			template <class InputIterator>  
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
				_tree(new tree_type()),
				_allocator(alloc),
				_size(0),
				_comp(comp)
			{
				insert(first,last);
			}

			map (const map& x):
				_tree(new tree_type()),
				_allocator(x._allocator),
				_size(0),
				_comp(x._comp)
			{
				insert(x.begin(),x.end());
			}

			/*DESTUCTEUR*/

			~map(){
				clear();
				delete this->_tree;
			}

			/*OPERATEUR =*/

			map& operator=(const map& x)
			{
				clear();
				_size = 0;
				this->_allocator = x._allocator;
				_comp = x._comp;
				insert(x.begin(), x.end());
				return *this;
			};
		

			/*ITERATEURS*/

			iterator begin()							{return (iterator(this->_tree->minimum()));};
			const_iterator begin() const				{return (const_iterator(this->_tree->minimum()));};

			iterator end()								{return (iterator(this->_tree->_leaf));};
			const_iterator end() const					{return (const_iterator(this->_tree->_leaf));};

			reverse_iterator rbegin()					{return (reverse_iterator(this->_tree->_leaf));};
			const_reverse_iterator rbegin() const		{return (const_reverse_iterator(this->_tree->_leaf));};

			reverse_iterator rend()						{return (reverse_iterator(this->_tree->minimum()));};
			const_reverse_iterator rend() const			{return (const_reverse_iterator(this->_tree->minimum()));};

			/*CAPACITE*/

			bool empty() const{
				return (this->_size == 0);
			}
			size_type size() const{
				return (this->_size);
			}
			size_type max_size() const{
				return (allocator_type().max_size());
			}

			/*ACCES AUX ELEMENTS*/

			mapped_type& operator[] (const key_type& k){
				return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
			}

			mapped_type& at (const key_type& k){
				return (operator[](k));
			}
			
			const mapped_type& at (const key_type& k) const{
				return (operator[](k));
			}

			/*MODIFIEURS*/


			ft::pair<iterator, bool>	insert(const value_type& data)
			{
				node_type **dst = &_tree->_root;
				node_type *parent = NULL;

				while (*dst != _tree->_leaf)	{
					
					parent = *dst;
					if (_comp(data.first, (*dst)->_data->first))
						dst = &(*dst)->_left;
					else if (_comp((*dst)->_data->first, data.first))
						dst = &(*dst)->_right;
					else
						return ft::make_pair(iterator(*dst), false);
				}

				value_type *new_data = _allocator.allocate(1);
				_allocator.construct(new_data, data);
				node_type *new_node = _node_allocator.allocate(1);
				_node_allocator.construct(new_node, node_type(new_data, *_tree));

				_tree->insert(parent, *dst, new_node);

				_size++;
				return ft::make_pair(iterator(new_node), true);
			};

			iterator insert (iterator position, const value_type& data){
				(void)position;
				return(insert(data).first);
			}

			template <class InputIterator>
			void insert (typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)	{
				for (; first != last; first++)
					insert(*first);
			}

			void erase (iterator position){
				node_type *node = position.getNode();
				this->_tree->EraseNode(node);
				_allocator.destroy(node->_data);
				_allocator.deallocate(node->_data,1);
				_node_allocator.destroy(node);
				_node_allocator.deallocate(node,1);
			}
			size_type erase (const key_type& k){
				node_type *node = this->find_node(k);
				if (node == this->_tree->_leaf)
					return (0);
				erase(iterator(node));
				return (1);
			}
			void erase (iterator first, iterator last){
				iterator del = first;
				while (del != last)
					erase(del++);
			}

			void clear(){
				erase(begin(), end());
			}

			void swap (map& x){
				ft::swap(this->_allocator, x._allocator);
				ft::swap(this->_comp, x._comp);
				ft::swap(this->_size, x._size);
				ft::swap(this->_tree, x._tree);
			}

			/*OBSERVEURS*/

			key_compare key_comp() const{
				return (_comp);
			}

			value_compare value_comp() const{
				return (value_compare(_comp));
			}

			/*OPERATIONS*/

			iterator find (const key_type& k){
				node_type *node = find_node(k);
				if (node == this->_tree->_leaf)
					return end();
				return (iterator(node));
			}
			const_iterator find (const key_type& k) const{
				node_type *node = find_node(k);
				if (node == this->_tree->_leaf)
					return end();
				return (const_iterator(node));
			}

			size_type count (const key_type& k) const{
				return (find_node(k) != this->_tree->_leaf);
			}

			// iterator lower_bound (const key_type& k);
			// const_iterator lower_bound (const key_type& k) const;
			// iterator upper_bound (const key_type& k);
			// const_iterator upper_bound (const key_type& k) const;
			// pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
			// pair<iterator,iterator>equal_range (const key_type& k);

			/*ALLOCATOR*/

			allocator_type get_allocator() const{
				return (this->_allocator);
			}

			/*AUTRE*/

		private:
			
			node_type *find_node(const key_type& k) const{
				node_type	*node =this->_tree->_root;
				while (node != this->_tree->_leaf)	{
					if (_comp(node->_data->first, k))
						node = node->_right;
					else if (_comp(k, node->_data->first))
						node = node->_left;
					else
						return node;
				}
				return (node);
			}
	};
	template <class Key, class T>
	bool operator!=(const map<Key, T>lhs, const map<Key, T>rhs){
		return !(rhs == lhs);
	}
	template <class Key, class T>
	bool operator<=(const map<Key, T>lhs, const map<Key, T>rhs){
		return !(rhs < lhs);
	}
	template <class Key, class T>
	bool operator>=(const map<Key, T>lhs, const map<Key, T>rhs){
		return !(lhs < rhs);
	}
	template <class Key, class T>
	bool operator>(const map<Key, T>lhs, const map<Key, T>rhs){
		return (rhs < lhs);
	}
	template<class Key, class T>
	void swap (map<Key, T>& x, map<Key, T>& y)
	{
		x.swap(y);
	};
}

#endif