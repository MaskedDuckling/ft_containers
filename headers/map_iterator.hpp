#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP


#include "iterator_traits.hpp"
#include "RB_node.hpp"
# include "utils.hpp"

namespace ft
{

template <bool isConst, class T>
class map_iterator
{
public :
	typedef	std::ptrdiff_t										difference_type;
	typedef typename choose<isConst, const T, T>::type			value_type;
	typedef	RB_node<value_type>									node_type;
	typedef value_type*											pointer;
	typedef value_type&											reference;
	typedef std::bidirectional_iterator_tag						iterator_category;


private:
	node_type	*_node;

public:
	map_iterator() : _node(NULL)	{};
	map_iterator(void *node) : _node(static_cast<node_type*>(node))	{};
	map_iterator(const map_iterator &rhs) : _node(rhs._node)	{};
	~map_iterator() {};

	operator map_iterator<true, T> () const {return (map_iterator<true, T>(this->_node)); };

map_iterator &operator=(const map_iterator *rhs)
{
	this->_node = rhs->_node;
	return (*this);
};

map_iterator	&operator++()
{
	this->_node = this->_node->successor();
	return (*this);
}

map_iterator	operator++(int)
{
	map_iterator	it(*this);
	++(*this);
	return (it);
}

map_iterator	&operator--()
{
	this->_node = this->_node->predecessor();

	return (*this);
}

map_iterator	operator--(int)
{
	map_iterator	it(*this);
	--(*this);
	return (it);
}

reference	operator*() const
{	return *this->_node->value;	};

pointer		operator->() const
{	return this->_node->value;	};


friend
bool	operator==(const map_iterator &lhs, const map_iterator &rhs)
{	return (lhs._node == rhs._node);	};

friend
bool	operator!=(const map_iterator &lhs, const map_iterator &rhs)
{	return (lhs._node != rhs._node);	};

node_type	*node()	const
{	return this->_node;	};

};




}



#endif