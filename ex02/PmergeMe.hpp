#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <math.h>
#include <vector>
#include <list>
#include <algorithm>
#include <chrono>

class PmergeMe{
    private:
        PmergeMe(PmergeMe const & src);
        PmergeMe & operator=(PmergeMe const & rhs);
        PmergeMe();
        size_t _k = 4; // split the N entries in N/k groups
        std::list<long> _listBefore;
        std::vector<long> _vectorBefore;
        std::vector<long> mergeInsertionVector(std::vector<long> &vector);
        std::vector<long> insertAlgorithmVector(std::vector<long> &vector);
        std::vector<long> mergeVectors(std::vector<long> &left, std::vector<long> &right);
        std::list<long> mergeInsertionList(std::list<long> &list);
        std::list<long> mergeLists(std::list<long> &left, std::list<long> &right);
        std::list<long> insertAlgorithmList(std::list<long> &list);
        void display(std::vector<long> vector);
        void display(std::list<long> list);
        std::vector<long> _vectorSorted;
        std::list<long> _listSorted;
    public:
        PmergeMe(int ac, char** av);
        void parseExpression();
        ~PmergeMe();
        void startMerges();

        void checkIfVecSorted();
        void checkIfListSorted();
        // std::list<long> mergeInsertionList(std::list<long> list);
        // std::list<long> mergeVectors(std::list<long> &left, std::list<long> &right);


    class DuplicateException : public std::exception { 
        public :
            virtual char const * what(void) const throw();    
    };
    class NegativeException : public std::exception { 
        public :
            virtual char const * what(void) const throw();    
    };
    class NotANumberException : public std::exception { 
        public :
            virtual char const * what(void) const throw();    
    };

};

#endif