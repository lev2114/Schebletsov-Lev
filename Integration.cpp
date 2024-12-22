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

const double kStartEpsilon = 0.1;
const int kHowManyEpsilon = 6;
const int kDecimalBase = 10;

const double kLinearIntegralDenominator = 2.0;
const double kInverseTangenciallDenominator = 2.0;
const double kTrapezoidalCoefficient = 2.0;

const int kMaxIterations = 1e6;

const int kAproximateXDegree = 5;
const double kCoefficientAproximateX = 5.;

const char kSideSymbol = '|';
const char kHorizontalSymbol = '-';
const char kConnectorSymbol = '+';

const int kColumnCount = 4;
const int kColumn0Width = 12;
const int kColumn1Width = 18;
const int kColumn2Width = 18;
const int kColumn3Width = 10;

const int kPrecisionHigh = 10;
const int kPrecisionLow = 6;

}  // namespace

namespace {
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

void TableOut(Integration::IntegrationResult array[kFunctionsAmount], double epsilon) {
    std::cout << "Точность: " << epsilon << std::endl;

    const int m = kColumnCount;
    int wn[m] = {kColumn0Width, kColumn1Width, kColumn2Width, kColumn3Width};

    const char* title[m] = {"Function", "Integral", "IntSum", "N "};

    int size[m];
    for (int i = 0; i < m; i++) {
        size[i] = (int)std::strlen(title[i]);
    }

    std::cout << kConnectorSymbol << std::setfill(kHorizontalSymbol);
    for (int j = 0; j < m - 1; j++) {
        std::cout << std::setw(wn[j]) << kConnectorSymbol;
    }
    std::cout << std::setw(wn[m - 1]) << kConnectorSymbol << std::endl;
    std::cout << kSideSymbol;
    for (int j = 0; j < m; j++) {
        std::cout << std::setw((wn[j] - size[j]) / 2) << std::setfill(' ') << ' ' << title[j] << std::setw((wn[j] - size[j]) / 2) << kSideSymbol;
    }
    std::cout << std::endl;

    for (int i = 0; i < 4; i++) {
        std::cout << kConnectorSymbol << std::fixed;
        for (int j = 0; j < m - 1; j++) {
            std::cout << std::setfill(kHorizontalSymbol) << std::setw(wn[j]) << kConnectorSymbol;
        }
        std::cout << std::setw(wn[m - 1]) << kConnectorSymbol << std::setfill(' ') << std::endl;

        std::cout << kSideSymbol << std::setw((int)(wn[0] - std::strlen(array[i].name)) / 2) << ' ' << array[i].name
                  << std::setw((int)(wn[0] - std::strlen(array[i].name)) / 2) << kSideSymbol;
        std::cout << std::setw(wn[1] - 1) << std::setprecision(kPrecisionHigh) << array[i].preciseIntegral << kSideSymbol << std::setw(wn[2] - 1)
                  << array[i].area << std::setprecision(kPrecisionLow) << kSideSymbol << std::setw(wn[3] - 1) << array[i].partitionsNumber
                  << kSideSymbol << std::endl;
    }

    std::cout << kConnectorSymbol << std::setfill(kHorizontalSymbol);
    for (int j = 0; j < m - 1; j++) {
        std::cout << std::setw(wn[j]) << kConnectorSymbol;
    }
    std::cout << std::setw(wn[m - 1]) << kConnectorSymbol << std::setfill(' ') << std::endl;
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
            StartRectangleMethod();
            break;
        case MethodsIntegration::Trapezoid:
            StartTrapezoidMethod();
            break;
        default:
            PrintError();
            break;
    }
}

void StartRectangleMethod() {
    double epsilon{kStartEpsilon};
    double a = ReadAFromStdin();
    double b = ReadBFromStdin();
    IntegrationResult IntegrationResults[kResultsNumber];

    IntegrationResults[0].name = "y=x ";
    IntegrationResults[1].name = "y=cos(22x)";
    IntegrationResults[2].name = "y=x^4 ";
    IntegrationResults[3].name = "y=atan(x) ";

    IntegrationResults[0].preciseIntegral = (b * b - a * a) / kLinearIntegralDenominator;
    IntegrationResults[1].preciseIntegral = (std::cos(a * kXCoefficient) - std::cos(b * kXCoefficient)) / kXCoefficient;
    IntegrationResults[2].preciseIntegral = (std::pow(b, kAproximateXDegree) - std::pow(a, kAproximateXDegree)) / kCoefficientAproximateX;
    IntegrationResults[3].preciseIntegral =
        b * std::atan(b) - a * std::atan(a) - (std::log(b * b + 1) - std::log(a * a + 1)) / kInverseTangenciallDenominator;

    if (a > b) {
        PrintError();
        return;
    }

    double (*functions[])(double) = {CalculateLinearFunction, CalculateSinusoidalFunction, CalculatePowerFunction,
                                     CalculateInverseTangencialFunction};

    for (size_t j = 0; j < kHowManyEpsilon; epsilon /= kDecimalBase, ++j) {
        for (size_t i = 0; i < kResultsNumber; ++i) {
            RectangleMethod(*functions[i], a, b, epsilon, IntegrationResults[i]);
        }

        TableOut(IntegrationResults, epsilon);
    }
}

void RectangleMethod(double (*Function)(double), double a, double b, double epsilon, IntegrationResult& IntegrationResults) {
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

void StartTrapezoidMethod() {
    double epsilon{kStartEpsilon};
    double a = ReadAFromStdin();
    double b = ReadBFromStdin();
    IntegrationResult IntegrationResults[kResultsNumber];

    double (*functions[])(double) = {CalculateLinearFunction, CalculateSinusoidalFunction, CalculatePowerFunction,
                                     CalculateInverseTangencialFunction};
    if (a > b) {
        PrintError();
        return;
    }

    IntegrationResults[0].name = "y=x ";
    IntegrationResults[1].name = "y=cos(22x)";
    IntegrationResults[2].name = "y=x^4 ";
    IntegrationResults[3].name = "y=atan(x) ";

    IntegrationResults[0].preciseIntegral = (b * b - a * a) / kLinearIntegralDenominator;
    IntegrationResults[1].preciseIntegral = (std::cos(a * kXCoefficient) - std::cos(b * kXCoefficient)) / kXCoefficient;
    IntegrationResults[2].preciseIntegral = (std::pow(b, kAproximateXDegree) - std::pow(a, kAproximateXDegree)) / kCoefficientAproximateX;
    IntegrationResults[3].preciseIntegral =
        b * std::atan(b) - a * std::atan(a) - (std::log(b * b + 1) - std::log(a * a + 1)) / kInverseTangenciallDenominator;

    for (size_t j = 0; j < kHowManyEpsilon; epsilon /= kDecimalBase, ++j) {
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

    IntegrationResults.area = f2 * dx / kTrapezoidalCoefficient;
    IntegrationResults.partitionsNumber = n;
}

}  // namespace Integration
