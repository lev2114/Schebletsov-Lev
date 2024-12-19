#include "MatrixManip.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const int kX = 1;
const int kStepFactorial = 1;
const int kDynamicMatrixsElementsCoefficient = -1;
const int kNumbersLines = 10;
const int kNumberColumn = 10;
}  // namespace

namespace {
long int CalculateFactorial(int number) {
    long int factorial = 1;

    while (number > 1) {
        factorial *= number;
        number -= kStepFactorial;
    }

    return factorial;
}
int ReadFromStdinPrecize() {
    int precize{};

    std::cout << "Введите количество знаков после запятой" << std::endl;
    std::cin >> precize;

    return precize;
}

bool ReadFromStdinPrintElementsWithPrecision(int& precize) {
    char printElementsWithPrecision{};

    std::cout << "Введите [p], чтобы вывести аргументы матрицы со знаками после запятой" << std::endl;
    std::cin >> printElementsWithPrecision;
    if (printElementsWithPrecision == 'p') {
        precize = ReadFromStdinPrecize();
        return false;
    }
    return true;
}

void ReadNAndMFromStdin(int& n, int& m) {
    std::cout << "Введите 2 натуральных числа N и M" << std::endl;
    std::cin >> n >> m;
}
}  // namespace

namespace MatrixManip {
void StartProgram() {
    StartDynamicMatrix();

    StartStaticMatrix();
}
void StartDynamicMatrix() {
    int n{};
    int m{};
    int precize{};
    bool printElementsWithPrecision = ReadFromStdinPrintElementsWithPrecision(precize);
    ReadNAndMFromStdin(n, m);

    double** DynamicMatrix = new double*[n];
    for (int i{}; i < n; ++i) {
        double* Column = new double[m];
        DynamicMatrix[i] = Column;
    }

    FillDynamicMatrixNumeric(DynamicMatrix, n, m);
    PrintMatrix(DynamicMatrix, n, m, printElementsWithPrecision, precize, MatrixTypes::Dynamic);

    for (int i{}; i < n; ++i) {
        delete[] DynamicMatrix[i];
    }
    delete[] DynamicMatrix;
}

void StartStaticMatrix() {
    double* StaticMatrix[kNumbersLines];

    double FirstLine[kNumberColumn];
    StaticMatrix[0] = FirstLine;
    double SecondLine[kNumberColumn];
    StaticMatrix[1] = SecondLine;
    double ThirdLine[kNumberColumn];
    StaticMatrix[2] = ThirdLine;
    double FourthLine[kNumberColumn];
    StaticMatrix[3] = FourthLine;
    double FifthLine[kNumberColumn];
    StaticMatrix[4] = FifthLine;
    double SixthLine[kNumberColumn];
    StaticMatrix[5] = SixthLine;
    double SeventhLine[kNumberColumn];
    StaticMatrix[6] = SeventhLine;
    double EightLine[kNumberColumn];
    StaticMatrix[7] = EightLine;
    double NinthLine[kNumberColumn];
    StaticMatrix[8] = NinthLine;
    double TenthLine[kNumberColumn];
    StaticMatrix[9] = TenthLine;

    FillStaticMatrixNumeric(StaticMatrix);
    PrintMatrix(StaticMatrix, kNumbersLines, kNumberColumn, false, 0, MatrixTypes::Static);
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

void FillStaticMatrixNumeric(double** StaticMatrix) {
    for (int i{}; i < kNumbersLines; ++i) {
        for (int j{}; j < kNumberColumn; ++j) {
            StaticMatrix[i][j] = i * 10 + j;
        }
    }
}

void PrintMatrix(double** Matrix, int linesNumber, int columnsNumber, bool sciencetific, int precision, MatrixTypes matrixType) {
    switch (matrixType) {
        case MatrixTypes::Dynamic:
            std::cout << "Динамическая матрица" << std::endl;
            break;
        case MatrixTypes::Static:
            std::cout << "Статическая матрица" << std::endl;
            break;
        default:
            std::cout << "Такой матрицы не существует" << std::endl;
    }


    int columnCounter = 0;

    for (int k{}; k < columnsNumber / 5 + 1; ++k) {
        if (columnCounter > columnsNumber) {
            break;
        }

        for (int i{}; i < linesNumber; ++i) {
            for (int j = k * 5; j < 5 * (k + 1); ++j) {
                if (j >= columnsNumber) {
                    break;
                }

                if (sciencetific) {
                std::cout <<std::fixed << std::setw(13) << std::scientific << Matrix[i][j] << '\t';
                } else {
                    std::cout <<std::fixed << std::setw(precision + 3) << std::setprecision(precision) << Matrix[i][j] << '\t';
                }
            }
        std::cout << '\n';
        columnCounter += 1;
        }

        std::cout << '\n';
    }


}

}  // namespace MatrixManip
