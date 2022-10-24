/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:53:29 by chdespon          #+#    #+#             */
/*   Updated: 2022/10/24 18:40:20 by chdespon         ###   ########.fr       */
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
#include "set.cpp"

# if FT //CREATE A REAL STL EXAMPLE
	#include "red_black_tree.hpp"
	# include "stack.hpp"
	# include "vector.hpp"
	# include "pair.hpp"
	# include "map.hpp"
	# include "set.hpp"
# else
	# include <utility>
	# include <map>
	# include <stack>
	# include <vector>
	# include <set>
	namespace ft = std;
# endif

int	main()
{
	std::cout << "STACK TEST\n";
	stack_test();
	std::cout << "\n\nVECTOR TEST\n";
	vector_test();
	map_test();
	std::cout << "\n\nSET TEST\n";
	set_test();
	return (0);
}
