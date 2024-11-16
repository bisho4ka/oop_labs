#include <gtest/gtest.h>
#include <cmath>
#include "../include/Octagon.h"
#include "../include/Hexagon.h"
#include "../include/Point.h"
#include "../include/Triangle.h"

TEST(HexagonTest, test_1) {
    Hexagon hexagon(
        Point(1, 0), Point(2, std::sqrt(3)), Point(1, std::sqrt(3) * 2),
        Point(-1, std::sqrt(3) * 2), Point(-2, std::sqrt(3)), Point(-1, 0));

    double result = 6 * std::sqrt(3);
    double area = static_cast<double>(hexagon);

    EXPECT_NEAR(area, result, 1e-5);
}

TEST(HexagonTest, test_2) {
    Hexagon hexagon(
        Point(1, 1), Point(4, 2), Point(5, 5),
        Point(3, 7), Point(0, 6), Point(-1, 3));

    Point res_center(2.0, 4.0);
    Point center = hexagon.GeomCenter();

    EXPECT_NEAR(center.getX(), res_center.getX(), 1e-5);
    EXPECT_NEAR(center.getY(), res_center.getY(), 1e-5);
}

TEST(HexagonTest, test_3) {
    Hexagon hexagon_1(
        Point(0, 0), Point(2, 1), Point(3, 3),
        Point(2, 5), Point(0, 6), Point(-1, 3));

    Hexagon hexagon_2 = hexagon_1;

    EXPECT_TRUE(hexagon_1 == hexagon_2);
}

TEST(OctagonTest, test_1) {
    Octagon octagon(
        Point(0, 0), Point(4, 0), Point(5, 1), Point(5, 3),
        Point(4, 4), Point(0, 4), Point(-1, 3), Point(-1, 1));

    double result = 22.0;
    double area = static_cast<double>(octagon);

    EXPECT_NEAR(area, result, 1e-5);
}

TEST(OctagonTest, test_2) {
    Octagon octagon(
        Point(1, 1), Point(4, 1), Point(5, 3), Point(4, 5),
        Point(2, 5), Point(1, 3), Point(0, 2), Point(0, 0));

    Point res_center(2.125, 2.5);
    Point center = octagon.GeomCenter();

    EXPECT_NEAR(center.getX(), res_center.getX(), 1e-5);
}

TEST(OctagonTest, test_3) {
    Octagon octagon_1(
        Point(2, 0), Point(1, std::sqrt(2)), Point(0, 2), Point(-1, std::sqrt(2)),
        Point(-2, 0), Point(-1, -(std::sqrt(2))), Point(0, -2), Point(1, -(std::sqrt(2))));

    Octagon octagon_2 = octagon_1;

    EXPECT_TRUE(octagon_1 == octagon_2);
}

TEST(TriangleTest, test_1) {
    Triangle triangle(Point(0, 0), Point(5, 0), Point(0, 5));

    double result = 12.5;
    double area = static_cast<double>(triangle);

    EXPECT_NEAR(area, result, 1e-5);
}

TEST(TriangleTest, test_2) {
    Triangle triangle(Point(1, 2), Point(5, 6), Point(3, 4));

    Point res_center(3, 4);
    Point center = triangle.GeomCenter();

    EXPECT_NEAR(center.getX(), res_center.getX(), 1e-5);
}

TEST(TriangleTest, test_3) {
    Triangle triangle_1(Point(2, 1), Point(6, 3), Point(4, 7));
    Triangle triangle_2 = triangle_1;

    EXPECT_TRUE(triangle_1 == triangle_2);
}