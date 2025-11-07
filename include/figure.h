#pragma once
#include "point.h"
#include <iostream>
#include <memory>
#include <type_traits>

template<class T>
class Figure {
public:
    virtual ~Figure() = default;
    
    virtual Point<T> geometricCenter() const = 0;
    virtual double area() const = 0;
    virtual operator double() const { return area(); }
    
    virtual bool operator==(const Figure<T>& other) const = 0;
    virtual bool operator!=(const Figure<T>& other) const {
        return !(*this == other);
    }
    
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    
    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
        fig.print(os);
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Figure<T>& fig) {
        fig.read(is);
        return is;
    }
};
