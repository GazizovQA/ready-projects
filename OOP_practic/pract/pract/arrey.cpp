#include "array.h"
#include <cmath>
#include <algorithm>
#include <iostream>

Array::Array() : data(nullptr), capacity(0), size(0) {}

Array::Array(int n, number value) : capacity(n), size(n)
{
    data = new number[capacity];
    for (int i = 0; i < size; ++i) {
        data[i] = value;
    }
}

Array::~Array()
{
    delete[] data;
}

int Array::getSize() const
{
    return size;
}

number& Array::operator[](int index)
{
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

const number& Array::operator[](int index) const
{
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

void Array::resize(int newCapacity)
{
    if (newCapacity == capacity) return;

    number* newData = new number[newCapacity];
    int elementsToCopy = (size < newCapacity) ? size : newCapacity;

    for (int i = 0; i < elementsToCopy; ++i) {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
    size = elementsToCopy;
}

void Array::changeSize(int newSize, number value)
{
    if (newSize > capacity) {
        resize(newSize);
    }

    for (int i = size; i < newSize; ++i) {
        data[i] = value;
    }
    size = newSize;
}

void Array::inputFromStream(std::istream& in)
{
    int newSize;
    std::cout << "Enter the number of elements: ";
    while (!(in >> newSize) || newSize < 0) {
        std::cout << "Invalid input. Please enter a non-negative integer: ";
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    changeSize(newSize);

    std::cout << "Enter " << newSize << " elements:" << std::endl;
    for (int i = 0; i < newSize; ++i) {
        while (!(in >> data[i])) {
            std::cout << "Invalid input. Please enter a number: ";
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Array::outputToStream(std::ostream& out) const
{
    out << "Array elements: [ ";
    for (int i = 0; i < size; ++i) {
        out << data[i] << " ";
    }
    out << "]" << std::endl;
}

number Array::calculateAverage() const
{
    if (size == 0) return 0;

    number sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += data[i];
    }
    return sum / size;
}

number Array::calculateStandardDeviation() const
{
    if (size == 0) return 0;

    number avg = calculateAverage();
    number sumSquares = 0;

    for (int i = 0; i < size; ++i) {
        sumSquares += (data[i] - avg) * (data[i] - avg);
    }

    return std::sqrt(sumSquares / size);
}

void Array::sort(bool ascending)
{
    std::sort(data, data + size);

    if (!ascending) {
        for (int i = 0; i < size / 2; ++i) {
            std::swap(data[i], data[size - 1 - i]);
        }
    }
}