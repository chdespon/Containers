/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:46:16 by chdespon          #+#    #+#             */
/*   Updated: 2022/10/20 18:12:42 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "iterator.hpp"
# include "iterator_traits.hpp"

namespace ft
{
	template <class Iterator>
	class random_access_iterator : public iterator<random_access_iterator_tag, Iterator>
	{
		public:
			typedef typename ft::iterator<random_access_iterator_tag, Iterator>::value_type			value_type;
			typedef typename ft::iterator<random_access_iterator_tag, Iterator>::difference_type	difference_type;
			typedef typename ft::iterator<random_access_iterator_tag, Iterator>::pointer			pointer;
			typedef typename ft::iterator<random_access_iterator_tag, Iterator>::reference			reference;
			typedef typename ft::iterator<random_access_iterator_tag, Iterator>::iterator_category	iterator_category;


			pointer	current;

		public:
			random_access_iterator(): current(0) {}
			explicit random_access_iterator(pointer x):current(x) {}

			template <class U>
			random_access_iterator(const random_access_iterator<U>& u): current(u.current) {}

			pointer base() const {return (current);}

			template <class U> random_access_iterator &operator=(const random_access_iterator<U>& u)
			{
				current = u.base();
				return (*this);
			}

			~random_access_iterator() {}

			reference operator*() const {return *(current);}

			pointer operator->() const {return (&(operator*()));}

			random_access_iterator& operator++()
			 {
				++current;
				return (*this);
			}

			random_access_iterator operator++(int)
			{
				random_access_iterator tmp = *this;
				++current;
				return (tmp);
			}
			random_access_iterator& operator--()
			{
				--current;
				return (*this);
			}
			random_access_iterator operator--(int)
			{
				random_access_iterator tmp = *this;
				--current;
				return (tmp);
			}
			random_access_iterator& operator+=(difference_type n)
			{
				current += n;
				return (*this);
			}

			random_access_iterator operator+(difference_type n) const
			{
				return (random_access_iterator(current + n));
			}

			random_access_iterator& operator-=(difference_type n)
			{
				current -= n;
				return (*this);
			}

			random_access_iterator operator-(difference_type n) const
			{
				random_access_iterator tmp(*this);
				return (tmp -= n);
			}

			reference operator[](difference_type n) const
			{
				return *(current + n);
			}
	};

	template <class T1, class T2>
	bool operator==(const random_access_iterator<T1>& x, const random_access_iterator<T2>& y)
	{
		return (x.base() == y.base());
	}

	template <class T>
	bool operator==(const random_access_iterator<T>& x, const random_access_iterator<T>& y)
	{
		return (x.base() == y.base());
	}

	template <class T1, class T2>
	bool operator<(const random_access_iterator<T1>& x, const random_access_iterator<T2>& y)
	{
		return (x.base() < y.base());
	}

	template <class T>
	bool operator<(const random_access_iterator<T>& x, const random_access_iterator<T>& y)
	{
		return (x.base() < y.base());
	}

	template <class T1, class T2>
	bool operator!=(const random_access_iterator<T1>& x, const random_access_iterator<T2>& y)
	{
		return (x.base() != y.base());
	}

	template <class T>
	bool operator!=(const random_access_iterator<T>& x, const random_access_iterator<T>& y)
	{
		return (x.base() != y.base());
	}

	template <class T1, class T2>
	bool operator>(const random_access_iterator<T1>& x, const random_access_iterator<T2>& y)
	{
		return (x.base() > y.base());
	}

	template <class T>
	bool operator>(const random_access_iterator<T>& x, const random_access_iterator<T>& y)
	{
		return (x.base() > y.base());
	}

	template <class T1, class T2>
	bool operator>=(const random_access_iterator<T1>& x, const random_access_iterator<T2>& y)
	{
		return (x.base() >= y.base());
	}

	template <class T>
	bool operator>=(const random_access_iterator<T>& x, const random_access_iterator<T>& y)
	{
		return (x.base() >= y.base());
	}

	template <class T1, class T2>
	bool operator<=(const random_access_iterator<T1>& x, const random_access_iterator<T2>& y)
	{
		return (x.base() <= y.base());
	}

	template <class T>
	bool operator<=(const random_access_iterator<T>& x, const random_access_iterator<T>& y)
	{
		return (x.base() <= y.base());
	}

	template <class T1, class T2>
	typename random_access_iterator<T1>::difference_type operator-(const random_access_iterator<T1>& x, const random_access_iterator<T2>& y)
	{
		return (x.base() - y.base());
	}

	template <class T>
	typename random_access_iterator<T>::difference_type operator-(const random_access_iterator<T>& x, const random_access_iterator<T>& y)
	{
		return (x.base() - y.base());
	}

	template <class T>
	random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type n, const random_access_iterator<T>& x)
	{
		return (random_access_iterator<T> (x.base() + n));
	}
}

#endif
