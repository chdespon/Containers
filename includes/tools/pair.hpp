/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:53:50 by chdespon          #+#    #+#             */
/*   Updated: 2022/09/20 18:18:43 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template< class T1, class T2 >
	struct pair
	{
		public:
			typedef T1 first_type;
			typedef T2 second_type;

			T1 first;
			T2 second;

			pair(): first(first_type()), second(second_type()) {}

			pair(const first_type & _first, const second_type & _second)
			: first(_first), second(_second) {}

			pair(const pair& p): first(p.first), second(p.second) {}

			template<class U, class V>
			pair(const pair<U,V>& pr): first(pr.first), second(pr.second) {}

			~pair() {}

			pair& operator=(const pair& pr)
			{
				if (this != &pr)
				{
					first = pr.first;
					second = pr.second;
				}
				return (*this);
			}
	};

	template< class T1, class T2 >
	ft::pair<T1, T2> make_pair( T1 t, T2 u )
	{ return (ft::pair<T1, T2>( t, u )); }

	template <class T1, class T2>
	bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return (lhs.first == rhs.first && lhs.second == rhs.second); }

	template <class T1, class T2>
	bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return (!(lhs == rhs)); }

	template <class T1, class T2>
	bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second)); }

	template <class T1, class T2>
	bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return (!(rhs < lhs)); }

	template <class T1, class T2>
	bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return (rhs < lhs); }

	template <class T1, class T2>
	bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return (!(lhs < rhs)); }
}

#endif
