#include "application.h"
#include <iostream>
#include <limits>
#include <cstdlib>  

#ifdef _WIN32
const std::string CLEAR_COMMAND = "cls";
#else
const std::string CLEAR_COMMAND = "clear";
#endif

void ConsoleApplication::clearScreen()
{
    system(CLEAR_COMMAND.c_str());
}

int ConsoleApplication::getMenuChoice()
{
    int choice = -1;
    std::string input;

    while (true) {
        std::cout << "Your choice: ";
        std::getline(std::cin, input);

        if (input.length() == 1 && isdigit(input[0])) {
            choice = input[0] - '0';
            if (choice >= 0 && choice <= 6) {
                break;
            }
        }

        std::cout << "Invalid input. Please enter a number between 0 and 6." << std::endl;
    }

    return choice;
}

void ConsoleApplication::run()
{
    int choice = 0;
    do {
        clearScreen();

        // Вывод меню
        std::cout << "\n=== Array Operations Menu ===" << std::endl;
        std::cout << "1. Input array" << std::endl;
        std::cout << "2. Calculate average and standard deviation" << std::endl;
        std::cout << "3. Sort array" << std::endl;
        std::cout << "4. Resize array" << std::endl;
        std::cout << "5. Edit element" << std::endl;
        std::cout << "6. Print array" << std::endl;
        std::cout << "0. Exit" << std::endl;

        choice = getMenuChoice();

        clearScreen();

        // Обработка выбора пользователя
        switch (choice) {
        case 1: handleInput(); break;
        case 2: handleCalculate(); break;
        case 3: handleSort(); break;
        case 4: handleResize(); break;
        case 5: handleEditElement(); break;
        case 6: handlePrint(); break;
        case 0: std::cout << "Goodbye!" << std::endl; break;
        }

        if (choice != 0) {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice != 0);
}

void ConsoleApplication::handleInput()
{
    std::cout << "=== Input Array ===" << std::endl;
    array.inputFromStream(std::cin);
}

void ConsoleApplication::handleCalculate()
{
    std::cout << "=== Calculate Average and Standard Deviation ===" << std::endl;
    if (array.getSize() == 0) {
        std::cout << "Array is empty. Cannot calculate." << std::endl;
        return;
    }

    std::cout << "Average: " << array.calculateAverage() << std::endl;
    std::cout << "Standard Deviation: " << array.calculateStandardDeviation() << std::endl;
}

void ConsoleApplication::handleSort()
{
    std::cout << "=== Sort Array ===" << std::endl;
    if (array.getSize() == 0) {
        std::cout << "Array is empty. Nothing to sort." << std::endl;
        return;
    }

    int order;
    std::string input;

    while (true) {
        std::cout << "Choose order (1 - Ascending, 2 - Descending): ";
        std::getline(std::cin, input);

        if (input.length() == 1 && (input[0] == '1' || input[0] == '2')) {
            order = input[0] - '0';
            break;
        }

        std::cout << "Invalid input. Please enter 1 or 2." << std::endl;
    }

    array.sort(order == 1);
    std::cout << "Array sorted." << std::endl;
    array.outputToStream(std::cout);
}

void ConsoleApplication::handleResize()
{
    std::cout << "=== Resize Array ===" << std::endl;

    int newSize;
    std::string input;

    while (true) {
        std::cout << "Enter new size: ";
        std::getline(std::cin, input);

        try {
            newSize = std::stoi(input);
            if (newSize >= 0) break;
            std::cout << "Size cannot be negative." << std::endl;
        }
        catch (...) {
            std::cout << "Invalid input. Please enter a non-negative integer." << std::endl;
        }
    }

    number value = 0;
    if (newSize > array.getSize()) {
        std::cout << "Enter value for new elements: ";
        std::cin >> value;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    array.changeSize(newSize, value);
    std::cout << "Array resized." << std::endl;
}

void ConsoleApplication::handleEditElement()
{
    std::cout << "=== Edit Element ===" << std::endl;
    if (array.getSize() == 0) {
        std::cout << "Array is empty. Nothing to edit." << std::endl;
        return;
    }

    array.outputToStream(std::cout);

    int index;
    std::string input;

    while (true) {
        std::cout << "Enter index of element to edit (0-" << array.getSize() - 1 << "): ";
        std::getline(std::cin, input);

        try {
            index = std::stoi(input);
            if (index >= 0 && index < array.getSize()) break;
            std::cout << "Index out of bounds." << std::endl;
        }
        catch (...) {
            std::cout << "Invalid input. Please enter a valid index." << std::endl;
        }
    }

    number newValue;
    while (true) {
        std::cout << "Enter new value: ";
        std::getline(std::cin, input);

        try {
            newValue = std::stod(input);
            break;
        }
        catch (...) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
        }
    }

    array[index] = newValue;
    std::cout << "Element updated." << std::endl;
}

void ConsoleApplication::handlePrint()
{
    std::cout << "=== Print Array ===" << std::endl;
    if (array.getSize() == 0) {
        std::cout << "Array is empty." << std::endl;
        return;
    }

    array.outputToStream(std::cout);
}