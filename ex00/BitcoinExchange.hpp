#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <ctime>
#include <iomanip>

class BitcoinExchange{
    private:
        BitcoinExchange(BitcoinExchange const & src);
        BitcoinExchange & operator=(BitcoinExchange const & rhs);
        BitcoinExchange();
        std::string const _filename;
        std::map<std::tm, double> _dataset;
        time_t _startDataset;
        time_t _endDataset;
        void parseDatabase();
        void parseInputFile();
        bool extractDate(const std::string& date, time_t &timestamp, std::tm &key);
        bool extractValue(const std::string &stringValue, double &value);
        std::string formatDate(const std::tm &date);
        std::string ltrim(const std::string &str);
        void AddDays(std::tm* dateAndTime, const int daysToAdd);
        double getValueFromGivenDate(std::tm dateToCheck);
    public:
        BitcoinExchange(std::string const & filename);
        ~BitcoinExchange();

    class DataCsvNotFoundException : public std::exception {
        public :
            virtual char const * what(void) const throw();
    };
    class FileNotFoundException : public std::exception {
        public :
            virtual char const * what(void) const throw();
    };
    class NegativeNumberException : public std::exception {
        public :
            virtual char const * what(void) const throw();
    };
    class NumberTooHighException : public std::exception {
        public :
            virtual char const * what(void) const throw();
    };
    class NotANumberException : public std::exception {
        public :
            virtual char const * what(void) const throw();
    };
    
};

#endif