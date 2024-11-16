#include "../include/Hexagon.h"
#include <cmath>

Hexagon::Hexagon() : p_1(), p_2(), p_3(), p_4(), p_5(),  p_6() {}
Hexagon::Hexagon(Point p1, Point p2, Point p3, Point p4, Point p5, Point p6) : p_1(p1), p_2(p2), p_3(p3), p_4(p4), p_5(p5), p_6(p6) {}

Hexagon::Hexagon(const Hexagon& other) : p_1(other.p_1), p_2(other.p_2), p_3(other.p_3), p_4(other.p_4), p_5(other.p_5), p_6(other.p_6) {}
Hexagon::Hexagon(Hexagon&& other) noexcept {
    p_1 = std::move(other.p_1);
    p_2 = std::move(other.p_2);
    p_3 = std::move(other.p_3);
    p_4 = std::move(other.p_4);
    p_5 = std::move(other.p_5);
    p_6 = std::move(other.p_6);
}

Hexagon& Hexagon::operator=(const Hexagon& other) {
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

Hexagon& Hexagon::operator=(Hexagon&& other) noexcept {
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

void Hexagon::print(std::ostream& os) const {
    os << "Шестиугольник:\n";
    os << "p_1: (" << p_1.getX() << ", " << p_1.getY() << ")\n";
    os << "p_2: (" << p_2.getX() << ", " << p_2.getY() << ")\n";
    os << "p_3: (" << p_3.getX() << ", " << p_3.getY() << ")\n";
    os << "p_4: (" << p_4.getX() << ", " << p_4.getY() << ")\n";
    os << "p_5: (" << p_5.getX() << ", " << p_5.getY() << ")\n";
    os << "p_6: (" << p_6.getX() << ", " << p_6.getY() << ")\n\n";
}
    
bool Hexagon::operator==(const Hexagon& other) const {
    const Hexagon* otherHexagon = dynamic_cast<const Hexagon*>(&other);
    if (!(otherHexagon)) return false;
    bool cond_1 =  p_1 == otherHexagon->p_1 && p_2 == otherHexagon->p_2 && p_3 == otherHexagon->p_3;
    bool cond_2 =  p_4 == otherHexagon->p_4 && p_5 == otherHexagon->p_5 && p_6 == otherHexagon->p_6;
    return (cond_1 && cond_2);
}

Hexagon::operator double() const {
    double area = 0.0;
    const Point* points[] = {&p_1, &p_2, &p_3, &p_4, &p_5, &p_6};
    int cnt_points = 6;
    for (int i = 0; i < cnt_points; i++) {
        const Point* current = points[i];
        const Point* next = points[(i + 1) % cnt_points];
        area += (current->getX() * next->getY()) - (next->getX() * current->getY());
    }
    area = std::fabs(area) / 2.0;
    return area;
}

Point Hexagon::GeomCenter() const {
    double x = (p_1.getX() + p_2.getX() + p_3.getX() + p_4.getX() + p_5.getX() + p_6.getX()) / 6;
    double y = (p_1.getY() + p_2.getY() + p_3.getY() + p_4.getY() + p_5.getY() + p_6.getY()) / 6;
    return Point(x, y);
}

std::istream& operator>>(std::istream& is, Hexagon& r) {
    double x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6;
    if (is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >> x5 >> y5 >> x6 >> y6)
        r = Hexagon(Point(x1, y1), Point(x2, y2), Point(x3, y3), Point(x4, y4), Point(x5, y5), Point(x6, y6));
    else {
        is.clear();
        throw std::invalid_argument("Ошибка ввода");
    }
    return is;
}