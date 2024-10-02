#ifndef A_H
#define A_H
#include <cmath>
#include <iomanip>
#include <iostream>
#endif
#include "a.h"

int main(int, char**) {
    int TaskNumber{};
    while (TaskNumber != 5) {
        std::cout << "Введите, пожалуйста, номер задания от 1 до 4! Если хотите закончить выполнение, введите 5!\n";
        std::cin >> TaskNumber;
        if (TaskNumber == 1) {
            std::cout << "Отлично! Введите два натуральных числа m и n (m<n) через пробел!\n";
            int n = -1;
            int m = -1;
            std::cin >> m >> n;
            if (n > 0 && m > 0 && m < n) {
                task1(n, m);
            } else {
                std::cout << "Введены неверные данные! ";
            }
        } else if (TaskNumber == 2) {
            std::cout << "Отлично! Введите целое число a!\n";
            int a{};
            std::cin >> a;
            task2(a);
        } else if (TaskNumber == 3) {
            double h = 0.2;
            task3(h);
        } else if (TaskNumber == 4) {
            char Exit = 'y';
            int n{};
            int NumberOfDecimalPlaces{};
            while (Exit != 'n') {
                std::cout << "Отлично! Введите целое число n, а также количество знаков после запятой через пробел!\n";
                std::cin >> n >> NumberOfDecimalPlaces;
                if (n > 0) {
                    task4(n, NumberOfDecimalPlaces);
                    std::cout << "Вы хотите ввести ещё одно n? (y/n)\n";
                    std::cin >> Exit;
                } else {
                }
            }
        } else {
            std::cout << "Введены неверные данные! ";
        }
    }
}
