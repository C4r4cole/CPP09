/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:32:59 by fmoulin           #+#    #+#             */
/*   Updated: 2026/05/29 18:50:22 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	try
	{
		if (argc < 2)
			throw std::out_of_range("not enough arguments");
		PmergeMe							fordJohnson;
		
		/* ------------ VECTOR VERSION ------------ */
		std::vector<int>					vOriginal;
		std::vector<int>					vSorted;
		
		fordJohnson.vParseInput(argc, argv);
		
		vOriginal = fordJohnson.getVOriginal();
		vSorted = fordJohnson.vRecursiveSort(vOriginal);
	
		/* ------------ DEQUE VERSION ------------ */
		std::deque<int>					dOriginal;
		std::deque<int>					dSorted;
		
		fordJohnson.dParseInput(argc, argv);
		
		dOriginal = fordJohnson.getDOriginal();
		dSorted = fordJohnson.dRecursiveSort(dOriginal);
		
		/* --------------- DISPLAY --------------- */
		std::cout << "Before :\t";
		for (int i = 1; i < argc; i++)
			std::cout << argv[i] << " ";
		std::cout << std::endl;
		
		std::cout << "After :\t\t";
		for (std::vector<int>::iterator it = vSorted.begin(); it != vSorted.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return 0;
}
