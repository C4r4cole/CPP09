/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 12:00:32 by fmoulin           #+#    #+#             */
/*   Updated: 2026/05/29 18:42:05 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <utility>
#include <cstdlib>
#include <cctype>
#include <climits>

class PmergeMe
{
private:
    std::vector<int>                    _vectorOriginal;
    std::vector<std::pair<int, int> >   _vectorPairs;
    std::deque<int>                     _dequeOriginal;
    std::deque<std::pair<int, int> >    _dequePairs;
    bool                                _hasStraggler;
    int                                 _straggler;
public:
    PmergeMe();
    PmergeMe(const PmergeMe &cpy);
    PmergeMe &operator =(const PmergeMe &src);
    ~PmergeMe();

    /* ---------------------------- VECTOR VERSION ---------------------------- */
    void                                    vParseInput(int argc, char **argv);
    void                                    vMakePairs(std::vector<int> &chain, std::vector<std::pair<int, int> > &pairChain);
    void                                    vMakeChains(std::vector<std::pair<int, int> > &pairContainer, std::vector<int> &chainA, std::vector<int> &chainB);
    void                                    vInsertInt(std::vector<int> &chainA, std::vector<int> &chainB);
    std::vector<int>                        vRecursiveSort(std::vector<int> &chain);

    std::vector<int>                        getVOriginal() const;

    /* ---------------------------- DEQUE VERSION ---------------------------- */
    void                                    dParseInput(int argc, char **argv);
    void                                    dMakePairs(std::deque<int> &chain, std::deque<std::pair<int, int> > &pairChain);
    void                                    dMakeChains(std::deque<std::pair<int, int> > &pairContainer, std::deque<int> &chainA, std::deque<int> &chainB);
    void                                    dInsertInt(std::deque<int> &chainA, std::deque<int> &chainB);
    std::deque<int>                         dRecursiveSort(std::deque<int> &chain);

    std::deque<int>                        getDOriginal() const;
};

#endif