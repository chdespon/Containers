/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:06:25 by chdespon          #+#    #+#             */
/*   Updated: 2022/09/01 15:58:06 by chdespon         ###   ########.fr       */
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
				{
					_node = u.base();
					_limit = u._limit;
				}
				return (*this);
			}

			operator	RBTIterator<const T>(void)
			{
				return (RBTIterator<const T>(_node));
			}

			RBTIterator	base() {return (_node);} // explicit

			reference	operator*() {return *(_node);}

			pointer	operator->() const {return (&(operator*()));}

			RBTIterator	&operator++()
			{
				if (_node == _limit)
				{
					_node = _node->last(_node);
					return (*this);
				}

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
				if (_node == _limit)
				{
					_node = _node->last(_node);
					return (*this);
				}

				Node	*p;

				p = _node;
				_node = _node->first(_node);
				if (_node == p)
				{
					_node = _limit;
					return (*this);
				}
				_node = p;
				
				if (_node->left != NULL)
				{
					_node = _node->left;
					while (_node && _node->left)
						_node = _node->left;
				}
				else
				{
					Node *tmp = _node->parent;
					while (tmp->left == _node)
					{
						_node = tmp;
						tmp = tmp->parent;
					}
					if (_node != tmp)
						_node = tmp;
				}
				return (*this);
			}

			RBTIterator	operator--(int)
			{
				operator--();
				return (*this);
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

	template<class T>
	class ConstRBTIterator: public iterator<bidirectional_iterator_tag, T>
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

			ConstRBTIterator(void): _node(NULL), _limit(NULL) {}
			explicit ConstRBTIterator(Node * n, Node *limit): _node(n), _limit(limit) {}

			ConstRBTIterator(ConstRBTIterator const& src) {*this = src;}

			~ConstRBTIterator(){}

			template <class U>
			ConstRBTIterator	&operator=(ConstRBTIterator<U> const& u)
			{
				if (this != &u)
				{
					_node = u.base();
					_limit = u._limit;
				}
				return (*this);
			}

			operator	ConstRBTIterator<const T>(void) const
			{
				return (ConstRBTIterator<const T>(_node));
			}

			ConstRBTIterator	base() {return (_node);} // explicit

			reference	operator*() const {return *(_node);}

			pointer	operator->() const {return (&(operator*()));}

			ConstRBTIterator	&operator++()
			{
				if (_node == _limit)
				{
					_node = _node->last(_node);
					return (*this);
				}

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

			ConstRBTIterator	operator++(int)
			{
				operator++();
				return (*this);
			}

			ConstRBTIterator	&operator--()
			{
				if (_node == _limit)
				{
					_node = _node->last(_node);
					return (*this);
				}

				Node	*p;

				p = _node;
				_node = _node->first(_node);
				if (_node == p)
				{
					_node = _limit;
					return (*this);
				}
				_node = p;

				if (_node->left != NULL)
				{
					_node = _node->left;
					while (_node && _node->left)
						_node = _node->left;
				}
				else
				{
					Node *tmp = _node->parent;
					while (tmp->left == _node)
					{
						_node = tmp;
						tmp = tmp->parent;
					}
					if (_node != tmp)
						_node = tmp;
				}
				return (*this);
			}

			ConstRBTIterator	operator--(int)
			{
				operator--();
				return (*this);
			}

			bool	operator==(const ConstRBTIterator &other) const
			{
				return (_node == other._node);
			}

			bool	operator!=(const ConstRBTIterator &other) const
			{
				return (_node != other._node);
			}
	};

	template <class T>
	bool	operator==(ConstRBTIterator<T> const &x, RBTIterator<T> const &y)
	{
		return (x.base() == y.base());
	}

	template <class TL, class TR>
	bool	operator==(ConstRBTIterator<TL> const &x, RBTIterator<TR> const &y)
	{
		return (x.base() == y.base());
	}

}
