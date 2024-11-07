#include "MassiveSort.hpp"
#include <iostream>
#include <random>
namespace {
const int kStaticMassiveLength = 7;

void Swap(int* lhs, int* rhs) {
    int temporaryStorage{};
    temporaryStorage = *lhs;
    *lhs = *rhs;
    *rhs = temporaryStorage;
}

[[nodiscard]] int AskMenuOption() {
    std::cout << "Выберите вид массива:\n1) Статический массив\n2) Динамический массив\n";
    int method{};
    std::cin >> method;
    return method;
}

void FillMassive(int* mas, int lhs, int rhs, int masLen){
    std::random_device r{};
    std::default_random_engine randomEngine(r()); 
    std::uniform_int_distribution<int> distribution(lhs, rhs);
    for(size_t i = 0; i < masLen; ++i){
        mas[i] = distribution(randomEngine);
    }
}

[[nodiscard]] int* MassiveCopy(int* massive,int masLen){
    int* massiveCopy = new int[masLen];
    for (size_t i = 0; i<masLen; ++i){
        massiveCopy[i] = massive[i];
    }
    return massiveCopy;
}

void printMassive(int* massive, int masLen){
    for(size_t i; i < masLen; ++i){
        std::cout << massive[i] << " ";
    }
}

}  // namespace

namespace MassiveSort {
void StaticSortsApp(int* massive, int masLen){
    int* massiveCopy = MassiveCopy(massive, masLen);
    std::cout << "Сортировка пузырьком:\nНеотсортированный массив:\n";
    printMassive(massive, masLen);
    std::cout << "\n";

    SortData sortData = BubbleSort(massive, 'u');
    std::cout << "Отсортированный вверх массив:\n";
    printMassive(massive, masLen);
    std::cout << "\n";
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений: " << sortData.comparasons << "\n";

    sortData = BubbleSort(massive, 'u');
    std::cout << "Отсортированный вверх массив:\n";
    printMassive(massive, masLen);
    std::cout << "\n";
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений: " << sortData.comparasons << "\n";

    sortData = BubbleSort(massive, 'd');
    std::cout << "Отсортированный вниз массив:\n";
    printMassive(massive, masLen);
    std::cout << "\n";
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений: " << sortData.comparasons << "\n";

    std::cout << "Сортировка выбором:\nНеотсортированный массив:\n";
    printMassive(massiveCopy, masLen);
    std::cout << "\n";
    
    sortData = MinMaxSort(massiveCopy, 'u');
    std::cout << "Отсортированный вверх массив:\n";
    printMassive(massiveCopy, masLen);
    std::cout << "\n";
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений: " << sortData.comparasons << "\n";

    sortData = MinMaxSort(massiveCopy, 'u');
    std::cout << "Отсортированный вверх массив:\n";
    printMassive(massiveCopy, masLen);
    std::cout << "\n";
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений: " << sortData.comparasons << "\n";

    sortData = MinMaxSort(massiveCopy, 'd');
    std::cout << "Отсортированный вниз массив:\n";
    printMassive(massiveCopy, masLen);
    std::cout << "\n";
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений: " << sortData.comparasons << "\n";

    delete[] massiveCopy;
}

void DynamicSortsApp(int* massive, int masLen){
    int* massiveCopy = MassiveCopy(massive, masLen);
    std::cout << "Сортировка пузырьком:\n";

    SortData sortData = BubbleSort(massive, 'u');
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений: " << sortData.comparasons << "\n";

    sortData = BubbleSort(massive, 'u');
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений: " << sortData.comparasons << "\n";

    sortData = BubbleSort(massive, 'd');
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений: " << sortData.comparasons << "\n";

    std::cout << "Сортировка выбором:\n";
    
    sortData = MinMaxSort(massiveCopy, 'u');
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений: " << sortData.comparasons << "\n";

    sortData = MinMaxSort(massiveCopy, 'u');
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений: " << sortData.comparasons << "\n";

    sortData = MinMaxSort(massiveCopy, 'd');
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений: " << sortData.comparasons << "\n";

    delete[] massiveCopy;
}

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
    int massive[kStaticMassiveLength]{};
    int lhs{};
    int rhs{};
    std::cout << "Введите границы распределения через пробел в порядке возрастания";
    std::cin >> lhs >> rhs;
    FillMassive(massive,lhs,rhs,kStaticMassiveLength);
    StaticSortsApp(massive,kStaticMassiveLength);
}

void DynamicApp() {
    std::cout << "Введите длину массива\n";
    int massiveLen{};
    std::cin >> massiveLen;
    int* massive = new int[massiveLen]{};
    int lhs{};
    int rhs{};
    std::cout << "Введите границы распределения через пробел в порядке возрастания";
    std::cin >> lhs >> rhs;
    FillMassive(massive,lhs,rhs,massiveLen);
    DynamicSortsApp(massive,massiveLen);
    delete[] massive;
}

}  // namespace MassiveSort
