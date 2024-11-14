#include <iostream>
#include "include/Octal.h"

int main() 
{
    try
    {
        std::string num_1, num_2;
        std::cin >> num_1;
        std::cin >> num_2;

        Octal First_num(num_1);
        Octal Second_num(num_2);

        std::cout << "Первое число: ";
        First_num.print(std::cout);
        std::cout << "Второе число: ";
        Second_num.print(std::cout);
    }
    catch (const std::exception &error){
        std::cout << "Произошла ощибка: " << error.what() << std::endl;
    }
}