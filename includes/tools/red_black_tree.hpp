/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:23:39 by chdespon          #+#    #+#             */
/*   Updated: 2022/07/12 19:51:31 by chdespon         ###   ########.fr       */
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
							std::swap(parent_ptr->color,
									grand_parent_ptr->color);
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
							std::swap(parent_ptr->color,
									grand_parent_ptr->color);
							ptr = parent_ptr;
						}
					}
				}
				root->color = BLACK;
			}

			Node*	BSTInsert(Node* root, Node *ptr)
			{
				/* If the tree is empty, return a new node */
				if (root == NULL)
					return (ptr);

				/* Otherwise, recur down the tree */
				if (ptr->data < root->data)
				{
					root->left  = BSTInsert(root->left, ptr);
					root->left->parent = root;
				}
				else if (ptr->data > root->data)
				{
					root->right = BSTInsert(root->right, ptr);
					root->right->parent = root;
				}

				/* return the (unchanged) node pointer */
				return (root);
			}

		public:
			RBTree():_root(NULL){
				std::cout << sizeof(_root) << std::endl;
			}

			void	insert(const T &data)
			{
				Node *ptr = new Node(data);

				// Do a normal BST insert
				_root = BSTInsert(_root, ptr);

				// fix Red Black Tree violations
				fixViolation(_root, ptr);
			}

			Node	*find(const T &value)
			{
				if (x->data == value || x == NULL)
					return (x);
				if (value < x->data)
					return (find(x->left, value));
				else
					return (find(x->right, value));
			}
	};
}