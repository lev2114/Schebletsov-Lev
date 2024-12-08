#include "dz.hpp"
#include <iostream>

namespace{
const int kDZE = 53;
const int kDZN = 299;
const int kDZP = 13;
const int kDZQ = 23;
const int kDZEilerFunc = 264;
const int kDZCryptedValue = 171;

int FindD(int kDZEilerFunc, int kDZE);
int Decrypt(int d, int kDZN);
void PrintResults(int kDZE, int d, int kDZN, int decryptedValue);

}

namespace dz{
void StartDZ(){
    int d = FindD(kDZEilerFunc, kDZE);
    int decryptedValue = Decrypt(d,kDZN);
    PrintResults(kDZE, d, kDZN, decryptedValue);
}

void StartProgram(){
    char continuation = 'y';
    while (continuation = 'y') {
        std::cout << "Введите, что вы хотите сделать!" << '\n' << "1: Выполнить ДЗ" << '\n' << "2: Зашифровать число" << std::endl;
        int a{};
        std::cin >> a;
        switch (a) {
        case 1:
            StartDZ();
            break;
        case 2:
            StartFullAlgorhytm();
            break;
        default:
            std::cout << "Введено невалидное значение!" << std::endl;
            break;
        }
        std::cout << "Вы хотите продолжить?(y/n)" << std::endl;
        std::cin >> continuation;
    }

    std::cout << "Введите, что вы хотите сделать!" << '\n' << "1: Выполнить ДЗ" << '\n' << "2: Зашифровать число" << std::endl;
    int a{};
    std::cin >> a;
    switch (a)
    {
    case 1:
        StartDZ();
        break;
    case 2:
        StartFullAlgorhytm();
        break;
    default:
        std::cout << "Введено невалидное значение!" << std::endl;
        break;
    }
}
}
