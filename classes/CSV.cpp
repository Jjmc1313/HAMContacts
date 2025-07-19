// CSV.HPP
#include <iostream>
#include <cstdio>
#include <fstream>
#include <limits>
#include <chrono>
#include <regex>
#include <conio.h>

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
    void editContact(std::string, char, std::string);
    void outputLog();
};

// Default Constructor
CSV::CSV(std::string name) {
    /*
    Since the header is located at the top of the file,
    open it with ios::in | ios::out, that way I 
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
    std::regex callsignPattern(callsign + ",.+");
    std::string temp;
    int contacts = 0;
    
    logFile.open(filename, std::ios::in);
    while (std::getline(logFile, temp)) {
        if (std::regex_match(temp, callsignPattern)) {
            contacts++;
        }
    }
    logFile.close();

    return contacts;
}

std::string CSV::lastContact(std::string callsign) {
    std::regex callsignPattern(callsign + ", .+");
    std::regex timestampPattern(", \\d{2,}");
    std::smatch match;

    std::string temp;
    bool hit = false;

    logFile.open(filename, std::ios::in);
    while (std::getline(logFile, temp)) {
        if (std::regex_match(temp, callsignPattern)) {
            if (std::regex_search(temp, match, timestampPattern)) {
                hit = true;
            }
        }
    }
    logFile.close();

    std::string output = "N/A";

    output = match.str();
    output = std::regex_replace(output, std::regex(" "), "");
    output = std::regex_replace(output, std::regex(","), "");

    return output;
}

void CSV::editContact(std::string callsign, char option, std::string newData) {
    std::regex callsignPattern(callsign + ",.+");
    std::ofstream tempOutput("log.csv.temp");
    
    std::string temp;

    logFile.open(filename, std::ios::in);
    if (option == 'c') {
        while (std::getline(logFile, temp)) {
            if (std::regex_match(temp, callsignPattern)) {
                tempOutput << std::regex_replace(temp, std::regex(callsign), newData) << std::endl;
            } else {
                tempOutput << temp << std::endl;
            }
        }
    } else if (option == 'n') {
        while (std::getline(logFile, temp)) {
            if (std::regex_match(temp, callsignPattern)) {
                tempOutput << std::regex_replace(temp, std::regex("\\S+$"), newData) << std::endl;
            } else {
                tempOutput << temp << std::endl;
            }
        }
    }
    tempOutput.close();
    logFile.close();

    logFile.open(filename, std::ios::out | std::ios::trunc);
    std::ifstream tempLog("log.csv.temp");
    while (std::getline(tempLog, temp)) {
        logFile << temp << std::endl;
    }
    logFile.close();
    tempLog.close();
    tempOutput.open("log.csv.temp");
    tempOutput.clear();
    tempOutput << "!!! THIS IS NOT YOUR LOG FILE, THIS IS A TEMPORARY FILE !!!" << std::endl;
    tempOutput.close();
}

void CSV::outputLog() {
    logFile.open(filename, std::ios::in);

    std::string temp;

    unsigned int i = 0;
    while (std::getline(logFile, temp)) {
        if (i > 0) {
            std::cout << temp << std::endl;
        }
        if (i != 0 && i % 5 == 0) {
            std::cout << "Press Space To Continue...";
            switch (getch())
            {
            case ' ':
                std::cout << "\33[2K\r";
                break;

            default:
                return;
            }
        }

        i++;
    }

    logFile.close();
}