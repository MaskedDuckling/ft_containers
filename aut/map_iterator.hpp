#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "utils.hpp"
#include "RB_tree.hpp"
#include "RB_node.hpp"

namespace ft{
	template <bool isConst, class T>
	class map_iterator{
		public:
			typedef typename choose<isConst, const T, T>::type	value_type;
			typedef value_type*									pointer;
			typedef value_type&									reference;
			typedef std::ptrdiff_t								difference_type;
			typedef std::random_access_iterator_tag				iterator_category;
			typedef ft::Node<value_type>						node_type;
		private :
			node_type *_node;
		public	:
			map_iterator() : _node(0){}
			map_iterator(void *node) : _node(static_cast<node_type *>(node)){}
			map_iterator(const map_iterator &rhs) : _node(rhs.getNode()){}
			~map_iterator(){}

			node_type *getNode() const { return this->_node; }

			map_iterator &operator=(const map_iterator & rhs){
				this->_node = rhs.getNode();
				return (*this);
			};

			map_iterator &operator++(){
				this->_node = this->_node->successor();
				return (*this);
			};
			map_iterator operator++(int){
				map_iterator tmp(*this);
				++(*this);
				return (tmp);
			};
			map_iterator &operator--(){
				this->_node = this->_node->predecessor();
				return (*this);
			};
			map_iterator operator--(int){
				map_iterator tmp(*this);
				--(*this);
				return (tmp);
			};

			pointer operator->()const{
				return (this->_node->_data);
			};
			reference operator*()const{
				return (*this->_node->_data);
			};

			friend
			bool	operator==(const map_iterator &lhs, const map_iterator &rhs){
				return (lhs._node == rhs._node);
			};
			friend
			bool	operator!=(const map_iterator &lhs, const map_iterator &rhs){
				return (lhs._node != rhs._node);
			};
	};
}

#endif