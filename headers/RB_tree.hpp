#ifndef RB_TREE_HPP
# define RB_TREE_HPP

#include "utils.hpp"
#include "RB_node.hpp"
#include <memory>
#include <iostream>

# define RED 1
# define BLACK 0

namespace ft
{
	template<typename T>
	struct RB_node;

	template <typename T>
	struct RB_tree
	{
		public:
			typedef T						value_type;
			typedef RB_node<value_type>		node_type;


			node_type						*root;
			node_type						*leaf;

		RB_tree()
		{
			this->leaf = new node_type(NULL, *this);
			leaf->color = BLACK;
			leaf->_left = NULL;
			leaf->_right = NULL;
			leaf->leaf = leaf;
			this->root = leaf;
		};

		~RB_tree(){
			delete this->leaf;
		};

		node_type	*maximum()	const	{
			return (root->maximum());
		};
		node_type	*minimum()	const	{
			return (root->minimum());
		};

		void	insert(node_type *parent, node_type *&side_ref, node_type *n)
		{
			side_ref = n;

			n->parent = parent;
			n->_left = leaf;
			n->_right = leaf;
			n->color = RED;
			insertFix(n);

			root = n->root();
		};

		void	delete_node(node_type *z)
		{
			node_type	*x;
			node_type	*y = z;
			int y_init_color = y->color;

			if (z->_left == leaf)
			{
				x = z->_right;
				node_swap(z, x);
			}
			else if (z->_right == leaf)
			{
			x = z->_left;
			node_swap(z, x);
			}
			else
			{
				y = z->_right->minimum();
				y_init_color = y->color;
				x = y->_right;
				if (y->parent == z)
					x->parent = y;
				else
				{
					node_swap(y, y->_right);
					y->_right = z->_right;
					y->_right->parent = y;
				}
				node_swap(z, y);
				y->_left = z->_left;
				y->_left->parent = y;
				y->color = z->color;
				if (y_init_color == BLACK)
					deleteFix(x);
			}
		};
		
		private :

		void	node_swap(node_type *u, node_type *v)
		{
			if (u->parent == NULL) {
				root = v;
			}
			else if (u == u->parent->_left) {
				u->parent->_left = v;
			}
			else {
				u->parent->_right = v;
			}
			v->parent = u->parent;
		};

		void transplant(node_type *u, node_type *v) {
			if (u->parent == NULL) {
				root = v;
			}
			else if (u == u->parent->_left) {
				u->parent->_left = v;
			}
			else {
				u->parent->_right = v;
			}
			v->parent = u->parent;
		}

		void	leftRotate(node_type *x)
		{

			node_type* y = x->_right;
			x->_right = y->_left;
			if (y->_left != leaf)
				y->_left->parent = x;

			transplant(x, y);

			y->_left = x;
			x->parent = y;
		};

		void	rightRotate(node_type *x)
		{
			node_type* y = x->_left;

			x->_left = y->_right;
			if (y->_right != leaf)
				y->_right->parent = x;

			transplant(x, y);

			y->_right = x;
			x->parent = y;

		};



		void	insertFix(node_type *x)
		{	
			if (x->parent == NULL)
				x->color = BLACK;
			else if (x->parent->color == BLACK) 
				return ;
			else if (x->uncle() != leaf && x->uncle()->color == RED)	{
				x->parent->color = BLACK;
				x->uncle()->color = BLACK;
				
				node_type *g = x->grandparent();
				g->color = RED;
				insertFix(g);
			}
			else	{
				node_type *g = x->grandparent();

				if (g->_left != leaf && x == g->_left->_right) {
					leftRotate(x->parent);
					x = x->_left;
				}
				else if (g->_right != leaf && x == g->_right->_left) {
					rightRotate(x->parent);
					x = x->_right; 
				}

				node_type *p = x->parent;
				node_type *gr = x->grandparent();

				if (x == p->_left)
					rightRotate(gr);
				else
					leftRotate(gr);
				
				p->color = BLACK;
				gr->color = RED;
			}
		};

		void	deleteFix(node_type *x)
		{
			node_type *s;
			while (x != root && x->color == BLACK) {
				if (x == x->parent->_left) {
					s = x->parent->_right;
					if (s->color == RED) {
						s->color = BLACK;
						x->parent->color = RED;
						leftRotate(x->parent);
						s = x->parent->_right;
					}
					if (s == leaf)
						return;
					
					if (s->_left->color == BLACK && s->_right->color == BLACK) {
						s->color = RED;
						x = x->parent;
					} else {
						if (s->_right->color == BLACK) {
							s->_left->color = BLACK;
							s->color = RED;
							rightRotate(s);
							s = x->parent->_right;
						}

						s->color = x->parent->color;
						x->parent->color = BLACK;
						s->_right->color = BLACK;
						leftRotate(x->parent);
						x = root;
					}
				
				} else {
					s = x->parent->_left;
					if (s->color == RED) {
						s->color = BLACK;
						x->parent->color = RED;
						rightRotate(x->parent);
						s = x->parent->_left;
					}
					if (s == leaf)
						return;

					if (s->_right->color == BLACK && s->_right->color == BLACK) {
						s->color = RED;
						x = x->parent;
					} else {
						if (s->_left->color == BLACK) {
							s->_right->color = BLACK;
							s->color = RED;
							leftRotate(s);
							s = x->parent->_left;
						}

						s->color = x->parent->color;
						x->parent->color = BLACK;
						s->_left->color = BLACK;
						rightRotate(x->parent);
						x = root;
					}
				}
			}
			x->color = BLACK;
		};
	};
}


#endif