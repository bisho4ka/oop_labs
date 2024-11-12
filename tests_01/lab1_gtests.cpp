#include <gtest/gtest.h>
#include "../include/checkingTheString.h"

TEST(tests_lab1, EmptyString) {
  std::string str = "";
  bool result = checkingTheString(str);
  EXPECT_EQ(result, true);
}

TEST(tests_lab1, CorrectString_1) {
  std::string str = "()()()";
  bool result = checkingTheString(str);
  EXPECT_EQ(result, true);
}

TEST(tests_lab1, CorrectString_2) {
  std::string str = "(()()(()))";
  bool result = checkingTheString(str);
  EXPECT_EQ(result, true);
}

TEST(tests_lab1, IncorrectString) {
  std::string str = ")())()";
  bool result = checkingTheString(str);
  EXPECT_EQ(result, false);
}

TEST(tests_lab1, LongString) {
  std::string str = "((()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()))";
  ASSERT_THROW(checkingTheString(str), std::length_error);
}

TEST(tests_lab1, OtherChar) {
  std::string str = "()(((hi)))()";
  ASSERT_THROW(checkingTheString(str), std::invalid_argument);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
