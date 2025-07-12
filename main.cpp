#include <conio.h>

#include "classes\CSV.hpp"

void input(auto&);
void addContact(CSV&);
void lookupContact(CSV&);
void displayHelpInfo();

int main() {
    system("chcp 65001"); // Default 437 (US)

    CSV csvLogFile("log.csv");

    bool loop = true;
    while (loop) {
        std::system("cls");
        std::cout << "┓┏┏┓┳┳┓  ┓   ┏┓  ┓ ┏┓" << std::endl
                  << "┣┫┣┫┃┃┃  ┃ ┏┓┃┓  ┃ ┃┫" << std::endl
                  << "┛┗┛┗┛ ┗  ┗┛┗┛┗┛  ┻•┗┛" << std::endl
                  << "¯¯¯¯¯PRESS A KEY¯¯¯¯¯" << std::endl;
        std::cout << "(1) Add Contact" << std::endl
                  << "(2) Recall Contact" << std::endl
                  << "(3) Update Contact" << std::endl
                  << "(4) Remove Contact\n" << std::endl
                  << "(0) Information" << std::endl
                  << "(q) Quit" << std::endl;
        
        std::string tempCall;
        std::string tempName;

        switch (getch())
        {
        case '1':
            addContact(csvLogFile);
            break;

        case '2':
            lookupContact(csvLogFile);
            break;

        case '3':
            std::cout << "test";
            break;

        case '0':
            displayHelpInfo();
            break;

        case 'q':
            std::cout << "\nAre you sure you want to quit? (y/n)";
            if (getch() == 'y') {
                loop = false;
            } else {
                break;
            }
        
        default:
            break;
        }

    }

    return 0;
}

void input(auto& targetVariable) {
    bool validInput = false;

    while (!validInput) {
        std::cin >> targetVariable;

        if (std::cin.fail()) {
            std::cerr << "Invalid input! Expected: " << typeid(targetVariable).name()
                 << "! Enter a valid input: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            validInput = true;
        }
    }
}

// Need to check if callsign already added, if so default name to existing log entry
void addContact(CSV& csv) {
    bool validInput = false;
    std::string tempCall;
    std::string tempName;

    do {
        std::cout << "\nEnter Callsign: ";
        input(tempCall);
        std::cout << "Enter Name: ";
        input(tempName);

        std::cout << "Is this correct? [" << tempCall << "-" << tempName << "] (y/n)";
        if (getch() == 'y') {
            validInput = true;
            csv.logCallsign(tempCall, tempName);
        }
        std::cout << std::endl;
    } while (!validInput);

    std::cout << tempCall << " has been contacted " << csv.lookupCallsign(tempCall) << " times." << std::endl
              << "Press Any Key To Continue...";
    getch();
}

// Need to add a last contact on function
void lookupContact(CSV& csv) {
    std::string tempCall;

    std::cout << "\nEnter Callsign: ";
    input(tempCall);

    std::cout << tempCall << " has been contacted " << csv.lookupCallsign(tempCall) << " times." << std::endl
              << "Last contacted on " << csv.lastContact(tempCall) << std::endl
              << "Press Any Key To Continue...";
    getch();
}

void displayHelpInfo() {
    std::cout << "\nDeveloped By: John Hartshorne" << std::endl
              << "Written In: C++" << std::endl
              << "Email: contact@doubleh.dev" << std::endl
              << "Github: github.com/Jjmc1313" << std::endl
              << "Press Any Key To Continue..." << std::endl;
    getch();
}