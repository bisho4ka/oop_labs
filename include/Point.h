#pragma once
#include <iostream>
#include <concepts>

template<typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
class Point {
public:
    Point();
    Point(T value_X, T value_Y);

    Point(const Point<T>& other);
    Point(Point<T>&& other) noexcept;

    Point<T>& operator=(const Point<T>& other);

    Point<T>& operator=(Point<T>&& other) noexcept;

    T getX() const;
    T getY() const;

    void setX(T value_X);
    void setY(T value_Y);

    bool operator==(const Point<T>& other) const;
private:
    T x;
    T y;
};

template<Scalar T>
Point<T>::Point(): x(0), y(0) {}

template<Scalar T>
Point<T>::Point(T value_X, T value_Y) : x(value_X), y(value_Y) {}

template<Scalar T>
Point<T>::Point(const Point<T>& other) : x(other.x), y(other.y) {}

template<Scalar T>
Point<T>::Point(Point<T>&& other) noexcept : x(std::move(other.x)), y(std::move(other.y)) {}

template<Scalar T>
Point<T>& Point<T>::operator=(const Point<T>& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

template<Scalar T>
Point<T>& Point<T>::operator=(Point<T>&& other) noexcept {
    if (this != &other) {
        x = std::move(other.x);
        y = std::move(other.y);
    }
    return *this;
}

template<Scalar T>
T Point<T>::getX() const {
    return x;
}

template<Scalar T>
T Point<T>::getY() const {
    return y;
}

template<Scalar T>
void Point<T>::setX(T value_X) {
    x = value_X;
}

template<Scalar T>
void Point<T>::setY(T value_Y) {
    y = value_Y;
}

template<Scalar T>
bool Point<T>::operator==(const Point<T>& other) const {
    return (x == other.x && y == other.y);
}