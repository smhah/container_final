/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 07:47:27 by smhah             #+#    #+#             */
/*   Updated: 2022/06/10 04:35:43 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "iterator.hpp"

namespace ft{
    template <class Node, class T, class comp>
        class map_iter : public ft::iterator<std::bidirectional_iterator_tag, T>
        {
            private:
                Node *_p;
                Node *_root;
                Node *_end;

                Node * minValueNode(Node* node)
                {
                    Node* current = node;
                
                    /* loop down to find the rightmost leaf */
                    while (current && current->left != NULL)
                        current = current->left;
                
                    return current;
                }
				
                Node * maxValueNode(Node* node)
                {
                    Node* current = node;
                
                    /* loop down to find the leftmost leaf */
                    while (current && current->right != NULL)
                        current = current->right;
                
                    return current;
                }
				
                Node * minValueNode(Node* node) const
                {
                    Node* current = node;
                
                    /* loop down to find the rightmost leaf */
                    while (current && current->left != NULL)
                        current = current->left;
                
                    return current;
                }
				
                Node * maxValueNode(Node* node) const
                {
                    Node* current = node;
                
                    /* loop down to find the leftmost leaf */
                    while (current && current->right != NULL)
                        current = current->right;
                
                    return current;
                }           
            public :
            
            map_iter(){
                _p = NULL;
                _end = NULL;
            }
            map_iter(Node *node, Node *root){
                _p = node;
                _root = root;
                _end = NULL;
            }
             map_iter(Node *node, Node *root, Node* end){
                _p = node;
                _root = root;
                _end = end;
            }
            map_iter(const map_iter& copy)
            {
                *this = copy;
            }
            map_iter&   operator=(const map_iter& rhs)
            {
                _p = rhs._p;
                _root = rhs._root;
                _end = rhs._end;
                return (*this);
            }
            ~map_iter(){}
            // T		&operator*() const {
			// 	return (_p->content);
			// }
            // T *			operator->() const {	return &operator*();	}
            T* operator->() const{ return (_p->content);}
            T& operator*() const{ return (*_p->content);}
            map_iter& operator--()
            {
                Node *n = _p;
                if (_p == NULL && _end)
                {
                    _p = _end;
                    _end = NULL;
                    return (*this);
                }               
                if (n->left != NULL)
                    _p = maxValueNode(n->left);
                else if (n->left == NULL)
                {
                    Node* p = n->parent;
                    while (p != NULL && n == p->left)
                    {
                        n = p;
                        p = p->parent;
                    }
                    _p = p;
                }
                return (*this);
            }
			
            Node *getNode() const
            {
                return _p;
            }
            
            
            map_iter& operator++()
            {
                Node *n = _p;
                Node *max = maxValueNode(_root);
	
                if (_p == max)
                {    _p = NULL;
                    _end = _p;
                    return *this;
                }
                if (n->right != NULL)
                    _p = minValueNode(n->right);
                else if (n->right == NULL)
                {   
                    Node* p = n->parent;
                    while (p != NULL && n == p->right)
                    {
                        n = p;
                        p = p->parent;
                        
                    }
                    _p = p;
                }

                return (*this);
            }

            map_iter operator++(int)
            {
                map_iter tmp(*this);
                this->operator++();
                return (tmp);
            }

            map_iter operator--(int)
            {
                map_iter tmp(*this);
                this->operator--();
                return (tmp);
            }

            operator map_iter<Node, const T,comp>() const{return map_iter<Node, const T,comp>(_p, _root, _end);}
            friend bool	operator==(map_iter const& lhs, map_iter const& rhs) { return (lhs._p == rhs._p); }
            friend bool	operator!=(map_iter const& lhs, map_iter const& rhs) { return (lhs._p != rhs._p); }
        };
}
