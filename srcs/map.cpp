/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:53:13 by chdespon          #+#    #+#             */
/*   Updated: 2022/09/29 19:00:48 by chdespon         ###   ########.fr       */
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
	// std::cout << "\n---Constructor test---" << std::endl;
	// {
	// 	ft::map<char,int> first;

	// 	first['a']=10;
	// 	first['b']=30;
	// 	first['c']=50;
	// 	first['d']=70;

	// 	ft::map<char,int> second (first.begin(),first.end());

	// 	ft::map<char,int> third (second);

	// 	ft::map<char,int,classcomp> fourth;                 // class as Compare

	// 	bool(*fn_pt)(char,char) = fncomp;
	// 	ft::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare
	// }
	// std::cout << "\n---operator= test---" << std::endl;
	// {
	// 	ft::map<char,int> first;
	// 	ft::map<char,int> second;

	// 	first['x']=8;
	// 	first['y']=16;
	// 	first['z']=32;

	// 	second=first;                // second now contains 3 ints
	// 	first=ft::map<char,int>();  // and first is now empty

	// 	std::cout << "Size of first: " << first.size() << '\n';
	// 	std::cout << "Size of second: " << second.size() << '\n';
	// }
	std::cout << "\n---begin&end test---" << std::endl;
	{
		ft::map<char,int> mymap;

		mymap['b'] = 100;
		mymap['a'] = 200;
		// mymap['c'] = 300;
		// mymap['b'];


		// show content:
		// for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		// 	std::cout << it->first << " => " << it->second << '\n';
		std::cout << mymap['b'] << std::endl;
	}
	// std::cout << "\n---rbegin&rend test---" << std::endl;
	// {
	// 	ft::map<char,int> mymap;

	// 	mymap['x'] = 100;
	// 	mymap['y'] = 200;
	// 	mymap['z'] = 300;

	// 	// show content:
	// 	ft::map<char,int>::reverse_iterator rit;
	// 	for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
	// 		std::cout << rit->first << " => " << rit->second << '\n';
	// }
	// std::cout << "\n---operator[] test---" << std::endl;
	// {
	// 	ft::map<char,std::string> mymap;

	// 	mymap['a']="an element";
	// 	mymap['b']="another element";
	// 	mymap['c']=mymap['b'];

	// 	std::cout << "mymap['a'] is " << mymap['a'] << '\n';
	// 	std::cout << "mymap['b'] is " << mymap['b'] << '\n';
	// 	std::cout << "mymap['c'] is " << mymap['c'] << '\n';
	// 	std::cout << "mymap['d'] is " << mymap['d'] << '\n';

	// 	std::cout << "mymap now contains " << mymap.size() << " elements.\n";
	// }
}
