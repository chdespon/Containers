/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:06:25 by chdespon          #+#    #+#             */
/*   Updated: 2022/06/14 18:10:34 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINER_VECTOR_HPP
# define CONTAINER_VECTOR_HPP

# include <vector>
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
		public:
			// types:
			typedef T												value_type;
			typedef size_t											size_type; // See 23.1
			typedef std::ptrdiff_t									difference_type;// See 23.1
			typedef Allocator										allocator_type;

			typedef typename Allocator::reference					reference;
			typedef typename Allocator::const_reference				const_reference;
			typedef typename Allocator::pointer						pointer;
			typedef typename Allocator::const_pointer				const_pointer;

			// typedef typename std::random_access_iterator<T>			iterator; // See 23.1
			// typedef typename std::random_access_iterator<const T>	const_iterator; // See 23.1
			// typedef std::reverse_iterator<iterator>					reverse_iterator;
			// typedef std::reverse_iterator<const_iterator>			const_reverse_iterator;

		private:
			T			*_datas;
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
			// template <class InputIterator>
			// vector(InputIterator first, InputIterator last,
			// 	const Allocator& = Allocator())
			// {
			// 	size_type n = 0;

			// 	for (InputIterator it = first; it != last; ++it)
			// 		++n;
			// 	_capacity = n;
			// 	_size = n;
			// 	_datas = _allocator.allocate(n);
			// 	for (size_type i = 0; first != last; ++first, ++i)
			// 		_allocator.construct(_datas + i, *first);
			// }

			// Copy constructor
			vector(const vector& other)
			:_allocator(other._allocator), _datas(NULL), _size(other._size), _capacity(other._capacity)
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

			// template <class InputIterator>
			// void assign(InputIterator first, InputIterator last)
			// {
			// 	clear();

			// }

			void assign(size_type n, const T& u)
			{
				clear();
				resize(n, u);
			}

			allocator_type get_allocator() const;

			// iterators:
			// iterator begin() {return (iterator(_datas));}
			// const_iterator begin() const {return (const_iterator(_datas));}
			// iterator end() {return (iterator(_datas + _size));}
			// const_iterator end() const {return (const_iterator(_datas + _size));}
			// reverse_iterator rbegin() {return (reverse_iterator(end()));}
			// const_reverse_iterator rbegin() const {return (const_reverse_iterator(end()));}
			// reverse_iterator rend() {return (reverse_iterator(begin()));}
			// const_reverse_iterator rend() const {return (const_reverse_iterator(begin()));}

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
					for (size_type i = _size; i < n; i++)
						_allocator.construct(&_datas[i], val);
				}
				else if (n < _size)
				{
					for (size_type i = n; i < _size; i++)
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
					for (size_type i = 0; i < _size; i++)
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

			// iterator insert(iterator position, const T& x);
			// void insert(iterator position, size_type n, const T& x);
			// template <class InputIterator>
			// void insert(iterator position, InputIterator first, InputIterator last);
			// iterator erase(iterator position);
			// iterator erase(iterator first, iterator last);

			void swap(vector<T,Allocator> &x)
			{
				std::swap(_datas, x._datas);
				std::swap(_size, x._size);
				std::swap(_capacity, x._capacity);
			}

			void clear()
			{
				for (size_type i = 0; i < _size; ++i)
					_allocator.destroy(&_datas[i]);
				_size = 0;
			}
	};

	template <class T, class Allocator>
	bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	template <class T, class Allocator>
	bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	template <class T, class Allocator>
	bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	template <class T, class Allocator>
	bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	template <class T, class Allocator>
	bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	template <class T, class Allocator>
	bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);

}

#endif
