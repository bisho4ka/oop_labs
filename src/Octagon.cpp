#include "../include/Octagon.h"
#include <cmath>

Octagon::Octagon() : p_1(), p_2(), p_3(), p_4(), p_5(), p_6(), p_7(), p_8() {}
Octagon::Octagon(Point p1, Point p2, Point p3, Point p4, Point p5, Point p6, Point p7, Point p8) {
    p_1 = p1;
    p_2 = p2;
    p_3 = p3;
    p_4 = p4;
    p_5 = p5;
    p_6 = p6;
    p_7 = p7;
    p_8 = p8;
}

Octagon::Octagon(const Octagon& other) {
    p_1 = other.p_1;
    p_2 = other.p_2;
    p_3 = other.p_3;
    p_4 = other.p_4;
    p_5 = other.p_5;
    p_6 = other.p_6;
    p_7 = other.p_7;
    p_8 = other.p_8;
}
Octagon::Octagon(Octagon&& other) noexcept {
    p_1 = std::move(other.p_1);
    p_2 = std::move(other.p_2);
    p_3 = std::move(other.p_3);
    p_4 = std::move(other.p_4);
    p_5 = std::move(other.p_5);
    p_6 = std::move(other.p_6);
    p_7 = std::move(other.p_7);
    p_8 = std::move(other.p_8);
}

Octagon& Octagon::operator=(const Octagon& other) {
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

Octagon& Octagon::operator=(Octagon&& other) noexcept {
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

void Octagon::print(std::ostream& os) const {
    os << "Восьмиугольник:\n";
    os << "p_1: (" << p_1.getX() << ", " << p_1.getY() << ")\n";
    os << "p_2: (" << p_2.getX() << ", " << p_2.getY() << ")\n";
    os << "p_3: (" << p_3.getX() << ", " << p_3.getY() << ")\n";
    os << "p_4: (" << p_4.getX() << ", " << p_4.getY() << ")\n";
    os << "p_5: (" << p_5.getX() << ", " << p_5.getY() << ")\n";
    os << "p_6: (" << p_6.getX() << ", " << p_6.getY() << ")\n";
    os << "p_7: (" << p_7.getX() << ", " << p_7.getY() << ")\n";
    os << "p_8: (" << p_8.getX() << ", " << p_8.getY() << ")\n\n";
}
    
bool Octagon::operator==(const Octagon& other) const {
    const Octagon* otherOctagon = dynamic_cast<const Octagon*>(&other);
    if (!(otherOctagon)) return false;
    bool cond_1 =  p_1 == otherOctagon->p_1 && p_2 == otherOctagon->p_2 && p_3 == otherOctagon->p_3 && p_4 == otherOctagon->p_4;
    bool cond_2 =  p_5 == otherOctagon->p_5 && p_6 == otherOctagon->p_6 && p_7 == otherOctagon->p_7 && p_8 == otherOctagon->p_8;
    return (cond_1 && cond_2);
}

Octagon::operator double() const {
    double area = 0.0;
    const Point* points[] = {&p_1, &p_2, &p_3, &p_4, &p_5, &p_6, &p_7, &p_8};
    int cnt_points = 8;
    for (int i = 0; i < cnt_points; i++) {
        const Point* current = points[i];
        const Point* next = points[(i + 1) % cnt_points];
        area += (current->getX() * next->getY()) - (next->getX() * current->getY());
    }
    area = std::fabs(area) / 2.0;
    return area;
}

Point Octagon::GeomCenter() const {
    double x = (p_1.getX() + p_2.getX() + p_3.getX() + p_4.getX() + 
                p_5.getX() + p_6.getX() + p_7.getX() + p_8.getX()) / 8;
    double y = (p_1.getY() + p_2.getY() + p_3.getY() + p_4.getY() + 
                p_5.getY() + p_6.getY() + p_7.getY() + p_8.getY()) / 8;
    return Point(x, y);
}

std::istream& operator>>(std::istream& is, Octagon& r) {
    double x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8;
    if (is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >> x5 >> y5 >> x6 >> y6 >> x7 >> y7 >> x8 >> y8)
        r = Octagon(Point(x1, y1), Point(x2, y2), Point(x3, y3), Point(x4, y4),
                    Point(x5, y5), Point(x6, y6), Point(x7, y7), Point(x8, y8));
    else {
        is.clear();
        throw std::invalid_argument("Ошибка ввода");
    }
    return is;
}