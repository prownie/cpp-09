#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <sstream>
#include <cctype>
#include <math.h>
class RPN{
    private:
        RPN(RPN const & src);
        RPN & operator=(RPN const & rhs);
        RPN();
        std::string _expression;
        std::stack<double> _numbers;
        double _actualValue;

    public:
        RPN(char* RPNexpression);
        void parseExpression();
        ~RPN();
        bool isOperator(char ope);
        void applyOperator(char ope);
        bool isOperand(std::string line);

    class NotEnoughOperands : public std::exception {
        public :
            virtual char const * what(void) const throw();
    };
    class BadSyntaxException : public std::exception { 
        public :
            virtual char const * what(void) const throw();    
    };
    class TooManyOperandsException : public std::exception { 
        public :
            virtual char const * what(void) const throw();    
    };
};

#endif