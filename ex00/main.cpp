#include "BitcoinExchange.hpp"

int main(int ac, char **av){
    if (ac != 2) {
        std::cout << "Wrong number of arguments, use ./btc INPUT_FILENAME" ;
        return 0;
    }
    try{
        BitcoinExchange btcEx(av[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}