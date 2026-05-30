/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 12:00:29 by fmoulin           #+#    #+#             */
/*   Updated: 2026/05/30 18:44:08 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
    :   _vectorOriginal(),
        _vectorPairs(),
        _dequeOriginal(),
        _dequePairs(),
        _hasStraggler(false),
        _straggler(0)
{

}

PmergeMe::PmergeMe(const PmergeMe &cpy)
    :   _vectorOriginal(cpy._vectorOriginal),
        _vectorPairs(cpy._vectorPairs),
        _dequeOriginal(cpy._dequeOriginal),
        _dequePairs(cpy._dequePairs),
        _hasStraggler(cpy._hasStraggler),
        _straggler(cpy._straggler)
{

}

PmergeMe &PmergeMe::operator =(const PmergeMe &src)
{
    if (this != &src)
    {
        _vectorOriginal = src._vectorOriginal;
        _vectorPairs = src._vectorPairs;
        _dequeOriginal = src._dequeOriginal;
        _dequePairs = src._dequePairs;
        _hasStraggler = src._hasStraggler;
        _straggler = src._straggler;
    }
    return (*this);
}

/* ---------------------------- VECTOR VERSION ---------------------------- */

void    PmergeMe::vParseInput(int argc, char **argv)
{
    int nbr;
    
    if ((argc - 1) % 2 != 0)
        _hasStraggler = true;
    if (_hasStraggler)
        _straggler = atoi(argv[argc - 1]);
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg.empty())
            throw std::out_of_range("an argument can not be empty");
        for (int j = 0; argv[i][j]; j++)
        {
            if (!isdigit(argv[i][j]))
                throw std::out_of_range("an argument is not a positive int");
        }
        long tmp = strtol(argv[i], NULL, 10);
        if (tmp > INT_MAX || tmp < INT_MIN)
            throw std::out_of_range("can not be more than INT_MAX or less than INT_MIN");
        nbr = atoi(argv[i]);
        _vectorOriginal.push_back(nbr);
    }
}

void    PmergeMe::vMakePairs(std::vector<int> &chain, std::vector<std::pair<int, int> > &pairChain)
{
    for (size_t i = 0; i < chain.size(); i += 2)
    {
        int next;

        if (i + 1 < chain.size())
        {
            next = chain[i + 1];
          
            if (chain[i] <= next)
                pairChain.push_back(std::pair<int, int>(chain[i], next));
            else
                pairChain.push_back(std::pair<int, int>(next, chain[i]));
        }
    }
}

void    PmergeMe::vMakeChains(std::vector<std::pair<int, int> > &pairContainer, std::vector<int> &chainA, std::vector<int> &chainB)
{
    chainA.clear();
    chainB.clear();
    for (std::vector<std::pair<int, int> >::iterator it = pairContainer.begin(); it != pairContainer.end(); ++it)
    {
        chainA.push_back(it->second);
        chainB.push_back(it->first);
    }
}

void    PmergeMe::vInsertInt(std::vector<int> &chainA, std::vector<int> &chainB)
{
	std::vector<int>	suite;
	std::vector<size_t>	order;

	suite = vJacobsthal(chainB);
	order = vInsertionOrder(suite, chainB);
    for (std::vector<size_t>::iterator it1 = order.begin(); it1 != order.end(); ++it1)
    {
        bool    inserted = false;
        
        for (std::vector<int>::iterator it2 = chainA.begin(); it2 != chainA.end(); ++it2)
        {
            if (*it2 > chainB[*it1])
            {
                chainA.insert(it2, chainB[*it1]);
                inserted = true;
                break ;
            }
        }
        if (!inserted)
            chainA.push_back(chainB[*it1]);
    }
}

std::vector<int>    PmergeMe::vRecursiveSort(std::vector<int> &chain)
{
    std::vector<std::pair<int, int> >   pairContainer;
    std::vector<int>                    mainChain;
    std::vector<int>                    pendingChain;
    bool                                hasLocalStraggler = false;
    int                                 localStraggler;
    std::vector<int>                    tempStragglerVec;
	
    if (chain.size() <= 1)
        return (chain);
    vMakePairs(chain, pairContainer);
    vMakeChains(pairContainer, mainChain, pendingChain);
    mainChain = vRecursiveSort(mainChain);
    if (chain.size() % 2 != 0)
        hasLocalStraggler = true;
    if (hasLocalStraggler)
    {
        localStraggler = chain.back();
        tempStragglerVec.push_back(localStraggler);
    }
    vInsertInt(mainChain, pendingChain);
    if (hasLocalStraggler)
        vInsertInt(mainChain, tempStragglerVec);
    return (mainChain);
}

std::vector<int>    PmergeMe::getVOriginal() const
{
    return (_vectorOriginal);
}

std::vector<int>	PmergeMe::vJacobsthal(std::vector<int> &chain)
{
	std::vector<int>	suite;
	size_t				current = 1;
	int					prev1 = 1;
	int					prev2 = 0;
	
	while (current < chain.size())
	{
		current = prev1 + (2 * prev2);
		prev2 = prev1;
		prev1 = current;
		suite.push_back(current);
	}
	return (suite);
}

std::vector<size_t>	PmergeMe::vInsertionOrder(std::vector<int> &suite, std::vector<int> &chain)
{
    std::vector<size_t> order;

    if (chain.empty())
        return order;

    order.push_back(0);

    for (size_t i = 1; i < suite.size(); ++i)
    {
        size_t previous = static_cast<size_t>(suite[i - 1]);
        size_t current = static_cast<size_t>(suite[i]);

        if (current > chain.size())
            current = chain.size();

        size_t countdown = current;

        while (countdown > previous)
        {
            order.push_back(countdown - 1);
            --countdown;
        }

        if (current == chain.size())
            break;
    }

    return order;
}

/* ---------------------------- DEQUE VERSION ---------------------------- */

void    PmergeMe::dParseInput(int argc, char **argv)
{
    int nbr;
    
    if ((argc - 1) % 2 != 0)
        _hasStraggler = true;
    if (_hasStraggler)
        _straggler = atoi(argv[argc - 1]);
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg.empty())
            throw std::out_of_range("an argument can not be empty");
        for (int j = 0; argv[i][j]; j++)
        {
            if (!isdigit(argv[i][j]))
                throw std::out_of_range("an argument is not a positive int");
        }
		errno = 0;
        long tmp = strtol(argv[i], NULL, 10);
		if (errno == ERANGE)
			throw std::out_of_range("can not be more than LONG_MAX");
		if (tmp <= 0)
			throw std::out_of_range("an argument is not a positive int");
        if (tmp > INT_MAX)
            throw std::out_of_range("can not be more than INT_MAX");
        nbr = static_cast<int>(tmp);
        _dequeOriginal.push_back(nbr);
    }
}

void    PmergeMe::dMakePairs(std::deque<int> &chain, std::deque<std::pair<int, int> > &pairChain)
{
    for (size_t i = 0; i < chain.size(); i += 2)
    {
        int next;

        if (i + 1 < chain.size())
        {
            next = chain[i + 1];
          
            if (chain[i] <= next)
                pairChain.push_back(std::pair<int, int>(chain[i], next));
            else
                pairChain.push_back(std::pair<int, int>(next, chain[i]));
        }
    }
}

void    PmergeMe::dMakeChains(std::deque<std::pair<int, int> > &pairContainer, std::deque<int> &chainA, std::deque<int> &chainB)
{
    chainA.clear();
    chainB.clear();
    for (std::deque<std::pair<int, int> >::iterator it = pairContainer.begin(); it != pairContainer.end(); ++it)
    {
        chainA.push_back(it->second);
        chainB.push_back(it->first);
    }
}

void    PmergeMe::dInsertInt(std::deque<int> &chainA, std::deque<int> &chainB)
{
	std::deque<int>	suite;
	std::deque<size_t>	order;

	suite = dJacobsthal(chainB);
	order = dInsertionOrder(suite, chainB);
	
    for (std::deque<size_t>::iterator it1 = order.begin(); it1 != order.end(); ++it1)
    {
        bool    inserted = false;
        
        for (std::deque<int>::iterator it2 = chainA.begin(); it2 != chainA.end(); ++it2)
        {
            if (*it2 > chainB[*it1])
            {
                chainA.insert(it2, chainB[*it1]);
                inserted = true;
                break ;
            }
        }
        if (!inserted)
            chainA.push_back(chainB[*it1]);
    }
}

std::deque<int>    PmergeMe::dRecursiveSort(std::deque<int> &chain)
{
    std::deque<std::pair<int, int> >   pairContainer;
    std::deque<int>                    mainChain;
    std::deque<int>                    pendingChain;
    bool                                hasLocalStraggler = false;
    int                                 localStraggler;
    std::deque<int>                    tempStragglerVec;
    
    if (chain.size() <= 1)
        return (chain);
    dMakePairs(chain, pairContainer);
    dMakeChains(pairContainer, mainChain, pendingChain);
    mainChain = dRecursiveSort(mainChain);
    if (chain.size() % 2 != 0)
        hasLocalStraggler = true;
    if (hasLocalStraggler)
    {
        localStraggler = chain.back();
        tempStragglerVec.push_back(localStraggler);
    }
    dInsertInt(mainChain, pendingChain);
    if (hasLocalStraggler)
        dInsertInt(mainChain, tempStragglerVec);
    return (mainChain);
}

std::deque<int>    PmergeMe::getDOriginal() const
{
    return (_dequeOriginal);
}

std::deque<int>	PmergeMe::dJacobsthal(std::deque<int> &chain)
{
	std::deque<int>	suite;
	size_t				current = 1;
	int					prev1 = 1;
	int					prev2 = 0;
	
	while (current < chain.size())
	{
		current = prev1 + (2 * prev2);
		prev2 = prev1;
		prev1 = current;
		suite.push_back(current);
	}
	return (suite);
}

std::deque<size_t>	PmergeMe::dInsertionOrder(std::deque<int> &suite, std::deque<int> &chain)
{
    std::deque<size_t> order;

    if (chain.empty())
        return order;

    order.push_back(0);

    for (size_t i = 1; i < suite.size(); ++i)
    {
        size_t previous = static_cast<size_t>(suite[i - 1]);
        size_t current = static_cast<size_t>(suite[i]);

        if (current > chain.size())
            current = chain.size();

        size_t countdown = current;

        while (countdown > previous)
        {
            order.push_back(countdown - 1);
            --countdown;
        }

        if (current == chain.size())
            break;
    }

    return order;
}

PmergeMe::~PmergeMe()
{
    
}