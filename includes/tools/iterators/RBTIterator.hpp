/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:06:25 by chdespon          #+#    #+#             */
/*   Updated: 2022/07/21 17:59:09 by chdespon         ###   ########.fr       */
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
			typedef ft::Node<T>	Node;

		private:
			Node	*_node;

		public:
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::iterator_category	iterator_category;

			RBTIterator(void): _node(NULL) {}
			explicit RBTIterator(Node const* n): _node(n) {}

			RBTIterator(RBTIterator const& src)
			{
				*this = src;
			}

			~RBTIterator();

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

			RBTIterator	base() const {return (_node);} // explicit

			reference	operator*() const {return *(_node);}

			pointer	operator->() const {return (&(operator*()));}

			RBTIterator	&operator++()
			{
				if (_node->right != NULL)
				{
					_node = _node->right;
					while (_node && _node->left)
						_node = _node->left;
				}
				else
				{
					Node *tmp = _node->parent;
					if (tmp->right == _node)
					{
						while (tmp->right == _node)
						{
							_node = tmp;
							tmp = tmp->parent;
						}
					}
					if (_node != tmp)
						_node = tmp;
				}
				return (*this);
			}

			RBTIterator	operator++(int)
			{
				RBTIterator tmp = *this;
				operator++();
				return (tmp);
			}

			RBTIterator	&operator--()
			{
				if (_node->_parent->_parent == _node
					&& _node->_color == RED)
					_node = _node->left;
				else if (_node->left)
				{
					while (_node->right)
						_node = _node->right;
				}
				else
				{
					Node *parent = _node->_parent;
					while (parent->left == _node)
					{
						_node = parent;
						parent = parent->_parent;
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
	};
	template <class T>
	bool	operator==(RBTIterator<T> const& x, RBTIterator<T> const& y)
	{
		return (x.base() == y.base());
	}

	template <class T>
	bool	operator!=(RBTIterator<T> const& x, RBTIterator<T> const& y)
	{
		return (x.base() != y.base());
	}

	template <class TL, class TR>
	bool	operator==(RBTIterator<TL> const& x, RBTIterator<TR> const& y)
	{
		return (x.base() == y.base());
	}

	template <class TL, class TR>
	bool	operator!=(RBTIterator<TL> const& x, RBTIterator<TR> const& y)
	{
		return (x.base() != y.base());
	}
}
