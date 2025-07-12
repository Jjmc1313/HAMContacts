// CSV.HPP
#include <iostream>
#include <fstream>
#include <limits>
#include <chrono>
#include <regex>

const auto p1 = std::chrono::system_clock::now();

class CSV {
private:
    std::string filename;
    std::fstream logFile{};

public:
    CSV(std::string);
    void logCallsign(std::string, std::string);
    int lookupCallsign(std::string);
    std::string lastContact(std::string);
};

// Default Constructor
CSV::CSV(std::string name) {
    /*
    Since the header is located at the top of the file,
    I had to open it with ios::in | ios::out, that way I 
    didn't need to seek to the beginning, by defaulting to
    that above though, the file would not be created if it
    was missing, so I create it if there is no open file, 
    then I write to it
    */
    this->filename = name;
    logFile.open(filename, std::ios::in | std::ios::out);

    // If file does not exist, create it
    if (!logFile.is_open()) {
        logFile.open(filename, std::ios::out);
    }

    logFile << "CALLSIGN, TIMESTAMP, NAME" << std::endl;
    logFile.close();
}

void CSV::logCallsign(std::string callsign, std::string name) {
    logFile.open(filename, std::ios::out | std::ios::app);
    logFile << callsign << ", "
            << std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count() << ", "
            << name << std::endl;
    logFile.close();
}

int CSV::lookupCallsign(std::string callsign) {
    std::regex pattern(callsign + ".+");
    std::string temp;
    int contacts = 0;
    
    logFile.open(filename, std::ios::in);
    while (std::getline(logFile, temp)) {
        if (std::regex_match(temp, pattern)) {
            contacts++;
        }
    }
    logFile.close();

    return contacts;
}

std::string CSV::lastContact(std::string callsign) {
    std::regex pattern(callsign + ".+");
    std::regex timestampPattern("\\d{2,10}");
    std::smatch match;

    std::string temp;
    bool hit = false;

    logFile.open(filename, std::ios::in);
    while (std::getline(logFile, temp)) {
        if (std::regex_match(temp, pattern)) {
            if (std::regex_search(temp, match, timestampPattern)) {
                hit = true;
            }
        }
    }
    logFile.close();

    if (hit) {
        return match.str();
    } else {
        return "N/A";
    }
}