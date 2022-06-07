/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdespon <chdespon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:53:29 by chdespon          #+#    #+#             */
/*   Updated: 2022/06/07 20:19:08 by chdespon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "stack.hpp"

int	main()
{
	ft::stack<int>::value_type stack_int;

	stack_int = 69;

	std::cout << "The value_type is int = " << stack_int << std::endl;

	ft::stack<int> s1;
	s1.push(stack_int);
	std::cout << "The element at the top of the stack is "
			<< s1.top( ) << "." << std::endl;
	return (0);
}