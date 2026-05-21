/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 16:40:09 by fmoulin           #+#    #+#             */
/*   Updated: 2026/05/21 10:38:24 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{
    
}

RPN::RPN(const RPN &cpy) : _stack(cpy._stack)
{
    
}

RPN &RPN::operator =(const RPN &src)
{
    if (this != &src)
    {
        _stack = src._stack;
    }
    return (*this);
}

void    RPN::calculate(std::string op)
{
    int right;
    int left;
    
    if (_stack.size() >= 2)
    {
        right = _stack.top();
        _stack.pop();
        left = _stack.top();
        _stack.pop();
    }
    if (op == "+")
    {
        _result = left + right;
        _stack.push(_result);
    }
    if (op == "-")
    {
        _result = left - right;
        _stack.push(_result);
    }
    if (op == "*")
    {
        _result = left * right;
        _stack.push(_result);
    }
    if (op == "/")
    {
        _result = left / right;
        _stack.push(_result);
    }
}

void RPN::pushOrCalculate(std::string &element)
{
    if (isdigit(element[0]))
        _stack.push(atoi(element.c_str()));
    else
    {
        calculate(element);
    }
}

void    RPN::parseInput(const std::string &argv)
{
    std::string element;
    size_t      prev = 0;
    
    for (size_t i = 0; i < argv.length(); ++i)
    {
        if (argv[i] == ' ')
        {
            element = argv.substr(prev, i - prev);
            pushOrCalculate(element);
            prev = i + 1;
        }
        else if (i == argv.length() - 1)
        {
            element = argv.substr(prev, i - prev + 1);
            pushOrCalculate(element);
            prev = i + 1;
        }
    }
}

void    RPN::displayResult(void)
{
    if (_stack.size() == 1)
    {
        std::cout << _result << std::endl;
    }
    else
    {
        std::cout << "ERROR!!!" << std::endl;
    }
}
    
RPN::~RPN()
{
    
}
