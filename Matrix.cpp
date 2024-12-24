#include "Matrix.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const int kStaticExperimentsShift = 20;

const int kX = 1;
const int kDynamicMatrixsElementsCoefficient = -1;

const int kStaticMatrixLineCoefficient = 10;
const int kMaximumNumbersInLine = 5;
const int kScientificWidth = 13;

long long unsigned int CalculateFactorial(int number) {
    long long unsigned int factorial = 1;

    for (int i = 2; i <= number; ++i) {
        factorial *= i;
    }

    return factorial;
}

void StartAdditionalTask(double** matrix) {
    std::cout << matrix << "  " << matrix[0] << "  " << matrix[2] << std::endl;
    std::cout << matrix[0][0] << "  " << **matrix << "  " << *matrix[0] << std::endl;
    std::cout << *(*(matrix + 1)) << "  " << *matrix[1] << std::endl;
    std::cout << *(matrix[0] + 1) << "  " << *(*matrix + 1) << std::endl;
    std::cout << matrix[0][kStaticExperimentsShift] << "  " << *(matrix[0] + kStaticExperimentsShift) << "  " << *matrix[2] << std::endl;
}

int ReadMethod() {
    std::cout << "Выберите вид матрицы: \n1) Статическая\n2) Динамическая" << std::endl;
    int method{};
    std::cin >> method;
    return method;
}

int ReadPrecicion() {
    int precicion{};

    std::cout << "Введите количество знаков после запятой" << std::endl;
    std::cin >> precicion;

    return precicion;
}

char FloatOrScientific() {
    char floatOrScientific{};

    std::cout << "Вы хотите вывести элементы в научном (s) или десятичном (f) виде?" << std::endl;
    std::cin >> floatOrScientific;
    if (floatOrScientific != 's' && floatOrScientific != 'f') {
        return 'e';
    }
    return floatOrScientific;
}

void ReadNAndM(int& n, int& m) {
    std::cout << "Введите 2 натуральных числа N и M" << std::endl;
    std::cin >> n >> m;
}
}  // namespace

namespace Matrix {

double** GetPointersFromStaticMatrix(double staticMatrix[kLinesNumber][kColumnsNumber]) {
    double** matrixPointer = new double*[kColumnsNumber];
    for (int i = 0; i < kColumnsNumber; ++i) {
        matrixPointer[i] = new double[kLinesNumber];
    }
    return matrixPointer;
}

double** AllocateMemory(int n, int m) {
    double** matrixPointer = new double*[n];
    for (int i = 0; i < n; ++i) {
        matrixPointer[i] = new double[m];
    }
    return matrixPointer;
}

void FreeMemory(double** matrix, int n) {
    for (int i{}; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void StartProgram() {
    char continueExecution = 'y';
    while (continueExecution == 'y') {
        switch (static_cast<MatrixTypes>(ReadMethod())) {
            case MatrixTypes::Dynamic:
                ProcessDynamicMatrix();
                break;
            case MatrixTypes::Static:
                ProcessStaticMatrix();
                break;
            default:
                std::cout << "Такой матрицы не существует" << std::endl;
                return;
        }
        std::cout << "Вы хотите продолжить? (y/n)" << std::endl;
        std::cin >> continueExecution;
    }
}

void ProcessDynamicMatrix() {
    int n{};
    int m{};
    char floatOrScientificChoice = FloatOrScientific();
    int precicion = ReadPrecicion();

    if (floatOrScientificChoice == 'e') {
        std::cout << "Введены неверные данные!";
        return;
    }
    ReadNAndM(n, m);

    double** dynamicMatrix = AllocateMemory(n, m);

    FillDynamicMatrix(dynamicMatrix, n, m);
    PrintMatrix(dynamicMatrix, n, m, static_cast<OutputType>(floatOrScientificChoice), precicion, MatrixTypes::Dynamic);

    FreeMemory(dynamicMatrix, n);
}

void ProcessStaticMatrix() {
    double staticMatrix[kLinesNumber][kColumnsNumber];
    double** staticPointer = GetPointersFromStaticMatrix(staticMatrix);

    FillStaticMatrix(staticPointer);
    PrintMatrix(staticPointer, kLinesNumber, kColumnsNumber, OutputType::Float, 0, MatrixTypes::Static);
    StartAdditionalTask(staticPointer);
    FreeMemory(staticPointer, kLinesNumber);
}

void FillDynamicMatrix(double** dynamicMatrix, int n, int m) {
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < m + 1; ++j) {
            if (i == j) {
                dynamicMatrix[i - 1][j - 1] = 1.;
            } else if (i > j) {
                dynamicMatrix[i - 1][j - 1] = (std::pow(kDynamicMatrixsElementsCoefficient * kX, i)) / (std::pow(CalculateFactorial(j), i));
            } else if (i < j) {
                dynamicMatrix[i - 1][j - 1] = (std::pow(kX, i)) / (std::pow(CalculateFactorial(j), i));
            }
        }
    }
}

void FillStaticMatrix(double**& staticMatrix) {
    for (int i{}; i < kLinesNumber; ++i) {
        for (int j{}; j < kColumnsNumber; ++j) {
            staticMatrix[i][j] = i * kStaticMatrixLineCoefficient + j;
        }
    }
}

void PrintMatrix(double** matrix, int linesNumber, int columnsNumber, OutputType floatOrScientificChoice, int precision, MatrixTypes matrixType) {
    switch (matrixType) {
        case MatrixTypes::Dynamic:
            std::cout << "Динамическая матрица: " << std::endl;
            break;
        case MatrixTypes::Static:
            std::cout << "Статическая матрица: " << std::endl;
            break;
        default:
            std::cout << "Такой матрицы не существует" << std::endl;
            return;
    }

    for (int blockStart = 0; blockStart < columnsNumber; blockStart += kMaximumNumbersInLine) {
        for (int i = 0; i < linesNumber; ++i) {
            for (int j = blockStart; j < blockStart + kMaximumNumbersInLine && j < columnsNumber; ++j) {
                if (floatOrScientificChoice == OutputType::Scientific) {
                    std::cout << std::fixed << std::setw(kScientificWidth) << std::scientific << std::setprecision(precision) << matrix[i][j] << '\t';
                } else {
                    std::cout << std::fixed << std::setw(precision + 3) << std::setprecision(precision) << matrix[i][j] << '\t';
                }
            }
            std::cout << '\n';
        }

        std::cout << '\n';
    }
}

}  // namespace Matrix
