// CSV.cpp
#ifndef CSV_HPP_
#define CSV_HPP_

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

#endif