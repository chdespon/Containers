/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:09:21 by chdespon          #+#    #+#             */
/*   Updated: 2022/10/20 20:52:41 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINER_STACK_HPP
#define CONTAINER_STACK_HPP

# include <deque>
# include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;

		protected:
			Container c;

		public:
			explicit stack(const Container&c = Container()): c(c) {}

			bool empty() const {return c.empty();}
			size_type size() const {return c.size();}

			value_type& top() {return c.back();}
			const value_type& top() const {return c.back();}

			void push(const value_type& x) {c.push_back(x);}
			void pop() {c.pop_back();}

			template < typename T2, typename Container2>
			friend inline bool	operator==(const stack<T2, Container2> & lhs, const stack <T2, Container2> & rhs);

			template < typename T2, typename Container2>
			friend	inline bool	operator<(const stack<T2, Container2> & lhs, const stack <T2, Container2> & rhs);

	};
	template < typename T, typename Container>
	inline bool	operator==(const stack<T, Container> & lhs, const stack <T, Container> & rhs)
	{
		return (lhs.c == rhs.c);
	}

	template < typename T, typename Container>
	inline bool	operator!=(const stack<T, Container> & lhs, const stack <T, Container> & rhs)
	{
		return !(lhs == rhs);
	}

	template < typename T, typename Container>
	inline bool	operator<(const stack<T, Container> & lhs, const stack <T, Container> & rhs)
	{
		return (lhs.c < rhs.c);
	}

	template < typename T, typename Container>
	inline bool	operator>(const stack<T, Container> & lhs, const stack <T, Container> & rhs)
	{
		return (rhs < lhs);
	}

	template < typename T, typename Container>
	inline bool	operator<=(const stack<T, Container> & lhs, const stack <T, Container> & rhs)
	{
		return !(rhs < lhs);
	}

		template < typename T, typename Container>
	inline bool	operator>=(const stack<T, Container> & lhs, const stack <T, Container> & rhs)
	{
		return !(lhs < rhs);
	}
}

#endif
