#pragma once
#include "figure.h"
#include <array>
#include <memory>
#include <cmath>
#include <type_traits>

template<class T>
class Rhombus : public Figure<T> {
private:
    std::array<std::unique_ptr<Point<T>>, 4> vertices;

    T distance(const Point<T>& p1, const Point<T>& p2) const {
        T dx = p1.getX() - p2.getX();
        T dy = p1.getY() - p2.getY();
        return std::sqrt(dx * dx + dy * dy);
    }

public:
    Rhombus() {
        static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
        for (auto& v : vertices) {
            v = std::make_unique<Point<T>>();
        }
    }
    
    Rhombus(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) {
        static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
        vertices[0] = std::make_unique<Point<T>>(p1);
        vertices[1] = std::make_unique<Point<T>>(p2);
        vertices[2] = std::make_unique<Point<T>>(p3);
        vertices[3] = std::make_unique<Point<T>>(p4);
    }

    Rhombus(const Rhombus& other) {
        static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
        for (size_t i = 0; i < 4; ++i) {
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        }
    }

    Rhombus& operator=(const Rhombus& other) {
        if (this != &other) {
            for (size_t i = 0; i < 4; ++i) {
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
        return Point<T>(x / 4, y / 4);
    }

    double area() const override {
        T d1 = distance(*vertices[0], *vertices[2]);
        T d2 = distance(*vertices[1], *vertices[3]);
        return (d1 * d2) / 2.0;
    }

    bool operator==(const Figure<T>& other) const override {
        const Rhombus* otherRhombus = dynamic_cast<const Rhombus*>(&other);
        if (!otherRhombus) return false;
        
        for (size_t i = 0; i < 4; ++i) {
            if (*vertices[i] != *otherRhombus->vertices[i]) return false;
        }
        return true;
    }

    void print(std::ostream& os) const override {
        os << "Rhombus: ";
        for (const auto& v : vertices) {
            os << *v << " ";
        }
    }

    void read(std::istream& is) override {
        for (int i = 0; i < 4; ++i) {
            T x, y;
            is >> x >> y;
            vertices[i] = std::make_unique<Point<T>>(x, y);
        }
    }

    const Point<T>& getVertex(size_t index) const {
        return *vertices[index];
    }
};
