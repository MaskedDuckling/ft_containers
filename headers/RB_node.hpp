#ifndef RB_NODE_HPP
# define RB_NODE_HPP

# include "RB_tree.hpp"
# include "utils.hpp"
# include <memory>

# define RED 1
# define BLACK 0

namespace ft{

	template <typename T>
	struct RB_tree;

	template <typename T>
	struct RB_node
	{
		typedef T		value_type;

		value_type		*value;
		int				color;
		RB_node			*parent;
		RB_node			*_left;
		RB_node			*_right;
		RB_node			**root_ptr;
		RB_node			*leaf;


		RB_node(value_type *val, RB_tree<value_type> &tree) :
			value(val),
			color(RED),
			parent(NULL),
			_left(tree.leaf),
			_right(tree.leaf),
			root_ptr(&tree.root),
			leaf(tree.leaf)
		{};

		~RB_node() {};

		RB_node	*grandparent()
		{
			if (!parent)
				return (NULL);
			return (this->parent->parent);
		};

		RB_node	*sibling()
		{
			if (!this->parent)
				return (NULL);
			if (this == this->parent->_left)
				return (this->parent->_right);
			return (this->parent->_left);
		};

		RB_node *uncle()
		{
			RB_node *gp = this->grandparent();

			if (!gp)
				return (NULL);
			return (this->parent->sibling());
		};

		RB_node	*maximum()
		{
			if (this == leaf)
				return (this);
			if (this->_right != leaf)
				return (this->_right->maximum());
			return (this);
		}

		RB_node	*minimum()
		{
			if (this == leaf)
				return (this);
			if (this->_left != leaf)
				return (this->_left->minimum());
			return (this);
		}

		RB_node	*root()
		{
			if (!this->parent)
				return(this);
			return (this->parent->root());
		};

		RB_node	*successor()
		{
			if (this == leaf)
				return ((*root_ptr)->minimum());
			if (this->_right != leaf)
				return (this->_right->minimum());
			RB_node	*tmp = this;
			while (tmp->parent && tmp == tmp->parent->_right)
				tmp = tmp->parent;
			if (!tmp->parent)
				return (tmp->leaf);
			return (tmp->parent);
		};

		RB_node	*predecessor()
		{
			if (this == leaf)
				return ((*root_ptr)->maximum());
			if (this->_left != leaf)
				return (this->_left->maximum());
			RB_node	*tmp = this;
			while (tmp->parent && tmp == tmp->parent->_left)
				tmp = tmp->parent;
			if (!tmp->parent)
				return (tmp->leaf);
			return (tmp->parent);
		};

	};
}


#endif