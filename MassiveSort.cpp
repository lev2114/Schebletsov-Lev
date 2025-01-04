#include "MassiveSort.hpp"
#include <iostream>
#include <random>
namespace {

const int kStaticMassiveLength = 7;
[[nodiscard]] int* ArrayCopy(int* array, int arrLen) {
    if (array == nullptr) {
        std::cerr << "Массив пуст!";
        return nullptr;
    }

    int* arrayCopy = new int[arrLen];
    for (size_t i = 0; i < arrLen; ++i) {
        arrayCopy[i] = array[i];
    }
    return arrayCopy;
}

void printArray(int* array, int arrLen) {
    if (array == nullptr) {
        std::cerr << "Массив пуст!";
        return;
    }
    for (size_t i = 0; i < arrLen; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << "\n";
}


void StaticSortsApp(int* array, int arrLen) {
    if (array == nullptr) {
        std::cerr << "Массив пуст!";
        return;
    }

    int* arrayCopy = ArrayCopy(array, arrLen);
    std::cout << "Сортировка пузырьком:\n Неотсортированный массив:\n";
    printArray(array, arrLen);

    MassiveSort::SortData sortData = MassiveSort::BubbleSort(array, arrLen, true);
    std::cout << "Отсортированный по возрастанию массив:\n";
    printArray(array, arrLen);
    std::cout << "Перестановок: " << sortData.swaps << "\n" << "Сравнений:  " << sortData.comparisons << "\n\n";

    sortData = MassiveSort::BubbleSort(array, arrLen, true);
    std::cout << "Отсортированный по возрастанию массив:\n";
    printArray(array, arrLen);
    std::cout << "Перестановок: " << sortData.swaps << "\n" << "Сравнений: " << sortData.comparisons << "\n\n";

    sortData = MassiveSort::BubbleSort(array, arrLen, false);
    std::cout << "Отсортированный по убыванию массив:\n";
    printArray(array, arrLen);
    std::cout << "Перестановок: " << sortData.swaps << "\n" << "Сравнений: " << sortData.comparisons << "\n\n";

    std::cout << "Сортировка выбором:\n отсортированный массив:\n";
    printArray(arrayCopy, arrLen);

    sortData = MassiveSort::SelectionSort(arrayCopy, arrLen, true);
    std::cout << "Отсортированный по возрастанию массив:\n\n";
    printArray(arrayCopy, arrLen);
    std::cout << "Перестановок: " << sortData.swaps << "\n" << "Сравнений: " << sortData.comparisons << "\n\n";

    sortData = MassiveSort::SelectionSort(arrayCopy, arrLen, true);
    std::cout << "Отсортированный по возрастанию массив:\n";
    printArray(arrayCopy, arrLen);
    std::cout << "Перестановок: " << sortData.swaps << "\n" << "Сравнений: " << sortData.comparisons << "\n\n";

    sortData = MassiveSort::SelectionSort(arrayCopy, arrLen, false);
    std::cout << "Отсортированный по убыванию массив:\n";
    printArray(arrayCopy, arrLen);
    std::cout << "Перестановок: " << sortData.swaps << "\n" << "Сравнений: " << sortData.comparisons << "\n\n";

    delete[] arrayCopy;
}

void DynamicSortsApp(int* array, int arrLen) {
    if (array == nullptr) {
        std::cerr << "Массив пуст!";
        return;
    }
    int* arrayCopy = ArrayCopy(array, arrLen);
    std::cout << "Сортировка пузырьком:\n";

    MassiveSort::SortData sortData = MassiveSort::BubbleSort(array, arrLen, true);
    std::cout << "Перестановок: " << sortData.swaps << "\n" << "Сравнений: " << sortData.comparisons << "\n\n";

    sortData = MassiveSort::BubbleSort(array, arrLen, true);
    std::cout << "Перестановок: " << sortData.swaps << "\n" << "Сравнений: " << sortData.comparisons << "\n\n";

    sortData = MassiveSort::BubbleSort(array, arrLen, false);
    std::cout << "Перестановок: " << sortData.swaps << "\n" << "Сравнений: " << sortData.comparisons << "\n\n";

    std::cout << "Сортировка выбором:\n";

    sortData = MassiveSort::SelectionSort(arrayCopy, arrLen, true);
    std::cout << "Перестановок: " << sortData.swaps << "\n" << "Сравнений: " << sortData.comparisons << "\n\n";

    sortData = MassiveSort::SelectionSort(arrayCopy, arrLen, true);
    std::cout << "Перестановок: " << sortData.swaps << "\n" << "Сравнений: " << sortData.comparisons << "\n\n";

    sortData = MassiveSort::SelectionSort(arrayCopy, arrLen, false);
    std::cout << "Перестановок: " << sortData.swaps << "\n" << "Сравнений: " << sortData.comparisons << "\n\n";

    delete[] arrayCopy;
}

void Swap(int* lhs, int* rhs) {
    *lhs = *rhs + *lhs;
    *rhs = *lhs - *rhs;
    *lhs -= *rhs;
}

[[nodiscard]] int AskMenuOption() {
    std::cout << "Выберите вид массива:\n1) Статический массив\n2) Динамический массив\n";
    int method{};
    std::cin >> method;
    return method;
}

void FillArray(int* array, int lhs, int rhs, int arrLen) {
    if (array == nullptr) {
        std::cerr << "Массив пуст!";
        return;
    }

    std::random_device r{};
    std::default_random_engine randomEngine(r());
    std::uniform_int_distribution<int> distribution(lhs, rhs);
    for (size_t i = 0; i < arrLen; ++i) {
        array[i] = distribution(randomEngine);
    }
}

}  // namespace

namespace MassiveSort {

SortData SelectionSort(int* array, int arrLen, bool ascending) {
    if (array == nullptr) {
        std::cerr << "Массив пуст!";
        return {};
    }

    int swaps{};
    int comparisons{};

        for (size_t i = 0; i < arrLen - 1; ++i) {
            for (size_t j = i + 1; j < arrLen; j++) {
                if (array[i] > array[j] == ascending && array[i] != array[j]) {
                    swaps += 1;
                    comparisons += 1;
                    Swap(array + i, array + j);
                } else{
                    comparisons += 1;
                }
            }
        }
        return { .swaps = swaps, .comparisons = comparisons};

}

SortData BubbleSort(int* array, int arrLen, bool ascending) {
    if (array == nullptr) {
        std::cerr << "Массив пуст!";
        return {};
    }

    int swaps{};
    int comparisons{};
    int swapsPrev{};

    for (size_t i = arrLen; i > 0; --i) {
        for (size_t j = 0; j < i - 1; ++j) {
            if (array[j] > array[j + 1] == ascending && array[j] != array[j + 1]) {
                comparisons +=1;
                Swap(array + j, array + j + 1);
                swaps += 1;
            } else{
                comparisons += 1;
            }
        }
        if (swapsPrev == swaps) {
            return {.swaps = swaps, .comparisons = comparisons};
        }
        swapsPrev = swaps;
    }
    return {.swaps = swaps, .comparisons = comparisons};
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

void MainLoop() {
    char continuation = 'y';
    while (continuation == 'y') {
        TaskChoose();
        std::cout << "Вы хотите продолжить?(y/n)\n";
        std::cin >> continuation;
    }
}

void StaticApp() {
    int array[kStaticMassiveLength]{};
    int lhs{};
    int rhs{};
    std::cout << "Введите границы распределения через пробел в порядке возрастания:\n";

    std::cin >> lhs >> rhs;
    FillArray(array, lhs, rhs, kStaticMassiveLength);
    StaticSortsApp(array, kStaticMassiveLength);
}

void DynamicApp() {
    std::cout << "Введите длину массива\n";
    int massiveLen{};
    std::cin >> massiveLen;
    int* array = new int[massiveLen]{};
    int lhs{};
    int rhs{};
    std::cout << "Введите границы распределения через пробел в порядке возрастания:\n";
    std::cin >> lhs >> rhs;
    FillArray(array, lhs, rhs, massiveLen);
    DynamicSortsApp(array, massiveLen);
    delete[] array;
}

}  // namespace MassiveSort
