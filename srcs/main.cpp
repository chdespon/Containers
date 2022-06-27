/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:53:29 by chdespon          #+#    #+#             */
/*   Updated: 2022/06/27 16:35:44 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>
#include <stdlib.h>

# if FT //CREATE A REAL STL EXAMPLE
	// #include <map.hpp>
	# include <stack.hpp>
	# include <vector.hpp>
# else
	# include <map>
	# include <stack>
	# include <vector>
	namespace ft = std;

# endif

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
	std::cout << '\n';
	std::cout << '\n';
	std::cout << '\n';


	ft::vector<int> vectorInsert (3,100);
	ft::vector<int>::iterator it;

	it = vectorInsert.begin();
	it = vectorInsert.insert ( it , 200 );
	// for (it=vectorInsert.begin(); it<vectorInsert.end(); it++)
	// 	std::cout << ' ' << *it;
	// std::cout << '\n';

	// std::cout << "[";
	vectorInsert.insert (it,2,300);
	// std::cout << "]\n";


	// "it" no longer valid, get a new one:
	it = vectorInsert.begin();

	ft::vector<int> anothervector (2,400);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  ,anothervector.end());

	int myarray [] = { 501,502,503 };
	vectorInsert.insert (vectorInsert.begin(), myarray, myarray+3);

	std::cout << "vectorInsert contains:";
	for (it=vectorInsert.begin(); it<vectorInsert.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';
	std::cout << '\n';
	std::cout << '\n';

	ft::vector<int> foo1 (3,100);   // three ints with a value of 100
	ft::vector<int> bar1 (5,200);   // five ints with a value of 200

	foo1.swap(bar1);

	std::cout << "foo1 contains:";
	for (unsigned i=0; i<foo1.size(); i++)
		std::cout << ' ' << foo1[i];
	std::cout << '\n';

	std::cout << "frgergr contains:";
	for (unsigned i=0; i<bar1.size(); i++)
		std::cout << ' ' << bar1[i];
	std::cout << '\n';
	std::cout << '\n';
	std::cout << '\n';

	ft::vector<int> newVector;

	// set some values (from 1 to 10)
	for (int i=1; i<=10000000; i++) newVector.push_back(i);

	// erase the 6th element
	// newVector.erase (newVector.begin()+3);

	// erase the first 3 elements:
	newVector.erase (newVector.begin()+3,newVector.begin()+9999999);

	std::cout << "newVector contains:";
	for (unsigned i=0; i<newVector.size(); ++i)
		std::cout << ' ' << newVector[i];
	std::cout << '\n';

	return (0);
}