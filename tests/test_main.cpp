#include <gtest/gtest.h>
#include <memory>
#include <cmath>
#include "../include/point.h"
#include "../include/figure.h"
#include "../include/rhombus.h"
#include "../include/pentagon.h"
#include "../include/hexagon.h"
#include "../include/array.h"

// Тесты для Point
TEST(PointTest, DefaultConstructor) {
    Point<double> p;
    EXPECT_DOUBLE_EQ(p.getX(), 0.0);
    EXPECT_DOUBLE_EQ(p.getY(), 0.0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<double> p(1.5, 2.5);
    EXPECT_DOUBLE_EQ(p.getX(), 1.5);
    EXPECT_DOUBLE_EQ(p.getY(), 2.5);
}

TEST(PointTest, SettersAndGetters) {
    Point<double> p;
    p.setX(3.0);
    p.setY(4.0);
    EXPECT_DOUBLE_EQ(p.getX(), 3.0);
    EXPECT_DOUBLE_EQ(p.getY(), 4.0);
}

TEST(PointTest, EqualityOperator) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.0, 2.0);
    Point<double> p3(3.0, 4.0);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(PointTest, InequalityOperator) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(3.0, 4.0);
    
    EXPECT_TRUE(p1 != p2);
    EXPECT_FALSE(p1 != p1);
}

TEST(PointTest, OutputOperator) {
    Point<double> p(1.5, 2.5);
    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "(1.5, 2.5)");
}

TEST(PointTest, InputOperator) {
    Point<double> p;
    std::stringstream ss("3.0 4.0");
    ss >> p;
    EXPECT_DOUBLE_EQ(p.getX(), 3.0);
    EXPECT_DOUBLE_EQ(p.getY(), 4.0);
}

// Тесты для Rhombus
TEST(RhombusTest, DefaultConstructor) {
    Rhombus<double> rhombus;
    // Проверяем, что объект создан без ошибок
    EXPECT_NO_THROW(rhombus.area());
}

TEST(RhombusTest, ParameterizedConstructor) {
    Rhombus<double> rhombus(
        Point<double>(0, 1),
        Point<double>(1, 0),
        Point<double>(0, -1),
        Point<double>(-1, 0)
    );
    
    EXPECT_NEAR(rhombus.area(), 2.0, 1e-6);
}

TEST(RhombusTest, AreaCalculation) {
    Rhombus<double> rhombus(
        Point<double>(0, 2),
        Point<double>(2, 0),
        Point<double>(0, -2),
        Point<double>(-2, 0)
    );
    
    EXPECT_NEAR(rhombus.area(), 8.0, 1e-6);
}

TEST(RhombusTest, GeometricCenter) {
    Rhombus<double> rhombus(
        Point<double>(0, 1),
        Point<double>(1, 0),
        Point<double>(0, -1),
        Point<double>(-1, 0)
    );
    
    Point<double> center = rhombus.geometricCenter();
    EXPECT_NEAR(center.getX(), 0.0, 1e-6);
    EXPECT_NEAR(center.getY(), 0.0, 1e-6);
}

TEST(RhombusTest, EqualityOperator) {
    Rhombus<double> rhombus1(
        Point<double>(0, 1),
        Point<double>(1, 0),
        Point<double>(0, -1),
        Point<double>(-1, 0)
    );
    
    Rhombus<double> rhombus2(
        Point<double>(0, 1),
        Point<double>(1, 0),
        Point<double>(0, -1),
        Point<double>(-1, 0)
    );
    
    Rhombus<double> rhombus3(
        Point<double>(0, 2),
        Point<double>(2, 0),
        Point<double>(0, -2),
        Point<double>(-2, 0)
    );
    
    EXPECT_TRUE(rhombus1 == rhombus2);
    EXPECT_FALSE(rhombus1 == rhombus3);
}

TEST(RhombusTest, DoubleConversion) {
    Rhombus<double> rhombus(
        Point<double>(0, 1),
        Point<double>(1, 0),
        Point<double>(0, -1),
        Point<double>(-1, 0)
    );
    
    double area = static_cast<double>(rhombus);
    EXPECT_NEAR(area, 2.0, 1e-6);
}

TEST(RhombusTest, InputOutput) {
    Rhombus<double> rhombus1(
        Point<double>(1, 2),
        Point<double>(3, 4),
        Point<double>(5, 6),
        Point<double>(7, 8)
    );
    
    std::stringstream ss;
    ss << rhombus1;
    
    Rhombus<double> rhombus2;
    // Для тестирования ввода нужно создать правильный формат данных
    std::stringstream input("1 2 3 4 5 6 7 8");
    input >> rhombus2;
    
    EXPECT_TRUE(rhombus1 == rhombus2);
}

// Тесты для Pentagon
TEST(PentagonTest, DefaultConstructor) {
    Pentagon<double> pentagon;
    EXPECT_NO_THROW(pentagon.area());
}

TEST(PentagonTest, CircleConstructor) {
    Pentagon<double> pentagon(Point<double>(0, 0), 1.0);
    double area = pentagon.area();
    EXPECT_GT(area, 0.0);
    EXPECT_LT(area, 3.0); // Площадь пятиугольника с радиусом 1 меньше 3
}

TEST(PentagonTest, GeometricCenter) {
    Pentagon<double> pentagon(Point<double>(2.0, 3.0), 1.0);
    Point<double> center = pentagon.geometricCenter();
    EXPECT_NEAR(center.getX(), 2.0, 1e-6);
    EXPECT_NEAR(center.getY(), 3.0, 1e-6);
}

TEST(PentagonTest, AreaCalculation) {
    Pentagon<double> pentagon(Point<double>(0, 0), 1.0);
    double area = pentagon.area();
    EXPECT_NEAR(area, 1.720477, 1e-6); // Известная площадь правильного пятиугольника с радиусом 1
}

TEST(PentagonTest, DoubleConversion) {
    Pentagon<double> pentagon(Point<double>(0, 0), 1.0);
    double area = static_cast<double>(pentagon);
    EXPECT_GT(area, 0.0);
}

// Тесты для Hexagon
TEST(HexagonTest, DefaultConstructor) {
    Hexagon<double> hexagon;
    EXPECT_NO_THROW(hexagon.area());
}

TEST(HexagonTest, CircleConstructor) {
    Hexagon<double> hexagon(Point<double>(0, 0), 1.0);
    double area = hexagon.area();
    EXPECT_NEAR(area, 2.598076, 1e-6); // Известная площадь правильного шестиугольника с радиусом 1
}

TEST(HexagonTest, GeometricCenter) {
    Hexagon<double> hexagon(Point<double>(1.0, 2.0), 1.0);
    Point<double> center = hexagon.geometricCenter();
    EXPECT_NEAR(center.getX(), 1.0, 1e-6);
    EXPECT_NEAR(center.getY(), 2.0, 1e-6);
}

TEST(HexagonTest, AreaCalculation) {
    Hexagon<double> hexagon(Point<double>(0, 0), 2.0);
    double area = hexagon.area();
    EXPECT_NEAR(area, 10.392304, 1e-6); // Площадь шестиугольника с радиусом 2
}

TEST(HexagonTest, DoubleConversion) {
    Hexagon<double> hexagon(Point<double>(0, 0), 1.0);
    double area = static_cast<double>(hexagon);
    EXPECT_NEAR(area, 2.598076, 1e-6);
}

// Тесты для Array
TEST(ArrayTest, DefaultConstructor) {
    Array<int> array;
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.empty());
}

TEST(ArrayTest, PushBackAndSize) {
    Array<std::shared_ptr<Figure<double>>> array;
    auto rhombus = std::make_shared<Rhombus<double>>();
    
    EXPECT_EQ(array.size(), 0);
    array.push_back(rhombus);
    EXPECT_EQ(array.size(), 1);
    EXPECT_FALSE(array.empty());
}

TEST(ArrayTest, MultiplePushBack) {
    Array<int> array;
    
    for (int i = 0; i < 10; ++i) {
        array.push_back(i);
    }
    
    EXPECT_EQ(array.size(), 10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(array[i], i);
    }
}

TEST(ArrayTest, EraseElement) {
    Array<std::shared_ptr<Figure<double>>> array;
    auto fig1 = std::make_shared<Rhombus<double>>();
    auto fig2 = std::make_shared<Pentagon<double>>();
    auto fig3 = std::make_shared<Hexagon<double>>();
    
    array.push_back(fig1);
    array.push_back(fig2);
    array.push_back(fig3);
    EXPECT_EQ(array.size(), 3);
    
    array.erase(1);
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array[0], fig1);
    EXPECT_EQ(array[1], fig3);
}

TEST(ArrayTest, EraseFirstElement) {
    Array<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);
    
    array.erase(0);
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array[0], 2);
    EXPECT_EQ(array[1], 3);
}

TEST(ArrayTest, EraseLastElement) {
    Array<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);
    
    array.erase(2);
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array[0], 1);
    EXPECT_EQ(array[1], 2);
}

TEST(ArrayTest, OutOfRangeAccess) {
    Array<int> array;
    array.push_back(1);
    
    EXPECT_THROW(array[1], std::out_of_range);
    EXPECT_THROW(array.erase(2), std::out_of_range);
}

TEST(ArrayTest, CopyConstructor) {
    Array<int> array1;
    array1.push_back(1);
    array1.push_back(2);
    array1.push_back(3);
    
    Array<int> array2(array1);
    EXPECT_EQ(array2.size(), array1.size());
    for (size_t i = 0; i < array1.size(); ++i) {
        EXPECT_EQ(array1[i], array2[i]);
    }
}

TEST(ArrayTest, MoveConstructor) {
    Array<int> array1;
    array1.push_back(1);
    array1.push_back(2);
    
    Array<int> array2(std::move(array1));
    EXPECT_EQ(array2.size(), 2);
    EXPECT_EQ(array1.size(), 0); // После перемещения исходный массив пуст
    EXPECT_EQ(array2[0], 1);
    EXPECT_EQ(array2[1], 2);
}

TEST(ArrayTest, CopyAssignment) {
    Array<int> array1;
    array1.push_back(1);
    array1.push_back(2);
    
    Array<int> array2;
    array2 = array1;
    
    EXPECT_EQ(array2.size(), array1.size());
    for (size_t i = 0; i < array1.size(); ++i) {
        EXPECT_EQ(array1[i], array2[i]);
    }
}

TEST(ArrayTest, MoveAssignment) {
    Array<int> array1;
    array1.push_back(1);
    array1.push_back(2);
    
    Array<int> array2;
    array2 = std::move(array1);
    
    EXPECT_EQ(array2.size(), 2);
    EXPECT_EQ(array1.size(), 0);
    EXPECT_EQ(array2[0], 1);
    EXPECT_EQ(array2[1], 2);
}

TEST(ArrayTest, Clear) {
    Array<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);
    
    EXPECT_EQ(array.size(), 3);
    array.clear();
    EXPECT_EQ(array.size(), 0);
    EXPECT_TRUE(array.empty());
}

// Интеграционные тесты
TEST(IntegrationTest, ArrayOfFigures) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
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
    
    figures.push_back(rhombus);
    figures.push_back(pentagon);
    figures.push_back(hexagon);
    
    EXPECT_EQ(figures.size(), 3);
    
    // Проверяем, что все фигуры имеют положительную площадь
    for (size_t i = 0; i < figures.size(); ++i) {
        EXPECT_GT(figures[i]->area(), 0.0);
        EXPECT_NO_THROW(figures[i]->geometricCenter());
    }
    
    // Проверяем общую площадь
    double totalArea = 0;
    for (size_t i = 0; i < figures.size(); ++i) {
        totalArea += figures[i]->area();
    }
    EXPECT_GT(totalArea, 0.0);
}

TEST(IntegrationTest, ArrayOfSpecificFigures) {
    Array<std::shared_ptr<Rhombus<double>>> rhombusArray;
    
    auto rhombus1 = std::make_shared<Rhombus<double>>(
        Point<double>(0, 1),
        Point<double>(1, 0),
        Point<double>(0, -1),
        Point<double>(-1, 0)
    );
    
    auto rhombus2 = std::make_shared<Rhombus<double>>(
        Point<double>(0, 2),
        Point<double>(2, 0),
        Point<double>(0, -2),
        Point<double>(-2, 0)
    );
    
    rhombusArray.push_back(rhombus1);
    rhombusArray.push_back(rhombus2);
    
    EXPECT_EQ(rhombusArray.size(), 2);
    EXPECT_NEAR(rhombusArray[0]->area(), 2.0, 1e-6);
    EXPECT_NEAR(rhombusArray[1]->area(), 8.0, 1e-6);
}

TEST(IntegrationTest, FigurePolymorphism) {
    std::shared_ptr<Figure<double>> figure1 = std::make_shared<Rhombus<double>>(
        Point<double>(0, 1),
        Point<double>(1, 0),
        Point<double>(0, -1),
        Point<double>(-1, 0)
    );
    
    std::shared_ptr<Figure<double>> figure2 = std::make_shared<Pentagon<double>>(
        Point<double>(0, 0), 1.0
    );
    
    std::shared_ptr<Figure<double>> figure3 = std::make_shared<Hexagon<double>>(
        Point<double>(0, 0), 1.0
    );
    
    // Проверяем полиморфное поведение
    EXPECT_GT(figure1->area(), 0.0);
    EXPECT_GT(figure2->area(), 0.0);
    EXPECT_GT(figure3->area(), 0.0);
    
    Point<double> center1 = figure1->geometricCenter();
    Point<double> center2 = figure2->geometricCenter();
    Point<double> center3 = figure3->geometricCenter();
    
    EXPECT_NEAR(center1.getX(), 0.0, 1e-6);
    EXPECT_NEAR(center1.getY(), 0.0, 1e-6);
    EXPECT_NEAR(center2.getX(), 0.0, 1e-6);
    EXPECT_NEAR(center2.getY(), 0.0, 1e-6);
    EXPECT_NEAR(center3.getX(), 0.0, 1e-6);
    EXPECT_NEAR(center3.getY(), 0.0, 1e-6);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
