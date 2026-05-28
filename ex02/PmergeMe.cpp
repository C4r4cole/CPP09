/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 12:00:29 by fmoulin           #+#    #+#             */
/*   Updated: 2026/05/28 18:25:23 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char **argv) : _original(), _pairs(), _hasStraggler(false), _straggler(0)
{

}

PmergeMe::PmergeMe(const PmergeMe &cpy)
    :   _original(cpy._original),
        _pairs(cpy._pairs),
        _hasStraggler(cpy._hasStraggler),
        _straggler(cpy._straggler)
{

}

PmergeMe &PmergeMe::operator =(const PmergeMe &src)
{
    if (this != &src)
    {
        _original = src._original;
        _pairs = src._pairs;
        _hasStraggler = src._hasStraggler;
        _straggler = src._straggler;
    }
    return (*this);
}

void    PmergeMe::parseInput(int argc, char **argv)
{
    int nbr;
    
    if ((argc - 1) % 2 != 0)
        _hasStraggler = true;
    if (_hasStraggler)
        _straggler = atoi(argv[argc - 1]);
    for (int i = 1; i < argc; i++)
    {
        nbr = atoi(argv[i]);
        _original.push_back(nbr);
    }
}

void    PmergeMe::makePairs(std::vector<int> &chain, std::vector<std::pair<int, int> > &pairChain)
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

void    PmergeMe::makeChains(std::vector<std::pair<int, int> > &pairContainer, std::vector<int> &chainA, std::vector<int> &chainB)
{
    chainA.clear();
    chainB.clear();
    for (std::vector<std::pair<int, int> >::iterator it = pairContainer.begin(); it != pairContainer.end(); ++it)
    {
        chainA.push_back(it->second);
        chainB.push_back(it->first);
    }
}

void    PmergeMe::insertInt(std::vector<int> &chainA, std::vector<int> &chainB)
{
    for (std::vector<int>::iterator it1 = chainB.begin(); it1 != chainB.end(); ++it1)
    {
        bool    inserted = false;
        
        for (std::vector<int>::iterator it2 = chainA.begin(); it2 != chainA.end(); ++it2)
        {
            if (*it2 > *it1)
            {
                chainA.insert(it2, *it1);
                inserted = true;
                break ;
            }
        }
        if (!inserted)
            chainA.push_back(*it1);
    }
}

std::vector<int>    PmergeMe::recursiveSort(std::vector<int> &chain)
{
    std::vector<std::pair<int, int> >   pairContainer;
    std::vector<int>                    localMainChain;
    std::vector<int>                    localPendingChain;
    bool                                hasLocalStraggler = false;
    int                                 localStraggler;
    std::vector<int>                    tempStragglerVec;
    
    if (chain.size() <= 1)
        return (chain);
    makePairs(chain, pairContainer);
    makeChains(pairContainer, localMainChain, localPendingChain);
    localMainChain = recursiveSort(localMainChain);
    if (chain.size() % 2 != 0)
        hasLocalStraggler = true;
    if (hasLocalStraggler)
    {
        localStraggler = chain.back();
        tempStragglerVec.push_back(localStraggler);
    }
    insertInt(localMainChain, localPendingChain);
    if (hasLocalStraggler)
        insertInt(localMainChain, tempStragglerVec);
    return (localMainChain);
}


PmergeMe::~PmergeMe()
{
    
}