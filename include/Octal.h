#pragma once

#include <iostream>
#include <initializer_list>
#include <string>

class Octal 
{
public:
    Octal();
    Octal(const size_t &n, unsigned char t = 0);
    Octal(const std::initializer_list<unsigned char> &t);
    Octal(const std::string &t);
    Octal(const Octal& other);
    Octal(Octal&& other) noexcept;

    Octal operator+(Octal const &other); // оператор сложения
    Octal operator-(Octal const &other); // оператор вычитания

    bool operator>(const Octal &other); // оператор сравнения >
    bool operator<(const Octal &other); // оператор сравнения <
    bool operator==(const Octal &other) const; // оператор сравнения ==

    Octal& operator=(const Octal &other); // оператор присваивания
    std::ostream &print(std::ostream &str);

    ~Octal() noexcept;

private:
    unsigned char* data; // указатель на массив
    size_t size; // размер массива
};