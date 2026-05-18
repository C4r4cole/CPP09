/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:09:12 by fmoulin           #+#    #+#             */
/*   Updated: 2026/05/18 17:52:42 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : _data()
{
    
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &cpy) : _data(cpy._data)
{
    
}

BitcoinExchange &BitcoinExchange::operator =(const BitcoinExchange &src)
{
    if (this != &src)
    {
        _data = src._data;
    }
    return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
    
}

float   BitcoinExchange::findExchangeRate(const std::string &date) const
{

}

void    BitcoinExchange::validateDate(const std::string &date) const
{
    
}

void    BitcoinExchange::validateValue(const std::string &value) const
{
    float nbr;
    int dotFlag = 0;
    int digitFlag = 0;
    
    if (value.empty())
        throw BitcoinExchange::BadInput();
    for (std::string::const_iterator it = value.begin(); it != value.end(); ++it)
    {
        if (*it == '-')
            throw BitcoinExchange::NotAPositiveNumber();        
        if (*it == '.' && dotFlag == 1)
            throw BitcoinExchange::BadInput();
        if (*it == '.')
            dotFlag = 1;
        if (!isdigit(*it) && *it != '.')
            throw BitcoinExchange::BadInput();
        if (isdigit(*it))
            digitFlag = 1;
    }
    if (digitFlag == 0)
        throw BitcoinExchange::BadInput();
        
    nbr = std::atof(value.c_str());
    
    if (nbr < 0)
        throw BitcoinExchange::NotAPositiveNumber();
    if (nbr > 1000)
        throw BitcoinExchange::NumberTooLarge();
}

void    BitcoinExchange::processLine(const std::string &line) const
{
    size_t          pos;
    std::string     date;
    std::string     valueString;
    
    try
    {
        pos = line.find(" | ");
        if (pos == std::string::npos)
            throw BitcoinExchange::BadInput();
        date = line.substr(0, pos);
        valueString = line.substr(pos + 3);
        validateDate(date);
        validateValue(valueString);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void    BitcoinExchange::loadDatabase(const std::string &filename)
{
    std::ifstream   file(filename);
    std::string     line;
    size_t          pos;
    std::string     date;
    std::string     rateString;
    float           rate;
    
    if (!file)
        throw BitcoinExchange::OpenFailure();
    
    std::getline(file, line);
    while (std::getline(file, line))
    {
        pos = line.find(',');
        if (pos == std::string::npos)
            return ;
        date = line.substr(0, pos);
        rateString = line.substr(pos + 1);
        rate = std::atof(rateString.c_str());
        _data[date] = rate;
    }
}

void    BitcoinExchange::processInputFile(const std::string &filename)
{
    std::ifstream   file(filename);
    std::string     line;

    if (!file)
        throw BitcoinExchange::OpenFailure();
    std::getline(file,line);
    while (std::getline(file, line))
    {
        processLine(line);
    }     
}

const char* BitcoinExchange::OpenFailure::what() const throw()
{
    return ("Error: could not open file.");
}

const char* BitcoinExchange::NotAPositiveNumber::what() const throw()
{
    return ("Error: not a positive number.");
}

const char* BitcoinExchange::NumberTooLarge::what() const throw()
{
    return ("Error: too large a number.");
}

const char* BitcoinExchange::BadInput::what() const throw()
{
    return ("Error: bad input => ");
}
