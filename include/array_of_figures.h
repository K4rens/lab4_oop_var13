#pragma once
#include "array.h"
#include "figure.h"
#include <iostream>

template<class T>
void printAllFigures(const Array<std::shared_ptr<Figure<T>>>& array) {
    std::cout << "=== All Figures ===" << std::endl;
    for (size_t i = 0; i < array.size(); ++i) {
        std::cout << "Figure " << i << ": " << *array[i] << std::endl;
        std::cout << "Geometric center: " << array[i]->geometricCenter() << std::endl;
        std::cout << "Area: " << array[i]->area() << std::endl;
        std::cout << "---" << std::endl;
    }
}

template<class T>
double totalArea(const Array<std::shared_ptr<Figure<T>>>& array) {
    double total = 0;
    for (size_t i = 0; i < array.size(); ++i) {
        total += static_cast<double>(*array[i]);
    }
    return total;
}
