#include "../include/Octal.h"

Octal::Octal() : size(0), data{nullptr} {}

Octal::Octal(const size_t &n, unsigned char t)
{
    if (!('0' <= t <= '7')) 
        throw std::invalid_argument("not octal system");
    size = n;
    data = new unsigned char[n];
    for (size_t i = 0; i < n; i++) 
        data[i] = t;
}

Octal::Octal(const std::initializer_list<unsigned char> &t) 
{
    size = t.size();
    data = new unsigned char[size];
    size_t i = 0;
    for (unsigned char num : t)
    {
        if (!('0' <= num <= '7')) 
            throw std::invalid_argument("not octal system");
        data[i] = num;
        i++;
    }
}

Octal:: Octal(const std::string &t)
{
    size = t.size();
    data = new unsigned char[size];
    for (size_t i = 0; i < size; i++)
    {
        if (!('0' <= t[i] && t[i] <= '7'))
            throw std::invalid_argument("not octal system");
        data[i] = t[i];
    }
}

Octal::Octal(const Octal& other)
{
    size = other.size;
    data = new unsigned char[size];
    for (size_t i = 0; i < size; i++)
        data[i] = other.data[i];
}

Octal::Octal(Octal&& other) noexcept
{
    size = other.size;
    data = other.data;

    other.size = 0;
    other.data = nullptr;
}

Octal Octal::operator+(Octal const& other)
{
    size_t res_size = std::max(other.size, size) + 1;
    std::string result(res_size, '0');
    int num = 0;
    for (size_t i = 0; i < res_size; i++)
    {
        int first = (i < size) ? (data[i] - '0') : 0;
        int second = (i < other.size) ? (other.data[i] - '0') : 0;
        int sum = first + second + num;

        result[i] = '0' + (sum % 8);
        num = sum / 8;
    }
    if (num > 0)
        result[res_size - 1] = '0' + num;

    if (result[res_size - 1] == '0')
        result.erase(res_size - 1, 1);
        
    std::reverse(result.begin(), result.end());

    return Octal(result);
}


Octal Octal::operator-(Octal const& other)
{
    if (*this < other)
        throw std::logic_error("answer can't be negative");

    size_t res_size = std::max(other.size, size) + 1;
    std::string result(res_size, '0');
    int num = 0;

    for (size_t i = 0; i < res_size; i++)
    {
        int first = (i < size) ? (data[i] - '0') : 0;
        int second = (i < other.size) ? (other.data[i] - '0') : 0;
        int dif = first - second - num;

        if (dif < 0)
        {
            dif += 8;
            num = 1;
        }
        else
            num = 0;

        result[i] = '0' + dif;
    }

    while (result[res_size - 1] == '0' && res_size > 1)
        result.erase(result.size() - 1, 1); 

    std::reverse(result.begin(), result.end());

    return Octal(result);

}

bool Octal::operator>(const Octal& other)
{
    if (*this < other || *this == other)
        return false;
    return true;
}

bool Octal::operator<(const Octal &other)
{
    if (*this > other || *this == other)
        return false;
    return true;
}

bool Octal::operator==(const Octal &other)
{
    if (size == other.size)
    {
        for (size_t i = 0; i < size; i++)
        {
            if(data[i] != other.data[i])
                return false;
        }
        return true;
    }
    return false;
}

Octal& Octal::operator=(const Octal& other)
{
    if (&other != this) 
    {
        delete[] data;
        size = other.size;
        data = new unsigned char[size];
        for (size_t i = 0; i < size; i++)
            data[i] = other.data[i];
    }
    
    return *this;
}

std::ostream &Octal::print(std::ostream &str)
{
    for (size_t i = size; i--;)
        str << data[i];
    
    str << std::endl;
    return str;
}

Octal::~Octal() noexcept
{
    if (size > 0)
    {
        size = 0;
        delete[] data;
        data = nullptr;
    }
}