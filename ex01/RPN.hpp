/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 16:40:15 by fmoulin           #+#    #+#             */
/*   Updated: 2026/05/21 10:37:10 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <stack>
#include <list>
#include <cstdlib>

class RPN
{
private:
    std::stack<int, std::list<int> > _stack;
    int             _result;

    void    pushOrCalculate(std::string &element);
    void    calculate(std::string op);
public:
    RPN();
    RPN(const RPN &cpy);
    RPN &operator =(const RPN &src);
    ~RPN();
    
    void    parseInput(const std::string &argv);
    void    displayResult(void);
};

#endif