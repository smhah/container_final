/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 16:37:43 by smhah             #+#    #+#             */
/*   Updated: 2022/06/10 06:25:22 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vector.hpp"
#include <vector>
#include "iterator_traits.hpp"

int main(int ac, char **av)
{
    /*------------ std::vector ---------*/
    ft::Vector<int> my_v;
    // std::vector<int> v(3, 4);
    // std::vector<int>::iterator it, it1, tm;
    // it = v.begin();
    // it1 = v.begin() + 1;
	// tm = it++;
	// std::cout << "*it = " << *it << "*tm = " << *tm << std::endl;
    // /*----------------------------------*/
    // /*------------ ft::Vector ---------*/
    // ft::Vector<int> my_v(3, 4);
    // ft::Vector<int>::iterator my_it, my_it1, tmp;
    // my_it = my_v.begin();
    // my_it1 = my_v.begin() + 1;
	// tmp = my_it++;
    // std::cout << "my_*it = " << *my_it << "*tmp = " << *tmp << std::endl;
    ft::Vector<std::string> ft_v1(10, "string1");
    ft::Vector<std::string> ft_v2(10, "string2");
    ft_v1 = ft_v2;
	system("leaks a.out");
}