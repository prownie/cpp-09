#include "RPN.hpp"
RPN::RPN(char* RPNexpression):
    _expression(RPNexpression) {
        parseExpression();
    }

RPN::~RPN() {}

void RPN::parseExpression(){
    std::stringstream ss(_expression);
    std::string token;
    
    while (ss >> token) {
        double number;
        std::stringstream tmp(token);
        if(isOperand(token)) {
            tmp >> number;
            _numbers.push(number);
        } else if (isOperator(token[0]) && token.length() == 1) {
            applyOperator(token[0]);
        } else {
            throw BadSyntaxException();
        }
    }
    //not sure what if more than 1 argument left in the stack is considered as an error ? can comment if needed
    if(_numbers.size() > 1)throw TooManyOperandsException();
    std::cout << _numbers.top() << std::endl;
}

void RPN::applyOperator(char ope){
    if (_numbers.size() < 2)
        throw NotEnoughOperands();
    double secondOperand = _numbers.top();
    _numbers.pop();
    double firstOperand = _numbers.top();
    _numbers.pop();
    switch(ope){
        case '+':
            _numbers.push(firstOperand + secondOperand);
            break;
        case '-':
           _numbers.push(firstOperand - secondOperand);
            break;
        case '*':
            _numbers.push(firstOperand * secondOperand);
            break;
        case '/':
            _numbers.push(firstOperand / secondOperand);
            break;
        case '^':
           _numbers.push(pow(firstOperand,secondOperand));
            break;
        default:
            throw BadSyntaxException();
    }
}

bool RPN::isOperator(char ope){
    std::string operands("/*-+^");
    return (operands.find(ope)!=std::string::npos);
}

bool RPN::isOperand(std::string line){
    if(line[0] == '-' && line.size() != 1)
        line = line.substr(1);
    std::string::iterator it = line.begin();
    bool commaAlreadyFound = false;
    while(it != line.end()){
        if((!isdigit(*it) && *it != '.') || (commaAlreadyFound && *it == '.')){
            return false;
        }
        if(*it == '.'){
            commaAlreadyFound = true;
        } 
        it++;
    }
    return true;
}

char const * RPN::NotEnoughOperands::what( void ) const throw(){
	return "Error: Not enough operands";
}
char const * RPN::BadSyntaxException::what( void ) const throw(){
	return "Error: Bad syntax";
}
char const * RPN::TooManyOperandsException::what( void ) const throw(){
	return "Error: Too many operands left in the stack";
}