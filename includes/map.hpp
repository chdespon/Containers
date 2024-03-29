/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:24:34 by chdespon          #+#    #+#             */
/*   Updated: 2022/10/24 17:46:17 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINER_MAP_HPP
# define CONTAINER_MAP_HPP

# include "pair.hpp"
# include "red_black_tree.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			// types:
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair<const Key, T>					value_type;
			typedef Compare									key_compare;
			typedef Allocator								allocator_type;
			typedef size_t									size_type;
			typedef std::ptrdiff_t							difference_type;

			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;

		public:
			class value_compare: public std::binary_function<value_type,value_type,bool>
			{
				friend class map;
					protected:
						Compare comp;
						value_compare(Compare c) : comp(c) {}

					public:
						bool operator()(const value_type& x, const value_type& y) const
						{
							return (comp(x.first, y.first));
						}
			};

		private:
			typedef ft::RBTree<value_type, value_compare, allocator_type>	_RBTree_type;

		public:
			typedef typename _RBTree_type::iterator					iterator;
			typedef typename _RBTree_type::const_iterator			const_iterator;
			typedef typename _RBTree_type::reverse_iterator			reverse_iterator;
			typedef typename _RBTree_type::const_reverse_iterator	const_reverse_iterator;

		private:
			_RBTree_type	_tree;
			allocator_type	_allocator;
			key_compare		_cmp;

		public:
			// 23.3.1.1 construct/copy/destroy:
			explicit map (const Compare& comp = Compare(), const allocator_type & alloc = allocator_type())
			: _tree(value_compare(comp)), _allocator(alloc), _cmp(comp) {}

			template <class InputIterator>
			map(InputIterator first, InputIterator last,
			const Compare& comp = Compare(), const allocator_type& alloc = allocator_type())
			: _tree(value_compare(comp)), _allocator(alloc), _cmp(comp)
			{
				insert(first, last);
			}

			map(const map& x)
			: _tree(x._tree), _allocator(x._allocator), _cmp(x._cmp)
			{
				insert(x.begin(), x.end());
			}

			~map() {}

			map& operator=(const map& x)
			{
				if (this != &x)
				{
					_tree.clear();
					insert(x.begin(), x.end());
				}
				return (*this);
			}

			allocator_type get_allocator() const {return (_allocator);}

			// iterators:
			iterator begin() {return (_tree.begin());}
			const_iterator begin() const {return (_tree.begin());}

			iterator end() {return (_tree.end());}
			const_iterator end() const {return (_tree.end());}

			reverse_iterator rbegin() {return (_tree.rbegin());}
			const_reverse_iterator rbegin() const {return (_tree.rbegin());}

			reverse_iterator rend() {return (_tree.rend());}
			const_reverse_iterator rend() const {return (_tree.rend());}

			// capacity:
			bool empty() const {return (_tree.empty());}
			size_type size() const {return (_tree.size());}
			size_type max_size() const {return (_allocator.max_size());}

			// 23.3.1.2 element access:
			mapped_type& operator[](const key_type& key)
			{
				return ((*((insert(ft::make_pair(key, mapped_type()))).first)).second);
			}

			// modifiers:
			ft::pair<iterator, bool> insert(const value_type& x)
			{
				return (_tree.insert(x));
			}

			iterator insert(iterator position, const value_type& x)
			{
				(void)position;
				return (_tree.insert(x).first);
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				_tree.insert(first, last);
			}

			void erase(iterator position)
			{
				_tree.erase(position);
			}

			size_type erase(const key_type& x)
			{
				iterator it = find(x);
				if (x == it->first)
					return (_tree.erase(ft::make_pair(x, mapped_type())));
				return (0);
			}

			void erase(iterator first, iterator last)
			{
				_tree.erase(first, last);
			}

			void swap(map& x)
			{
				_tree.swap(x._tree);
				std::swap(_allocator, x._allocator);
				std::swap(_cmp, x._cmp);
			}

			void clear()
			{
				_tree.clear();
			}

			// // observers:
			key_compare key_comp() const {return (_cmp);}
			value_compare value_comp() const {return (value_compare(_cmp));}

			// // 23.3.1.3 map operations:
			iterator find(const key_type& key)
			{
				return (_tree.find(ft::make_pair(key, mapped_type())));
			}

			const_iterator find(const key_type& key) const
			{
				return (_tree.find(ft::make_pair(key, mapped_type())));
			}

			size_type count(const key_type& key) const
			{
				const_iterator it = find(key);

				if (it->first != key)
					return (0);
				return (1);
			}

			iterator lower_bound(const key_type& key)
			{
				iterator it = find(key);
				iterator end = _tree.end();

				if (it->first == key)
					return (it);

				for (iterator it = _tree.begin(); it != end; it++)
				{
					if (it->first > key)
						return (it);
				}
				return (end);
			}

			const_iterator lower_bound(const key_type& key) const
			{
				const_iterator it = find(key);
				const_iterator end = _tree.end();

				if (it->first == key)
					return (it);

				for (const_iterator it = _tree.begin(); it != end; it++)
				{
					if (it->first > key)
						return (it);
				}
				return (end);
			}

			iterator upper_bound(const key_type& key)
			{
				iterator it = find(key);
				iterator end = _tree.end();

				if (it->first == key)
				{
					++it;
					return (it);
				}

				for (iterator it = _tree.begin(); it != end; it++)
				{
					if (it->first > key)
						return (it);
				}
				return (end);
			}

			const_iterator upper_bound(const key_type& key) const
			{
				const_iterator it = find(key);
				const_iterator end = _tree.end();

				if (it->first == key)
				{
					++it;
					return (it);
				}

				for (const_iterator it = _tree.begin(); it != end; it++)
				{
					if (it->first > key)
						return (it);
				}
				return (end);
			}

			pair<iterator,iterator>
			equal_range(const key_type& key) {return (ft::make_pair(lower_bound(key), upper_bound(key)));}

			pair<const_iterator,const_iterator>
			equal_range(const key_type& key) const {return (ft::make_pair(lower_bound(key), upper_bound(key)));}

			friend bool operator==(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
			{
				if (x.size() != y.size())
					return (false);
				return (ft::equal(x.begin(), x.end(), y.begin()));
			}

			friend bool operator<(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
			{
				return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
			}
	};

	template <class Key, class T, class Compare, class Allocator>
	bool operator!=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
	{
		return !(x == y);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator> (const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
	{
		return (y < x);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator>=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
	{
		return !(x < y);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator<=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
	{
		return !(y < x);
	}

	// specialized algorithms:
	template <class Key, class T, class Compare, class Allocator>
	void swap(map<Key,T,Compare,Allocator>& x, map<Key,T,Compare,Allocator>& y)
	{
		x.swap(y);
	}
}

#endif
