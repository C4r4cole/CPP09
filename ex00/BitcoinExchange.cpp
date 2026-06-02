/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:09:12 by fmoulin           #+#    #+#             */
/*   Updated: 2026/05/20 16:00:12 by fmoulin          ###   ########.fr       */
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
    std::map<std::string, float>::const_iterator it = _data.lower_bound(date);

    if (it == _data.end())
    {
        --it;
        return (it->second);
    }
    
    if (it->first != date)
    {
        if (it == _data.begin())
            throw BitcoinExchange::BadInput();
        --it;
    }
    return (it->second);
}

void    BitcoinExchange::validateDate(const std::string &date) const
{
	std::string	yearString;
    int			year;
    std::string monthString;
    int         month;
    std::string dayString;
    int         day;
	bool		isLeap;
    int			maxDay;
    
	yearString = date.substr(0, 4);
	monthString = date.substr(5, 2);
	dayString = date.substr(8, 2);
	year = atoi(yearString.c_str());
	month = atoi(monthString.c_str());
	day = atoi(dayString.c_str());
	isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    if (date.empty())
        throw BitcoinExchange::BadInput();
    if (date.size() != 10)
        throw BitcoinExchange::BadInput();
    if (date[4] != '-')
        throw BitcoinExchange::BadInput();
    if (date[7] != '-')
    	throw BitcoinExchange::BadInput();

    if (month < 1 || month > 12)
        throw BitcoinExchange::BadInput();
    if (day < 1 || day > 31)
        throw BitcoinExchange::BadInput();

    switch (month) {
        case 2:
            maxDay = isLeap ? 29 : 28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            maxDay = 30;
            break;
        default:
            maxDay = 31;
            break;
    }

    if (day > maxDay)
        throw BitcoinExchange::BadInput();
    for (int i = 0; i < 10; i++)
    {
        if (date[i] == '-')
            continue ;
        if (!isdigit(date[i]))
            throw BitcoinExchange::BadInput();
    }
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
        
    nbr = atof(value.c_str());
    
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
	float			value;
	float			rate;
	float			result;
    
    try
    {
        pos = line.find(" | ");
        if (pos == std::string::npos)
            throw BitcoinExchange::BadInput();
        date = line.substr(0, pos);
        valueString = line.substr(pos + 3);
        validateDate(date);
        validateValue(valueString);
		value = atof(valueString.c_str());
		rate = this->findExchangeRate(date);
		result = value * rate;
		std::cout << date << " => " << value << " = " << result << std::endl;
    }
	catch (const BitcoinExchange::BadInput &e)
	{
		std::cerr << e.what() << line << std::endl;
	}
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void    BitcoinExchange::loadDatabase(const std::string &filename)
{
    std::ifstream   file(filename.c_str());
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
        rate = atof(rateString.c_str());
        _data[date] = rate;
    }
}

void    BitcoinExchange::processInputFile(const std::string &filename)
{
    std::ifstream   file(filename.c_str());
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
