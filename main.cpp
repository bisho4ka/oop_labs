#include <iostream>
#include <vector>
#include "include/Hexagon.h"
#include "include/Octagon.h"
#include "include/Triangle.h"
#include "include/Array.h"
#include "include/Figure.h"

int main() {
    Array<double> list;

    try {
        Hexagon<double> hexagon(
            Point<double>(0, 0), Point<double>(2, 1), Point<double>(3, 3),
            Point<double>(2, 5), Point<double>(0, 6), Point<double>(-1, 3));
        hexagon.print(std::cout);
        list.add(std::make_unique<Hexagon<double>>(hexagon));

        Octagon<double> octagon(
            Point<double>(0, 0), Point<double>(4, 0), Point<double>(5, 1), Point<double>(5, 3),
            Point<double>(4, 4), Point<double>(0, 4), Point<double>(-1, 3), Point<double>(-1, 1));
        octagon.print(std::cout);
        list.add(std::make_unique<Octagon<double>>(octagon));

        Triangle<double> triangle(Point<double>(0, 0), Point<double>(5, 0), Point<double>(0, 5));
        triangle.print(std::cout);
        list.add(std::make_unique<Triangle<double>>(triangle));
    } 
    
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    std::cout << "\nВсе фигуры:\n";
    for (size_t i = 0; i < list.size(); i++) {
        Figure<double>* f = list.getFigure(i);
        std::cout << "\nФигура №" << i + 1 << "\n";
        f->print(std::cout);
        Point<double> center = f->GeomCenter();
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
        Figure<double>* f = list.getFigure(i);
        std::cout << "\nФигура № " << i + 1 << ":\n";
        f->print(std::cout);
        Point<double> center = f->GeomCenter();
        std::cout << "Центр: (" << center.getX() << ", " << center.getY() << ")" << std::endl;
        double area = static_cast<double>(*f);
        std::cout << "Площадь: " << area << std::endl;
    }

    return 0;
}