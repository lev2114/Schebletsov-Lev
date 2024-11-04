#include "NonlinearEquationSolver.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const double kXDefine = 0.;
const int kMaxIterations = 10'000;

int Answer{};

const int kDerivativeX = 1;
}  // namespace

namespace {
[[nodiscard]] int ReadCosineCoefficient() {
    std::cout << "Введите коэффициент перед косинусом\n";
    int cosineCoefficient{};
    std::cin >> cosineCoefficient;
    return cosineCoefficient;
}

[[nodiscard]] int ReadMethod() {
    int menuOption{};
    std::cout << "Введите номер задания:\n1) Метод итераций\n2) Метод Ньютона\n3) Метод половинного деления\n";
    std::cin >> menuOption;
    return menuOption;
}

[[nodiscard]] double ReadPrecicion() {
    std::cout << "Введите погрешность(в формате 1e-k, где k - целое число)\n";
    double precicion{};
    std::cin >> precicion;
    return precicion;
}

[[nodiscard]] bool IsSignDifferent(double a, double b) {
    return (a > 0 && b < 0) || (a < 0 && b > 0);
}

[[nodiscard]] double EquationSolve(double a, int cosineCoefficient) {
    return a - cosineCoefficient * std::cos(a);
}

[[nodiscard]] double NextIteration(double xPrev, int cosineCoefficient) {
    return cosineCoefficient * std::cos(xPrev);
}

void PrintAnswer(double x, int iterations, double precicion) {
    std::cout << "Ответ: " << std::setw(static_cast<int>(std::log10(1 / precicion))) << x << "\n" << "Количество итераций: " << iterations << "\n";
}

}  // namespace

namespace NonLinearEquationSolver {
Answer IterationMethodCount(int cosineCoefficient, double eps) {
    int iterations{};
    double xPrev = kXDefine + 1;
    double xCurr = kXDefine;

    while ((std::abs(xCurr - xPrev) > eps) && (iterations <= kMaxIterations)) {
        xPrev = xCurr;
        xCurr = NextIteration(xPrev, cosineCoefficient);
        ++iterations;
    }

    if (iterations > kMaxIterations) {
        return {false};
    }

    return {.x = xCurr, .iterations = iterations};
}

void IterationMethodApp() {
    int cosineCoefficient = ReadCosineCoefficient();
    double precicion = ReadPrecicion();

    Answer answer = IterationMethodCount(cosineCoefficient, precicion);

    if (!answer.xValid) {
        std::cerr << "Решение с данными параметрами данным методом не сходится или сходится слишком медленно! Пожалуйста, попробуйте другой метод!\n";
    } else {
        PrintAnswer(answer.x, answer.iterations, precicion);
    }
}

Answer NewthonMethodCount(int cosineCoefficient, double eps) {
    int iterations{};
    double xPrev = kXDefine + 1;
    double xCurr = kXDefine;

    while (std::abs(xCurr - xPrev) > eps) {
        xPrev = xCurr;
        xCurr -= (EquationSolve(xPrev, cosineCoefficient)) / (kDerivativeX + std::sin(xPrev));
        ++iterations;
        if (iterations > kMaxIterations) {
            return {false};
        }
    }

    return {.x = xCurr, .iterations = iterations};
}

void NewthonMethodApp() {
    int cosineCoefficient = ReadCosineCoefficient();
    double precicion = ReadPrecicion();

    Answer answer = NewthonMethodCount(cosineCoefficient, precicion);

    if (!answer.xValid) {
        std::cerr << "Решение с данными параметрами данным методом не сходится или сходится слишком медленно! Пожалуйста, попробуйте другой метод!\n";

    } else {
        PrintAnswer(answer.x, answer.iterations, precicion);
    }
}

Answer HalfDivisionMethodCount(int cosineCoefficient, double eps, double lhs, double rhs) {
    int iterations{};
    double x{};
    double fx{};

    double fa = EquationSolve(lhs, cosineCoefficient);
    double fb = EquationSolve(rhs, cosineCoefficient);

    if (IsSignDifferent(fa, fb)) {
        while (std::abs(rhs - lhs) > eps) {
            x = (lhs + rhs) / 2;
            fx = EquationSolve(x, cosineCoefficient);

            if (IsSignDifferent(fa, fx)) {
                rhs = x;
            } else {
                lhs = x;
                fa = fx;
            }
            iterations += 1;
        }

        return {.x = x, .iterations = iterations};

    } else {
        return {false};
    }
}

void HalfDivisionMethodApp() {
    int cosineCoefficient = ReadCosineCoefficient();
    double precicion = ReadPrecicion();

    std::cout << "Введите числа a и b (a<b) через пробел\n";
    double lhs{};
    double rhs{};
    std::cin >> lhs >> rhs;
    if (!(lhs < rhs)) {
        std::cerr << "a не меньше b!";
        return;
    }
    Answer answer = HalfDivisionMethodCount(cosineCoefficient, precicion, lhs, rhs);
    if (answer.xValid) {
        PrintAnswer(answer.x, answer.iterations, precicion);
    } else {
        std::cout << "Значение функции в точках a и b не противоположно по знаку!\n";
    }
}

void ExecuteMethod() {
    switch (static_cast<Method>(ReadMethod())) {
        case Method::Iteration:
            IterationMethodApp();
            break;

        case Method::Newthon:
            NewthonMethodApp();
            break;

        case Method::HalfDivision:
            HalfDivisionMethodApp();
            break;

        default:
            std::cout << "Введены неверные данные!\n";
            break;
    }
}

void StartLoop() {
    char continueExecution = 'y';
    while (continueExecution == 'y') {
        ExecuteMethod();

        std::cout << "Вы хотите продолжить? (y/n)\n";
        std::cin >> continueExecution;
    }
}
}  // namespace NonLinearEquationSolver
