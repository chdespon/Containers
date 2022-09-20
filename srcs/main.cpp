/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:53:29 by chdespon          #+#    #+#             */
/*   Updated: 2022/09/20 16:11:33 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <iostream>
#include <string>
#include <deque>
#include <stdlib.h>
#include "stack.cpp"
#include "vector.cpp"

# if FT //CREATE A REAL STL EXAMPLE
	// #include <map.hpp>
	#include "red_black_tree.hpp"
	# include "stack.hpp"
	# include "vector.hpp"
	# include "pair.hpp"
	# include "map.hpp"
# else
	# include <utility>
	# include <map>
	# include <stack>
	# include <vector>
	namespace ft = std;

# endif

bool fncomp (char lhs, char rhs) {return (lhs<rhs);}

struct classcomp
{
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs<rhs;}
};

int	main()
{
	std::cout << "STACK TEST\n";
	stack_test();
	std::cout << "\n\nVECTOR TEST\n";
	vector_test();
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
	std::cout << '\n';
	std::cout << '\n';

	std::cout << "ASSIGN TEST\n";
	ft::vector<int> first;
	ft::vector<int> third;

	first.assign (7,100);
	int myints[] = {1776,7,4};
	third.assign (myints,myints+3);
	std::cout << "Size of first: " << int (first.size()) << '\n';
	// std::cout << "Size of third: " << int (third.size()) << '\n';
	std::cout << '\n';
	std::cout << '\n';

	std::cout << "VECTOR INSERT TEST\n";
	ft::vector<int> vectortest (3,100);
	ft::vector<int>::iterator it;

	it = vectortest.begin();
	it = vectortest.insert ( it , 200 );

	vectortest.insert (it,2,300);

	// "it" no longer valid, get a new one:
	it = vectortest.begin();

	ft::vector<int> anothervector (5,400);
	vectortest.insert (it+1,anothervector.begin(),anothervector.end());

	int myarray [] = { 501,502,503 };
	vectortest.insert (vectortest.begin(), myarray, myarray+3);

	std::cout << "vector test contains:";
	for (it=vectortest.begin(); it<vectortest.end(); it++)
		std::cout << ' ' << *it;
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

	std::cout << "ERASE TEST\n";
	ft::vector<int> newVector;

	// set some values (from 1 to 10)
	for (int i=1; i<=10; i++) newVector.push_back(i);

	// erase the 6th element
	newVector.erase (newVector.begin()+3);

	// erase the first 3 elements:
	newVector.erase (newVector.begin(),newVector.begin()+4);

	std::cout << "newVector contains:";
	for (unsigned i=0; i<newVector.size(); ++i)
		std::cout << ' ' << newVector[i];
	std::cout << '\n';
	std::cout << '\n';
	std::cout << '\n';

	std::cout << "ASIGN TEST\n";
	{
		ft::vector<int> first;
		ft::vector<int> second;
		ft::vector<int> third;

		first.assign (7,100);             // 7 ints with a value of 100

		ft::vector<int>::iterator it;
		it=first.begin()+1;

		second.assign (it,first.end()-1); // the 5 central values of first

		int myints[] = {1776,7,4};
		third.assign (myints,myints+3);   // assigning from array.

		std::cout << "Size of first: " << int (first.size()) << '\n';
		std::cout << "Size of second: " << int (second.size()) << '\n';
		std::cout << "Size of third: " << int (third.size()) << '\n';
	}
	std::cout << '\n';
	std::cout << '\n';

	std::cout << "RELATIONAL OPERATOR TEST\n";
	{
		ft::vector<int> foo (3,100);   // three ints with a value of 100
		ft::vector<int> bar (2,200);   // two ints with a value of 200

		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	}
	std::cout << '\n';
	std::cout << '\n';

	std::cout << "SWAP TEST\n";
	{
		ft::vector<int> foo (3,100);   // three ints with a value of 100
		ft::vector<int> bar (5,200);   // five ints with a value of 200

		foo.swap(bar);

		std::cout << "foo contains:";
		for (ft::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';

		std::cout << "bar contains:";
		for (ft::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}
	std::cout << '\n';
	std::cout << '\n';

	std::cout << "PAIR consinserttor TEST\n";
	{
		ft::pair <std::string,double> product1;                     // default consinserttor
		ft::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
		ft::pair <std::string,double> product3 (product2);          // copy consinserttor

		product1 = ft::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)

		product2.first = "shoes";                  // the type of first is string
		product2.second = 39.90;                   // the type of second is double

		std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
		std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
		std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';
	}
	std::cout << '\n';
	std::cout << '\n';

	std::cout << "PAIR OPERATOR= TEST\n";
	{
		ft::pair <std::string,int> planet, homeplanet;

		planet = ft::make_pair("Earth",6371);

		homeplanet = planet;

		std::cout << "Home planet: " << homeplanet.first << '\n';
		std::cout << "Planet size: " << homeplanet.second << '\n';
	}
	std::cout << '\n';
	std::cout << '\n';

	std::cout << "PAIR RELATIONAL OPERATORS TEST\n";
	{
		ft::pair<int,char> foo (10,'z');
		ft::pair<int,char> bar (90,'a');

		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	}
	std::cout << '\n';
	std::cout << '\n';
	std::cout << "Map TEST\n";

	{
		ft::map<char,int> mymap;

		// first insert function version (single parameter):
		// mymap.insert ( ft::pair<char,int>('a',100) );
		// mymap.insert ( ft::pair<char,int>('z',200) );

		// ft::pair<ft::map<char,int>::iterator,bool> ret;
		// ret = mymap.insert ( ft::pair<char,int>('z',500) );
		// if (ret.second==false) {
		// 	std::cout << "element 'z' already existed";
		// 	std::cout << " with a value of " << ret.first->second << '\n';
		// }

		// // second insert function version (with hint position):
		// ft::map<char,int>::iterator it = mymap.begin();
		// mymap.insert (it, ft::pair<char,int>('b',300));  // max efficiency inserting
		// mymap.insert (it, ft::pair<char,int>('c',400));  // no max efficiency inserting

		// // third insert function version (range insertion):
		// ft::map<char,int> anothermap;
		// anothermap.insert(mymap.begin(),mymap.find('c'));

		// // showing contents:
		// std::cout << "mymap contains:\n";
		// for (it=mymap.begin(); it!=mymap.end(); ++it)
		// 	std::cout << it->first << " => " << it->second << '\n';

		// std::cout << "anothermap contains:\n";
		// for (it=anothermap.begin(); it!=anothermap.end(); ++it)
		// 	std::cout << it->first << " => " << it->second << '\n';
	}

	{
		ft::map<char,int> first;

		// first['a'] = 10;
		// first['b'] = 30;
		// first['c'] = 50;
		// first['d'] = 70;

		// ft::map<char,int> second (first.begin(),first.end());

		// ft::map<char,int> third (second);

		// ft::map<char,int,classcomp> fourth;                 // class as Compare

		// bool(*fn_pt)(char,char) = fncomp;
		// ft::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare
	}

	// std::cout << "RBTREE TEST\n";
	// {
	// 	srand (time(NULL));
	// 	ft::RBTree<char, int> tree;
	// 	ft::RBTree<int, int>::iterator it;
	// 	// int insert(0);
	// 	// int nbInsert(0);

	// 	// std::cout << "Enter the number of insert in the TREE\n";
	// 	// // std::cin >> nbInsert;
	// 	// for (int i = 0; i < 1000000; i++)
	// 	// {
	// 	// 	// std::cout << "Add on Tree\n\n";
	// 	// 	// std::cin >> insert;
	// 	// 	// tree.insert(insert);
	// 	// 	tree.insert(rand() % 999999);
	// 		// tree.printTree();
	// 	// }
	// 	// tree.insert(-1);
	// 	// tree.printTree();
	// 	std::string test;
	// 	std::cout << "Add on Tree\n\n";
	// 	// tree.insert( ft::pair<char,int>('a',100).first );
	// 	while (std::getline(std::cin, test))
	// 	{
	// 		if (test.empty())
	// 			break ;
	// 		// tree.insert(rand() % 500);
	// 		tree.insert(std::atoi(test.c_str()));
	// 		tree.printTree();
	// 		std::cout << "Add on Tree\n\n";
	// 	}
	// 	std::cout << "delete on Tree\n\n";
	// 	tree.erase(tree.begin(), tree.end());
	// 	// it = tree.begin();
	// 	// tree.erase(it);
	// 	// it = tree.begin();
	// 	tree.printTree();

	// 	while (std::getline(std::cin, test))
	// 	{
	// 		if (test.empty())
	// 			break ;
	// 		if (!test.compare("s"))
	// 		{
	// 			std::cout << "tree size = " << tree.size() << std::endl;
	// 			std::cout << "delete on Tree\n\n";
	// 		}
	// 		else
	// 		{
	// 			tree.erase(std::atoi(test.c_str()));
	// 			tree.printTree();
	// 			std::cout << "delete on Tree\n\n";
	// 		}
	// 	}
	// }
	return (0);
}
