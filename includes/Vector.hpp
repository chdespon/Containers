/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:06:25 by chdespon          #+#    #+#             */
/*   Updated: 2022/06/03 18:59:52 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINER_VECTOR_HPP
# define CONTAINER_VECTOR_HPP

# include <memory>
# include <sstream>
# include <exception>
# include <iostream>

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
			// types:
			typedef typename Allocator::reference reference;
			typedef typename Allocator::const_reference const_reference;
			typedef implementation defined iterator; // See 23.1
			typedef implementation defined const_iterator; // See 23.1
			typedef implementation defined size_type; // See 23.1
			typedef implementation defined difference_type;// See 23.1
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef std::reverse_iterator<iterator> reverse_iterator;
			typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

			// 23.2.2.1 construct/copy/destroy:
			explicit list(const Allocator& = Allocator());
			explicit list(size_type n, const T& value = T(),
				const Allocator& = Allocator());
			template <class InputIterator>
			list(InputIterator first, InputIterator last,
				const Allocator& = Allocator());
			list(const list<T,Allocator>& x);
			~list();
			list<T,Allocator>& operator=(const list<T,Allocator>& x);
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last);
			void assign(size_type n, const T& t);
			allocator_type get_allocator() const;

			// iterators:
			iterator begin();
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;

		private:
			Alloc		_alloc;
			size_type	_size;


	};
}

#endif
