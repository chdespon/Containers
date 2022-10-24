/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:18:39 by chdespon          #+#    #+#             */
/*   Updated: 2022/10/24 18:40:51 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_MAP_HPP
# define SET_MAP_HPP

# include "pair.hpp"
# include "red_black_tree.hpp"

namespace ft
{
	template <class Key, class Compare = less<Key>, class Allocator = std::allocator<Key> >
	class set
	{
		public:
			// types:
			typedef Key										key_type;
			typedef Key										value_type;
			typedef Compare									key_compare;
			typedef Compare									value_compare;
			typedef Allocator								allocator_type;
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef size_t									size_type;
			typedef ptrdiff_t								difference_type;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;

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
			// 23.3.3.1 construct/copy/destroy:
			explicit set(const Compare& comp = Compare(), const Allocator& alloc = Allocator())
			: _tree(value_compare(comp)), _allocator(alloc), _cmp(comp) {}

			template <class InputIterator>
			set(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
			: _tree(value_compare(comp)), _allocator(alloc), _cmp(comp)
			{
				insert(first, last);
			}

			set(const set<Key,Compare,Allocator>& cpy)
			: _tree(cpy._tree), _allocator(cpy._allocator), _cmp(cpy._cmp)
			{
				insert(cpy.begin(), cpy.end());
			}

			~set() {}

			set<Key,Compare,Allocator>&operator=(const set<Key,Compare,Allocator>& x)
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
				return (_tree.erase(x));
			}

			void erase(iterator first, iterator last)
			{
				_tree.erase(first, last);
			}

			void swap(set<Key,Compare,Allocator>& x)
			{
				_tree.swap(x._tree);
				std::swap(_allocator, x._allocator);
				std::swap(_cmp, x._cmp);
			}

			void clear()
			{
				_tree.clear();
			}

			// observers:
			key_compare key_comp() const {return (_cmp);}
			value_compare value_comp() const {return (value_compare(_cmp));}

			// set operations:
			iterator find(const key_type& key)
			{
				return (_tree.find(key));
			}

			const_iterator find(const key_type& key) const
			{
				return (_tree.find(key));
			}

			size_type count(const key_type& key) const
			{
				const_iterator it = find(key);

				if (*it != key)
					return (0);
				return (1);
			}

			iterator lower_bound(const key_type& key)
			{
				iterator it = find(key);
				iterator end = _tree.end();

				if (*it == key)
					return (it);

				for (iterator it = _tree.begin(); it != end; it++)
				{
					if (*it > key)
						return (it);
				}
				return (end);
			}

			const_iterator lower_bound(const key_type& key) const
			{
				const_iterator it = find(key);
				const_iterator end = _tree.end();

				if (*it == key)
					return (it);

				for (const_iterator it = _tree.begin(); it != end; it++)
				{
					if (*it > key)
						return (it);
				}
				return (end);
			}

			iterator upper_bound(const key_type& key)
			{
				iterator it = find(key);
				iterator end = _tree.end();

				if (*it == key)
				{
					++it;
					return (it);
				}

				for (iterator it = _tree.begin(); it != end; it++)
				{
					if (*it > key)
						return (it);
				}
				return (end);
			}

			const_iterator upper_bound(const key_type& key) const
			{
				const_iterator it = find(key);
				const_iterator end = _tree.end();

				if (*it == key)
				{
					++it;
					return (it);
				}

				for (const_iterator it = _tree.begin(); it != end; it++)
				{
					if (*it > key)
						return (it);
				}
				return (end);
			}

			pair<iterator,iterator>
			equal_range(const key_type& key) {return (ft::make_pair(lower_bound(key), upper_bound(key)));}

			pair<const_iterator,const_iterator>
			equal_range(const key_type& key) const {return (ft::make_pair(lower_bound(key), upper_bound(key)));}

			// Operations
			friend bool operator==(const set<Key, Compare, Allocator>& lhs, const set<Key, Compare, Allocator>& rhs)
			{
				if (lhs.size() != rhs.size())
					return (false);
				return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
			}

			friend bool operator<(const set<Key, Compare, Allocator>& lhs, const set<Key, Compare, Allocator>& rhs)
			{
				return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
			}
	};

	template <class Key, class Compare, class Allocator>
	bool operator!=(const set<Key, Compare, Allocator>& lhs, const set<Key, Compare, Allocator>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class Key, class Compare, class Allocator>
	bool operator>(const set<Key, Compare, Allocator>& lhs, const set<Key, Compare, Allocator>& rhs)
	{
		return rhs < lhs;
	}

	template <class Key, class Compare, class Allocator>
	bool operator<=(const set<Key, Compare, Allocator>& lhs, const set<Key, Compare, Allocator>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class Key, class Compare, class Allocator>
	bool operator>=(const set<Key, Compare, Allocator>& lhs, const set<Key, Compare, Allocator>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class Key, class Compare, class Allocator>
	void swap(set<Key,Compare,Allocator>& x, set<Key,Compare,Allocator>& y)
	{
		x.swap(y);
	}
}

#endif
