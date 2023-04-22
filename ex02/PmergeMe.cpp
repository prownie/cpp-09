#include "PmergeMe.hpp"
PmergeMe::PmergeMe(int ac, char** av){
    for (int i = 1; i < ac; i++){
        std::stringstream ss(av[i]);
        long number;
        ss >> number;
        if (number < 0) throw NegativeException();
        if (std::find(_vectorBefore.begin(), _vectorBefore.end(), number) != _vectorBefore.end()) throw DuplicateException();
        if (number == 0 && av[i][0] != '0') throw NotANumberException();
        _listBefore.push_back(number);
        _vectorBefore.push_back(number);
    }
    // mergeInsertionList(_listBefore);
    std::cout << "Before: ";display(_vectorBefore);
    _vectorSorted = mergeInsertionVector(_vectorBefore);
    std::cout << "After:  ";display(_vectorSorted);
}

PmergeMe::~PmergeMe() {}

void PmergeMe::startMerges() {
    std::cout << "wtf" << std::endl;
    if(_listBefore.empty() || _vectorBefore.empty()) return;
    std::cout << "wtf" << std::endl;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    _vectorSorted = mergeInsertionVector(_vectorBefore);
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time to process a range of " << _vectorBefore.size() << " elements with std::vector : "
     << duration.count()*1000 << " milliseconds" << std::endl;


    start = std::chrono::system_clock::now();
    _listSorted = mergeInsertionList(_listBefore);
    end = std::chrono::system_clock::now();
    duration = end - start;
    std::cout << "Time to process a range of " << _listBefore.size() << " elements with std::list  :  "
         << duration.count()*1000 << " milliseconds" << std::endl;
}

std::vector<long> PmergeMe::mergeInsertionVector(std::vector<long> &vector){
    if (vector.size() <= _k){
        return insertAlgorithmVector(vector);
    } else {
        size_t midIndex = vector.size() / 2 + vector.size() % 2;
        std::vector<long> left(vector.begin(),vector.begin()+midIndex);
        std::vector<long> right(vector.begin()+midIndex,vector.end());
        left = mergeInsertionVector(left);
        right = mergeInsertionVector(right);
        return mergeVectors(left, right);
    }
}

std::vector<long> PmergeMe::insertAlgorithmVector(std::vector<long> &vector){
    std::vector<long> result;

    // int actualPos = 0;
    std::vector<long>::iterator it = vector.begin();
    result.push_back(*it);
    while (++it != vector.end()){
        long key = *it;
        std::vector<long>::iterator beginResult = result.begin();
        do {
            if(key < *(beginResult)) {
                result.insert(beginResult,key);
                break;
            }
            beginResult++;
        } while (beginResult != result.end());
        if (beginResult == result.end())
            result.push_back(key);
    }
    return result;
}

std::vector<long> PmergeMe::mergeVectors(std::vector<long> &left, std::vector<long> &right){
    std::vector<long> mergedVec;

    while (!left.empty() && !right.empty()){
        // add lowest until first number of each vector until one is empty
        if (left.front() < right.front()) {
            // mergedVec.insert(mergedVec.begin(),left.front());
            mergedVec.push_back(left.front());
            left.erase(left.begin());
        } else {
            // mergedVec.insert(mergedVec.begin(),right.front());
            mergedVec.push_back(right.front());
            right.erase(right.begin());
        }
    }
    // when one vector becomes empty, add the other one
    while (!left.empty()) {
        mergedVec.push_back(left.front());
        left.erase(left.begin());
    }
    while (!right.empty()) {
        mergedVec.push_back(right.front());
        right.erase(right.begin());
    }
    return mergedVec;
}

std::list<long> PmergeMe::mergeInsertionList(std::list<long> &list){
    if(list.size() <= _k) {
        return insertAlgorithmList(list);
    } else {
        size_t midIndex = list.size() / 2 + list.size() % 2;
        std::list<long>::iterator it = list.begin();
        std::advance(it, midIndex);
        std::list<long> left(list.begin(),it);
        std::list<long> right(it,list.end());
        left = mergeInsertionList(left);
        right = mergeInsertionList(right);
        return mergeLists(left, right);
    }
}

std::list<long> PmergeMe::insertAlgorithmList(std::list<long> &list){
    std::list<long> result;

    // int actualPos = 0;
    std::list<long>::iterator it = list.begin();
    result.push_back(*it);
    while (++it != list.end()){
        long key = *it;
        std::list<long>::iterator beginResult = result.begin();
        do {
            if(key < *(beginResult)) {
                result.insert(beginResult,key);
                break;
            }
            beginResult++;
        } while (beginResult != result.end());
        if (beginResult == result.end())
            result.push_back(key);
    }
    return result;
}

std::list<long> PmergeMe::mergeLists(std::list<long> &left, std::list<long> &right){
    std::list<long> mergedList;

    while (!left.empty() && !right.empty()){
        // add lowest until first number of each list until one is empty
        if (left.front() < right.front()) {
            // mergedList.insert(mergedList.begin(),left.front());
            mergedList.push_back(left.front());
            left.erase(left.begin());
        } else {
            // mergedList.insert(mergedList.begin(),right.front());
            mergedList.push_back(right.front());
            right.erase(right.begin());
        }
    }
    // when one list becomes empty, add the other one
    while (!left.empty()) {
        mergedList.push_back(left.front());
        left.erase(left.begin());
    }
    while (!right.empty()) {
        mergedList.push_back(right.front());
        right.erase(right.begin());
    }
    return mergedList;
}


void PmergeMe::display(std::vector<long> vector){
    std::vector<long>::iterator it = vector.begin();
    while (it != vector.end()){
        std::cout << *it << " ";
        it++;
    }
    std::cout << std::endl;
}

void PmergeMe::display(std::list<long> list){
    std::list<long>::iterator it = list.begin();
    while (it != list.end()){
        std::cout << *it << " ";
        it++;
    }
    std::cout << std::endl;
}

void PmergeMe::checkIfVecSorted(){
    bool success=!_vectorSorted.empty();
    std::vector<long>::iterator it = _vectorSorted.begin();
    long previous = *it;
    while (++it != _vectorSorted.end()){
        if(previous > *it) {
            success = false;
            break;
        }
    }
    if (success)
        std::cout << "Vector is sorted" << std::endl;
    else
        std::cout << "Vector not sorted" << std::endl;
}

void PmergeMe::checkIfListSorted(){
    bool success=!_listSorted.empty();
    std::list<long>::iterator it = _listSorted.begin();
    long previous = *it;
    while (++it != _listSorted.end()){
        if(previous > *it) {
            success = false;
            break;
        }
    }
    if (success)
        std::cout << "List is sorted" << std::endl;
    else
        std::cout << "List not sorted" << std::endl;
}

char const * PmergeMe::DuplicateException::what( void ) const throw(){
	return "Error: Duplicate number";
}

char const * PmergeMe::NegativeException::what( void ) const throw(){
	return "Error: Negative number";
}

char const * PmergeMe::NotANumberException::what( void ) const throw(){
	return "Error: Not a number";
}
