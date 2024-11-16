#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include "Figure.h"
#include "Point.h"

namespace { const size_t OC_POINTS = 8; }

template <typename T>
class Octagon : public Figure<T> {
public:
    Octagon() = default;
    Octagon(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4,
            Point<T> p5, Point<T> p6, Point<T> p7, Point<T> p8);

    Octagon(const Octagon<T>& other);
    Octagon(Octagon<T>&& other) noexcept;

    Octagon<T>& operator=(const Octagon<T>& other);
    Octagon<T>& operator=(Octagon<T>&& other) noexcept;

    bool operator==(const Octagon<T>& other) const;
    operator double() const override;

    Point<T> GeomCenter() const override;

    void print(std::ostream& os) const override;
private:
    Point<T> p_1, p_2, p_3, p_4, p_5, p_6, p_7, p_8;
};

template<typename T>
Octagon<T>::Octagon(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4,
                    Point<T> p5, Point<T> p6, Point<T> p7, Point<T> p8) {
    p_1 = p1; 
    p_2 = p2; 
    p_3 = p3; 
    p_4 = p4; 
    p_5 = p5; 
    p_6 = p6;
    p_7 = p7; 
    p_8 = p8;
}

template<typename T>
Octagon<T>::Octagon(const Octagon<T>& other) {
    p_1 = other.p_1;
    p_2 = other.p_2;
    p_3 = other.p_3;
    p_4 = other.p_4;
    p_5 = other.p_5;
    p_6 = other.p_6;
    p_7 = other.p_7;
    p_8 = other.p_8;
}

template<typename T>
Octagon<T>::Octagon(Octagon<T>&& other) noexcept {
    p_1 = std::move(other.p_1);
    p_2 = std::move(other.p_2);
    p_3 = std::move(other.p_3);
    p_4 = std::move(other.p_4);
    p_5 = std::move(other.p_5);
    p_6 = std::move(other.p_6);
    p_7 = std::move(other.p_7);
    p_8 = std::move(other.p_8);
}

template<typename T>
Octagon<T>& Octagon<T>::operator=(const Octagon<T>& other) {
    if (this != &other) {
        p_1 = other.p_1;
        p_2 = other.p_2;
        p_3 = other.p_3;
        p_4 = other.p_4;
        p_5 = other.p_5;
        p_6 = other.p_6;
        p_7 = other.p_7;
        p_8 = other.p_8;
    }
    return *this;
}

template<typename T>
Octagon<T>& Octagon<T>::operator=(Octagon<T>&& other) noexcept {
    if (this != &other) {
        p_1 = std::move(other.p_1);
        p_2 = std::move(other.p_2);
        p_3 = std::move(other.p_3);
        p_4 = std::move(other.p_4);
        p_5 = std::move(other.p_5);
        p_6 = std::move(other.p_6);
        p_7 = std::move(other.p_7);
        p_8 = std::move(other.p_8);
    }
    return *this;
} 

template<typename T>
bool Octagon<T>::operator==(const Octagon<T>& other) const {
    const Octagon<T> *octagon = dynamic_cast<const Octagon<T>*>(&other);
    if (!octagon) return false;

    return (p_1 == octagon->p_1 && p_2 == octagon->p_2 && p_3 == octagon->p_3 &&
            p_4 == octagon->p_4 && p_5 == octagon->p_5 && p_6 == octagon->p_6 &&
            p_7 == octagon->p_7 && p_8 == octagon->p_8);
}

template<typename T>
Octagon<T>::operator double() const {
    double a1 = sqrt(pow(p_2.getX() - p_1.getX(), 2) + pow(p_2.getY() - p_1.getY(), 2));
    double a2 = sqrt(pow(p_3.getX() - p_2.getX(), 2) + pow(p_3.getY() - p_2.getY(), 2));
    double a3 = sqrt(pow(p_4.getX() - p_3.getX(), 2) + pow(p_4.getY() - p_3.getY(), 2));
    double a4 = sqrt(pow(p_5.getX() - p_4.getX(), 2) + pow(p_5.getY() - p_4.getY(), 2));
    double a5 = sqrt(pow(p_6.getX() - p_5.getX(), 2) + pow(p_6.getY() - p_5.getY(), 2));
    double a6 = sqrt(pow(p_7.getX() - p_6.getX(), 2) + pow(p_7.getY() - p_6.getY(), 2));
    double a7 = sqrt(pow(p_8.getX() - p_7.getX(), 2) + pow(p_8.getY() - p_7.getY(), 2));
    double a8 = sqrt(pow(p_1.getX() - p_8.getX(), 2) + pow(p_1.getY() - p_8.getY(), 2));
    
    double Area = (a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8) / OC_POINTS;
    return 2 * (1 + sqrt(2)) * Area * Area;
}

template<typename T>
Point<T> Octagon<T>::GeomCenter() const {
    double x = (p_1.getX() + p_2.getX() + p_3.getX() +
                p_4.getX() + p_5.getX() + p_6.getX() +
                p_7.getX() + p_7.getX()) / OC_POINTS;
    double y = (p_1.getY() + p_2.getY() + p_3.getY() +
                p_4.getY() + p_5.getY() + p_6.getY() +
                p_7.getY() + p_8.getY()) / OC_POINTS;
    return Point(x, y);
}

template<typename T>
void Octagon<T>::print(std::ostream& os) const {
    os << "Восьмиугольник:\n";
    os << "p_1: (" << p_1.getX() << ", " << p_1.getY() << ")\n";
    os << "p_2: (" << p_2.getX() << ", " << p_2.getY() << ")\n";
    os << "p_3: (" << p_3.getX() << ", " << p_3.getY() << ")\n";
    os << "p_4: (" << p_4.getX() << ", " << p_4.getY() << ")\n";
    os << "p_5: (" << p_5.getX() << ", " << p_5.getY() << ")\n";
    os << "p_6: (" << p_6.getX() << ", " << p_6.getY() << ")\n";
    os << "p_7: (" << p_7.getX() << ", " << p_7.getY() << ")\n";
    os << "p_8: (" << p_8.getX() << ", " << p_8.getY() << ")\n";
}