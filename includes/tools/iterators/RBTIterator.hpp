/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:06:25 by chdespon          #+#    #+#             */
/*   Updated: 2022/09/26 14:28:19 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "iterator.hpp"
# include "iterator_tags.hpp"

namespace ft
{
	template<class I>
	class RBTIterator: public ft::iterator<bidirectional_iterator_tag, I>
	{
		public:
			typedef I	Node;
			Node		*_node;
			Node		*_limit;

			typedef ft::bidirectional_iterator_tag	iterator_category;
			typedef I								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef I *								pointer;
			typedef I &								reference;
			typedef typename I::value_type*			value_pointer;
			typedef typename I::value_type&			value_reference;

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

			operator	RBTIterator<const I>(void)
			{
				return (RBTIterator<const I>(_node));
			}

			pointer	base() {return (_node);} // explicit

			value_reference	operator*() const {return (_node->data);}

			value_pointer	operator->() {return (&(operator*()));}

			const value_pointer	operator->() const {return (&(operator*()));}

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

	template <class I>
	bool	operator==(RBTIterator<I> const &x, RBTIterator<I> const &y)
	{
		return (x.base() == y.base());
	}

	// template <class I>
	// bool	operator!=(RBTIterator<I> &x, RBTIterator<I> &y)
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

	template<class I>
	class ConstRBTIterator: public iterator<bidirectional_iterator_tag, I>
	{
		public:
			typedef I	Node;
			Node		*_node;
			Node		*_limit;

			typedef ft::bidirectional_iterator_tag	iterator_category;
			typedef I								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef I *								pointer;
			typedef I &								reference;
			typedef typename I::value_type*			value_pointer;
			typedef typename I::value_type&			value_reference;

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

			operator	ConstRBTIterator<const I>(void) const
			{
				return (ConstRBTIterator<const I>(_node));
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

	template <class I>
	bool	operator==(ConstRBTIterator<I> const &x, RBTIterator<I> const &y)
	{
		return (x.base() == y.base());
	}

	template <class IL, class IR>
	bool	operator==(ConstRBTIterator<IL> const &x, RBTIterator<IR> const &y)
	{
		return (x.base() == y.base());
	}



template<class It>
	class rb_reverse_iterator : public
		ft::iterator<typename ft::iterator_traits<It>::iterator_category,
					typename ft::iterator_traits<It>::value_type,
					typename ft::iterator_traits<It>::difference_type,
					typename ft::iterator_traits<It>::pointer,
					typename ft::iterator_traits<It>::reference >
	{
		protected:
			It															current;
		public:
			typedef It													iterator_type;
			typedef typename ft::iterator_traits<It>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<It>::value_type		value_type;
			typedef typename ft::iterator_traits<It>::difference_type	difference_type;
			typedef typename ft::iterator_traits<It>::pointer			pointer;
			typedef typename ft::iterator_traits<It>::reference			reference;
			typedef typename iterator_type::value_pointer				type_pointer;
			typedef typename iterator_type::value_reference				type_reference;

			rb_reverse_iterator() : current() {}
			explicit rb_reverse_iterator(iterator_type it) : current(it) {}
			template<class It2>
			rb_reverse_iterator(const rb_reverse_iterator<It2> & it) : current(it.base()) {}

			rb_reverse_iterator & operator=(const rb_reverse_iterator & it)
			{
				current = it.current;
				return *this;
			}

			iterator_type base() const { return current; }

			type_reference operator*() const { iterator_type tmp = current; --tmp; return *tmp; }
			type_pointer operator->() const { return &(operator*()); }

			type_reference operator[](difference_type n) const { return *(current - 1 - n); }

			rb_reverse_iterator& operator++() { --current; return *this; }
			rb_reverse_iterator operator++(int) { rb_reverse_iterator tmp(*this); --current; return tmp; }

			rb_reverse_iterator& operator--() { ++current; return *this; }
			rb_reverse_iterator operator--(int) { rb_reverse_iterator tmp(*this); ++current; return tmp; }

			rb_reverse_iterator& operator+=(difference_type n) { current -= n; return *this; }
			rb_reverse_iterator& operator-=(difference_type n) { current += n; return *this; }

			rb_reverse_iterator operator+(difference_type n) const { rb_reverse_iterator tmp(current - n); return tmp; }
			rb_reverse_iterator operator-(difference_type n) const { rb_reverse_iterator tmp(current + n); return tmp; }
	};
	template< class It1, class It2 >
	bool operator==(const rb_reverse_iterator<It1>& lhs, const rb_reverse_iterator<It2>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template< class It1, class It2 >
	bool operator!=(const rb_reverse_iterator<It1>& lhs, const rb_reverse_iterator<It2>& rhs)
	{
		return lhs.base() != rhs.base();
	}

	template< class It1, class It2 >
	bool operator<(const rb_reverse_iterator<It1>& lhs, const rb_reverse_iterator<It2>& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template< class It1, class It2 >
	bool operator<=(const rb_reverse_iterator<It1>& lhs, const rb_reverse_iterator<It2>& rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template< class It1, class It2 >
	bool operator>(const rb_reverse_iterator<It1>& lhs, const rb_reverse_iterator<It2>& rhs)
	{
		return lhs.base() < rhs.base();
	}

	template< class It1, class It2 >
	bool operator>=(const rb_reverse_iterator<It1>& lhs, const rb_reverse_iterator<It2>& rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template< class It >
	rb_reverse_iterator<It> operator+(typename rb_reverse_iterator<It>::difference_type n, const rb_reverse_iterator<It>& it)
	{
		return it + n;
	}

	template < class It >
	typename rb_reverse_iterator<It>::difference_type operator-(const rb_reverse_iterator<It>& lhs,
		const rb_reverse_iterator<It>& rhs)
	{
		return rhs.base() - lhs.base();
	}

	// A c++11 compliant reverse iterator
	template < class It1 , class It2>
	typename rb_reverse_iterator<It1>::difference_type operator-(const rb_reverse_iterator<It1>& lhs,
		const rb_reverse_iterator<It2>& rhs)
	{
		return rhs.base() - lhs.base();
	}
}
