/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:23:39 by chdespon          #+#    #+#             */
/*   Updated: 2022/09/05 18:51:22 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <memory>
# include "Node.hpp"
# include "pair.hpp"
# include "RBTIterator.hpp"
# include "reverse_iterator.hpp"

namespace tree
{
	template <class T, class Compare = std::less<T>,
		class Allocator = std::allocator<T> >
	class RBTree
	{
		public:
			typedef T														value_type;
			typedef ft::Node<value_type>												Node;
			typedef ft::RBTIterator<Node>									iterator;
			typedef ft::ConstRBTIterator<Node>								const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

			typedef Allocator												allocator_type;
			typedef typename allocator_type::template rebind<Node>::other	node_allocator_type;


		private:
			Node							*_root;
			Node							*_limit; // dont now if is usefull yet check it later!!!
			typename Allocator::size_type	_size;
			node_allocator_type				_allocator;


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
				_limit =_allocator.allocate(1);
				_allocator.construct(_limit, Node(0));
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

			void	swapValues(Node *u, Node *v)
			{
				int	tmp;

				tmp = u->data;
				u->data = v->data;
				v->data = tmp;
			}

			// find node that do not have a left child
			// in the subtree of the given node
			Node	*successor(Node *x)
			{
				Node *tmp = x;

				while (tmp->left != NULL)
					tmp = tmp->left;
				return (tmp);
			}

			// find node that replaces a deleted node in RBTree
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
						// {

						// }

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

				// v has 2 children, swap values with successor and recurse
				swapValues(u, v);
				deleteNode(u);
			}

		public:


			void	erase(iterator position)
			{
				if (position != end())
				{
					deleteNode(position._node);
					_update_limit();
				}
			}

			size_t	erase(const value_type& n)
			{
				if (_root == NULL)
				{
					// Tree is empty
					std::cout << "Tree is empty" << std::endl;
					return (1);
				}

				Node *v = find(n);
				if (v->data != n)
				{
					std::cout << "No node found to delete with value: " << n << std::endl;
					return (1);
				}

				deleteNode(v);
				_update_limit();
				return (0);
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

			Node	*find(const value_type &n)
			{
				Node *tmp = _root;

				while (tmp != NULL)
				{
					if (n < tmp->data)
					{
						if (tmp->left == NULL)
							break ;
						else
							tmp = tmp->left;
					}
					else if (n == tmp->data)
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
						std::cout<< "\033[0;31m" << root->data;
					else
						std::cout<< "\033[0;36m" << root->data;

					std::cout<<"\033[0;37m" << "\n";
					printTreeHelper(root->left, space);
				}
			}

			void	printTree() {printTreeHelper(_root, 0);}

			// Constructor
			RBTree(const Allocator& = Allocator())
			:_root(NULL), _size(0)
			{
				_limit = _create_limit();
			}


			RBTree(const RBTree &copy)
			: _root(NULL), _size(0), _allocator(copy._allocator)
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
				return *this;
			}

			~RBTree()
			{
				clear();
				_allocator.destroy(_limit);
				_allocator.deallocate(_limit, 1);
			}

			// Iterator
			iterator	begin() {return (_root == NULL) ? iterator(_limit, _limit) : iterator(_root->getMostLeft(), _limit);}
			const_iterator	begin() const {return (_root == NULL) ? const_iterator(_limit, _limit) : const_iterator(_root->getMostLeft(), _limit);}
			iterator	end() {return (iterator(_limit, _limit));}
			const_iterator	end() const {return (const_iterator(_limit, _limit));}
			reverse_iterator	rbeging() {return (reverse_iterator(end()));}
			const_reverse_iterator	rbeging() const {return (const_reverse_iterator(end()));}
			reverse_iterator	rend() {return (reverse_iterator(begin()));}
			const_reverse_iterator	rend() const {return (const_reverse_iterator(begin()));}

			// Capacity
			bool	empty() const {return (_root == NULL);}
			size_t	size() const {return (_size);}
			size_t	max_size() const {return (_allocator.max_size());}

			// Modifiers
			// void	insert(const value_type data)
			ft::pair<iterator,bool>	insert(const value_type data)
			{
				ft::pair<iterator,bool> result;
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
					Node *tmp = find(data);
					if (tmp->data == data)
						return (result = ft::make_pair<iterator, bool>(iterator(find(data), _limit), false));

					Node *ptr =_allocator.allocate(1);
					_allocator.construct(ptr, Node(data));
					++_size;

					ptr->parent = tmp;
					if (data < tmp->data)
						tmp->left = ptr;
					else
						tmp->right = ptr;
					fixViolation(_root, ptr);
				}
				_update_limit();
				return (ft::make_pair<iterator, bool>(iterator(_root, _limit), true));
			}

			// iterator	insert(iterator position, const value_type& data)
			// {
			// 	iterator tmp;
			// }

			void	clear()
			{
				_destroy_tree(_root);
				_root = NULL;
				_update_limit();
			}
	};
}