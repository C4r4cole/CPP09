/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 12:00:32 by fmoulin           #+#    #+#             */
/*   Updated: 2026/05/28 18:13:31 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <utility>

class PmergeMe
{
private:
    std::vector<int>                    _original;
    std::vector<std::pair<int, int> >   _pairs;
    bool                                _hasStraggler;
    int                                 _straggler;
    std::vector<int>                    _mainChain;
    std::vector<int>                    _pendingChain;
public:
    PmergeMe(int argc, char **argv);
    PmergeMe(const PmergeMe &cpy);
    PmergeMe &operator =(const PmergeMe &src);
    ~PmergeMe();

    void                parseInput(int argc, char **argv);
    void                makePairs(std::vector<int> &chain, std::vector<std::pair<int, int> > &pairChain);
    void                makeChains(std::vector<std::pair<int, int> > &pairContainer, std::vector<int> &chainA, std::vector<int> &chainB);
    void                insertInt(std::vector<int> &chainA, std::vector<int> &chainB);
    std::vector<int>    recursiveSort(std::vector<int> &chain);
};

#endif