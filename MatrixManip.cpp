#include "MatrixManip.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const int kX = 1;
const int kDynamicMatrixsElementsCoefficient = -1;
const int kLinesNumber = 10;
const int kNumberColumns = 10;
}  // namespace

namespace {
long long unsigned int CalculateFactorial(int number) {
    long long unsigned int factorial = 1;

    for (int i = 2; i <= number; ++i) {
        factorial *= i;
    }

    return factorial;
}

int ReadMethod(){
    std::cout << "Выберите вид матрицы: \n1) Статическая\n2) Динамическая" << std::endl;
    int Method{};
    std::cin >> Method;
    return Method;
}

int ReadPrecicion() {
    int precicion{};

    std::cout << "Введите количество знаков после запятой" << std::endl;
    std::cin >> precicion;

    return precicion;
}

char FloatOrScientific() {
    char FloatOrScientific{};

    std::cout << "Вы хотите вывести элементы в научном (s) или десятичном (f) виде?" << std::endl;
    std::cin >> FloatOrScientific;
    if (FloatOrScientific != 's' && FloatOrScientific != 'f') {
        return 'e';
    }
    return FloatOrScientific;
}

void ReadNAndM(int& n, int& m) {
    std::cout << "Введите 2 натуральных числа N и M" << std::endl;
    std::cin >> n >> m;
}
}  // namespace

namespace MatrixManip {
void StartProgram() {
    switch (static_cast<MatrixTypes>(ReadMethod())) {
        case MatrixTypes::Dynamic:
            StartDynamicMatrix();
            break;
        case MatrixTypes::Static:
            StartStaticMatrix();
            break;
        default:
            std::cout << "Такой матрицы не существует" << std::endl;
            return;
    }
}

void StartDynamicMatrix() {
    int n{};
    int m{};
    int precicion = ReadPrecicion();
    char FloatOrScientificChoice = FloatOrScientific();

    if (FloatOrScientificChoice == 'e') {
        std::cout << "Введены неверные данные!";
        return;
    }
    ReadNAndM(n, m);

    double** DynamicMatrix = new double*[n];
    for (int i{}; i < n; ++i) {
        DynamicMatrix[i] = new double[m];
    }

    FillDynamicMatrixNumeric(DynamicMatrix, n, m);
    PrintMatrix(nullptr, DynamicMatrix, n, m, static_cast<OutputType>(FloatOrScientificChoice), precicion, MatrixTypes::Dynamic);

    for (int i{}; i < n; ++i) {
        delete[] DynamicMatrix[i];
    }
    delete[] DynamicMatrix;
}

void StartStaticMatrix() {
    double StaticMatrix[kLinesNumber][kNumberColumns];

    FillStaticMatrixNumeric(StaticMatrix);
    PrintMatrix(StaticMatrix, nullptr, kLinesNumber, kNumberColumns, OutputType::Float, 0, MatrixTypes::Static);
}

void FillDynamicMatrixNumeric(double** DynamicMatrix, int n, int m) {
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < m + 1; ++j) {
            if (i == j) {
                DynamicMatrix[i - 1][j - 1] = 1.;
            } else if (i > j) {
                DynamicMatrix[i - 1][j - 1] = (std::pow(kX, i)) / (std::pow(CalculateFactorial(j), i));
            } else if (i < j) {
                DynamicMatrix[i - 1][j - 1] = (std::pow(kDynamicMatrixsElementsCoefficient * kX, i)) / (std::pow(CalculateFactorial(j), i));
            }
        }
    }
}

void FillStaticMatrixNumeric(double StaticMatrix[kLinesNumber][kNumberColumns]) {
    for (int i{}; i < kLinesNumber; ++i) {
        for (int j{}; j < kNumberColumns; ++j) {
            StaticMatrix[i][j] = i * 10 + j;
        }
    }
}

void PrintMatrix(double StaticMatrix[kLinesNumber][kNumberColumns], double** DynamicMatrix, int linesNumber, int columnsNumber,
                 OutputType FloatOrScientificChoice, int precision, MatrixTypes matrixType) {

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

    int columnCounter = 0;

    for (int k{}; k < columnsNumber / 5 + 1; ++k) {
        if (columnCounter >= columnsNumber) {
            break;
        }

        for (int i{}; i < linesNumber; ++i) {
            for (int j = k * 5; j < 5 * (k + 1); ++j) {
                if (j >= columnsNumber) {
                    break;
                }

                double value = (matrixType == MatrixTypes::Static)
                               ? StaticMatrix[i][j]
                               : DynamicMatrix[i][j];

                if (FloatOrScientificChoice == OutputType::Scientific) {
                    std::cout << std::fixed << std::setw(13) << std::scientific << value << '\t';
                } else {
                    std::cout << std::fixed << std::setw(precision + 3) << std::setprecision(precision) << value << '\t';
                }
            }
            std::cout << '\n';
            ++columnCounter;
        }

        std::cout << '\n';
    }
}


}  // namespace MatrixManip
