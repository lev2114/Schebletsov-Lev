#include "Integration.hpp"

#include <iomanip>
#include <iostream>
#include <cmath>


namespace {
const char kStandardTableLine[] = "+-----------+-----------------+-----------------+---------+\n";


[[nodiscard]]int ReadIntegrationMethod(){
    std::cout << "Выберите метод:\n1) Метод прямоугольников\n2) Метод трапеций";
    int method{};
    std::cin >> method;
    return method;
}



}

namespace Integration{

void StartSquareIntegration(int a, int b, double precicion){

}


void StartProgram(){
    char continueExecution = 'y';
    while (continueExecution == 'y') {
        std::cout << "Введите натуральные числа a и b через пробел:\n";
        int a{};
        int b{};
        std::cin >> a, b;

        std::cout << "Введите требуемую погрешность в виде десятичной дроби или в научном виде:\n";
        double precicion{};
        std::cin >> precicion;

        switch(static_cast<Method>(ReadIntegrationMethod())){
            case Method::squareMethod:
                StartSquareIntegration(a,b,precicion);
                break;
            case Method::trapezioidMethod:
                StartTrapezioidIntegration(a,b,precicion);
                break;
        }

        std::cout << "Вы хотите продолжить? (y/n)\n";
        std::cin >> continueExecution;
    }


}



}
