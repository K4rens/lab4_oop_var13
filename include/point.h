#pragma once
#include <type_traits>
#include <memory>
#include <iostream>
#include <cmath>

template<class T>
class Point {
private:
    T x, y;

public:
    Point(T x = 0, T y = 0) : x(x), y(y) {
        static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    }

    T getX() const { return x; }
    T getY() const { return y; }

    void setX(T newX) { x = newX; }
    void setY(T newY) { y = newY; }

    bool operator==(const Point& other) const {
        if (std::is_integral<T>::value) {
            return x == other.x && y == other.y;
        } else {
            return std::abs(x - other.x) < 1e-6 && std::abs(y - other.y) < 1e-6;
        }
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }

    friend std::istream& operator>>(std::istream& is, Point& p) {
        return is >> p.x >> p.y;
    }
};
