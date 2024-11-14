#pragma once
#include "Figure.h"  

class Array {
public:
    Array();

    Array(const Array& other); 
    Array(Array&& other) noexcept;

    Figure* getFigure (size_t index) const;

    void add(Figure* figure);
    void remove(size_t index);
    
    size_t size() const;
    double TotalArea() const;
    
    ~Array();
private:
    size_t count;
    size_t capacity; 
    Figure** data; 

    void resize(size_t value_C);
};