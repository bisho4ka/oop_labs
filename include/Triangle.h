#pragma once
#include <iostream>
#include "Figure.h"
#include "Point.h"

class Triangle : public Figure {
public:
    Triangle();
    Triangle(Point p1, Point p2, Point p3);

    Triangle(const Triangle& other); 
    Triangle(Triangle&& other) noexcept;

    Triangle& operator=(const Triangle& other);
    Triangle& operator=(Triangle&& other) noexcept;    
    
    void print(std::ostream& os) const;
    
    bool operator==(const Triangle& other) const;

    operator double() const;
    Point GeomCenter() const;

    friend std::istream& operator>>(std::istream& is, Triangle& triangle);
private:
    Point p_1;
    Point p_2;
    Point p_3;
};