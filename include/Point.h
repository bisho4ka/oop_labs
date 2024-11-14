#pragma once
#include <iostream>

class Point {
private:
    double x;
    double y;
public:
    Point();
    Point(double value_X, double value_Y);

    Point(const Point& other);
    Point(Point&& other) noexcept;

    Point& operator=(const Point& other); 
    Point& operator=(Point&& other) noexcept; 

    double getX() const; 
    double getY() const; 

    void setX(double value_X);
    void setY(double value_Y);

    bool operator==(const Point& other) const;
};