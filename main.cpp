#include <iostream>
#include "../include/checkingTheString.h"

int main() {
    std::string str;

    std::cout << "Введите строку: ";
    std::cin >> str;

    try {
        std::cout << "Результат: " << checkingTheString(str) << std::endl;
    }
    catch(std::invalid_argument error) {
        std::cout << "Произошла ошибка: " << error.what() << std::endl;
    }

    return 0;
}
