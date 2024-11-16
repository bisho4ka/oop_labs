#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include "Figure.h"
#include "Point.h"

namespace { const size_t HX_POINTS = 6; }

template <typename T>
class Hexagon : public Figure<T> {
public:
    Hexagon() = default;
    Hexagon(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4, Point<T> p5, Point<T> p6);

    Hexagon(const Hexagon<T>& other);
    Hexagon(Hexagon<T>&& other) noexcept;

    Hexagon<T>& operator=(const Hexagon<T>& other);
    Hexagon<T>& operator=(Hexagon<T>&& other) noexcept;

    bool operator==(const Hexagon<T>& other) const;
    operator double() const;

    Point<T> GeomCenter() const override;

    void print(std::ostream& os) const override;
private:
    Point<T> p_1, p_2, p_3, p_4, p_5, p_6;
};

template<typename T>
Hexagon<T>::Hexagon(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4, Point<T> p5, Point<T> p6) {
    p_1 = p1; 
    p_2 = p2; 
    p_3 = p3; 
    p_4 = p4; 
    p_5 = p5; 
    p_6 = p6;
}

template<typename T>
Hexagon<T>::Hexagon(const Hexagon<T>& other) {
    p_1 = other.p_1;
    p_2 = other.p_2;
    p_3 = other.p_3;
    p_4 = other.p_4;
    p_5 = other.p_5;
    p_6 = other.p_6;
}

template<typename T>
Hexagon<T>::Hexagon(Hexagon<T>&& other) noexcept {
    p_1 = std::move(other.p_1);
    p_2 = std::move(other.p_2);
    p_3 = std::move(other.p_3);
    p_4 = std::move(other.p_4);
    p_5 = std::move(other.p_5);
    p_6 = std::move(other.p_6);
}

template<typename T>
Hexagon<T>& Hexagon<T>::operator=(const Hexagon<T>& other) {
    if (this != &other) {
        p_1 = other.p_1;
        p_2 = other.p_2;
        p_3 = other.p_3;
        p_4 = other.p_4;
        p_5 = other.p_5;
        p_6 = other.p_6;
    }
    return *this;
}

template<typename T>
Hexagon<T>& Hexagon<T>::operator=(Hexagon<T>&& other) noexcept {
    if (this != &other) {
        p_1 = std::move(other.p_1);
        p_2 = std::move(other.p_2);
        p_3 = std::move(other.p_3);
        p_4 = std::move(other.p_4);
        p_5 = std::move(other.p_5);
        p_6 = std::move(other.p_6);
    }
    return *this;
} 

template<typename T>
bool Hexagon<T>::operator==(const Hexagon<T>& other) const {
    const Hexagon<T> *hexagon = dynamic_cast<const Hexagon<T>*>(&other);
    if (!hexagon) return false;

    return (p_1 == hexagon->p_1 && p_2 == hexagon->p_2 && p_3 == hexagon->p_3 &&
            p_4 == hexagon->p_4 && p_5 == hexagon->p_5 && p_6 == hexagon->p_6);
}

template<typename T>
Hexagon<T>::operator double() const {
    double a1 = sqrt(pow(p_2.getX() - p_1.getX(), 2) + pow(p_2.getY() - p_1.getY(), 2));
    double a2 = sqrt(pow(p_3.getX() - p_2.getX(), 2) + pow(p_3.getY() - p_2.getY(), 2));
    double a3 = sqrt(pow(p_4.getX() - p_3.getX(), 2) + pow(p_4.getY() - p_3.getY(), 2));
    double a4 = sqrt(pow(p_5.getX() - p_4.getX(), 2) + pow(p_5.getY() - p_4.getY(), 2));
    double a5 = sqrt(pow(p_6.getX() - p_5.getX(), 2) + pow(p_6.getY() - p_5.getY(), 2));
    double a6 = sqrt(pow(p_1.getX() - p_6.getX(), 2) + pow(p_1.getY() - p_6.getY(), 2));
    
    double Area = (a1 + a2 + a3 + a4 + a5 + a6) / HX_POINTS;
    return (3 * sqrt(3) / 2) * Area * Area;
}

template<typename T>
Point<T> Hexagon<T>::GeomCenter() const {
    double x = (p_1.getX() + p_2.getX() + p_3.getX() +
                p_4.getX() + p_5.getX() + p_6.getX()) / HX_POINTS;
    double y = (p_1.getY() + p_2.getY() + p_3.getY() +
                p_4.getY() + p_5.getY() + p_6.getY()) / HX_POINTS;
    return Point(x, y);
}

template<typename T>
void Hexagon<T>::print(std::ostream& os) const {
    os << "Шестиугольник:\n";
    os << "p_1: (" << p_1.getX() << ", " << p_1.getY() << ")\n";
    os << "p_2: (" << p_2.getX() << ", " << p_2.getY() << ")\n";
    os << "p_3: (" << p_3.getX() << ", " << p_3.getY() << ")\n";
    os << "p_4: (" << p_4.getX() << ", " << p_4.getY() << ")\n";
    os << "p_5: (" << p_5.getX() << ", " << p_5.getY() << ")\n";
    os << "p_6: (" << p_6.getX() << ", " << p_6.getY() << ")\n\n";
}