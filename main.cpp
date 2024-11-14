#include <iostream>
#include <vector>
#include "include/Hexagon.h"
#include "include/Octagon.h"
#include "include/Triangle.h"
#include "include/Array.h"

int main() {
    Array list;

    try {
        Hexagon hexagon(
            Point(0, 0), Point(2, 1), Point(3, 3),
            Point(2, 5), Point(0, 6), Point(-1, 3));
        hexagon.print(std::cout);
        list.add(new Hexagon(hexagon));

        Octagon octagon(
            Point(0, 0), Point(4, 0), Point(5, 1), Point(5, 3),
            Point(4, 4), Point(0, 4), Point(-1, 3), Point(-1, 1));
        octagon.print(std::cout);
        list.add(new Octagon(octagon));

        Triangle triangle(Point(0, 0), Point(5, 0), Point(0, 5));
        triangle.print(std::cout);
        list.add(new Triangle(triangle));
    } 
    
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    std::cout << "\nВсе фигуры:\n";
    for (size_t i = 0; i < list.size(); i++) {
        Figure* f = list.getFigure(i);
        std::cout << "\nФигура №" << i + 1 << "\n";
        f->print(std::cout);
        Point center = f->GeomCenter();
        std::cout << "Центр: (" << center.getX() << ", " << center.getY() << ")" << std::endl;
        double area = static_cast<double>(*f);
        std::cout << "Площадь: " << area << "\n";
    }

    std::cout << "\nУдалить 3-ий элемент\n";

    if (list.size() > 2) 
        list.remove(2);
    else 
        std::cout << "Отсутствует фигура на 3-ей позиции" << std::endl;

    std::cout << "\nВсе фигуры:\n";
    for (size_t i = 0; i < list.size(); i++) {
        Figure* f = list.getFigure(i);
        std::cout << "\nФигура № " << i + 1 << ":\n";
        f->print(std::cout);
        Point center = f->GeomCenter();
        std::cout << "Центр: (" << center.getX() << ", " << center.getY() << ")" << std::endl;
        double area = static_cast<double>(*f);
        std::cout << "Площадь: " << area << std::endl;
    }

    return 0;
}