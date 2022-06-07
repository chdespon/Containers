/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:09:21 by chdespon          #+#    #+#             */
/*   Updated: 2022/06/07 21:10:27 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINER_STACK_HPP
#define CONTAINER_STACK_HPP

# include <vector>
# include <deque>

namespace ft
{
	template <class T, class Container = std::vector<T> >
	class stack
	{
		public:
			typedef typename Container::value_type value_type;
			typedef typename Container::size_type size_type;
			typedef Container container_type;

		protected:
			Container c;

		public:
			explicit stack(const Container&c = Container()): c(c) {}

			bool empty() const { return c.empty(); }
			size_type size() const { return c.size(); }

			value_type& top() { return c.back(); }
			const value_type& top() const { return c.back(); }

			void push(const value_type& x) { c.push_back(x); }
			void pop() { c.pop_back(); }

			friend bool	operator==( const stack<T, Container>& lhs, const stack<T, Container>& rhs )
			{
				return (lhs.c == rhs.c);
			}
			friend bool	operator<( const stack<T, Container>& lhs, const stack<T, Container>& rhs )
			{
				return (lhs.c < rhs.c);
			}
	};
	template <class T, class Container>
	bool operator!=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator> (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return !(lhs > rhs);
	}

	template <class T, class Container>
	bool operator>=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Container>
	bool operator<=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return !(lhs < rhs);
	}
}


#endif
