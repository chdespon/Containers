/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:02:08 by chdespon          #+#    #+#             */
/*   Updated: 2022/07/21 18:47:16 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

enum Color {RED, BLACK};
namespace ft
{
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
		bool	isOnLeft() {return (this == parent->left);}

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

		Node	*getMostLight()
		{
			Node *res = this;

			while (res->left != NULL)
				res = res->left;
			return (res);
		}
	};
}
