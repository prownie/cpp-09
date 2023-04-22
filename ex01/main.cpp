#include "RPN.hpp"

int main(int ac, char **av){
    if (ac != 2) {
        std::cout << "Wrong number of arguments, use ./RPN \"RPN EXPRESSION\"" ;
        return 0;
    }
    try {
        RPN rpn(av[1]);
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    
}