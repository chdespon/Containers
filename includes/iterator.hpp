/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:07:24 by chdespon          #+#    #+#             */
/*   Updated: 2022/06/14 18:11:24 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINER_ITERATOR_HPP
# define CONTAINER_ITERATOR_HPP

# include <cstddef>

namespace ft {
	// 24.3, primitives:
	template<class Iterator> struct iterator_traits;
	template<class T> struct iterator_traits<T*>;
	template<class Category, class T, class Distance = ptrdiff_t,
	class Pointer = T*, class Reference = T&> struct iterator;
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag: public input_iterator_tag {};
	struct bidirectional_iterator_tag: public forward_iterator_tag {};
	struct random_access_iterator_tag: public bidirectional_iterator_tag {};

	// 24.3.4, iterator operations:
	template <class InputIterator, class Distance>
	void advance(InputIterator& i, Distance n);
	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last);

	// 24.4, predefined iterators:
	template <class Iterator> class reverse_iterator;
	template <class Iterator>
	bool operator==(
	const reverse_iterator<Iterator>& x,
	const reverse_iterator<Iterator>& y);
	template <class Iterator>
	bool operator<(
	const reverse_iterator<Iterator>& x,
	const reverse_iterator<Iterator>& y);
	template <class Iterator>
	bool operator!=(
	const reverse_iterator<Iterator>& x,
	const reverse_iterator<Iterator>& y);
	template <class Iterator>
	bool operator>(
	const reverse_iterator<Iterator>& x,
	const reverse_iterator<Iterator>& y);
	template <class Iterator>
	bool operator>=(
	const reverse_iterator<Iterator>& x,
	const reverse_iterator<Iterator>& y);
	template <class Iterator>
	bool operator<=(
	const reverse_iterator<Iterator>& x,
	const reverse_iterator<Iterator>& y);
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(
	const reverse_iterator<Iterator>& x,
	const reverse_iterator<Iterator>& y);
	template <class Iterator>
	reverse_iterator<Iterator>
	operator+(
	typename reverse_iterator<Iterator>::difference_type n,
	const reverse_iterator<Iterator>& x);
	template <class Container> class back_insert_iterator;
	template <class Container>
	back_insert_iterator<Container> back_inserter(Container& x);
	template <class Container> class front_insert_iterator;
	template <class Container>
	front_insert_iterator<Container> front_inserter(Container& x);
	template <class Container> class insert_iterator;
	template <class Container, class Iterator>
	insert_iterator<Container> inserter(Container& x, Iterator i);

	// 24.5, stream iterators:
	template <class T, class charT = char, class traits = char_traits<charT>,
	class Distance = ptrdiff_t>
	class istream_iterator;
	template <class T, class charT, class traits, class Distance>
	bool operator==(const istream_iterator<T,charT,traits,Distance>& x,
	const istream_iterator<T,charT,traits,Distance>& y);
	template <class T, class charT, class traits, class Distance>
	bool operator!=(const istream_iterator<T,charT,traits,Distance>& x,
	const istream_iterator<T,charT,traits,Distance>& y);
	template <class T, class charT = char, class traits = char_traits<charT> >
	class ostream_iterator;
	template<class charT, class traits = char_traits<charT> >
	class istreambuf_iterator;
	template <class charT, class traits>
	bool operator==(const istreambuf_iterator<charT,traits>& a,
	const istreambuf_iterator<charT,traits>& b);
	template <class charT, class traits>
	bool operator!=(const istreambuf_iterator<charT,traits>& a,
	const istreambuf_iterator<charT,traits>& b);
	template <class charT, class traits = char_traits<charT> >
	class ostreambuf_iterator;
}

#endif
