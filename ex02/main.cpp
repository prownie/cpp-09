#include "PmergeMe.hpp"

int main(int ac, char **av){
    if (ac < 3) {
        std::cout << "Wrong number of arguments, use ./RPN LIST TO SORT" ;
        return 0;
    }
    try{
        PmergeMe PmergeMe(ac, av);
        PmergeMe.startMerges();
        PmergeMe.checkIfVecSorted();
        PmergeMe.checkIfListSorted();
    }
    catch(const std::exception& e)
    {
       std::cerr << e.what();
    }
     

}