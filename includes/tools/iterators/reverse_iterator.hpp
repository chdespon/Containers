/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:57:49 by chdespon          #+#    #+#             */
/*   Updated: 2022/10/20 18:14:25 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator.hpp"
# include "iterator_traits.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator : public
		ft::iterator<typename ft::iterator_traits<Iterator>::iterator_category,
			typename ft::iterator_traits<Iterator>::value_type,
			typename ft::iterator_traits<Iterator>::difference_type,
			typename ft::iterator_traits<Iterator>::pointer,
			typename ft::iterator_traits<Iterator>::reference>
	{

			Iterator	current;

		public:
			typedef Iterator												iterator_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type	difference_type;
			typedef typename ft::iterator_traits<Iterator>::reference		reference;
			typedef typename ft::iterator_traits<Iterator>::pointer			pointer;

			reverse_iterator():current() {}
			explicit reverse_iterator(Iterator x):current(x) {}

			template <class U>
			reverse_iterator(const reverse_iterator<U>& u): current(u.current) {}

			Iterator base() const {return (current);}

			reference operator*() const
			{
				Iterator tmp = current;
				return *(--tmp);
			}

			pointer operator->() const {return (&(operator*()));}

			reverse_iterator& operator++()
			{
				--current;
				return (*this);
			}

			template <class U>
			reverse_iterator& operator=(const reverse_iterator<U> &u)
			{
				current = u.base();
				return (*this);
			};

			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				--current;
				return (tmp);
			}

			reverse_iterator& operator--()
			{
				++current;
				return (*this);
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				++current;
				return (tmp);
			}

			reverse_iterator operator+ (difference_type n) const
			{
				return (reverse_iterator(current - n));
			}

			reverse_iterator& operator+=(difference_type n)
			{
				current -= n;
				return (*this);
			}

			reverse_iterator operator- (difference_type n) const
			{
				return (reverse_iterator(current + n));
			}

			reverse_iterator& operator-=(difference_type n)
			{
				current += n;
				return (*this);
			}

			reference operator[](difference_type n) const {return (current[-n - 1]);}
	};

	template <class Iterator1, class Iterator2>
	bool operator==( const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y)
	{
		return (x.base() == y.base());
	}

	template <class Iterator>
	bool operator==( const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y)
	{
		return (x.base() == y.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator<( const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y)
	{
		return (x.base() > y.base());
	}

	template <class Iterator>
	bool operator<( const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y)
	{
		return (x.base() > y.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator!=(const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y)
	{
		return (x.base() != y.base());
	}

	template <class Iterator>
	bool operator!=(const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y)
	{
		return (x.base() != y.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>(const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y)
	{
		return (x.base() < y.base());
	}

	template <class Iterator>
	bool operator>(const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y)
	{
		return (x.base() < y.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>=(const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y)
	{
		return (x.base() <= y.base());
	}

	template <class Iterator>
	bool operator>=(const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y)
	{
		return (x.base() <= y.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator<=(const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y)
	{
		return (x.base() >= y.base());
	}

	template <class Iterator>
	bool operator<=(const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y)
	{
		return (x.base() >= y.base());
	}

	template <class Iterator1, class Iterator2>
	typename ft::reverse_iterator<Iterator1>::difference_type operator-(const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y)
	{
		return (y.base() - x.base());
	}

	template <class Iterator>
	typename ft::reverse_iterator<Iterator>::difference_type operator-(const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y)
	{
		return (y.base() - x.base());
	}

	template <class Iterator>
	ft::reverse_iterator<Iterator> operator+(typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator>& x)
	{
		return (ft::reverse_iterator<Iterator> (x.base() - n));
	}
}

#endif
