/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:23:39 by chdespon          #+#    #+#             */
/*   Updated: 2022/07/17 20:57:36 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <memory>

enum Color {RED, BLACK};

template<class T>
struct Node
{
	T		data;
	bool	color;
	Node<T>	*left;
	Node<T>	*right;
	Node<T>	*parent;

	// Constructor
	Node(T val)
	{
		data = val;
		left = right = parent = NULL;
		color = RED;
	}

	Node *uncle()
	{
		// If no parent or grandparent, then no uncle
		if (parent == NULL or parent->parent == NULL)
			return (NULL);

		if (parent->isOnLeft())
			// uncle on right
			return (parent->parent->right);
		else
			// uncle on left
			return (parent->parent->left);
	}

	// check if node is left child of parent
	bool isOnLeft() { return this == parent->left; }

	// returns pointer to sibling
	Node *sibling()
	{
		// sibling null if no parent
		if (parent == NULL)
			return (NULL);

		if (isOnLeft())
			return (parent->right);

		return (parent->left);
	}

	 bool hasRedChild()
	{
		return ((left != NULL and left->color == RED) || (right != NULL and right->color == RED));
	}
};

namespace ft
{
	template <class T, class Allocator = std::allocator<Node<T> > >
	class RBTree
	{
		public:
			typedef Node<T>	Node;

		private:
			Node							*_root;
			Allocator						_allocator;
			typename Allocator::size_type	_size;

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

			// Node	*BSTInsert(Node* root, Node *ptr)
			// {
			// 	/* If the tree is empty, return a new node */
			// 	if (root == NULL)
			// 		return (ptr);

			// 	/* Otherwise, recur down the tree */
			// 	if (ptr->data < root->data)
			// 	{
			// 		root->left  = BSTInsert(root->left, ptr);
			// 		root->left->parent = root;
			// 	}
			// 	else if (ptr->data > root->data)
			// 	{
			// 		root->right = BSTInsert(root->right, ptr);
			// 		root->right->parent = root;
			// 	}

			// 	/* return the (unchanged) node pointer */
			// 	return (root);
			// }

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
							if (sibling->left != NULL and sibling->left->color == RED)
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
				int temp;
				temp = u->data;
				u->data = v->data;
				v->data = temp;
			}

			// find node that do not have a left child
			// in the subtree of the given node
			Node	*successor(Node *x)
			{
				Node *temp = x;

				while (temp->left != NULL)
					temp = temp->left;

				return (temp);
			}

			// find node that replaces a deleted node in BST
			Node	*BSTreplace(Node *x)
			{
				// when node have 2 children
				if (x->left != NULL and x->right != NULL)
					return (successor(x->right));

				// when leaf
				if (x->left == NULL and x->right == NULL)
					return (NULL);

				// when single child
				if (x->left != NULL)
					return (x->left);
				else
					return (x->right);
			}

			void	deleteNode(Node *v)
			{
				Node *u = BSTreplace(v);

				// True when u and v are both black
				bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
				Node *parent = v->parent;

				if (u == NULL)
				{
					// u is NULL therefore v is leaf
					if (v == _root)
						// v is root, making root null
						_root = NULL;
					else
					{
						// u and v both black
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
						// v is root, assign the value of u to v, and delete u
						v->data = u->data;
						v->left = v->right = NULL;
						_allocator.destroy(u);
						_allocator.deallocate(u, 1);
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
			RBTree():_root(NULL), _size(0) {}

			~RBTree()
			{
				_destroy_tree(_root);
			}

			// void	insert(const T &data)
			// {
			// 	Node *ptr = _allocator.allocate(1);
			// 	_allocator.construct(Node) Node(data);

			// 	// Do a normal BST insert
			// 	_root = BSTInsert(_root, ptr);

			// 	// fix Red Black Tree violations
			// 	fixViolation(_root, ptr);
			// }

			void	insert(const T data)
			{
				if (_root == NULL)
				{
					Node *ptr =_allocator.allocate(1);
					_allocator.construct(ptr, Node(data));
					++_size;

					ptr->color = BLACK;
					_root = ptr;
					fixViolation(_root, ptr);
				}
				else
				{
					Node *tmp = find(data);
					if (tmp->data == data)
						return ;

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
			}
			void	deleteByval(int n)
			{
				if (_root == NULL)
				{
					// Tree is empty
					std::cout << "Tree is empty" << std::endl;
					return ;
				}

				Node *v = find(n);
				if (v->data != n)
				{
					std::cout << "No node found to delete with value: " << n << std::endl;
					return ;
				}

				deleteNode(v);
			}

			Node	*find(const T &n)
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

			size_t	size(void) {return (_size);}

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
			void	printTree()
			{
				printTreeHelper(_root, 0);
			}
	};
}