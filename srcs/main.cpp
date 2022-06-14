/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:53:29 by chdespon          #+#    #+#             */
/*   Updated: 2022/06/14 18:10:49 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "stack.hpp"

int	main()
{
	ft::vector<int> b(15, 6);
	std::cout << b[3] << "\n";
	ft::stack<int>::value_type stack_int;



	stack_int = 69;

	std::cout << "The value_type is int = " << stack_int << std::endl;

	ft::stack<int> s1;
	s1.push(stack_int);
	std::cout << "The element at the top of the stack is "
			<< s1.top( ) << ".\n\n" << std::endl;

	ft::vector<int>::size_type sz;

	ft::vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	for (int i=0; i<100; ++i)
	{
		foo.push_back(i);
		if (sz!=foo.capacity())
		{
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}

	ft::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);   // this is the only difference with foo above
	std::cout << "making bar grow:\n";
	for (int i=0; i<100; ++i)
	{
		bar.push_back(i);
		if (sz!=bar.capacity())
		{
			sz = bar.capacity();
			std::cout << "capacity changed: " << sz << "\n\n\n\n\n";
		}
	}

	ft::vector<int> myvector;

  // set some initial content:
	for (size_t i=1;i<10;i++)
		myvector.push_back(i);
	std::cout << "myvector contains:";
	for (size_t i=0;i<myvector.size();i++)
		std::cout << ' ' << myvector[i];
	myvector.resize(5);
	std::cout << "\nmyvector contains:";
	for (size_t i=0;i<myvector.size();i++)
		std::cout << ' ' << myvector[i];
	myvector.resize(8,100);
	std::cout << "\nmyvector contains:";
	for (size_t i=0;i<myvector.size();i++)
		std::cout << ' ' << myvector[i];
	myvector.resize(12);
	std::cout << "\nmyvector contains:";
	for (size_t i=0;i<myvector.size();i++)
		std::cout << ' ' << myvector[i];

	std::cout << "\nmyvector contains:";
	for (size_t i=0;i<myvector.size();i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	ft::vector<int> first;
	// ft::vector<int> third;

	first.assign (7,100);
	// int myints[] = {1776,7,4};
	// third.assign (myints,myints+3);
	std::cout << "Size of first: " << int (first.size()) << '\n';
	// std::cout << "Size of third: " << int (third.size()) << '\n';

	return (0);
}