#ifndef MAP_HPP
# define MAP_HPP


# include "iterator_traits.hpp"
# include "map_iterator.hpp"
# include "reverse_iterator.hpp"
# include "RB_tree.hpp"
# include "pair.hpp"
# include "utils.hpp"
# include "equal.hpp"
# include "enable_if.hpp"
# include <limits>
# include <iostream>
# include <memory>

namespace ft
{

template<typename T>
struct RB_node;

// template <typename T>
// struct RBtree;

template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<pair<const Key, T> >
	>
class map
{
	public:

	typedef	Key													key_type;
	typedef	T													mapped_type;
	typedef	ft::pair<const key_type, mapped_type>				value_type;
	typedef	size_t												size_type;
	typedef Compare												key_compare;

	typedef				Allocator								allocator_type;
	typedef	typename	allocator_type::reference				reference;
	typedef	typename	allocator_type::const_reference			const_reference;
	typedef	typename	allocator_type::pointer					pointer;
	typedef	typename	allocator_type::const_pointer			const_pointer;


	typedef 			ft::map_iterator<0, value_type>			iterator;
	typedef				ft::map_iterator<1, value_type>			const_iterator;
	typedef 			ft::reverse_iterator<iterator>			reverse_iterator;
	typedef 			ft::reverse_iterator<const_iterator>	const_reverse_iterator;
	typedef typename iterator_traits<iterator>::difference_type	difference_type;

	typedef				ft::RB_node<value_type>					node_type;
	typedef				ft::RB_tree<value_type>					tree_type;


	class value_compare
	{
		friend class map;
	protected:
		key_compare comp;
		value_compare (key_compare c) : comp(c) {}
	public:
		typedef bool result_type;
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;
		bool operator() (const value_type& x, const value_type& y) const
		{
			return comp(x.first, y.first);
		}
	};

	private:
	tree_type					*tree;
	allocator_type				_allocator;
	size_type					_size;
	key_compare					comp;
	std::allocator<node_type>	_node_allocator;



	public:

	explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
	: tree(new tree_type()), _allocator(alloc), _size(0) , comp(comp)
	{};
			  
	template <class InputIterator>
	map(InputIterator first, InputIterator last,
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type())
	: tree(new tree_type()), _allocator(alloc), _size(0) , comp(comp)
	{
		insert(first, last);
	};
		
	map(const map& x)	
	: tree(new tree_type()), _allocator(x._allocator), _size(0) , comp(x.comp)
	{
		insert(x.begin(), x.end());
	};

	virtual ~map()
	{
		clear();
		delete this->tree;
	};

	map& operator=(const map& x)
	{
		clear();
		_size = 0;
		this->_allocator = x._allocator;
		comp = x.comp;
		insert(x.begin(), x.end());
		return *this;
	};

T& at( const Key& key )
{
	return (operator[](key));
};
const T& at( const Key& key ) const
{
	return (operator[](key));
};


mapped_type& operator[] (const key_type& k)	{
		return (*((insert(ft::make_pair(k, mapped_type()))).first)).second;
	}

	iterator begin()	{
		return iterator(this->tree->minimum());
	};
	const_iterator begin() const	{
		return const_iterator(this->tree->minimum());
	};
	iterator end()	{
		return iterator(this->tree->leaf);
	};
	const_iterator end() const	{
		return const_iterator(this->tree->leaf);
	};
	reverse_iterator rbegin()	{
		return reverse_iterator(this->tree->leaf);
	};
	const_reverse_iterator rbegin() const	{
		return const_reverse_iterator(this->tree->leaf);
	};
	reverse_iterator rend()	{
		return reverse_iterator(this->tree->minimum());
	};
	const_reverse_iterator rend() const	{
		return const_reverse_iterator(this->tree->minimum());
	};


	bool empty() const
	{
		return (_size == 0);
	};

	size_type size() const
	{
		return (_size);
	};

	size_type max_size() const
	{
		try	{
			return this->_allocator.max_size();
		}
		catch(const std::exception& e)	{
			std::cerr << e.what() << '\n';
		}
		return (-1);
	};


	void erase (iterator position)
	{
		node_type	*del = position.node();
		this->tree->delete_node(del);

		this->_allocator.destroy(del->value);
		this->_allocator.deallocate(del->value, 1);
		this->_node_allocator.destroy(del);
		this->_node_allocator.deallocate(del, 1);
		_size--;
	};
	
	size_type erase (const key_type& k)
	{
		node_type *node = get_node(k);
		if (node ==this->tree->leaf)
			return 0;
		erase(iterator(node));
		return 1;
	};

	void erase (iterator first, iterator last)
	{
		iterator tmp = first;

		while (tmp != last)	{
			erase(tmp++);
		}		
	};

	void clear()
	{	erase(begin(), end());	};

	ft::pair<iterator, bool>	insert(const value_type& val)
	{
		node_type **dst = &tree->root;
		node_type *parent = NULL;

		while (*dst != tree->leaf)	{
			
			parent = *dst;
			if (comp(val.first, (*dst)->value->first))
				dst = &(*dst)->leftChild;
			else if (comp((*dst)->value->first, val.first))
				dst = &(*dst)->rightChild;
			else
				return ft::make_pair(iterator(*dst), false);
		}

		value_type *new_val = _allocator.allocate(1);
		_allocator.construct(new_val, val);
		node_type *new_node = _node_allocator.allocate(1);
		_node_allocator.construct(new_node, node_type(new_val, *tree));

		tree->insert(parent, *dst, new_node);

		_size++;
		return ft::make_pair(iterator(new_node), true);
	};

	iterator insert (iterator position, const value_type& val)	{
		(void) position;
		return insert(val).first;
	}
	
	template <class InputIterator>
	void insert (typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)	{
		for (; first != last; first++)
			insert(*first);
	}

	void swap (map& x)
	{
		ft::swap(this->_size, x._size);
		ft::swap(this->tree, x.tree);
		ft::swap(this->_allocator, x._allocator);
		ft::swap(this->comp, x.comp);
	};

	key_compare key_comp() const	{
		return comp;
	}

	value_compare	value_comp() const	{
		return value_compare(comp);
	}

	allocator_type	get_allocator() const	{
		return this->_allocator;
	}

	iterator find (const key_type& k)	{
		node_type	*node = get_node(k);
		if (node ==this->tree->leaf)
			return end();
		return iterator(node);
	}
	const_iterator find (const key_type& k) const	{
		node_type	*node = get_node(k);
		if (node ==this->tree->leaf)
			return end();
		return const_iterator(node);
	}
	
	size_type count (const key_type& k) const	{
		node_type	*node = get_node(k);
		if (node ==this->tree->leaf)
			return 0;
		return 1;
	}

	iterator 	lower_bound(const key_type& k)	{
		pair<node_type*, node_type*> res = get_node_parent(k);
		if (res.first !=this->tree->leaf)
			return iterator(res.first);
		if (res.second == NULL)
			return end();
		if (!comp(res.second->value->first, k))
			return iterator(res.second);
		return ++iterator(res.second);
	}
	const_iterator lower_bound(const key_type& k) const	{
		pair<node_type*, node_type*> res = get_node_parent(k);
		if (res.first !=this->tree->leaf)
			return const_iterator(res.first);
		if (res.second == NULL)
			return end();
		if (!comp(res.second->value->first, k))
			return const_iterator(res.second);
		return ++const_iterator(res.second);
	}

	iterator upper_bound (const key_type& k)	{
		pair<node_type*, node_type*> res = get_node_parent(k);
		if (res.first !=this->tree->leaf)
			return ++iterator(res.first);
		if (res.second == NULL)
			return end();
		if (comp(k, res.second->value->first))
			return iterator(res.second);
		return ++iterator(res.second);
	}
	const_iterator upper_bound (const key_type& k) const	{
		pair<node_type*, node_type*> res = get_node_parent(k);
		if (res.first !=this->tree->leaf)
			return const_iterator(res.first->successor());
		if (res.second == NULL)
			return end();
		if (comp(k, res.second->value->first))
			return const_iterator(res.second);
		return ++const_iterator(res.second);
	}

	pair<const_iterator,const_iterator> equal_range (const key_type& k) const	{
		return ft::make_pair(lower_bound(k), upper_bound(k));
	}
	pair<iterator,iterator>             equal_range (const key_type& k)
	{
		return ft::make_pair(lower_bound(k), upper_bound(k));	};


	friend
	bool operator== (const map& lhs, const map& rhs)	{
		if (lhs._size != rhs._size)
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	
	friend
	bool operator<  (const map& lhs, const map& rhs)	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	


	private:

	node_type *get_node(const key_type& key) const	{
		node_type	*n =this->tree->root;

		while (n !=this->tree->leaf)	{
			if (comp(n->value->first, key))
				n = n->rightChild;
			else if (comp(key, n->value->first))
				n = n->leftChild;
			else
				return n;
		}
		return (n);
	}

	pair<node_type*, node_type*>	get_node_parent(const key_type& key) const
	{
		node_type	*n = this->tree->root;
		node_type	*parent = NULL;
	
		while (n != this->tree->leaf)	{
			if (comp(n->value->first, key))	{
				parent = n;
				n = n->rightChild;
			}
			else if (comp(key, n->value->first))	{
				parent = n;
				n = n->leftChild;
			}
			else
				return (ft::make_pair(n, parent));
		}
		return (ft::make_pair(n, parent));
	};





};

template <class Key, class T>
void swap (map<Key, T>& x, map<Key, T> &y)	{
	x.swap(y);
}

	template <class Key, class T>
	bool operator<= (const map<Key, T>& lhs, const map<Key, T>& rhs)	{
		return !(rhs < lhs);
	}

	template <class Key, class T>
	bool operator>  (const map<Key, T>& lhs, const map<Key, T>& rhs)	{
		return rhs < lhs;
	}

	template <class Key, class T>
	bool operator>= (const map<Key, T>& lhs, const map<Key, T>& rhs)	{
		return !(lhs < rhs);
	}

	template <class Key, class T>
	bool operator!= (const map<Key, T>& lhs, const map<Key, T>& rhs)	{
		return !(lhs == rhs);
	}

}



#endif