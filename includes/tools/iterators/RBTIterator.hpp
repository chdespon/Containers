/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:06:25 by chdespon          #+#    #+#             */
/*   Updated: 2022/08/31 18:31:12 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "Node.hpp"
# include "iterator.hpp"
# include "iterator_tags.hpp"

namespace ft
{
	template<class T>
	class RBTIterator: public iterator<bidirectional_iterator_tag, T>
	{
		public:
			typedef T	Node;
			Node		*_node;
			Node		*_limit;

			typedef typename ft::iterator<bidirectional_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::iterator_category	iterator_category;

			RBTIterator(void): _node(NULL), _limit(NULL) {}
			explicit RBTIterator(Node * n, Node *limit): _node(n), _limit(limit) {}

			RBTIterator(RBTIterator const& src) {*this = src;}

			~RBTIterator(){}

			template <class U>
			RBTIterator	&operator=(RBTIterator<U> const& u)
			{
				if (this != &u)
					_node = u.base();
				return (*this);
			}

			operator	RBTIterator<const T>(void) const
			{
				return (RBTIterator<const T>(_node));
			}

			RBTIterator	base() {return (_node);} // explicit

			reference	operator*() const {return *(_node);}

			pointer	operator->() const {return (&(operator*()));}

			RBTIterator	&operator++()
			{
				if (_node == _limit)
					return (*this);

				Node	*p;

				p = _node;
				_node = _node->last(_node);
				if (_node == p)
				{
					_node = _limit;
					return (*this);
				}
				_node = p;

				if (_node->right != NULL)
				{
					_node = _node->right;
					while (_node && _node->left)
						_node = _node->left;
				}
				else
				{
					Node *tmp = _node->parent;
					while (tmp->right == _node)
					{
						_node = tmp;
						tmp = tmp->parent;
					}
					if (_node != tmp)
						_node = tmp;
				}
				return (*this);
			}

			RBTIterator	operator++(int)
			{
				operator++();
				return (*this);
			}

			RBTIterator	&operator--()
			{
				if (_node->parent->parent == _node
					&& _node->color == RED)
					_node = _node->left;
				else if (_node->left)
				{
					while (_node->right)
						_node = _node->right;
				}
				else
				{
					Node *parent = _node->parent;
					while (parent->left == _node)
					{
						_node = parent;
						parent = parent->parent;
					}
					_node = parent;
				}
				return (*this);
			}

			RBTIterator	operator--(int)
			{
				RBTIterator tmp = *this;
				operator--();
				return (tmp);
			}

			bool	operator==(const RBTIterator &other) const
			{
				return (_node == other._node);
			}

			bool	operator!=(const RBTIterator &other) const
			{
				return (_node != other._node);
			}
	};
	template <class T>
	bool	operator==(RBTIterator<T> const &x, RBTIterator<T> const &y)
	{
		return (x.base() == y.base());
	}

	// template <class T>
	// bool	operator!=(RBTIterator<T> &x, RBTIterator<T> &y)
	// {
	// 	return (x.base() != y.base());
	// }

	template <class TL, class TR>
	bool	operator==(RBTIterator<TL> const &x, RBTIterator<TR> const &y)
	{
		return (x.base() == y.base());
	}

	// template <class TL, class TR>
	// bool	operator!=(RBTIterator<TL> &x, RBTIterator<TR> &y)
	// {
	// 	return (x.base() != y.base());
	// }
}
