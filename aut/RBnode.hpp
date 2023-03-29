#ifndef RBNODE_HPP
# define RBNODE_HPP

#define RED 1
#define BLACK 0

namespace ft{
    template <typename T>
    class RBtree;
    
    template<class value_type>
    class Node {
        public:
            value_type  *_data; // holds the key
            int         _color; // 1 -> Red, 0 -> Black
            Node        *_parent; // pointer to the parent
            Node        *_left; // pointer to left child
            Node        *_right; // pointer to right child
            Node        *_leaf;
            Node        **_root;


            Node(value_type *val, RBtree<value_type> &tree) :
                _data(val),
                _color(RED),
                _parent(NULL),
                _left(tree._leaf),
                _right(tree._leaf),
                _leaf(tree._leaf),
                _root(&tree._root)
            {};

            Node	*successor(){
                if (this == _leaf)
                    return ((*_root)->minimum());
                if (this->_right != _leaf)
                    return (this->_right->minimum());
                Node	*tmp = this;
                while (tmp->_parent && tmp == tmp->_parent->_right)
                    tmp = tmp->_parent;
                if (!tmp->_parent)
                    return (tmp->_leaf);
                return (tmp->_parent);
            };

            Node	*predecessor(){
                if (this == _leaf)
                    return ((*_root)->maximum());
                if (this->_left != _leaf)
                    return (this->_left->maximum());
                Node	*tmp = this;
                while (tmp->_parent && tmp == tmp->_parent->_left)
                    tmp = tmp->_parent;
                if (!tmp->_parent)
                    return (tmp->_leaf);
                return (tmp->_parent);
            };

            Node	*maximum()
            {
                if (this == _leaf)
                    return (this);
                if (this->_right != _leaf)
                    return (this->_right->maximum());
                return (this);
            }

            Node	*minimum()
            {
                if (this == _leaf)
                    return (this);
                if (this->_left != _leaf)
                    return (this->_left->minimum());
                return (this);
            }

            Node	*root(){
                if (!this->_parent)
                    return(this);
                return (this->_parent->root());
            };

        
    };
}

#endif