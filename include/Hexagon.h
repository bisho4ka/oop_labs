#pragma once
#include <iostream>
#include "Figure.h"
#include "Point.h"

class Hexagon : public Figure {
public:
    Hexagon();
    Hexagon(Point p1, Point p2, Point p3, Point p4, Point p5, Point p6);

    Hexagon(const Hexagon& other); 
    Hexagon(Hexagon&& other) noexcept;

    Hexagon& operator=(const Hexagon& other);
    Hexagon& operator=(Hexagon&& other) noexcept;    
    
    void print(std::ostream& os) const;
    
    bool operator==(const Hexagon& other) const;

    operator double() const;
    Point GeomCenter() const;

    friend std::istream& operator>>(std::istream& is, Hexagon& hexagon);

private:
    Point p_1;
    Point p_2;
    Point p_3;
    Point p_4;
    Point p_5;
    Point p_6;
};