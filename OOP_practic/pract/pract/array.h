#pragma once

#include "number.h"
#include <iostream>
#include <string>

class Array
{
private:
    number* data;
    int capacity;
    int size;

    void resize(int newCapacity);

public:
    Array();
    Array(int n, number value = 0);
    ~Array();

    int getSize() const;
    number& operator[](int index);
    const number& operator[](int index) const;

    void changeSize(int newSize, number value = 0);
    void inputFromStream(std::istream& in);
    void outputToStream(std::ostream& out) const;

    number calculateAverage() const;
    number calculateStandardDeviation() const;

    void sort(bool ascending = true);
};
