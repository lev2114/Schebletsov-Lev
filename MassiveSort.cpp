#include "MassiveSort.hpp"
#include <iostream>

namespace {
const int kStaticMassiveLength = 7;

void Swap(int* lhs, int* rhs) {
    int temporaryStorage{};
    temporaryStorage = *lhs;
    *lhs = *rhs;
    *rhs = temporaryStorage;
}

[[nodiscard]] int AskSortMethod() {
    std::cout << "Выберите метод сортировки:\n1) Метод min/max\n2) Метод пузырька\n";
    int method{};
    std::cin >> method;
    return method;
}

[[nodiscard]] int AskMenuOption() {
    std::cout << "Выберите вид массива:\n1) Статический массив\n2) Динамический массив\n";
    int method{};
    std::cin >> method;
    return method;
}

}  // namespace

namespace MassiveSort {
void TaskChoose() {
    MenuOption option = static_cast<MenuOption>(AskMenuOption());
    switch (option) {
        case MenuOption::Static:
            StaticApp();
            break;

        case MenuOption::Dynamic:
            DynamicApp();
            break;

        default:
            std::cerr << "Введены неверные данные!\n";
            return;
    }
}

void StartCycle() {
    char Continuation = 'y';
    while (Continuation == 'y') {
        TaskChoose();
        std::cout << "Вы хотите продолжить?(y/n)\n";
        std::cin >> Continuation;
    }
}

void StaticApp() {
    int massive[kStaticMassiveLength]{1, 6, 4, 34, 38, 35, 3};
    MethodOption method = static_cast<MethodOption>(AskSortMethod());
    switch (method) {
        case MethodOption::bubble:
            BubbleSort(massive);
            break;

        case MethodOption::minMax:
            MinMaxSort(massive);
            break;

        default:
            std::cerr << "Введены неверные данные!\n";
            return;
    }
}

void DynamicApp() {
    std::cout << "Введите длину массива\n";
    int massiveLen;
    std::cin >> massiveLen;
    int* massive = new int[massiveLen]{};
    MethodOption method = static_cast<MethodOption>(AskSortMethod());
    switch (method) {
        case MethodOption::bubble:
            BubbleSort(massive);
            break;

        case MethodOption::minMax:
            MinMaxSort(massive);
            break;

        default:
            std::cerr << "Введены неверные данные!\n";
            delete[] massive;
            return;
    }
    delete[] massive;
}

}  // namespace MassiveSort
