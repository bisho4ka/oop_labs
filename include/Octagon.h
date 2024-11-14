#pragma once
#include <iostream>
#include "Figure.h"
#include "Point.h"

class Octagon : public Figure {
public:
    Octagon();
    Octagon(Point p1, Point p2, Point p3, Point p4, Point p5, Point p6, Point p7, Point p8);

    Octagon(const Octagon& other); 
    Octagon(Octagon&& other) noexcept;

    Octagon& operator=(const Octagon& other);
    Octagon& operator=(Octagon&& other) noexcept;    
    
    void print(std::ostream& os) const;
    
    bool operator==(const Octagon& other) const;

    operator double() const;
    Point GeomCenter() const;

    friend std::istream& operator>>(std::istream& is, Octagon& octagon);
private:
    Point p_1;
    Point p_2;
    Point p_3;
    Point p_4;
    Point p_5;
    Point p_6;
    Point p_7;
    Point p_8;
};