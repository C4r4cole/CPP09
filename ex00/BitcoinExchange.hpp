/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:09:17 by fmoulin           #+#    #+#             */
/*   Updated: 2026/05/20 15:53:40 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <map>
#include <cstdlib>

class BitcoinExchange
{
    private:
        std::map<std::string, float> _data;

        float   findExchangeRate(const std::string &date) const;
        void    validateDate(const std::string &date) const;
        void    validateValue(const std::string &value) const;
        void    processLine(const std::string &line) const;
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &cpy);
        BitcoinExchange &operator =(const BitcoinExchange &src);
        ~BitcoinExchange();

        void    loadDatabase(const std::string &filename);
        void    processInputFile(const std::string &filename);        

        class OpenFailure : public std::exception
        {
        public:
            const char*	what() const throw();
        };
        
       	class NotAPositiveNumber : public std::exception
        {
        public:
            const char*	what() const throw();
        };
        
        class NumberTooLarge : public std::exception
        {
        public:
            const char*	what() const throw();
        };
        
        class BadInput : public std::exception
        {
        public:
            const char*	what() const throw();
        };
};

#endif