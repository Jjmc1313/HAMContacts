#include <conio.h>

#include "classes\CSV.hpp"

void toUpper(std::string&);
void input(auto&);

void addContact(CSV&);
void lookupContact(CSV&);
void editContact(CSV&);
void outputLog(CSV&);
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
        std::cout << "(1) Add Contact"       << std::endl
                  << "(2) Recall Contact"    << std::endl
                  << "(3) Update Contact"    << std::endl
                  << "(4) Output Log"        << std::endl
                  << "(5) Remove Contact\n"  << std::endl // incomplete
                  << "(0) Information"       << std::endl
                  << "(q) Quit"              << std::endl;

        switch (getch())
        {
        case '1':
            addContact(csvLogFile);
            break;

        case '2':
            lookupContact(csvLogFile);
            break;

        case '3':
            editContact(csvLogFile);
            break;

        case '4':
            outputLog(csvLogFile);
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

// -----------------------------------------------------------------------------------------

void toUpper(std::string& s) {
    for (char& c : s) {
        c = toupper(c);
    }
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

// -----------------------------------------------------------------------------------------

// Need to check if callsign already added, if so default name to existing log entry
void addContact(CSV& csv) {
    bool validInput = false;
    std::string tempCall;
    std::string tempName;

    do {
        std::cout << "\nEnter Callsign: ";
        input(tempCall);
        toUpper(tempCall);
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

void lookupContact(CSV& csv) {
    std::string tempCall;

    std::cout << "\nEnter Callsign: ";
    input(tempCall);
    toUpper(tempCall);

    std::cout << tempCall << " has been contacted " << csv.lookupCallsign(tempCall) << " times." << std::endl
              << "Last contacted on " << csv.lastContact(tempCall) << std::endl
              << "Press Any Key To Continue...";
    getch();
}

void editContact(CSV& csv) {
    std::string tempCall;
    std::string newData;

    std::cout << "\nEnter Callsign: ";
    input(tempCall);
    toUpper(tempCall);

    std::cout << "(c) Edit Callsign" << std::endl
              << "(n) Edit Name" << std::endl;
    switch (getch())
    {
    case 'c':
        std::cout << "Enter New Callsign: ";
        input(newData);
        toUpper(newData);
        csv.editContact(tempCall, 'c', newData);
        break;
    case 'n':
        std::cout << "Enter New Name: ";
        input(newData);
        csv.editContact(tempCall, 'n', newData);
        break;
    default:
        break;
    }

    std::cout << "Callsign updated!" << std::endl
              << "Press Any Key To Continue...";
    getch();
}

void outputLog(CSV& csv) {
    std::cout << std::endl;
    std::cout << "- START OF LOG -";
    csv.outputLog();
    std::cout << "- END OF LOG -" << std::endl
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