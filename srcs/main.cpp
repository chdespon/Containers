/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:53:29 by chdespon          #+#    #+#             */
/*   Updated: 2022/09/21 16:57:49 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <iostream>
#include <string>
#include <deque>
#include <stdlib.h>
#include "stack.cpp"
#include "vector.cpp"
#include "map.cpp"

# if FT //CREATE A REAL STL EXAMPLE
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

int	main()
{
	std::cout << "STACK TEST\n";
	stack_test();
	std::cout << "\n\nVECTOR TEST\n";
	vector_test();
	std::cout << "\n\nMap TEST\n";
	map_test();

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
