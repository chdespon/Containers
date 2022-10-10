/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:53:13 by chdespon          #+#    #+#             */
/*   Updated: 2022/10/10 19:23:24 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <iostream>
#include <string>
#include <deque>
#include <stdlib.h>

# if FT //CREATE A REAL STL EXAMPLE
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

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp
{
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs<rhs;}
};


void	map_test(void)
{
	std::cout << "\n\nPair TEST\n";
	{
		std::cout << "\n---Constructor test---" << std::endl;
		{
			ft::pair <std::string,double> product1;                     // default constructor
			ft::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
			ft::pair <std::string,double> product3 (product2);          // copy constructor

			product1 = ft::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)

			product2.first = "shoes";                  // the type of first is string
			product2.second = 39.90;                   // the type of second is double

			std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
			std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
			std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';
		}
		std::cout << "\n---operator= test---" << std::endl;
		{
			ft::pair <std::string,int> planet, homeplanet;

			planet = ft::make_pair("Earth",6371);

			homeplanet = planet;

			std::cout << "Home planet: " << homeplanet.first << '\n';
			std::cout << "Planet size: " << homeplanet.second << '\n';
		}
		std::cout << "\n---make_pair test---" << std::endl;
		{
			ft::pair <int,int> foo;
			ft::pair <int,int> bar;

			foo = ft::make_pair (10,20);
			bar = ft::make_pair (10.5,'A'); // ok: implicit conversion from pair<double,char>

			std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
			std::cout << "bar: " << bar.first << ", " << bar.second << '\n';
		}
		std::cout << "\n---relational operators test---" << std::endl;
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
	}
	std::cout << "\n\nMap TEST\n";
	std::cout << "\n---Constructor test---" << std::endl;
	{
		ft::map<char,int> first;

		first['a']=10;
		first['b']=30;
		first['c']=50;
		first['d']=70;

		ft::map<char,int> second (first.begin(),first.end());

		ft::map<char,int> third (second);

		ft::map<char,int,classcomp> fourth;                 // class as Compare

		bool(*fn_pt)(char,char) = fncomp;
		ft::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare
	}
	std::cout << "\n---operator= test---" << std::endl;
	{
		ft::map<char,int> first;
		ft::map<char,int> second;

		first['x']=8;
		first['y']=16;
		first['z']=32;

		second=first;                // second now contains 3 ints
		first=ft::map<char,int>();  // and first is now empty

		std::cout << "Size of first: " << first.size() << '\n';
		std::cout << "Size of second: " << second.size() << '\n';
	}
	std::cout << "\n---begin&end test---" << std::endl;
	{
		ft::map<char,int> mymap;

		mymap['b'] = 100;
		mymap['a'] = 200;
		mymap['c'] = 300;
		// mymap['b'];


		// show content:
		for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
	std::cout << "\n---rbegin&rend test---" << std::endl;
	{
		ft::map<char,int> mymap;

		mymap['x'] = 100;
		mymap['y'] = 200;
		mymap['z'] = 300;

		// show content:
		ft::map<char,int>::reverse_iterator rit;
		for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
			std::cout << rit->first << " => " << rit->second << '\n';
	}
	std::cout << "\n---empty test---" << std::endl;
	{
		ft::map<char,int> mymap;

		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;

		while (!mymap.empty())
		{
			std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
			mymap.erase(mymap.begin());
		}
	}
	std::cout << "\n---size test---" << std::endl;
	{
		ft::map<char,int> mymap;
		mymap['a']=101;
		mymap['b']=202;
		mymap['c']=302;

		std::cout << "mymap.size() is " << mymap.size() << '\n';
	}
	std::cout << "\n---max_size test---" << std::endl;
	{
		int i;
		ft::map<int,int> mymap;
		if (mymap.max_size()>1000)
		{
			for (i=0; i<1000; i++) mymap[i]=0;
			std::cout << "The map contains 1000 elements.\n";
		}
		else std::cout << "The map could not hold 1000 elements.\n";
	}
	std::cout << "\n---operator[] test---" << std::endl;
	{
		ft::map<char,std::string> mymap;

		mymap['a']="an element";
		mymap['b']="another element";
		mymap['c']=mymap['b'];

		std::cout << "mymap['a'] is " << mymap['a'] << '\n';
		std::cout << "mymap['b'] is " << mymap['b'] << '\n';
		std::cout << "mymap['c'] is " << mymap['c'] << '\n';
		std::cout << "mymap['d'] is " << mymap['d'] << '\n';

		std::cout << "mymap now contains " << mymap.size() << " elements.\n";
	}
	{
		ft::map<char,int> mymap;

		// first insert function version (single parameter):
		mymap.insert ( ft::pair<char,int>('a',100) );
		mymap.insert ( ft::pair<char,int>('z',200) );

		ft::pair<ft::map<char,int>::iterator,bool> ret;
		ret = mymap.insert ( ft::pair<char,int>('z',500) );
		if (ret.second==false) {
			std::cout << "element 'z' already existed";
			std::cout << " with a value of " << ret.first->second << '\n';
		}

		// second insert function version (with hint position):
		ft::map<char,int>::iterator it = mymap.begin();
		mymap.insert (it, ft::pair<char,int>('b',300));  // max efficiency inserting
		mymap.insert (it, ft::pair<char,int>('c',400));  // no max efficiency inserting

		// third insert function version (range insertion):
		ft::map<char,int> anothermap;
		anothermap.insert(mymap.begin(),mymap.find('c'));

		// showing contents:
		std::cout << "mymap contains:\n";
		for (it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		std::cout << "anothermap contains:\n";
		for (it=anothermap.begin(); it!=anothermap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
}
