#include <cmath>
#include <iomanip>
#include <iostream>

#include "a.h"

namespace {
const double h = 0.2;
const int kNumberToLeave = 5;
const int kTask4NumberOfDecimalPlaces = 6;
}  // namespace

int main(int, char**) {
    char toLeaveOrNotToLeave = 'y';
    int taskNumber{-1};
    while (toLeaveOrNotToLeave != 'n') {
        std::cout << "Введите, пожалуйста, номер задания от 1 до 4!\n";
        std::cin >> taskNumber;
        switch (taskNumber) {
            case 1: {
                std::cout << "Отлично! Введите два натуральных числа m и n (m<n) через пробел!\n";
                int n = -1;
                int m = -1;
                std::cin >> m >> n;
                Task1(n, m);
                break;
            }

            case 2: {
                std::cout << "Отлично! Введите число a!\n";
                double a{};
                std::cin >> a;
                Task2(a);
                break;
            }

            case 3:
                Task3(h);
                break;

            case 4: {
                char exit = 'y';
                int n{};
                while (exit != 'n') {
                    std::cout << "Отлично! Введите целое число n!\n";
                    std::cin >> n;
                    if (n > 0) {
                        Task4(n, kTask4NumberOfDecimalPlaces);
                        std::cout << "Вы хотите ввести ещё одно n? (y/n)\n";
                        std::cin >> exit;
                    } else {
                        std::cout << "Введено ненатуральное n!";
                    }
                }
                break;
            }

            default:
                std::cout << "Введены неверные данные!";
                return 1;
        }
        std::cout << "Вы хотите продолжить выполнение? (y/n)\n";
        std::cin >> toLeaveOrNotToLeave;
    }
    return 0;
}
