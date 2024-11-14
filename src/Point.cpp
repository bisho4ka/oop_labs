#include "../include/Point.h"

Point::Point() : x(0.0), y(0.0) {}
Point::Point(double value_X, double value_Y) : x(value_X), y(value_Y) {}

Point::Point(const Point& other) : x(other.x), y(other.y) {}
Point::Point(Point&& other) noexcept {
    x = other.x;
    y = other.y;
    other.x = 0.0;
    other.y = 0.0;
}

Point& Point::operator=(const Point& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

Point& Point::operator=(Point&& other) noexcept {
    if (!(*this == other)) {
        x = other.x;
        y = other.y;
        other.x = 0.0;
        other.y = 0.0;
    }
    return *this;
} 

double Point::getX() const {
    return x;
}

double Point::getY() const {
    return y;
}

void Point::setX(double value_X) {
    x = value_X;
}

void Point::setY(double value_Y) {
    y = value_Y;
}

bool Point::operator==(const Point& other) const {
    return (x == other.x && y == other.y);
}
