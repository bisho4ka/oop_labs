#include <gtest/gtest.h>
#include "../include/Octal.h"

TEST(tests_lab2, construct_1) {
    Octal num_1("3333");
    Octal num_2(4, '3');
    ASSERT_EQ(num_1, num_2);
}

TEST(tests_lab2, construct_2) {
    Octal num_1("20");
    Octal num_2 = {'2', '0'};
    ASSERT_EQ(num_1, num_2);
}

TEST(tests_lab2, construct_3) {
    Octal num_1("123");
    Octal num_2 = num_1;
    ASSERT_EQ(num_1, num_2);
}

TEST(tests_lab2, operators_1) {
    Octal num_1("303");
    Octal num_2("303");
    ASSERT_TRUE(num_1 == num_2);
}

TEST(tests_lab2, operators_2) {
    Octal num_1("10");
    Octal num_2("11");
    ASSERT_TRUE(num_1 < num_2);
}

TEST(tests_lab2, operators_3) {
    Octal num_1("234");
    Octal num_2("223");
    ASSERT_TRUE(num_1 > num_2);
}

TEST(tests_lab2, operators_4) {
    Octal num_1("1");
    Octal num_2("777");
    Octal num_3("1000");
    ASSERT_TRUE(num_3 == (num_1 + num_2));
}

TEST(tests_lab2, operators_5) {
    Octal num_1("666");
    Octal num_2("3");
    Octal num_3("663");
    ASSERT_TRUE(num_3 == (num_1 - num_2));
}

TEST(tests_lab2, operators_6) {
    Octal num_1("10");
    Octal num_2("1");
    Octal num_3("7");
    ASSERT_TRUE(num_3 == (num_1 - num_2));
}

TEST(tests_lab2, operators_7) {
    Octal num_1("1");
    Octal num_2("7");
    Octal num_3("10");
    ASSERT_TRUE(num_3 == (num_1 + num_2));
}

TEST(tests_lab2, error_1) {
    ASSERT_THROW(Octal num("908"), std::invalid_argument);
}

TEST(tests_lab2, error_2) {
    Octal num_1('1');
    Octal num_2{'3', '8'};
    ASSERT_THROW(num_1 - num_2, std::logic_error);
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
