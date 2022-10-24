/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:02:08 by chdespon          #+#    #+#             */
/*   Updated: 2022/10/24 18:43:20 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

enum Color {RED, BLACK};
namespace ft
{
	template < typename T>
	struct less : public std::binary_function<T, T, bool>
	{
		bool	operator()(const T & x, const T & y) const
		{
			return (x < y);
		}
	};

	template<class T>
	struct Node
	{
		typedef T		value_type;
		typedef Node*	pointer;

		value_type	data;
		bool		color;
		pointer		left;
		pointer		right;
		pointer		parent;

		// Constructor
		Node(): data(), color(RED), left(NULL), right(NULL), parent(NULL) {}

		Node(T const &val): data(val)
		{
			left = right = parent = NULL;
			color = RED;
		}

		Node(Node const &cpy)
		: data(cpy.data), color(cpy.color), left(cpy.left), right(cpy.right), parent(cpy.parent)
		{}

		~Node() {}

		Node	*root(Node *node)
		{
			if (node == NULL)
				return (NULL);
			while (node->parent != NULL)
				node = node->parent;
			return (node);
		}

		Node	*uncle()
		{
			// If no parent or grandparent, then no uncle
			if (parent == NULL || parent->parent == NULL)
				return (NULL);

			if (parent->isOnLeft())
				// uncle on right
				return (parent->parent->right);
			else
				// uncle on left
				return (parent->parent->left);
		}

		// check if node is left child of parent
		bool	isOnLeft()
		{
			if (parent != NULL && parent->left == this)
				return (true) ;
			return (false) ;
		}

		// returns pointer to sibling
		Node	*sibling()
		{
			// sibling null if no parent
			if (parent == NULL)
				return (NULL);

			if (isOnLeft())
				return (parent->right);

			return (parent->left);
		}

		bool	hasRedChild()
		{
			return ((left != NULL && left->color == RED) || (right != NULL && right->color == RED));
		}

		Node	*getMostRight()
		{
			Node *res = this;

			while (res->right != NULL)
				res = res->right;
			return (res);
		}

		Node	*getMostLeft()
		{
			Node *res = this;

			while (res->left != NULL)
				res = res->left;
			return (res);
		}

		Node	*first(Node *node)
		{
			if (node == NULL)
				return (NULL);
			node = node->root(node);
			if (node != NULL)
				while (node->left != NULL)
					node = node->left;
			return (node);
		}

		Node	*last(Node *node)
		{
			if (node == NULL)
				return (NULL);
			node = node->root(node);
			if (node != NULL)
				node = node->getMostRight();
			return (node);
		}

		Node	&operator=(Node const& u)
		{
			if (this != &u)
			{
				data = u.data;
				color = u.color;
				left = u.left;
				right = u.right;
				parent = u.parent;
			}
			return (*this);
		}
	};
}
