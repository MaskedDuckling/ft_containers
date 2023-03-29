#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <iostream>
#include <stddef.h>
#include <memory>
#include "RBnode.hpp"
#include "pair.hpp"

namespace ft{
    template<class T>
    class RBtree {
         public:
            typedef T						value_type;
            typedef Node<value_type>		node_type;

            node_type                       *_leaf;
            node_type						*_root;

            std::allocator<node_type>	_node_allocator;

            RBtree()
            {
                // value_type *t;
                _leaf = new node_type(0, *this);
                _root=_leaf;
                this->_leaf->_color = BLACK;
            }

            ~RBtree(){
                Destroy(_root);
                delete this->_leaf; 
            }

            /**/

             node_type *InsertNode(value_type newdata){
                node_type *n = new node_type(newdata, *this);
                node_type *x = this->_root;
                node_type *y = NULL;
                while (x != _leaf) {
                    y = x;
                    if (n->_data < x->_data) {
                        x = x->_left;
                    } else {
                        x = x->_right;
                    }
                }
                n->_parent = y;
                if (!y) {
                    _root = n;
                    n->_color = BLACK;
                    return (NULL);
                } else if (n->_data < y->_data) {
                    y->_left = n;
                } else {
                    y->_right = n;
                }
                if (!n->_parent->_parent) {
                    return (NULL);
                }
                insertFix(n);
                return (n);
            }

            void	insert(node_type *parent, node_type *&side_ref, node_type *n)
            {
                side_ref = n;

                n->_parent = parent;
                n->_left = _leaf;
                n->_right = _leaf;
                n->_color = RED;
                insertFix(n);

                _root = n->root();
            };


            void insertFix(node_type *k){
                node_type *u;
                if (k->_parent == NULL){
			        k->_color = BLACK;
                    return ;
                }
                while (k->_parent->_color == 1) {
                    if (k->_parent == k->_parent->_parent->_right) {
                        u = k->_parent->_parent->_left;
                        if (u->_color == 1) {
                            u->_color = 0;
                            k->_parent->_color = 0;
                            k->_parent->_parent->_color = 1;
                            k = k->_parent->_parent;
                        } else {
                            if (k == k->_parent->_left) {
                                k = k->_parent;
                                right_rotation(k);
                            }
                            k->_parent->_color = 0;
                            k->_parent->_parent->_color = 1;
                            left_rotation(k->_parent->_parent);
                        }
                    } else {
                        u = k->_parent->_parent->_right;

                        if (u->_color == 1) {
                            u->_color = 0;
                            k->_parent->_color = 0;
                            k->_parent->_parent->_color = 1;
                            k = k->_parent->_parent;	
                        } else {
                            if (k == k->_parent->_right) {
                                k = k->_parent;
                                left_rotation(k);
                            }
                            k->_parent->_color = 0;
                            k->_parent->_parent->_color = 1;
                            right_rotation(k->_parent->_parent);
                        }
                    }
                    if (k == _root) {
                        break;
                    }
                }
                _root->_color = 0;
            }

            void EraseNode(node_type *tosupr){
                node_type *node = _root;
                node_type *del = NULL;
                node_type *x,*y;
                int ycolor;
                while (node != _leaf){
                    if (node->_data == tosupr->_data){
                        del = node;
                        break;
                    }
                    if (tosupr->_data < node->_data)
                        node = node->_left;
                    else if (tosupr->_data > node->_data)
                        node = node->_right;
                }
                if (del == _leaf)
                    return ;
                y=del;
                ycolor = y->_color;
                if (del->_right == _leaf){
                    x = del->_left;
                    changement(del, del->_left);
                }else if (del->_left == _leaf){
                    x = del->_right;
                    changement(del, del->_right);
                }else {
                    y = minikeum(del->_right);
                    ycolor = y->_color;
                    x = y->_right;
                    if (y->_parent == del) {
                        x->_parent = y;
                    } else {
                        changement(y, y->_right);
                        y->_right = del->_right;
                        y->_right->_parent = y;
                    }
                    changement(del, y);
                    y->_left = del->_left;
                    y->_left->_parent = y;
                    y->_color = del->_color;
                }
                // delete del;
                if (ycolor == BLACK)
                    deleteFix(x);
                return ;
            }

            void deleteFix(node_type *node){
                node_type *s;
                while (node != _root && node->_color == BLACK){
                    if (node == node->_parent->_left){
                        s = node->_parent->_right;
                        if (s->_color == RED){
                            s->_color = BLACK; // case 3.1
                            node->_parent->_color = RED; // case 3.1
                            left_rotation(node->_parent); // case 3.1
                            s = node->_parent->_right; // case 3.1
                        }
                        if (s->_left->_color == BLACK && s->_right->_color == BLACK){
                            s->_color = RED; // case 3.2
                            node = node->_parent; //case 3.2
                        }
                        else{
                            if (s->_right->_color == BLACK){
                                s->_left->_color = BLACK; // case 3.3
                                s->_color = RED; //case 3.3
                                right_rotation(s); // case 3.3
                                s = node->_parent->_right; // case 3.3
                            }
                            s->_color = node->_parent->_right->_color; // case 3.4
                            node->_parent->_color = BLACK; // case 3.4
                            s->_right->_color = BLACK; // case 3.4
                            left_rotation(node->_parent); // case 3.4
                            node = _root;
                        }
                    }
                    else{
                        s = node->_parent->_left;
                        if (s->_color == RED){
                            s->_color = BLACK; // case 3.1
                            node->_parent->_color = RED; // case 3.1
                            right_rotation(node->_parent); // case 3.1
                            s = node->_parent->_left; // case 3.1
                        }
                        if (s->_right->_color == BLACK && s->_left->_color == BLACK){
                            s->_color = RED; // case 3.2
                            node = node->_parent; //case 3.2
                        }
                        else{
                            if (s->_left->_color == BLACK){
                                s->_right->_color = BLACK; // case 3.3
                                s->_color = RED; //case 3.3
                                left_rotation(s); // case 3.3
                                s = node->_parent->_left; // case 3.3
                            }
                            s->_color = node->_parent->_left->_color; // case 3.4
                            node->_parent->_color = BLACK; // case 3.4
                            s->_right->_color = BLACK; // case 3.4
                            right_rotation(node->_parent); // case 3.4
                            node = _root;
                        }
                    }
                }
                node->_color = BLACK;
                return;
            }

            void left_rotation(node_type *x){
                node_type *y = x->_right;
                x->_right = y->_left;
                if (y->_left != _leaf){
                    y->_left->_parent = x;
                }
                y->_parent = x->_parent;
                if (!x->_parent)
			        this->_root = y;
                else if (x == x->_parent->_left)
                    x->_parent->_left = y;
                else
                    x->_parent->_right = y;
                y->_left = x;
                x->_parent = y; 
            }
            void right_rotation(node_type *x){
                node_type *y = x->_left;
                x->_left = y->_right;
                if (y->_right != _leaf){
                    y->_right->_parent = x;
                }
                y->_parent = x->_parent;
                if (!x->_parent)
			        this->_root = y;
                else if (x == x->_parent->_right)
                    x->_parent->_right = y;
                else
                    x->_parent->_left = y;
                y->_right = x;
                x->_parent = y; 
            }


            node_type *minikeum(node_type *node){
                while (node->_left != _leaf)
                    node = node->_left;
                return (node);
            }
             node_type	*maximum()	const{	
                return (_root->maximum());
            };
	        node_type	*minimum()	const{	
                return (_root->minimum());
            };

            void affichage(node_type *recur, int depth){
                if (recur == _leaf)
                    return ;
                else{
                    affichage(recur->_left, depth + 1);
                    for (int k = depth; k > 0; k--)
                        std::cout << "       ";
                    if (recur->_parent && recur == recur->_parent->_left){
                        std::cout << "/";
                    }else if (recur->_parent && recur == recur->_parent->_right){
                        std::cout << "\\";
                    }
                    std::cout << "{" << *recur->_data << " color = "<< (recur->_color < 1 ? "Black" : "Red") << "}" << std::endl;

                    affichage(recur->_right, depth + 1);
                }
            }

            void changement(node_type *u, node_type *v){
                if (!(u->_parent)) {
                    _root = v;
                } else if (u == u->_parent->_left){
                    u->_parent->_left = v;
                } else {
                    u->_parent->_right = v;
                }
                v->_parent = u->_parent;
            }

            void Destroy(node_type *recur){
                if (recur == _leaf)
                    return ;
                else{
                    Destroy(recur->_left);
                    Destroy(recur->_right);
                    delete recur;
                }
            }

            int profondeur(node_type *recur){
                if (recur == _leaf)
                    return (0);
                else{
                    int b = profondeur(recur->_left);
                    int c = profondeur(recur->_right);
                    return 1 + ((b > c)? b : c);
                }
            }
        };
}

#endif