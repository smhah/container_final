/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapmain.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 22:45:00 by smhah             #+#    #+#             */
/*   Updated: 2022/06/09 09:55:35 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Map.hpp"
# include <map>
// Driver Code
int main()
{
	// std::map<int,int> mymap;
	
	// // mymap.insert ( std::pair<char,int>('6',100) );
  	// // mymap.insert ( std::pair<char,int>('3',200) );
	// // mymap.insert ( std::pair<char,int>('9',200) );
	// // mymap.insert ( std::pair<char,int>('5',200) );
	// // mymap.insert ( std::pair<char,int>('8',200) );
	// mymap[6] = 100;
	// mymap[3] = 200;
	// mymap[9] = 200;
	// mymap[5] = 200;
	// mymap[8] = 200;
	// std::map<int, int>::iterator it2 = mymap.end();
	
	// //it2 = mymap.begin();
	// std::cout << "it2 is " << it2->first << std::endl;
	// it2--;
	// std::cout << "it2 is " << it2->first << std::endl;
	// ft::map<int, int> m;
	// ft::pair<int, int> planet1;
	// ft::pair<int, int> planet3;
	// ft::pair<int, int> planet5;
	// ft::pair<int, int> planet6;
	// ft::pair<int, int> planet7;
	// ft::pair<int, int> planet9;
	// ft::pair<int, int> planet8;


	
	// //it = m.begin();
	// //std::cout << "it 1 is " << it->first << std::endl;
	// //std::cout << "*it = " << *it << std::endl;

	// planet1 = ft::make_pair(1, 1);
	// planet3 = ft::make_pair(3, 2);
	// planet5 = ft::make_pair(5, 3);
	// planet6 = ft::make_pair(6, 4);
	// planet7 = ft::make_pair(7, 4);
	// planet9 = ft::make_pair(9, 5);
	// planet8 = ft::make_pair(8, 6);
	// //std::cout << "string is "<< planet.first << " int is " << planet.second << std::endl;
	// // root = m.insert(root, planet7, root);
	// // root = m.insert(root, planet3, root);
	// // root = m.insert(root, planet9, root);
	// // root = m.insert(root, planet5, root);
	// // root = m.insert(root, planet8, root);
	// m.insert(planet6);
	// m.insert(planet3);
	// m.insert(planet9);
	// m.insert(planet5);
	// m.insert(planet8);
	// //m.erase(planet9.first);
	// //m.erase(9);
	// ft::map<int, int>::const_iterator it;
	// ft::map<int, int>::iterator it1;
	// // ft::map<int, int>::reverse_iterator rit;

	// // rit = m.rbegin();
	// // std::cout << "rbegin is " << rit->first << std::endl;
	// it = m.begin();
	// std::cout << "test const iterator " << it->first << std::endl;
	// // std::cout << "o_lower_bound " << mymap.lower_bound(10)->first << std::endl;
	// // std::cout << mymap.end()->first << std::endl;
	// // std::cout << "lower_bound " << m.lower_bound(10)->first << std::endl;
	// //it = m.find(0);
	// // /* The constructed AVL Tree would be
	// // 			30
	// // 		/ \
	// // 		20 40
	// // 		/ \ \
	// // 	10 25 50
	// // */
	// // std::cout << "Preorder traversal of the "
	// // 		"constructed AVL tree is \n";
	// //m.preOrder(root);
	// m.printTree(m.get_root(), nullptr, false);
	std::map<int, std::string> m;
	ft::map<int, std::string> ft_m;
	for (size_t i = 0; i < 1e6; ++i)
	{
		m.insert(std::make_pair(i, "value"));
		ft_m.insert(ft::make_pair(i, "value"));
	}
	return 0;
}

// This code is contributed by
// rathbhupendra