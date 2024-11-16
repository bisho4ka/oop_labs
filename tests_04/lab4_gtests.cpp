#include <gtest/gtest.h>
#include "../include/Hexagon.h"
#include "../include/Octagon.h"
#include "../include/Triangle.h"
#include "../include/Point.h"

TEST(HexagonTest, test_1) {
    Hexagon<double> hexagon(
        Point<double>(1, 0), Point<double>(2, std::sqrt(3)), Point<double>(1, std::sqrt(3) * 2),
        Point<double>(-1, std::sqrt(3) * 2), Point<double>(-2, std::sqrt(3)), Point<double>(-1, 0));

    double result = 6 * std::sqrt(3);
    double area = static_cast<double>(hexagon);

    EXPECT_NEAR(area, result, 1e-5);
}

TEST(HexagonTest, test_2) {
    Hexagon<double> hexagon(
        Point<double>(1, 1), Point<double>(4, 2), Point<double>(5, 5),
        Point<double>(3, 7), Point<double>(0, 6), Point<double>(-1, 3));

    Point<double> res_center(2.0, 4.0);
    Point<double> center = hexagon.GeomCenter();

    EXPECT_NEAR(center.getX(), res_center.getX(), 1e-5);
    EXPECT_NEAR(center.getY(), res_center.getY(), 1e-5);
}

TEST(HexagonTest, test_3) {
    Hexagon<double> hexagon_1(
        Point<double>(0, 0), Point<double>(2, 1), Point<double>(3, 3),
        Point<double>(2, 5), Point<double>(0, 6), Point<double>(-1, 3));

    Hexagon<double> hexagon_2 = hexagon_1;

    EXPECT_TRUE(hexagon_1 == hexagon_2);
}

TEST(OctagonTest, test_1) {
    Octagon<double> octagon(
        Point<double>(1, 0), Point<double>(1 / std::sqrt(2), 1 / std::sqrt(2)), Point<double>(0, 1),
        Point<double>(- 1 / std::sqrt(2), 1 / std::sqrt(2)), Point<double>(-1, 0),
        Point<double>(- 1 / std::sqrt(2), - 1 / std::sqrt(2)), Point<double>(0, -1),
        Point<double>(1 / std::sqrt(2), - 1 / std::sqrt(2)));

    double result = 2 * std::sqrt(2);
    double area = static_cast<double>(octagon);

    EXPECT_NEAR(area, result, 1e-5);
}

TEST(OctagonTest, test_2) {
    Octagon<double> octagon(
        Point<double>(1, 1), Point<double>(4, 1), Point<double>(5, 3), Point<double>(4, 5),
        Point<double>(2, 5), Point<double>(1, 3), Point<double>(0, 2), Point<double>(0, 0));

    Point<double> res_center(2.125, 2.5);
    Point<double> center = octagon.GeomCenter();

    EXPECT_NEAR(center.getX(), res_center.getX(), 1e-5);
}

TEST(OctagonTest, test_3) {
    Octagon<double> octagon_1(
        Point<double>(2, 0), Point<double>(1, std::sqrt(2)), Point<double>(0, 2), Point<double>(-1, std::sqrt(2)),
        Point<double>(-2, 0), Point<double>(-1, -(std::sqrt(2))), Point<double>(0, -2), Point<double>(1, -(std::sqrt(2))));

    Octagon<double> octagon_2 = octagon_1;

    EXPECT_TRUE(octagon_1 == octagon_2);
}

TEST(TriangleTest, test_1) {
    Triangle<double> triangle(Point<double>(0, 0), Point<double>(5, 0), Point<double>(0, 5));

    double result = 12.5;
    double area = static_cast<double>(triangle);

    EXPECT_NEAR(area, result, 1e-5);
}

TEST(TriangleTest, test_2) {
    Triangle<double> triangle(Point<double>(1, 2), Point<double>(5, 6), Point<double>(3, 4));

    Point<double> res_center(3, 4);
    Point<double> center = triangle.GeomCenter();

    EXPECT_NEAR(center.getX(), res_center.getX(), 1e-5);
}

TEST(TriangleTest, test_3) {
    Triangle<double> triangle_1(Point<double>(2, 1), Point<double>(6, 3), Point<double>(4, 7));
    Triangle<double> triangle_2 = triangle_1;

    EXPECT_TRUE(triangle_1 == triangle_2);
}