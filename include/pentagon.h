#pragma once
#include "figure.h"
#include <array>
#include <memory>
#include <cmath>
#include <type_traits>

template<class T>
class Pentagon : public Figure<T> {
private:
    std::array<std::unique_ptr<Point<T>>, 5> vertices;

    T distance(const Point<T>& p1, const Point<T>& p2) const {
        T dx = p1.getX() - p2.getX();
        T dy = p1.getY() - p2.getY();
        return std::sqrt(dx * dx + dy * dy);
    }

public:
    Pentagon() {
        static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
        for (auto& v : vertices) {
            v = std::make_unique<Point<T>>();
        }
    }
    
    Pentagon(const Point<T>& center, T radius) {
        static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
        for (int i = 0; i < 5; ++i) {
            T angle = 2 * M_PI * i / 5;
            T x = center.getX() + radius * std::cos(angle);
            T y = center.getY() + radius * std::sin(angle);
            vertices[i] = std::make_unique<Point<T>>(x, y);
        }
    }

    Pentagon(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, 
             const Point<T>& p4, const Point<T>& p5) {
        static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
        vertices[0] = std::make_unique<Point<T>>(p1);
        vertices[1] = std::make_unique<Point<T>>(p2);
        vertices[2] = std::make_unique<Point<T>>(p3);
        vertices[3] = std::make_unique<Point<T>>(p4);
        vertices[4] = std::make_unique<Point<T>>(p5);
    }

    Pentagon(const Pentagon& other) {
        static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
        for (size_t i = 0; i < 5; ++i) {
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        }
    }

    Pentagon& operator=(const Pentagon& other) {
        if (this != &other) {
            for (size_t i = 0; i < 5; ++i) {
                vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
            }
        }
        return *this;
    }

    Point<T> geometricCenter() const override {
        T x = 0, y = 0;
        for (const auto& v : vertices) {
            x += v->getX();
            y += v->getY();
        }
        return Point<T>(x / 5, y / 5);
    }

    double area() const override {
        T side = distance(*vertices[0], *vertices[1]);
        return 0.25 * std::sqrt(5 * (5 + 2 * std::sqrt(5))) * side * side;
    }

    bool operator==(const Figure<T>& other) const override {
        const Pentagon* otherPentagon = dynamic_cast<const Pentagon*>(&other);
        if (!otherPentagon) return false;
        
        for (size_t i = 0; i < 5; ++i) {
            if (*vertices[i] != *otherPentagon->vertices[i]) return false;
        }
        return true;
    }

    void print(std::ostream& os) const override {
        os << "Pentagon: ";
        for (const auto& v : vertices) {
            os << *v << " ";
        }
    }

    void read(std::istream& is) override {
        for (int i = 0; i < 5; ++i) {
            T x, y;
            is >> x >> y;
            vertices[i] = std::make_unique<Point<T>>(x, y);
        }
    }

    const Point<T>& getVertex(size_t index) const {
        return *vertices[index];
    }
};
