#include "Integration.hpp"

#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>

namespace {
const int kFunctionsAmount = 4;
const int kXDegree = 4;
const double kXCoefficient = 22;
const int kResultsNumber = 4;
const int kHowManyEpsilon = 6;
const int kMaxIterations = 1e6;
const int kAproximateXDegree = 5;
const double kCoefficientAproximateX = 5.;
}  // namespace

namespace {
[[nodiscard]] bool IsRightBiggerLeft(double a, double b) {
    return b > a;
}

[[nodiscard]] double CalculateLinearFunction(double x) {
    return x;
}

[[nodiscard]] double CalculateSinusoidalFunction(double x) {
    return std::sin(kXCoefficient * x);
}

[[nodiscard]] double CalculatePowerFunction(double x) {
    return std::pow(x, kXDegree);
}

[[nodiscard]] double CalculateInverseTangencialFunction(double x) {
    return std::atan(x);
}

[[nodiscard]] double ReadAFromStdin() {
    double a{};

    std::cout << "Введите значение a" << std::endl;
    std::cin >> a;

    return a;
}

[[nodiscard]] double ReadBFromStdin() {
    double b{};

    std::cout << "Введите значение b" << std::endl;
    std::cin >> b;

    return b;
}

[[nodiscard]] char ReadContinueExecutionFromStdin() {
    char continueExecution{};

    std::cout << "Вы хотите продолжить? (y/n)" << std::endl;
    std::cin >> continueExecution;

    return continueExecution;
}

[[nodiscard]] int ReadMethodFromStdin() {
    int method{};

    std::cout << "Введите номер метода, которым хотите проинтегрировать\n" << "1. Метод прямоугольников\n" << "2. Метод трапеций" << std::endl;
    std::cin >> method;

    return method;
}

void PrintError() {
    std::cerr << "Введены недопустимые данные" << std::endl;
}

}  // namespace

namespace Integration {
void StartProgram() {
    char continueExecution = 'y';

    while (continueExecution == 'y') {
        SelectMethod();

        continueExecution = ReadContinueExecutionFromStdin();
    }
}

void SelectMethod() {
    int method = ReadMethodFromStdin();

    switch (static_cast<MethodsIntegration>(method)) {
        case MethodsIntegration::Rectangle:
            LaunchRectangleMethod();
            break;
        case MethodsIntegration::Trapezoid:
            LaunchTrapezoidMethod();
            break;
        default:
            PrintError();
            break;
    }
}

void LaunchRectangleMethod() {
    double epsilon{0.1};
    double a = ReadAFromStdin();
    double b = ReadBFromStdin();
    IntegrationResult IntegrationResults[kResultsNumber];

    IntegrationResults[0].name = (char*)"y=x ";
    IntegrationResults[1].name = (char*)"y=cos(22x)";
    IntegrationResults[2].name = (char*)"y=x^4 ";
    IntegrationResults[3].name = (char*)"y=atan(x) ";

    IntegrationResults[0].preciseIntegral = (b * b - a * a) / 2.;
    IntegrationResults[1].preciseIntegral = (std::cos(a * kXCoefficient) - std::cos(b * kXCoefficient)) / kXCoefficient;
    IntegrationResults[2].preciseIntegral = (std::pow(b, kAproximateXDegree) - std::pow(a, kAproximateXDegree)) / kCoefficientAproximateX;
    IntegrationResults[3].preciseIntegral = b * std::atan(b) - a * std::atan(a) - (std::log(b * b + 1) - std::log(a * a + 1)) / 2.0;

    if (!IsRightBiggerLeft(a, b)) {
        PrintError();
            return;
        }

    double (*functions[])(double) = {CalculateLinearFunction, CalculateSinusoidalFunction, CalculatePowerFunction,
                                     CalculateInverseTangencialFunction};

    for (size_t j = 0; j < kHowManyEpsilon; epsilon/=10 , ++j){

        for (size_t i = 0; i < kResultsNumber; ++i) {
            RectangleMethod(*functions[i], a, b, epsilon, IntegrationResults[i]);
        }

        TableOut(IntegrationResults, epsilon);
    }
}
    

void RectangleMethod(double (*Function)(double), double a, double b, double epsilon,
                                      IntegrationResult& IntegrationResults) {
    double dx = b - a;
    double f1 = 0;
    double f2 = Function(a + dx / 2) * dx;
    int n = 1;

    while ((std::fabs(f1 - f2) > epsilon) && (n < kMaxIterations)) {
        f1 = f2;
        f2 = 0;
        n *= 2;
        dx = (b - a) / n;

        for (int k = 0; k < n; ++k) {
            f2 += Function(a + k * dx + dx / 2);
        }
        f2 *= dx;

    }

    IntegrationResults.area = f2;
    IntegrationResults.partitionsNumber = n;
}



void LaunchTrapezoidMethod() {
    double epsilon{0.1};
    double a = ReadAFromStdin();
    double b = ReadBFromStdin();
    IntegrationResult IntegrationResults[kResultsNumber];

    double (*functions[])(double) = {CalculateLinearFunction, CalculateSinusoidalFunction, CalculatePowerFunction,
                                CalculateInverseTangencialFunction};
    if (!IsRightBiggerLeft(a, b)) {
        PrintError();
        return;
    }

    IntegrationResults[0].name = (char*)"y=x ";
    IntegrationResults[1].name = (char*)"y=cos(22x)";
    IntegrationResults[2].name = (char*)"y=x^4 ";
    IntegrationResults[3].name = (char*)"y=atan(x) ";

    IntegrationResults[0].preciseIntegral = (b * b - a * a) / 2.;
    IntegrationResults[1].preciseIntegral = (std::cos(a * kXCoefficient) - std::cos(b * kXCoefficient)) / kXCoefficient;
    IntegrationResults[2].preciseIntegral = (std::pow(b, kAproximateXDegree) - std::pow(a, kAproximateXDegree)) / kCoefficientAproximateX;
    IntegrationResults[3].preciseIntegral = b * std::atan(b) - a * std::atan(a) - (std::log(b * b + 1) - std::log(a * a + 1)) / 2.0;
    for (size_t j = 0; j < kHowManyEpsilon; epsilon/=10){

        for (size_t i = 0; i < kResultsNumber; ++i) {
            TrapezoidMethod(*functions[i], a, b, epsilon, IntegrationResults[i]);
        }


        TableOut(IntegrationResults, epsilon);
    }
}

void TrapezoidMethod(double (*Function)(double), double a, double b, double epsilon, IntegrationResult& IntegrationResults) {
    double dx = b - a;
    double f1 = (Function(a) + Function(b)) / 2;
    double f2 = ((Function(a) + Function(a + dx / 2)) / 2 + (Function(a + dx / 2) + Function(b)) / 2);
    int n = 1;

    while ((std::fabs(f1 - f2 / 2) / 3 > epsilon) && (n < kMaxIterations)) {
        n *= 2;
        f1 = f2;
        f2 = 0;
        dx = (b - a) / n;
        for (int k = 0; k < n * 2; ++k) {
            f2 += (Function(a + k * dx / 2) + Function(a + (k + 1) * dx / 2)) / 2;
        }
    }

    IntegrationResults.area = f2 * dx / 2.;
    IntegrationResults.partitionsNumber = n;
}

void TableOut(IntegrationResult array[kFunctionsAmount], double epsilon) {
    std::cout << "Точность: " << epsilon << std::endl; 

    const char SIDE_SYBMOL = '|';
    const char HORIZONTAL_SYBMOL = '-';
    const char CONNECTOR_SYBMOL = '+';

    const int m = 4;
    int wn[m] = {12, 18, 18, 10};
    char* title[m] = {(char*)"Function", (char*)"Integral", (char*)"IntSum", (char*)"N "};
    int size[m];
    for (int i = 0; i < m; i++) {
        size[i] = (int)std::strlen(title[i]);
    }

    std::cout << CONNECTOR_SYBMOL << std::setfill(HORIZONTAL_SYBMOL);
    for (int j = 0; j < m - 1; j++) {
        std::cout << std::setw(wn[j]) << CONNECTOR_SYBMOL;
    }
    std::cout << std::setw(wn[m - 1]) << CONNECTOR_SYBMOL << std::endl;
    std::cout << SIDE_SYBMOL;
    for (int j = 0; j < m; j++) {
        std::cout << std::setw((wn[j] - size[j]) / 2) << std::setfill(' ') << ' ' << title[j] << std::setw((wn[j] - size[j]) / 2) << SIDE_SYBMOL;
    }
    std::cout << std::endl;

    for (int i = 0; i < 4; i++) {
        std::cout << CONNECTOR_SYBMOL << std::fixed;
        for (int j = 0; j < m - 1; j++) {
            std::cout << std::setfill(HORIZONTAL_SYBMOL) << std::setw(wn[j]) << CONNECTOR_SYBMOL;
        }
        std::cout << std::setw(wn[m - 1]) << CONNECTOR_SYBMOL << std::setfill(' ') << std::endl;

        std::cout << SIDE_SYBMOL << std::setw((int)(wn[0] - std::strlen(array[i].name)) / 2) << ' ' << array[i].name
                  << std::setw((int)(wn[0] - std::strlen(array[i].name)) / 2) << SIDE_SYBMOL;
        std::cout << std::setw(wn[1] - 1) << std::setprecision(10) << array[i].preciseIntegral << SIDE_SYBMOL << std::setw(wn[2] - 1) << array[i].area
                  << std::setprecision(6) << SIDE_SYBMOL << std::setw(wn[3] - 1) << array[i].partitionsNumber << SIDE_SYBMOL << std::endl;
    }

    std::cout << CONNECTOR_SYBMOL << std::setfill(HORIZONTAL_SYBMOL);
    for (int j = 0; j < m - 1; j++) {
        std::cout << std::setw(wn[j]) << CONNECTOR_SYBMOL;
    }
    std::cout << std::setw(wn[m - 1]) << CONNECTOR_SYBMOL << std::setfill(' ') << std::endl;
}
}  // namespace Integration
