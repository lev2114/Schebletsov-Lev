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

void FillMassive(int* massive, int lhs, int rhs, int masLen) {
    if (massive == nullptr) {
        std::cerr << "Массива не существует!";
        return;
    }

    std::random_device r{};
    std::default_random_engine randomEngine(r());
    std::uniform_int_distribution<int> distribution(lhs, rhs);
    for (size_t i = 0; i < masLen; ++i) {
        massive[i] = distribution(randomEngine);
    }
}

[[nodiscard]] int* MassiveCopy(int* massive, int masLen) {
    if (massive == nullptr) {
        std::cerr << "Массива не существует!";
        return nullptr;
    }

    int* massiveCopy = new int[masLen];
    for (size_t i = 0; i < masLen; ++i) {
        massiveCopy[i] = massive[i];
    }
    return massiveCopy;
}

void printMassive(int* massive, int masLen) {
    if (massive == nullptr) {
        std::cerr << "Массива не существует!";
        return;
    }
    for (size_t i = 0; i < masLen; ++i) {
        std::cout << massive[i] << " ";
    }
    std::cout << "\n";
}

}  // namespace

namespace MassiveSort {

SortData MinMaxSort(int* massive, int masLen, char where){
    if (massive == nullptr) {
        std::cerr << "Массива не существует!";
        return {};
    }

    int replacements{};
    int comparasons{};

    if (where == 'u'){
        for (size_t i = 0; i < masLen-1; ++i){
            for (size_t j = i+1; j < masLen; j++){
                comparasons += 1;
                if (massive[i] > massive[j]){
                    replacements += 1;
                    Swap(massive + i, massive + j);
                }
            }
        }
        return {.replacements = replacements, .comparasons = comparasons};
    } else {
        for (size_t i = 0; i < masLen-1; ++i){
            for (size_t j = i+1; j < masLen; j++){
                comparasons += 1;
                if (massive[i] < massive[j]){
                    replacements += 1;
                    Swap(massive + i, massive + j);
                }
            }
        }
        return {.replacements = replacements, .comparasons = comparasons};
    }
    return {.replacements = replacements, .comparasons = comparasons};
}

SortData BubbleSort(int* massive, int masLen, char where) {
    if (massive == nullptr) {
        std::cerr << "Массива не существует!";
        return {};
    }

    int replacements{};
    int comparasons{};
    int replacementsPrev{};

    if (where == 'u') {
        for (size_t i = masLen; i > 0; --i) {
            for (size_t j = 0; j < i - 1; ++j) {
                comparasons += 1;
                if (massive[j] > massive[j + 1]) {
                    Swap(massive + j, massive + j + 1);
                    replacements += 1;
                }
            }
            if (replacementsPrev == replacements) {
                return {.replacements = replacements, .comparasons = comparasons};
            }
            replacementsPrev = replacements;
        }
        return {.replacements = replacements, .comparasons = comparasons};

    } else {
        for (size_t i = 0; i < masLen - 1; ++i) {
            for (size_t j = masLen - 1; j > i ; --j) {
                comparasons += 1;
                if (massive[j] > massive[j - 1]) {
                    Swap(massive + j, massive + j - 1);
                    replacements += 1;
                }
            }
            if (replacementsPrev == replacements) {
                return {.replacements = replacements, .comparasons = comparasons};
            }
            replacementsPrev = replacements;
        }
        return {.replacements = replacements, .comparasons = comparasons};
    }
    return {.replacements = replacements, .comparasons = comparasons};
}

void StaticSortsApp(int* massive, int masLen) {
    if (massive == nullptr) {
        std::cerr << "Массива не существует!";
        return;
    }

    int* massiveCopy = MassiveCopy(massive, masLen);
    std::cout << "Сортировка пузырьком:\nНеотсортированный массив:\n";
    printMassive(massive, masLen);

    SortData sortData = BubbleSort(massive, masLen, 'u');
    std::cout << "Отсортированный вверх массив:\n";
    printMassive(massive, masLen);
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений:  " << sortData.comparasons << "\n";

    sortData = BubbleSort(massive, masLen, 'u');
    std::cout << "Отсортированный вверх массив:\n";
    printMassive(massive, masLen);
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений: " << sortData.comparasons << "\n";

    sortData = BubbleSort(massive, masLen, 'd');
    std::cout << "Отсортированный вниз массив:\n";
    printMassive(massive, masLen);
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений: " << sortData.comparasons << "\n";

    std::cout << "Сортировка выбором:\nНеотсортированный массив:\n";
    printMassive(massiveCopy, masLen);

    sortData = MinMaxSort(massiveCopy, masLen, 'u');
    std::cout << "Отсортированный вверх массив:\n";
    printMassive(massiveCopy, masLen);
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений: " << sortData.comparasons << "\n";

    sortData = MinMaxSort(massiveCopy, masLen, 'u');
    std::cout << "Отсортированный вверх массив:\n";
    printMassive(massiveCopy, masLen);
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений: " << sortData.comparasons << "\n";

    sortData = MinMaxSort(massiveCopy, masLen, 'd');
    std::cout << "Отсортированный вниз массив:\n";
    printMassive(massiveCopy, masLen);
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений: " << sortData.comparasons << "\n";



    delete[] massiveCopy;
}

void DynamicSortsApp(int* massive, int masLen) {
    if (massive == nullptr) {
        std::cerr << "Массива не существует!";
        return;
    }
    int* massiveCopy = MassiveCopy(massive, masLen);
    std::cout << "Сортировка пузырьком:\n";

    SortData sortData = BubbleSort(massive, masLen, 'u');
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений: " << sortData.comparasons << "\n";

    sortData = BubbleSort(massive, masLen, 'u');
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений: " << sortData.comparasons << "\n";

    sortData = BubbleSort(massive, masLen, 'd');
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений: " << sortData.comparasons << "\n";

    std::cout << "Сортировка выбором:\n";

    sortData = MinMaxSort(massiveCopy, masLen, 'u');
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений: " << sortData.comparasons << "\n";

    sortData = MinMaxSort(massiveCopy, masLen, 'u');
    std::cout << "Перестановок: " << sortData.replacements << "\n" << "Сравнений: " << sortData.comparasons << "\n";

    sortData = MinMaxSort(massiveCopy, masLen, 'd');
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
    std::cout << "Введите границы распределения через пробел в порядке возрастания:\n";

    std::cin >> lhs >> rhs;
    FillMassive(massive, lhs, rhs, kStaticMassiveLength);
    StaticSortsApp(massive, kStaticMassiveLength);
}

void DynamicApp() {
    std::cout << "Введите длину массива\n";
    int massiveLen{};
    std::cin >> massiveLen;
    int* massive = new int[massiveLen]{};
    int lhs{};
    int rhs{};
    std::cout << "Введите границы распределения через пробел в порядке возрастания:\n";
    std::cin >> lhs >> rhs;
    FillMassive(massive, lhs, rhs, massiveLen);
    DynamicSortsApp(massive, massiveLen);
    delete[] massive;
}

}  // namespace MassiveSort
