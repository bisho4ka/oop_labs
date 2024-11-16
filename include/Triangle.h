#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include "Figure.h"
#include "Point.h"

namespace { const size_t TR_POINTS = 3; }

template <Scalar T>
class Triangle : public Figure<T> {
public:
    Triangle() = default;
    Triangle(Point<T> p1, Point<T> p2, Point<T> p3);

    Triangle(const Triangle<T>& other);
    Triangle(Triangle<T>&& other) noexcept;

    Triangle<T>& operator=(const Triangle<T>& other);
    Triangle<T>& operator=(Triangle<T>&& other) noexcept;

    bool operator==(const Triangle<T>& other) const;
    operator double() const override;

    Point<T> GeomCenter() const override;

    void print(std::ostream& os) const override;
private:
    Point<T> p_1, p_2, p_3;
};

template<Scalar T>
Triangle<T>::Triangle(Point<T> p1, Point<T> p2, Point<T> p3) : p_1(p1), p_2(p2), p_3(p3) {}

template<Scalar T>
Triangle<T>::Triangle(const Triangle<T>& other) : p_1(other.p_1), p_2(other.p_2), p_3(other.p_3) {}

template<Scalar T>
Triangle<T>::Triangle(Triangle<T>&& other) noexcept {
    p_1 = std::move(other.p_1);
    p_2 = std::move(other.p_2);
    p_3 = std::move(other.p_3);
}

template<Scalar T>
Triangle<T>& Triangle<T>::operator=(const Triangle<T>& other) {
    if (this != &other) {
        p_1 = other.p_1;
        p_2 = other.p_2;
        p_3 = other.p_3;
    }
    return *this;
}

template<Scalar T>
Triangle<T>& Triangle<T>::operator=(Triangle<T>&& other) noexcept {
    if (this != &other) {
        p_1 = std::move(other.p_1);
        p_2 = std::move(other.p_2);
        p_3 = std::move(other.p_3);
    }
    return *this;
} 

template<Scalar T>
bool Triangle<T>::operator==(const Triangle<T>& other) const {
    const Triangle<T> *triangle = dynamic_cast<const Triangle<T>*>(&other);
    if (!triangle) return false;

    return (p_1 == triangle->p_1 && p_2 == triangle->p_2 && p_3 == triangle->p_3);
}

template<Scalar T>
Triangle<T>::operator double() const {
    double area = 0.5 * std::fabs(
        (p_2.getX() - p_1.getX()) * (p_3.getY() - p_1.getY()) - 
        (p_3.getX() - p_1.getX()) * (p_2.getY() - p_1.getY()));
    return area;
}

template<Scalar T>
Point<T> Triangle<T>::GeomCenter() const {
    double x = (p_1.getX() + p_2.getX() + p_3.getX()) / TR_POINTS;
    double y = (p_1.getY() + p_2.getY() + p_3.getY()) / TR_POINTS;
    return Point(x, y);
}

template<Scalar T>
void Triangle<T>::print(std::ostream& os) const {
    os << "Треугольник:\n";
    os << "p_1: (" << p_1.getX() << ", " << p_1.getY() << ")\n";
    os << "p_2: (" << p_2.getX() << ", " << p_2.getY() << ")\n";
    os << "p_3: (" << p_3.getX() << ", " << p_3.getY() << ")\n\n";
}