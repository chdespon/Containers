/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:23:39 by chdespon          #+#    #+#             */
/*   Updated: 2022/10/24 17:37:01 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <memory>
# include "Node.hpp"
# include "pair.hpp"
# include "RBTIterator.hpp"
# include "reverse_iterator.hpp"
# include "is_integral.hpp"
# include "enable_if.hpp"
# include "lexicographical_compare.hpp"

namespace ft
{
	template <class T, class Compare, class Allocator = std::allocator<T> >
	class RBTree
	{
		public:
			typedef T														value_type;
			typedef ft::Node<value_type>									Node;
			typedef ft::RBTIterator<Node>									iterator;
			typedef ft::ConstRBTIterator<Node>								const_iterator;
			typedef ft::rb_reverse_iterator<iterator>						reverse_iterator;
			typedef ft::rb_reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef Compare													compare;

			typedef Allocator												allocator_type;
			typedef typename allocator_type::template rebind<Node>::other	node_allocator_type;


		private:
			Node							*_root;
			Node							*_limit;
			typename Allocator::size_type	_size;
			node_allocator_type				_allocator;
			compare							_cmp;

			void	_destroy_tree(Node *node)
			{
				if (node == NULL)
					return ;
				if (node->left)
					_destroy_tree(node->left);
				if (node->right)
					_destroy_tree(node->right);
				_allocator.destroy(node);
				_allocator.deallocate(node, 1);
				--_size;
			}

			Node	*_create_limit()
			{
				_limit = _allocator.allocate(1);
				_allocator.construct(_limit, Node());
				_limit->parent = _root;
				_limit->left = NULL;
				_limit->right = NULL;
				_limit->color = BLACK;
				return (_limit);
			}

			void	_update_limit()
			{
				_limit->parent = _root;
			}

		public:
			void	printTree() {printTreeHelper(_root, 0);}

			// Constructor
			RBTree(const compare& cmp = compare(), const allocator_type & alloc = allocator_type())
			:_root(NULL), _size(0), _allocator(alloc), _cmp(cmp)
			{
				_limit = _create_limit();
			}

			RBTree(const RBTree &copy)
			: _root(NULL), _size(0), _allocator(copy._allocator), _cmp(copy._cmp)
			{
				_limit = _create_limit();
				insert(copy.begin(), copy.end());
			}

			RBTree	&operator=(const RBTree &other)
			{
				if (this != &other)
				{
					clear();
					insert(other.begin(), other.end());
				}
				return (*this);
			}

			~RBTree()
			{
				clear();
				_allocator.destroy(_limit);
				_allocator.deallocate(_limit, 1);
			}

			// Iterator
			iterator begin() {return (_root == NULL) ? iterator(_limit, _limit) : iterator(_root->getMostLeft(), _limit);}
			const_iterator begin() const {return (_root == NULL) ? const_iterator(_limit, _limit) : const_iterator(_root->getMostLeft(), _limit);}

			iterator end() {return (iterator(_limit, _limit));}
			const_iterator end() const {return (const_iterator(_limit, _limit));}

			reverse_iterator rbegin() {return (reverse_iterator(end()));}
			const_reverse_iterator rbegin() const {return (const_reverse_iterator(end()));}

			reverse_iterator rend() {return (reverse_iterator(begin()));}
			const_reverse_iterator rend() const {return (const_reverse_iterator(begin()));}

			// Capacity
			bool	empty() const {return (_root == NULL);}
			size_t	size() const {return (_size);}
			size_t	max_size() const {return (_allocator.max_size());}

			// Modifiers
			ft::pair<iterator,bool>	insert(const value_type& data)
			{
				if (_root == NULL)
				{
					Node *ptr =_allocator.allocate(1);
					_allocator.construct(ptr, data);
					++_size;
					ptr->color = BLACK;
					_root = ptr;
					fixViolation(_root, ptr);
				}
				else
				{
					Node *tmp = _find(data);
					if (!_cmp(data, tmp->data) && !_cmp(tmp->data, data))
						return (ft::make_pair<iterator, bool>(iterator(_find(data), _limit), false));
					Node *ptr =_allocator.allocate(1);
					_allocator.construct(ptr, data);
					++_size;
					ptr->parent = tmp;
					if (_cmp(data, tmp->data) == 1)
						tmp->left = ptr;
					else
						tmp->right = ptr;
					fixViolation(_root, ptr);
				}
				_update_limit();
				return (ft::make_pair<iterator, bool>(iterator(_find(data), _limit), true));
			}

			template < typename InputIterator >
			void insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = NULL )
			{
				while (first != last)
				{
					insert(*first);
					++first;
				}
			}

			void	erase(iterator position)
			{
				if (position != end())
				{
					_delete(position._node);
					_update_limit();
				}
			}

			size_t	erase(const value_type& n)
			{
				if (_root == NULL)// Tree is empty
					return (0);

				Node *v = _find(n);
				if (_cmp(n, v->data) && _cmp(v->data, n))
					return (0);
				_delete(v);
				_update_limit();
				return (1);
			}

			void	erase(iterator first, iterator last)
			{
				iterator tmp;

				while (first != last)
				{
					tmp = first;;
					++tmp;
					erase(first);
					first = tmp;
				}
			}

			void	swap(RBTree &other)
			{
				std::swap(_root, other._root);
				std::swap(_limit, other._limit);
				std::swap(_cmp, other._cmp);
				std::swap(_size, other._size);
			}

			void	clear()
			{
				_destroy_tree(_root);
				_root = NULL;
				_update_limit();
			}

			// 23.3.1.3 map operations:
			iterator find(const T& x) const
			{
				return (iterator(_find(x), _limit));
			}

		protected:
			void	rotateLeft(Node *&root, Node *&ptr)
			{
				Node *ptr_right = ptr->right;

				ptr->right = ptr_right->left;

				if (ptr->right != NULL)
					ptr->right->parent = ptr;

				ptr_right->parent = ptr->parent;

				if (ptr->parent == NULL)
					root = ptr_right;

				else if (ptr == ptr->parent->left)
					ptr->parent->left = ptr_right;

				else
					ptr->parent->right = ptr_right;

				ptr_right->left = ptr;
				ptr->parent = ptr_right;
			}

			void	rotateRight(Node *&root, Node *&ptr)
			{
				Node *ptr_left = ptr->left;

				ptr->left = ptr_left->right;
				if (ptr->left != NULL)
					ptr->left->parent = ptr;

				ptr_left->parent = ptr->parent;
				if (ptr->parent == NULL)
					root = ptr_left;
				else if (ptr == ptr->parent->left)
					ptr->parent->left = ptr_left;
				else
					ptr->parent->right = ptr_left;
				ptr_left->right = ptr;
				ptr->parent = ptr_left;
			}

			void	fixViolation(Node *&root, Node *&ptr)
			{
				Node	*parent_ptr = NULL;
				Node	*grand_parent_ptr = NULL;

				while ((ptr != root) && (ptr->color != BLACK) &&
						(ptr->parent->color == RED))
				{

					parent_ptr = ptr->parent;
					grand_parent_ptr = ptr->parent->parent;

					/*  Case : A
						Parent of ptr is left child
						of Grand-parent of ptr */
					if (parent_ptr == grand_parent_ptr->left)
					{
						Node *uncle_ptr = grand_parent_ptr->right;
						/* Case : 1
						The uncle of ptr is also red
						Only Recoloring required */
						if (uncle_ptr != NULL && uncle_ptr->color == RED)
						{
							grand_parent_ptr->color = RED;
							parent_ptr->color = BLACK;
							uncle_ptr->color = BLACK;
							ptr = grand_parent_ptr;
						}
						else
						{
							/* Case : 2
							ptr is right child of its parent
							Left-rotation required */
							if (ptr == parent_ptr->right)
							{
								rotateLeft(root, parent_ptr);
								ptr = parent_ptr;
								parent_ptr = ptr->parent;
							}
							/* Case : 3
							ptr is left child of its parent
							Right-rotation required */
							rotateRight(root, grand_parent_ptr);
							std::swap(parent_ptr->color, grand_parent_ptr->color);
							ptr = parent_ptr;
						}
					}
					/* Case : B
					Parent of ptr is right child
					of Grand-parent of ptr */
					else
					{
						Node *uncle_ptr = grand_parent_ptr->left;
						/*  Case : 1
							The uncle of ptr is also red
							Only Recoloring required */
						if ((uncle_ptr != NULL) && (uncle_ptr->color == RED))
						{
							grand_parent_ptr->color = RED;
							parent_ptr->color = BLACK;
							uncle_ptr->color = BLACK;
							ptr = grand_parent_ptr;
						}
						else
						{
							/* Case : 2
							ptr is left child of its parent
							Right-rotation required */
							if (ptr == parent_ptr->left)
							{
								rotateRight(root, parent_ptr);
								ptr = parent_ptr;
								parent_ptr = ptr->parent;
							}
							/* Case : 3
							ptr is right child of its parent
							Left-rotation required */
							rotateLeft(root, grand_parent_ptr);
							std::swap(parent_ptr->color, grand_parent_ptr->color);
							ptr = parent_ptr;
						}
					}
				}
				root->color = BLACK;
			}

			void	fixDoubleBlack(Node *x)
			{
				if (x == _root)
				// Reached root
					return ;

				Node *sibling = x->sibling(), *parent = x->parent;
				if (sibling == NULL)
					// No sibiling, double black pushed up
					fixDoubleBlack(parent);
				else
				{
					if (sibling->color == RED)
					{
						// Sibling red
						parent->color = RED;
						sibling->color = BLACK;
						if (sibling->isOnLeft())
							// left case
							rotateRight(_root, parent);
						else
						// right case
							rotateLeft(_root, parent);
						fixDoubleBlack(x);
					}
					else
					{
						// Sibling black
						if (sibling->hasRedChild())
						{
							// at least 1 red children
							if (sibling->left != NULL && sibling->left->color == RED)
							{
								if (sibling->isOnLeft())
								{
									// left left
									sibling->left->color = sibling->color;
									sibling->color = parent->color;
									rotateRight(_root, parent);
								}
								else
								{
									// right left
									sibling->left->color = parent->color;
									rotateRight(_root, sibling);
									rotateLeft(_root, parent);
								}
							}
							else
							{
								if (sibling->isOnLeft())
								{
									// left right
									sibling->right->color = parent->color;
									rotateLeft(_root, sibling);
									rotateRight(_root, parent);
								}
								else
								{
									// right right
									sibling->right->color = sibling->color;
									sibling->color = parent->color;
									rotateLeft(_root, parent);
								}
							}
							parent->color = BLACK;
						}
						else
						{
							// 2 black children
							sibling->color = RED;
							if (parent->color == BLACK)
								fixDoubleBlack(parent);
							else
								parent->color = BLACK;
						}
					}
				}
			}

			// _find node that do not have a left child
			// in the subtree of the given node
			Node	*successor(Node *x)
			{
				Node *tmp = x;

				while (tmp->left != NULL)
					tmp = tmp->left;
				return (tmp);
			}

			// _find node that replaces a deleted node in RBTree
			Node	*replace(Node *x)
			{
				// when node have 2 children
				if (x->left != NULL && x->right != NULL)
					return (successor(x->right));

				// when leaf
				if (x->left == NULL && x->right == NULL)
					return (NULL);

				// when single child
				if (x->left != NULL)
					return (x->left);
				else
					return (x->right);
			}

			void	deleteNode(Node *v)
			{
				Node *u = replace(v);

				// True when u && v are both black
				bool uvBlack = ((u == NULL || u->color == BLACK) && (v->color == BLACK));
				Node *parent = v->parent;

				if (u == NULL)
				{
					// u is NULL therefore v is leaf
					if (v == _root)
						// v is root, making root null
						_root = NULL;
					else
					{
						// u && v both black
						if (uvBlack)
							// v is leaf, fix double black at v
							fixDoubleBlack(v);
						// u or v is red
						else if (v->sibling() != NULL)
							// sibling is not null, make it red"
							v->sibling()->color = RED;
						// delete v from the tree
						if (v->isOnLeft())
							parent->left = NULL;
						else
							parent->right = NULL;
					}
					_allocator.destroy(v);
					_allocator.deallocate(v, 1);
					--_size;
					return ;
				}

				if (v->left == NULL || v->right == NULL)
				{
					// v has 1 child
					if (v == _root)
					{
						// v is root, delete v and make u root
						u->color = BLACK;
						u->parent = NULL;
						u->left = u->right = NULL;
						_root = u;
						_allocator.destroy(v);
						_allocator.deallocate(v, 1);
						--_size;
					}
					else
					{
						// Detach v from tree and move u up
						if (v->isOnLeft())
							parent->left = u;
						else
							parent->right = u;

						_allocator.destroy(v);
						_allocator.deallocate(v, 1);
						--_size;
						u->parent = parent;
						if (uvBlack)
						// u and v both black, fix double black at u
							fixDoubleBlack(u);
						else
						// u or v red, color u black
							u->color = BLACK;
					}
					return ;
				}
				// std::swap(u->data, v->data);
				// _swapValues(u, v);
				deleteNode(u);
			}

			void	_transplant(Node* deleted, Node* replaced)
			{
				if (deleted->parent == NULL)
					_root = replaced;
				else if (deleted->isOnLeft())
					deleted->parent->left = replaced;
				else
					deleted->parent->right = replaced;
				if (replaced != NULL)
					replaced->parent = deleted->parent;
			}

			/*
			** Delete :
			*/

			void	_delete(Node *to_dell)
			{
				Node *child = NULL;
				Node *successor = to_dell;
				Node *parent = to_dell->parent;

				bool original_color = to_dell->color;
				bool child_is_left = to_dell->isOnLeft();

				// if is not only one
				if (_size > 1)
				{
				// check if no child or onlsuccessor one
					if (to_dell->left == NULL)
					{
						child = to_dell->right;
						_transplant(to_dell, to_dell->right);
					}
					else if (to_dell->right == NULL)
					{
						child = to_dell->left;
						_transplant(to_dell, to_dell->left);
					}
					else // two childs
					{
						successor = to_dell->right->getMostLeft();
						original_color = successor->color;
						child = successor->right;
						child_is_left = successor->isOnLeft();
						if (successor->parent == to_dell) // direct child
							parent = successor;
						else
						{
							_transplant(successor, successor->right);
							successor->right = to_dell->right;
							successor->right->parent = successor;
							parent = successor->parent;
						}
						_transplant(to_dell, successor);
						successor->left = to_dell->left;
						successor->left->parent = successor;
						successor->color = to_dell->color;
					}
					if (child != NULL)
						parent = child->parent;
					if (original_color == BLACK && _size > 2)
						_delete_fixup(child, parent, child_is_left);
				}
				_allocator.destroy(to_dell);
				_allocator.deallocate(to_dell, 1);
				if (to_dell == _root)
					_root = NULL;
				--_size;
				if (_root)
					_root->color = BLACK;
			}

			void	_delete_fixup(Node* current, Node* parent, bool is_left)
			{
				Node* sister;

				while (current == NULL || (current != _root && current->color == BLACK ))
				{
					if (current != NULL)
						is_left = current->isOnLeft();
					if (is_left == true)
					{
						sister = parent->right;
						if (sister != NULL && sister->color == RED)
						{
							sister->color = BLACK;
							parent->color = RED;
							rotateLeft(_root,parent);
							sister = parent->right;
						}
						if (sister != NULL && (sister->left == NULL || sister->left->color == BLACK)
						&& (sister->right == NULL || sister->right->color == BLACK))
						{
							sister->color = RED;
							current = parent;
							parent = parent->parent;
						}
						else
						{
							if (sister != NULL && (sister->right == NULL || sister->right->color == BLACK))
							{
								if (sister->left != NULL)
									sister->left->color = BLACK;
								sister->color = RED;
								rotateRight(_root, sister);
								sister = parent->right;
							}
							if (sister != NULL)
								sister->color = parent->color;
							parent->color = BLACK;
							if (sister && sister->right != NULL)
								sister->right->color = BLACK;
							rotateLeft(_root, parent);
							current = _root;
							parent = _limit;
						}
					}
					else
					{
						sister = parent->left;
						if (sister != NULL && sister->color == RED)
						{
							sister->color = BLACK;
							parent->color = RED;
							rotateRight(_root, parent);
							sister = parent->left;
						}
						if (sister != NULL
						&& (sister->left == NULL || sister->left->color == BLACK)
						&& (sister->right == NULL || sister->right->color == BLACK))
						{
							sister->color = RED;
							current = parent;
							parent = parent->parent;
						}
						else
						{
							if (sister != NULL && (sister->left == NULL || sister->left->color == BLACK))
							{
								if (sister->right != NULL)
									sister->right->color = BLACK;
								sister->color = RED;
								rotateLeft(_root, sister);
								sister = parent->left;
							}
							if (sister != NULL)
								sister->color = parent->color;
							parent->color = BLACK;
							if (sister != NULL && sister->left != NULL)
								sister->left->color = BLACK;
							rotateRight(_root, parent);
							current = _root;
							parent = _limit;
						}
					}
				}
				if (current != NULL)
					current->color = BLACK;
			}

			void	printTreeHelper(Node *root, int space)
			{
				int i;

				if(root != NULL)
				{
					space = space + 10;
					printTreeHelper(root->right, space);
					std::cout<< "\n";
					for ( i = 10; i < space; i++)
					{
						std::cout<< " ";
					}
					if (root->color == RED)
						std::cout<< "\033[0;31m" << root->data.first;
					else
						std::cout<< "\033[0;36m" << root->data.first;

					std::cout<<"\033[0;37m" << "\n";
					printTreeHelper(root->left, space);
				}
			}

			Node	*_find(const value_type &n) const
			{
				Node *tmp = _root;
				if (tmp == NULL)
					return (_limit);

				while (tmp != NULL)
				{
					if (_cmp(n, tmp->data) == 1)
					// if (n.first < tmp->data.first)
					{
						if (tmp->left == NULL)
							break ;
						else
							tmp = tmp->left;
					}
					// else if (n.first == tmp->data.first)
					else if (!_cmp(tmp->data, n) && !_cmp(n, tmp->data))
						break ;
					else
					{
						if (tmp->right == NULL)
							break ;
						else
							tmp = tmp->right;
					}
				}
				return (tmp);
			}
	};
}
