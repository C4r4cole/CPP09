/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:32:59 by fmoulin           #+#    #+#             */
/*   Updated: 2026/05/30 18:07:24 by fmoulin          ###   ########.fr       */
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
		clock_t								vStart;
		clock_t 							vEnd;
		double								vElapsed;
		vStart = clock();
		
		std::vector<int>					vOriginal;
		std::vector<int>					vSorted;
		
		fordJohnson.vParseInput(argc, argv);
		
		vOriginal = fordJohnson.getVOriginal();
		vSorted = fordJohnson.vRecursiveSort(vOriginal);
		
		vEnd = clock();
		vElapsed = static_cast<double>(vEnd - vStart) / CLOCKS_PER_SEC;
		
		
		/* ------------ DEQUE VERSION ------------ */
		clock_t								dStart;
		clock_t 							dEnd;
		double								dElapsed;
		dStart = clock();
		
		std::deque<int>					dOriginal;
		std::deque<int>					dSorted;
		
		fordJohnson.dParseInput(argc, argv);
		
		dOriginal = fordJohnson.getDOriginal();
		dSorted = fordJohnson.dRecursiveSort(dOriginal);

		dEnd = clock();
		dElapsed = static_cast<double>(dEnd - dStart) / CLOCKS_PER_SEC;
		
		/* --------------- DISPLAY --------------- */
		std::cout << "Before :\t";
		for (int i = 1; i < argc; i++)
		std::cout << argv[i] << " ";
		std::cout << std::endl;
		
		std::cout << "After :\t\t";
		for (std::vector<int>::iterator it = vSorted.begin(); it != vSorted.end(); ++it)
		std::cout << *it << " ";
		std::cout << std::endl;
			
		std::cout	<< "Time to process a range of \t"
					<< vOriginal.size()
					<< " elements with std::vector : "
					<< vElapsed * 1000000
					<< " us"
					<< std::endl;

		std::cout	<< "Time to process a range of \t"
					<< dOriginal.size()
					<< " elements with std::deque : "
					<< dElapsed * 1000000
					<< " us"
					<< std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return 0;
}
