#include <iostream>
#include <memory>
#include "include/point.h"
#include "include/figure.h"
#include "include/rhombus.h"
#include "include/pentagon.h"
#include "include/hexagon.h"
#include "include/array.h"
#include "include/array_of_figures.h"


int main() {
    try {
        // Пример работы с базовыми типами
        Array<std::shared_ptr<Figure<double>>> figures;
        
        // Создаем фигуры
        auto rhombus = std::make_shared<Rhombus<double>>(
            Point<double>(0, 1),
            Point<double>(1, 0),
            Point<double>(0, -1),
            Point<double>(-1, 0)
        );
        
        auto pentagon = std::make_shared<Pentagon<double>>(
            Point<double>(0, 0), 1.0
        );
        
        auto hexagon = std::make_shared<Hexagon<double>>(
            Point<double>(0, 0), 1.0
        );
        
        // Добавляем фигуры в массив
        figures.push_back(rhombus);
        figures.push_back(pentagon);
        figures.push_back(hexagon);
        
        std::cout << "Total figures: " << figures.size() << std::endl;
        std::cout << "Total area: " << totalArea(figures) << std::endl;
        
        // Выводим информацию о всех фигурах
        printAllFigures(figures);
        
        // Демонстрация работы с массивом конкретных типов
        Array<std::shared_ptr<Rhombus<double>>> rhombusArray;
        auto rhombus2 = std::make_shared<Rhombus<double>>(
            Point<double>(0, 2),
            Point<double>(2, 0),
            Point<double>(0, -2),
            Point<double>(-2, 0)
        );
        rhombusArray.push_back(rhombus2);
        
        std::cout << "\n=== Rhombus Array ===" << std::endl;
        for (size_t i = 0; i < rhombusArray.size(); ++i) {
            std::cout << "Figure: " << *rhombusArray[i] << std::endl;
            std::cout << "Geometric center: " << rhombusArray[i]->geometricCenter() << std::endl;
            std::cout << "Area: " << rhombusArray[i]->area() << std::endl;
        }

        std::cout << "\n=== After removing first figure ===" << std::endl;
        figures.erase(0);
        printAllFigures(figures);
        std::cout << "Total area after removal: " << totalArea(figures) << std::endl;
        

        std::cout << "\n=== Input demonstration ===" << std::endl;
        Rhombus<double> inputRhombus;
        std::cout << "Enter 4 points for rhombus (x y for each point):" << std::endl;
        std::cin >> inputRhombus;
        std::cout << "You entered: " << inputRhombus << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}
