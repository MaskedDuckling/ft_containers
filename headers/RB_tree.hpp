#ifndef RB_TREE_HPP
# define RB_TREE_HPP


# include "utils.hpp"
#include "RB_node.hpp"
#include <memory>
#include <iostream>

namespace ft
{



template<typename T>
struct RB_node;

template <
typename T
>
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
		leaf->leftChild = NULL;
		leaf->rightChild = NULL;
		leaf->leaf = leaf;
		this->root = leaf;
	};

	~RB_tree()
	{	delete this->leaf;	};

	node_type	*maximum()	const	{	return (root->maximum());	};
	node_type	*minimum()		const	{	return (root->minimum());	};

	void	insert(node_type *parent, node_type *&side_ref, node_type *n)
	{
		side_ref = n;

		n->parent = parent;
		n->leftChild = leaf;
		n->rightChild = leaf;
		n->color = RED;
		insertFix(n);

		root = n->root();
	};

	void	delete_node(node_type *z)
	{
		node_type	*x;
		node_type	*y = z;
		int y_init_color = y->color;

		if (z->leftChild == leaf)
		{
			x = z->rightChild;
			node_swap(z, x);
		}
		else if (z->rightChild == leaf)
		{
		x = z->leftChild;
		node_swap(z, x);
		}
		else
		{
			y = z->rightChild->minimum();
			y_init_color = y->color;
			x = y->rightChild;
			if (y->parent == z)
				x->parent = y;
			else
			{
				node_swap(y, y->rightChild);
				y->rightChild = z->rightChild;
				y->rightChild->parent = y;
			}
			node_swap(z, y);
			y->leftChild = z->leftChild;
			y->leftChild->parent = y;
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
		else if (u == u->parent->leftChild) {
			u->parent->leftChild = v;
		}
		else {
			u->parent->rightChild = v;
		}
		v->parent = u->parent;
	};

	void transplant(node_type *u, node_type *v) {
		if (u->parent == NULL) {
			root = v;
		}
		else if (u == u->parent->leftChild) {
			u->parent->leftChild = v;
		}
		else {
			u->parent->rightChild = v;
		}
		v->parent = u->parent;
	}

	void	leftRotate(node_type *x)
	{

		node_type* y = x->rightChild;
		x->rightChild = y->leftChild;
		if (y->leftChild != leaf)
			y->leftChild->parent = x;

		transplant(x, y);

		y->leftChild = x;
		x->parent = y;
	};

	void	rightRotate(node_type *x)
	{
		node_type* y = x->leftChild;

		x->leftChild = y->rightChild;
		if (y->rightChild != leaf)
			y->rightChild->parent = x;

		transplant(x, y);

		y->rightChild = x;
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

			if (g->leftChild != leaf && x == g->leftChild->rightChild) {
				leftRotate(x->parent);
				x = x->leftChild;
			}
			else if (g->rightChild != leaf && x == g->rightChild->leftChild) {
				rightRotate(x->parent);
				x = x->rightChild; 
			}

			node_type *p = x->parent;
			node_type *gr = x->grandparent();

			if (x == p->leftChild)
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
			if (x == x->parent->leftChild) {
				s = x->parent->rightChild;
				if (s->color == RED) {
					s->color = BLACK;
					x->parent->color = RED;
					leftRotate(x->parent);
					s = x->parent->rightChild;
				}
				if (s == leaf)
					return;
				
				if (s->leftChild->color == BLACK && s->rightChild->color == BLACK) {
					s->color = RED;
					x = x->parent;
				} else {
					if (s->rightChild->color == BLACK) {
						s->leftChild->color = BLACK;
						s->color = RED;
						rightRotate(s);
						s = x->parent->rightChild;
					}

					s->color = x->parent->color;
					x->parent->color = BLACK;
					s->rightChild->color = BLACK;
					leftRotate(x->parent);
					x = root;
				}
			
			} else {
				s = x->parent->leftChild;
				if (s->color == RED) {
					s->color = BLACK;
					x->parent->color = RED;
					rightRotate(x->parent);
					s = x->parent->leftChild;
				}
				if (s == leaf)
					return;

				if (s->rightChild->color == BLACK && s->rightChild->color == BLACK) {
					s->color = RED;
					x = x->parent;
				} else {
					if (s->leftChild->color == BLACK) {
						s->rightChild->color = BLACK;
						s->color = RED;
						leftRotate(s);
						s = x->parent->leftChild;
					}

					s->color = x->parent->color;
					x->parent->color = BLACK;
					s->leftChild->color = BLACK;
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