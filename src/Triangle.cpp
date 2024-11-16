#include "../include/Triangle.h"
#include <cmath>

Triangle::Triangle() : p_1(), p_2(), p_3() {}
Triangle::Triangle(Point p1, Point p2, Point p3) : p_1(p1), p_2(p2), p_3(p3) {}

Triangle::Triangle(const Triangle& other) : p_1(other.p_1), p_2(other.p_2), p_3(other.p_3) {}
Triangle::Triangle(Triangle&& other) noexcept {
    p_1 = std::move(other.p_1);
    p_2 = std::move(other.p_2);
    p_3 = std::move(other.p_3);
}

Triangle& Triangle::operator=(const Triangle& other) {
    if (this != &other) {
        p_1 = other.p_1;
        p_2 = other.p_2;
        p_3 = other.p_3;
    }
    return *this;
}

Triangle& Triangle::operator=(Triangle&& other) noexcept {
    if (this != &other) {
        p_1 = std::move(other.p_1);
        p_2 = std::move(other.p_2);
        p_3 = std::move(other.p_3);
    }
    return *this;
} 

void Triangle::print(std::ostream& os) const {
    os << "Треугольник:\n";
    os << "p_1: (" << p_1.getX() << ", " << p_1.getY() << ")\n";
    os << "p_2: (" << p_2.getX() << ", " << p_2.getY() << ")\n";
    os << "p_3: (" << p_3.getX() << ", " << p_3.getY() << ")\n\n";
}
    
bool Triangle::operator==(const Triangle& other) const {
    const Triangle* otherTriangle = dynamic_cast<const Triangle*>(&other);
    if (!(otherTriangle)) return false;
    return (p_1 == otherTriangle->p_1 && p_2 == otherTriangle->p_2 && p_3 == otherTriangle->p_3);
}

Triangle::operator double() const {
    double area = 0.5 * std::fabs(
        (p_2.getX() - p_1.getX()) * (p_3.getY() - p_1.getY()) - 
        (p_3.getX() - p_1.getX()) * (p_2.getY() - p_1.getY()));
    return area;
}

Point Triangle::GeomCenter() const {
    double x = (p_1.getX() + p_2.getX() + p_3.getX()) / 3;
    double y = (p_1.getY() + p_2.getY() + p_3.getY()) / 3;
    return Point(x, y);
}

std::istream& operator>>(std::istream& is, Triangle& triangle) {
    double x1, y1, x2, y2, x3, y3;
    if (is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3)
        triangle = Triangle(Point(x1, y1), Point(x2, y2), Point(x3, y3));
    else {
        is.clear();
        throw std::invalid_argument("Ошибка ввода");
    }
    return is;
}