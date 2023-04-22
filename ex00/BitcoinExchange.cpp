#include "BitcoinExchange.hpp"
BitcoinExchange::BitcoinExchange(std::string const & filename) :
    _filename(filename) {
        parseDatabase();
        parseInputFile();
    }

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::parseDatabase(){
    std::string filename = "data.csv";
    std::ifstream btcData;
    bool startDate = true;
    time_t timestamp;
    std::string currentLine;

    btcData.open(filename);
    if(!btcData.is_open()) throw DataCsvNotFoundException();
   
    getline(btcData, currentLine);
    while(getline(btcData, currentLine)){
        std::istringstream iss(currentLine);
        std::string token;
        std::tm key;
        while (std::getline(iss, token, ',')){   
            try{ 
                if (!extractDate(token,timestamp,key)) continue;
                std::getline(iss,token, ',');
                std::stringstream ss(token);
                double value;
                ss >> value;
                if (startDate) {
                    _startDataset = timestamp;
                    startDate = false;
                }
                _endDataset = timestamp;
                _dataset.insert({key,value});
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
    }
}

void BitcoinExchange::parseInputFile(){
    std::ifstream inputFile;
    std::string currentLine;
    time_t timestamp;

    inputFile.open(_filename);
    if(!inputFile.is_open()) throw FileNotFoundException();
   
    getline(inputFile, currentLine);
    while(getline(inputFile, currentLine)){
        std::istringstream iss(currentLine);
        std::string firstHalf;
        std::string secondHalf;
        std::tm key;
        double value;
        try{ 
            getline(iss,firstHalf,'|');
            getline(iss,secondHalf);
            secondHalf = ltrim(secondHalf);
            if (secondHalf.empty()) {
                std::cout << "Error: bad input => " << currentLine << std::endl;
            } else if(!extractDate(currentLine,timestamp,key)){
                std::cout << "Error: wrong date => " << currentLine << std::endl;
            } else if(extractValue(secondHalf,value)) {
                std::cout << formatDate(key) << " => " << value << " = " << std::fixed << std::setprecision(2) << getValueFromGivenDate(key)*value << std::endl;
            }
        }
        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
        }
    }


}


bool BitcoinExchange::extractDate(const std::string &date, time_t &timestamp, std::tm &key) {
    std::istringstream is(date);
    int y,m,d;
    char delimiter;
    if (is >> y >> delimiter >> m >> delimiter >> d) {
        std::tm t = { .tm_sec = 0, .tm_min = 0, .tm_hour = 0, .tm_mday = 0, .tm_mon = 0, .tm_year = 0, .tm_wday = 0, .tm_yday = 0, .tm_isdst = 0 };
        t.tm_mday = d;
        t.tm_mon = m - 1;
        t.tm_year = y - 1900;
        t.tm_min = 0;
        time_t when = mktime(&t);
        const std::tm *norm = localtime(&when);
        timestamp=when;
        key = t;
        if (norm->tm_mday == d && norm->tm_mon  == m - 1 && norm->tm_year == y - 1900) {
            return true;
        }
    }
    return false;
}

bool BitcoinExchange::extractValue(const std::string &stringValue, double &value) {
    try {
        std::stringstream ss(stringValue);
        ss >> value;
        if (value < 0) {
            throw NegativeNumberException();
        } else if (value > 1000) {
            throw NumberTooHighException();
        } else if (!isdigit(int(stringValue.at(0)))) {
            throw NotANumberException();
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
}

std::string BitcoinExchange::formatDate(const std::tm &date){
    std::stringstream ss;
    ss << date.tm_year+1900 << "-" << date.tm_mon+1 << "-" << date.tm_mday;
    return ss.str();
}

std::string BitcoinExchange::ltrim(const std::string &str) {
    const std::string WHITESPACE = " \n\r\t\f\v";
    size_t start = str.find_first_not_of(WHITESPACE);

    return (start == std::string::npos) ? "" : str.substr(start);
}

void BitcoinExchange::AddDays(std::tm* dateAndTime, const int daysToAdd){
    const time_t oneDay = 24 * 60 * 60;
    time_t date_seconds = mktime(dateAndTime) + (daysToAdd * oneDay);
    *dateAndTime = *localtime(&date_seconds);
}

double BitcoinExchange::getValueFromGivenDate(std::tm dateToCheck){
    if (mktime(&dateToCheck) < _startDataset) return 0;
    if (mktime(&dateToCheck) > _endDataset) {
        std::map<std::tm, double>::iterator ite =  _dataset.end();
        ite--;
        return ite->second;
    }
    std::map<std::tm, double>::iterator it;
    while(_dataset.count(dateToCheck) == 0){
        AddDays(&dateToCheck,-1);
    }
    return _dataset[dateToCheck];
}

bool operator < (const std::tm & t1, const std::tm & t2) {
    std::tm tm1 = t1;
    std::tm tm2 = t2;
    return (mktime(&tm1) < mktime(&tm2));
};

char const * BitcoinExchange::DataCsvNotFoundException::what( void ) const throw(){
	return "Dataset file not found";
}

char const * BitcoinExchange::FileNotFoundException::what( void ) const throw(){
	return "Input file not found";
}

char const * BitcoinExchange::NegativeNumberException::what( void ) const throw(){
	return "Error: not a positive number.";
}

char const * BitcoinExchange::NumberTooHighException::what( void ) const throw(){
	return "Error: too large a number.";
}

char const * BitcoinExchange::NotANumberException::what( void ) const throw(){
	return "Error: Not a valid value.";
}