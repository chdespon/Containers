/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:06:25 by chdespon          #+#    #+#             */
/*   Updated: 2022/06/07 21:38:44 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINER_VECTOR_HPP
# define CONTAINER_VECTOR_HPP

# include <iterator>
# include <memory>
# include <sstream>
# include <exception>
# include <iostream>

namespace ft
{
	template <typename T, typename Allocator = std::allocator<T> >
	class vector
	{
		private:
			T								*_datas;
			typename Allocator::size_type	_capacity;
			typename Allocator::size_type	_size;
			Allocator						_allocator;

		public:
			// types:
			typedef size_t	size_type;
			typedef typename Allocator::reference reference;
			typedef typename Allocator::const_reference const_reference;
			typedef typename std::random_access_iterator<T>			iterator; // See 23.1
			typedef typename std::random_access_iterator<const T>	const_iterator; // See 23.1
			typedef size_t size_type; // See 23.1
			typedef ptrdiff_t difference_type;// See 23.1
			typedef T value_type;
			typedef Allocator allocator_type;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef std::reverse_iterator<iterator> reverse_iterator;
			typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

			// 23.2.4.1 construct/copy/destroy:
			explicit vector(const Allocator& = Allocator())
			:_datas(0), _capacity(0), _size(0){}
			explicit vector(size_type n, const T& value = T(), const Allocator& = Allocator())
			{
				_datas = _allocator.allocate(n);
				for (typename Allocator::size_type i = 0; i < n; i++)
					_allocator.construct(_datas + i, value);
			}

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const Allocator& = Allocator())
			{

			}

			vector(const vector<T,Allocator>& x);
			~vector();
			vector<T,Allocator>& operator=(const vector<T,Allocator>& x);
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last);
			void assign(size_type n, const T& u);
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

			// 23.2.4.2 capacity:
			size_type size() const;
			size_type max_size() const;
			void resize(size_type sz, T c = T());
			size_type capacity() const;
			bool empty() const;
			void reserve(size_type n);

			// element access:
			reference operator[](size_type n);
			const_reference operator[](size_type n) const;
			const_reference at(size_type n) const;
			reference at(size_type n);
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;

			// 23.2.4.3 modifiers:
			void push_back(const T& x);
			void pop_back();
			iterator insert(iterator position, const T& x);
			void insert(iterator position, size_type n, const T& x);
			template <class InputIterator>
			void insert(iterator position,
			InputIterator first, InputIterator last);
			iterator erase(iterator position);
			iterator erase(iterator first, iterator last);
			void swap(vector<T,Allocator>&);
			void clear();



	};
	template <class T, class Allocator>
	bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator< (const vector<T,Allocator>& x,
		const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator!=(const vector<T,Allocator>& x,
		const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator> (const vector<T,Allocator>& x,
		const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator>=(const vector<T,Allocator>& x,
		const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator<=(const vector<T,Allocator>& x,
		const vector<T,Allocator>& y);
}

#endif
