#include "../include/Array.h"  

Array::Array() : data(nullptr), capacity(0), count(0) {}

Array::Array(const Array& other) {
    data = other.data;
    count = other.count;
    capacity = other.capacity;
    for (size_t i = 0; i < other.size(); i++)
        data[i] = other.data[i];
}

Array::Array(Array&& other) noexcept {
    count = other.size();
    capacity = other.capacity;
    data = other.data;
    other.data = nullptr;
}

Figure* Array::getFigure (size_t index) const {
    return data[index];
}

void Array::add(Figure* figure) {
    resize(count + 1);
    count++;
    data[count - 1] = figure;
}

void Array::remove(size_t index) {
    if (index >= count) 
        throw std::out_of_range("Несуществующий индекс");
    delete data[index];
    for (size_t i = index; i < count - 1; i++)
        data[i] = data[i + 1];
    count--;
}

void Array::resize(size_t value_C) {
    Figure** value_D = new Figure* [value_C];
    for (size_t i = 0; i < count; i++) 
        value_D[i] = data[i];
    data = value_D;
    capacity = value_C;
}

size_t Array::size() const {
    return count;
}

double Array::TotalArea() const {
    double result = 0.0;
    for (size_t i = 0; i < count; i++) {
        if (data[i] != nullptr)
            result += (double)*data[i];
    }
    return result;
}
    
Array::~Array() {
    delete[] data;
}
