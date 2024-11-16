#pragma once
#include "Point.h"

template <typename T>
class Figure {
public:
    virtual Point<T> GeomCenter() const = 0;
    virtual operator double() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual ~Figure() noexcept = default; 

    template<typename S>
    friend std::ostream &operator<<(std::ostream &os, const Figure<S> &figure);
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const Figure<T> &figure) {
    figure.print(os);
    return os;
}