#pragma once

#include "array.h"

class ConsoleApplication
{
private:
    Array array;

    void handleInput();
    void handleCalculate();
    void handleSort();
    void handleResize();
    void handleEditElement();
    void handlePrint();
    void clearScreen();
    int getMenuChoice();

public:
    void run();  
};

