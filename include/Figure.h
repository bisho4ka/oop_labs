#pragma once
#include "Point.h"

class Figure {
public:
    virtual Point GeomCenter() const = 0;
    virtual operator double() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual ~Figure() noexcept = default;
};