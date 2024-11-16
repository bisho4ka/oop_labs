#pragma once
#include "Figure.h"

#include <memory>


template <typename T>
class Array {
public:
    Array();
    Array(size_t n);

    Array(const Array<T>&);
    Array(Array<T>&&) noexcept; 

    void add(std::unique_ptr<Figure<T>> figure);
    void remove(size_t index);

    Figure<T>* getFigure (size_t index) const;
    size_t size() const;

    double totalArea() const;

    ~Array() = default;
private:
    size_t count, capacity; 
    std::unique_ptr<std::unique_ptr<Figure<T>>[]> data;

    void resize(size_t value);
};


template <typename T>
Array<T>::Array() : count(0), capacity(0), data(nullptr) {}

template <typename T>
Array<T>::Array(size_t n) : count(n), capacity(n) {
    data = std::unique_ptr<Figure<T>[]>(new T[n]);
}

template <typename T>
Array<T>::Array(const Array<T>& other) : count(other.count), capacity(other.capacity) {
    data = std::unique_ptr<Figure<T>[]>(new T[capacity]);
    for (size_t i = 0; i < count; i++) 
        data[i] = other.data[i];
}

template <typename T>
Array<T>::Array(Array<T>&& other) noexcept : count(other.count), capacity(other.capacity) {
    data = std::move(other.data);
    other.count = 0;
    other.capacity = 0;
}

template <typename T>
void Array<T>::add(std::unique_ptr<Figure<T>> figure) {
    if (count == capacity)
        resize(count + 1);
    data[count] = std::move(figure);
    count++;
}

template <typename T>
void Array<T>::remove(size_t index) {
    if (index >= count)
        throw std::out_of_range("Несуществующий индекс");

    for (size_t i = index; i < count - 1; i++) 
        data[i] = std::move(data[i + 1]);

    if (index < count) 
        count--;
}

template<typename T>
Figure<T>* Array<T>::getFigure(size_t index) const {
    if (index >= count)
        throw std::out_of_range("Несуществующий индекс");

    return data[index].get();
}

template <typename T>
size_t Array<T>::size() const {
    return count;
}

template <typename T>
double Array<T>::totalArea() const{
    double result = 0.0;
    for (size_t i = 0; i < count; i++) {
        if (data[i]) 
            result += static_cast<double>(*data[i]);
    }
    return result;
}

template <typename T>
void Array<T>::resize(size_t value) {
    auto value_D = std::make_unique<std::unique_ptr<Figure<T>>[]>(value);
    for (size_t i = 0; i < count; i++) 
        value_D[i] = std::move(data[i]);

    data = std::move(value_D);
    capacity = value;
}
