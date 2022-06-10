/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 22:44:26 by smhah             #+#    #+#             */
/*   Updated: 2022/06/10 05:41:38 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// C++ program to insert a node in AVL tree
//#include<bits/stdc++.h>
#include "ft_pair.hpp"
#include "map_iterator.hpp"
#include "vector.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
	template < class Key,                                     // map::key_type
			class T,                                       // map::mapped_type
			class Compare = std::less<Key>,                     // map::key_compare
			class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
			> class map
	{
		public:

		// struct Node
		// {
		// 	m_value_type content;
		// 	Node *left;
		// 	Node *right;
		// 	Node *parent;
		// 	int height;
		// };
		// typedef typename Alloc::template rebind<Node>::other aloc;
		
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const key_type,mapped_type> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef size_t	size_type;
		std::allocator<ft::pair<Key, T> > all;
	
		class value_compare
		{   // in C++98, it is required to inherit binary_function<m_value_type,m_value_type,bool>
			protected:
			Compare comp;
			public:
			value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};

		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _aln()
		{
			_size = 0;
			_al = alloc;
			_kc = comp;
			_root = NULL;
		}
		
		template <class InputIterator>
  		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _aln()
		{
			_root = NULL;
			_size = 0;
			_al = alloc;
			_kc = comp;
			insert(first, last);
		}

		map (const map& x) : _aln()
		{
			_size = 0;
			_root = NULL;
			const_iterator beg = x.begin();
			const_iterator end = x.end();
			while(beg != end)
			{
				insert(*beg);
				beg++;
			}
		}

		~map()
		{
        	clear();
        }

		map& operator= (const map& x)
		{
			if(_size != 0)
				clear();
			
			const_iterator beg = x.begin();
			const_iterator end = x.end();
			while(beg != end)
			{
				insert(*beg);
				beg++;
			}
			return(*this);
		}
		// An AVL tree node
		typedef ft::pair<key_type,mapped_type> m_value_type;

		struct Node
		{
			m_value_type *content;
			Node *left;
			Node *right;
			Node *parent;
			int height;
		};
		
		Node * get_root(void)
		{
			return (_root);
		}
		
		
		typedef typename ft::map_iter<Node, m_value_type,Compare> iterator;
		typedef typename ft::map_iter<Node, const m_value_type, Compare> const_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename ft::reverse_iterator<iterator> reverse_iterator;

		//typedef typename Alloc::template rebind<Node>::other aloc;
		typename Alloc::template rebind<Node>::other _aln;
		Node *_root;
		Node *last_inserted;
		Node *not_inserted;
	
		iterator begin()
		{
			return(iterator(minValueNode(_root), _root));
		}
		const_iterator begin() const
		{
			return (const_iterator(minValueNode(_root), _root));
		}
		//const_iterator begin() const;
		
		iterator end()
		{
			return(iterator(NULL, _root, maxValueNode(_root)));
		}
		
		const_iterator end() const
		{
			return(const_iterator(NULL, _root, maxValueNode(_root)));
		}
		
		reverse_iterator rend(){return(reverse_iterator(begin()));}
        const_reverse_iterator rend() const{return(const_reverse_iterator(begin()));}
        
        reverse_iterator rbegin(){return(reverse_iterator(end()));}
        const_reverse_iterator rbegin()const {return(const_reverse_iterator(end()));}

		void clear()
		{
			erase(begin(), end());
		}
		
		size_type count (const key_type& k) const
		{
			Node *p = _root;
			while(p != NULL)
			{
				if(_kc(p->content->first, k))
					p = p->right;
				else if (_kc(k, p->content->first))
					p = p->left;
				else
					return (1);
			}
			return (0);
		}

		Node *search(Node *node, const key_type & k) const
		{
			if (node == NULL)
                return NULL;
            if(_kc(k, node->content->first))
			{
                node = search(node->left, k);           
            }
			else if(_kc(node->content->first, k))
			{
                node = search(node->right, k);
            }
            return node;	
		}
		
		iterator find (const key_type & k)
		{
			return (iterator(search(_root, k), _root));
		}

		// const_iterator find (const key_type& k) const;
		size_type size() const
		{
			return _size;
		}
		
		bool empty() const
		{
			return(_size == 0);
		}

		key_compare key_comp() const
		{
			return (_kc);
		}

        allocator_type get_allocator() const
		{
			return _al;
		}
		
		Node *bound(Node *root, key_type k)
        {
            Node *current = root;
            Node *parent = root;

            while(current)
            {
                if(_kc(k, current->content->first))
                {
                    parent = current;
                    current = current->left;
                }
                else if (_kc(current->content->first, k))
                    current = current->right;
                else
                    return current;
            }
            return parent;
        }

		Node *bound(Node *root, key_type k) const
        {
            Node *current = root;
            Node *parent = root;

            while(current)
            {
                if(_kc(k, current->content->first))
                {
                    parent = current;
                    current = current->left;
                }
                else if (_kc(current->content->first, k))
                    current = current->right;
                else
                    return current;
            }
            return parent;
        }
		
		iterator lower_bound (const key_type& k)
		{
			return (iterator(bound(_root, k), _root));
		}

		const_iterator lower_bound (const key_type& k) const
		{
			return (const_iterator(bound(_root, k), _root));
		}

		iterator upper_bound (const key_type& k)
        {
            Node *n = bound(_root, k);
            iterator it = iterator(n, _root);
            if(it != end() && !_kc(n->content->first,k) && !_kc(k, n->content->first))
                return(++it);
            return(it);
        }
	
		const_iterator upper_bound (const key_type& k) const
        {
            Node *n = bound(_root, k);
            iterator it = iterator(n, _root);
            if(it != end() && !_kc(n->content->first,k) && !_kc(k, n->content->first))
                return(++it);
            return(it);
        }
		
		pair<const_iterator,const_iterator> equal_range (const key_type& k) const
        {
            return (ft::make_pair(lower_bound(k), upper_bound(k)));
        }
		
        pair<iterator,iterator> equal_range (const key_type& k)
        {
            return (ft::make_pair(lower_bound(k), upper_bound(k)));
        }
	
		value_compare value_comp() const
        {
            return (value_compare(_kc));
        }

		void swap (map& x)
        {
            std::swap(_size, x._size);
            std::swap(_root, x._root);
            std::swap(_kc, x._kc);
        }
		// A utility function to get the
		// height of the tree
		// template<class Key, class T>
		int height(Node*  N)
		{
			if (N == NULL)
				return 0;
			return N->height;
		}

		// A utility function to get maximum
		// of two integers
		int max(int a, int b)
		{
			return (a > b)? a : b;
		}

		/* Helper function that allocates a
		new node with the given key and
		NULL left and right pointers. */
		// template<class Key, class T>
		Node* newNode(m_value_type content, Node* parent)
		{
			// Node* node = new Node();
			Node* node = _aln.allocate(1);
			//node->content = _al.allocate(1);
			//node->content = new m_value_type();
			node->content = all.allocate(1);
			all.construct(node->content, content);
			// node->key = key;
			// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! "&" for test
			// node->content = &content;
			// node->content->first = content.first;
			// node->content->second = content.second;
			node->left = NULL;
			node->right = NULL;
			node->parent = parent;
			node->height = 1;				 // new node is initially
							// added at leaf
			// std::cout << "node inserted " << node->content->first << std::endl;
			// if(parent)
			// 	std::cout << "parent of the node " << node->parent->content->first << std::endl;
			return(node);
		}

		// A utility function to right
		// rotate subtree rooted with y
		// See the diagram given above.
		// template<class Key, class T>
		Node *rightRotate(Node *y)
		{
			Node *x = y->left;
			Node *T2 = x->right;

			// Perform rotation
			x->right = y;
			x->parent = y->parent;
			y->parent = x;
			if(T2)
				T2->parent = y;
			y->left = T2;

			// Update heights
			y->height = max(height(y->left),
							height(y->right)) + 1;
			x->height = max(height(x->left),
							height(x->right)) + 1;

			// Return new root
			return x;
		}

		// A utility function to left
		// rotate subtree rooted with x
		// See the diagram given above.
		// template<class Key, class T>
		Node *leftRotate(Node *x)
		{
			Node *y = x->right;
			Node *T2 = y->left;

			// Perform rotation
			y->left = x;
			y->parent = x->parent;
			x->parent = y;
			//std::cout << "t2 content is " << T2->content->first << std::endl;
			if(T2)
				T2->parent = x;
			x->right = T2;

			// Update heights
			x->height = max(height(x->left),
							height(x->right)) + 1;
			y->height = max(height(y->left),
							height(y->right)) + 1;

			// Return new root
			return y;
		}

		// Get Balance factor of node N
		// template<class Key, class T>
		int getBalance(Node *N)
		{
			if (N == NULL)
				return 0;
			return height(N->left) - height(N->right);
		}

		pair<iterator,bool> insert (const m_value_type& val)
        {
            size_t s = _size;
            _root = insert(_root, val, _root);
            if (s == _size)
                return(ft::make_pair(iterator(not_inserted,_root), false));
            else
                return(ft::make_pair(iterator(last_inserted,_root), true));
        }

		void insert (iterator position, const m_value_type& val)
        {
            (void) position;
            insert(val);
        }

		template <class InputIterator>
        void insert (InputIterator first, InputIterator last)
        {
            while (first != last)
            {
               insert(*first);
                first++;
            }
        }

		mapped_type& operator[] (const key_type& k)
        {
            return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
        }
		// Recursive function to insert a key
		// in the subtree rooted with node and
		// returns the new root of the subtree.
		// template<class Key, class T>
		Node* insert(Node* node, const m_value_type & content, Node* parent)
		{
			/* 1. Perform the normal BST insertion */
			if (node == NULL)
			{
				Node * n;
				n = newNode(content, parent);
				node = n;
				last_inserted = n;
				_size++;
				return(node);
			}
			
			// if (key < node->key)
			// 	node->left = insert(node->left, key);
			// else if (key > node->key)
			// 	node->right = insert(node->right, key);
			// else // Equal keys are not allowed in BST
			// 	return node;
			//if (content < node->content)
			if(_kc(content.first, node->content->first))
				node->left = insert(node->left, content, node);
			else if (_kc(node->content->first, content.first))
				node->right = insert(node->right, content, node);
			else // Equal keys are not allowed in BST
			{
				not_inserted = node;
				return node;
			}
			// if(_kc(node->content->first, content->first))
			// {
			// 	if(node->right->content)
			// 		std::cout << "check value content first " << node->right->content->first << std::endl;
			// }
			/* 2. Update height of this ancestor node */
			node->height = 1 + max(height(node->left),
								height(node->right));

			/* 3. Get the balance factor of this ancestor
				node to check whether this node became
				unbalanced */
			int balance = getBalance(node);

			// If this node becomes unbalanced, then
			// there are 4 cases

			// Left Left Case

			if (balance > 1 && _kc(content.first, node->left->content->first))
				return rightRotate(node);

			// Right Right Case

			if (balance < -1 && !(_kc(content.first, node->right->content->first)))
				return leftRotate(node);

			// Left Right Case

			if (balance > 1 && !(_kc(content.first, node->left->content->first)))
			{	
				node->left = leftRotate(node->left);
				return rightRotate(node);
			}
			// Right Left Case

			if (balance < -1 && _kc(content.first, node->right->content->first))
			{
				node->right = rightRotate(node->right);
				return leftRotate(node);
			}
			/* return the (unchanged) node pointer */
			return node;
		}

		// A utility function to print preorder
		// traversal of the tree.
		// The function also prints height
		// of every node
		/* Given a non-empty binary search tree,
		return the node with minimum key value
		found in that tree. Note that the entire
		tree does not need to be searched. */
		// template<class Key, class T>
		Node * minValueNode(Node* node)
		{
			Node* current = node;
		
			/* loop down to find the leftmost leaf */
			while (current && current->left != NULL)
				current = current->left;
		
			return current;
		}
		
		Node * minValueNode(Node* node) const
		{
			Node* current = node;
		
			/* loop down to find the leftmost leaf */
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

		Node * maxValueNode(Node* node) const
		{
			Node* current = node;
		
			/* loop down to find the leftmost leaf */
			while (current && current->right != NULL)
				current = current->right;
		
			return current;
		}
		// Recursive function to delete a node
		// with given key from subtree with
		// given root. It returns root of the
		// modified subtree.
		// template<class Key, class T>
		Node* deleteNode(Node* root,const m_value_type & content)
		{
			
			 // STEP 1: PERFORM STANDARD BST DELETE
            if (root == NULL)
                return root;
            // If the data to be deleted is smaller
            // than the root's data, then it lies
            // in left subtree
            if (_kc(content.first, root->content->first))
                root->left = deleteNode(root->left, content);
        
            // If the content to be deleted is greater
            // than the root's content, then it lies
            // in right subtree
            else if(_kc(root->content->first, content.first))
                root->right = deleteNode(root->right, content);
        
            // if content is same as root's content, then
            // This is the node to be deleted
            else
            {
                // node with only one child or no child
                if( (root->left == NULL) || (root->right == NULL) )
                {
                    Node *temp = NULL;
                    temp = root->left ? root->left : root->right;
                    // No child case
                    if (temp == root->left)
                        root->left = NULL;
                    else if (temp == root->right)
                        root->right = NULL;
                    if (temp == NULL)
                    {
                        temp = root;
                        root = NULL;
                    }
                    else // One child case
                    {
                    //    std::swap(*root, *temp);
                         all.construct(root->content, *temp->content);
                    //    root->parent = tmp;

                    }
                   
                    // delete(temp->content);
                    // delete (temp);
                    
                    if(_size) 
                        _size--;
                    // all.destroy(temp->content);
                    all.deallocate(temp->content, 1);
                    // _aln.destroy(temp);
                    _aln.deallocate(temp, 1);
                    temp= NULL;
                }
                else
                {
                    // node with two children: Get the inorder
                    // successor (smallest in the right subtree)
                    Node* temp = minValueNode(root->right);
        
                    // Copy the inorder successor's
                    // content to this node
                    //  root->content=  temp->content;
                     all.construct(root->content, *temp->content);
                    
                    // Delete the inorder successor
                    
                    root->right = deleteNode(root->right, *temp->content);
                }
            }
		
			// If the tree had only one node
			// then return
			if (root == NULL)
			return root;
		
			// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
			root->height = 1 + max(height(root->left),
								height(root->right));
		
			// STEP 3: GET THE BALANCE FACTOR OF
			// THIS NODE (to check whether this
			// node became unbalanced)
			int balance = getBalance(root);
		
			// If this node becomes unbalanced,
			// then there are 4 cases
		
			// Left Left Case
			if (balance > 1 &&
				getBalance(root->left) >= 0)
				return rightRotate(root);
		
			// Left Right Case
			if (balance > 1 &&
				getBalance(root->left) < 0)
			{
				root->left = leftRotate(root->left);
				return rightRotate(root);
			}
		
			// Right Right Case
			if (balance < -1 &&
				getBalance(root->right) <= 0)
				return leftRotate(root);
		
			// Right Left Case
			if (balance < -1 &&
				getBalance(root->right) > 0)
			{
				root->right = rightRotate(root->right);
				return leftRotate(root);
			}
		
			return root;
		}

		struct Trunk
		{
			Trunk *prev;
			std::string str;
		
			Trunk(Trunk *prev, std::string str)
			{
				this->prev = prev;
				this->str = str;
			}
		};
		
		size_type erase (const key_type& k)
        {
            size_type s = _size;
            //  printTree(_root, nullptr, false);
			// m_value_type *content;
			// content = ft::make_pair(k, mapped_type());
            _root = deleteNode(_root, ft::make_pair(k, mapped_type()));
            // printTree(_root, nullptr, false);
            if (s == _size)
                return 0;
            return (1);    
        }

		void erase (iterator position)
        {
            erase(position->first);
        }

		void erase (iterator first, iterator last)
        {
            size_t i = 0;
            ft::Vector<key_type> vec;
            
            if (first == last)
                return ;
            while (first != last)
            {
                vec.push_back(first.getNode()->content->first);
                first++;
            }
            while (i < vec.size())
            {           
                erase(vec[i]);
                i++;
            }
        }
		// Helper function to print branches of the binary tree
		void showTrunks(Trunk *p)
		{
			if (p == nullptr) {
				return;
			}
		
			showTrunks(p->prev);
			std::cout << p->str;
		}

		// template<class Key, class T>
		void printTree(Node* root, Trunk *prev, bool isLeft)
		{
			if (root == nullptr) {
				return;
			}
		
			std::string prev_str = "    ";
			Trunk *trunk = new Trunk(prev, prev_str);
		
			printTree(root->right, trunk, true);
		
			if (!prev) {
				trunk->str = "———";
			}
			else if (isLeft)
			{
				trunk->str = ".———";
				prev_str = "   |";
			}
			else {
				trunk->str = "`———";
				prev->str = prev_str;
			}
		
			showTrunks(trunk);
			std::cout << " " << root->content->first << std::endl;
		
			if (prev) {
				prev->str = prev_str;
			}
			trunk->str = "   |";
		
			printTree(root->left, trunk, false);
		}

		// template<class Key, class T>
		void preOrder(Node *root)
		{
			if(root != NULL)
			{
				std::cout <<"key is " << root->content->first << std::endl;
				if(root->left)
					std::cout << "left child is " << root->left->content->first << std::endl;
				if (root->right)
					std::cout << "right child is " << root->right->content->first << std::endl;
				if(root->parent)
					std::cout <<"parent is " << root->parent->content->first <<std::endl;
				preOrder(root->left);
				preOrder(root->right);
			}
		}
		private:
            size_t  _size;
            allocator_type   _al;
            key_compare _kc;
			//aloc	_aln;
	};
	//relational operators
    template <class Key, class T, class Compare, class Alloc>
    bool operator== (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return (lhs.size() == rhs.size());
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator!= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
    {
        return(!(lhs == rhs));
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<  (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    
    template <class Key, class T, class Compare, class Alloc>
    bool operator> (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
    {
        return(rhs < lhs);
    }
    
    template <class Key, class T, class Compare, class Alloc>
    bool operator<= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
    {
        if (lhs < rhs || lhs == rhs)
            return(true);
        return (false);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
    {
        if (lhs > rhs || lhs == rhs)
            return(true);
        return (false);
    }
    template <class Key, class T, class Compare, class Alloc>
    void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
    {
        x.swap(y);
    }
}
