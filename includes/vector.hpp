/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:06:25 by chdespon          #+#    #+#             */
/*   Updated: 2022/07/16 18:50:23 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINER_VECTOR_HPP
# define CONTAINER_VECTOR_HPP

# include <memory>
# include <sstream>
# include <exception>
# include <iostream>
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"
# include "lexicographical_compare.hpp"

namespace ft
{
	template <typename T, typename Allocator = std::allocator<T> >
	class vector
	{
		public:
			// types:
			typedef T												value_type;
			typedef size_t											size_type;
			typedef std::ptrdiff_t									difference_type;
			typedef Allocator										allocator_type;

			typedef typename Allocator::reference					reference;
			typedef typename Allocator::const_reference				const_reference;
			typedef typename Allocator::pointer						pointer;
			typedef typename Allocator::const_pointer				const_pointer;

			typedef typename ft::random_access_iterator<T>			iterator;
			typedef typename ft::random_access_iterator<const T>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		private:
			pointer		_datas;
			size_type	_capacity;
			size_type	_size;
			Allocator	_allocator;

		public:
			// Default constructor
			explicit vector(const Allocator& = Allocator())
			:_datas(0), _capacity(0), _size(0){}

			// Fill constructor
			explicit vector(size_type n, const T& value = T(),
				const Allocator& = Allocator()):_capacity(n), _size(n)
			{
				_datas = _allocator.allocate(n);
				for (size_type i = 0; i < n; ++i)
					_allocator.construct(_datas + i, value);
			}

			// Range constructor
			template <class InputIterator>
			vector(InputIterator first, typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type last,
				const Allocator& = Allocator())
			{
				size_type n = 0;
				for (InputIterator it = first; it != last; ++it, ++n)

				_capacity = n;
				_size = n;
				_datas = _allocator.allocate(n);
				for (size_type i = 0; first != last; ++first, ++i)
					_allocator.construct(_datas + i, *first);
			}

			// Copy constructor
			vector(const vector& other)
			: _datas(NULL), _capacity(other._capacity), _size(other._size), _allocator(other._allocator)
			{
				_datas = _allocator.allocate(_capacity);
				for (size_type i = 0; i < _size; ++i)
					_allocator.construct(&_datas[i], other._datas[i]);
			}

			~vector()
			{
				clear();
				_allocator.deallocate(_datas, _capacity);
			}

			vector<T,Allocator>& operator=(const vector<T,Allocator>& x);

			template <class InputIterator>
			void assign(InputIterator first, typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
			{
				size_type n = 0;
				for (InputIterator it = first; it != last; ++it, ++n)

				clear();
				reserve(n);
				for (; first != last; ++_size)
				{
					_allocator.construct(&_datas[_size], *first);
					++first;
				}
			}

			void assign(size_type n, const T& u)
			{
				clear();
				resize(n, u);
			}

			allocator_type get_allocator() const {return (_allocator);}

			// iterators:
			iterator begin() {return (iterator(_datas));}
			const_iterator begin() const {return (const_iterator(_datas));}
			iterator end() {return (iterator(_datas + _size));}
			const_iterator end() const {return (const_iterator(_datas + _size));}
			reverse_iterator rbegin() {return (reverse_iterator(end()));}
			const_reverse_iterator rbegin() const {return (const_reverse_iterator(end()));}
			reverse_iterator rend() {return (reverse_iterator(begin()));}
			const_reverse_iterator rend() const {return (const_reverse_iterator(begin()));}

			// 23.2.4.2 capacity:
			size_type size() const {return (_size);}
			size_type max_size() const {return (_allocator.max_size());}

			void resize(size_type n, T val = T())
			{
				if (n < _size * 2 && n > _capacity)
					reserve(_size * 2);
				else
					reserve(n);
				if (n > _size)
				{
					for (size_type i = _size; i < n; ++i)
						_allocator.construct(&_datas[i], val);
				}
				else if (n < _size)
				{
					for (size_type i = n; i < _size; ++i)
						_allocator.destroy(&_datas[i]);
				}
				_size = n;
			}

			size_type capacity() const {return (_capacity);}
			bool empty() const {return (_size == 0);}

			void reserve(size_type n)
			{
				if (n > max_size())
					throw std::length_error("vector::reserve");
				if (n == 0)
					n = 1;
				if (n > _capacity)
				{
					pointer tmp = _allocator.allocate(n);
					for (size_type i = 0; i < _size; ++i)
					{
						_allocator.construct(&tmp[i], _datas[i]);
						_allocator.destroy(&_datas[i]);
					}
					_allocator.deallocate(_datas, _capacity);
					_datas = tmp;
					_capacity = n;
				}
			}

			// element access:
			reference operator[](size_type n) {return (_datas[n]);}
			const_reference operator[](size_type n) const {return (_datas[n]);}

			const_reference at(size_type n) const
			{
				if (_size <= n)
					throw std::out_of_range("Out of range");
				return (_datas[n]);
			}

			reference at(size_type n)
			{
				if (_size <= n)
					throw std::out_of_range("Out of range");
				return (_datas[n]);
			}

			reference front() {return (_datas[0]);}
			const_reference front() const {return (_datas[0]);}
			reference back() {return (_datas[_size - 1]);}
			const_reference back() const {return (_datas[_size - 1]);}

			// 23.2.4.3 modifiers:
			void push_back(const T& val)
			{
				if (_capacity == 0)
					reserve(1);
				else if (_size == _capacity)
					reserve(_capacity * 2);
				_allocator.construct(&_datas[_size], val);
				++_size;
			}

			void pop_back()
			{
				_allocator.destroy(&_datas[_size -1]);
				--_size;
			}

			iterator insert(iterator position, const T& val)
			{
				size_t	pos = position - begin();
				size_t	end = _size;

				if (_capacity == 0)
					reserve(1);
				else if (_size == _capacity)
					reserve(_capacity * 2);

				while(end > pos)
				{
					_allocator.construct(&_datas[end], _datas[end - 1]);
					_allocator.destroy(&_datas[end - 1]);
					--end;
				}
				_allocator.construct(&_datas[end], val);
				++_size;
				return iterator(&_datas[end]);
			}

			void insert(iterator position, size_type n, const T& val)
			{
				size_type pos = position - begin();

				if (_size + n > _capacity * 2)
					reserve(_size + n);
				else if (_size + n > _capacity)
					reserve(_capacity * 2);

				position = begin() + pos;
				while (n)
				{
					--n;
					insert(position, val);
				}
			}

			template <class InputIterator>
			void insert(iterator position, InputIterator first,
				typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
			{
				size_type n = 0;
				size_type pos = position - begin();
				for (InputIterator it = first; it != last; ++it, ++n)
				if (_size + n > _capacity * 2)
					reserve(_size + n);
				 else if (_size + n > _capacity)
					reserve(_capacity * 2);

				position = begin() + pos;
				while (last != first)
					insert(position, *--last);
			}

			iterator erase(iterator position)
			{
				iterator replace(position);
				iterator it_end(end());
				_GLIBCXX_MOVE3(position + 1, end(), position);
				// while (position + 1 != it_end)
				// {
				// 	*position = *(position + 1);
				// 	*position++;
				// }
				// _allocator.destroy(&*position);
				_allocator.destroy(&*(end()-1));
				--_size;
				return (position);
			}

			iterator erase(iterator first, iterator last) //TODO erase do not segfault when last is to big
			{
				iterator it_return(first);
				iterator it_end(end());

				// while (last < it_end)
				// 	*first++ = *last++;
				// if (last +1 == it_end)
				// {
				// 	_GLIBCXX_MOVE3(last, it_end, it_return);
				// 	++first;
				// 	while (first < last+1)
				// 	{
				// 		_allocator.destroy(&*first);
				// 		++first;
				// 		--_size;
				// 	}
				// 	return (it_return);
				// }
				_GLIBCXX_MOVE3(last, it_end, it_return);
				while (first < last)
				{
					_allocator.destroy(&*first);
					++first;
					--_size;
				}
				return (it_return);
			}

			void swap(vector<T,Allocator> &x)
			{
				T	*tmp_datas(_datas); _datas = x._datas; x._datas = tmp_datas;
				T	tmp_size(_size); _size = x._size; x._size = tmp_size;
				T	tmp_capacity(_capacity); _capacity = x._capacity; x._capacity = tmp_capacity;
			}

			void clear()
			{
				for (size_type i = 0; i < _size; ++i)
					_allocator.destroy(&_datas[i]);
				_size = 0;
			}
	};

	template <class T, class Allocator>
	bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
	{
		if (y.size() != x.size())
			return false;
		return (ft::equal(y.begin(), y.end(), x.begin()));
	}

	template <class T, class Allocator>
	bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y)
	{
		return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
	}

	template <class T, class Allocator>
	bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
	{
		return (!(x == y));
	}

	template <class T, class Allocator>
	bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y)
	{
		return (y < x);
	}

	template <class T, class Allocator>
	bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
	{
		return (x == y || x > y);
	}

	template <class T, class Allocator>
	bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
	{
		return (x == y || x < y);
	}

	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
