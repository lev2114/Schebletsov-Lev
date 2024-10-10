#include <cmath>
#include <iomanip>
#include <iostream>

#include "a.h"

namespace {
const int kTask1FirstDividend = 5;
const int kTask1Step = 5;

const int kTask2NumberToLeaveCycleNonNegativeA = 8;
const int kTask2NumberToLeaveCycleNegativeA = 9;

const double eps = 1e-8;
const int kTask3NumberToLeaveCycle = 1;

const int kTask3YLength = 11;
const int kTask3SXLength = 14;
const int kTask3XLength = 3;
const int kTask3NLength = 3;

const int kTask3XPrecicion = 1;
const int kTask3YPrecicion = 6;
const int kTask3SXPrecicion = 6;
const int kTask3NPrecicion = 1;

const int kTask4FirstLimitForIntermediateCalc = 3;
const int kTask4SecondLimitForIntermediateCalc = 5;
const int kTask4ThirdLimitForIntermediateCalc = 10;
}  // namespace

void Task1(int n, int m) {
    if (m < n && n > 0 && m > 0) {
        int sum = 0;

        for (int i = kTask1FirstDividend; i <= n; i += kTask1Step) {
            if (i % m != 0) {
                sum += i;
            }
        }

        std::cout << sum << std::endl;

    } else {
        std::cout << "Введены некорректные данные!\n";
        return;
    }
}

void Task2(double a) {
    double product = 1;
    if (a >= 0) {
        for (int i = 2; i <= kTask2NumberToLeaveCycleNonNegativeA; i += 2) {
            product *= i * i;
        }
        product -= a;
    } else {
        for (int i = 3; i <= kTask2NumberToLeaveCycleNegativeA; i += 3) {
            product *= (i - 2);
        }
    }
    std::cout << std::fixed << std::setprecision(3) << product << std::endl;
}

void Task3(double h) {
    std::cout << std::setw(kTask3XLength) << "x" << std::setw(kTask3YLength) << "y" << std::setw(kTask3SXLength) << "S(x)" << std::setw(kTask3NLength)
              << "N" << '\n';

    for (double x = 0; x <= kTask3NumberToLeaveCycle; x += h) {
        double y{};
        y = (1 - x * x / 2) * cos(x) - x / 2 * sin(x);

        std::cout << std::setw(kTask3XLength) << std::fixed << std::setprecision(kTask3XPrecicion) << x;
        std::cout << std::setw(kTask3YLength) << std::fixed << std::setprecision(kTask3YPrecicion) << y;

        int N = 1;
        double sumOfSeries = 1.0;
        double nextMemberOfSeries = -1 * (3 * x * x / 2);

        while (std::fabs(nextMemberOfSeries) >= eps) {
            sumOfSeries += nextMemberOfSeries;
            nextMemberOfSeries *= -1 * (x * x * (2 * (N + 1) * (N + 1) + 1)) / ((2 * N * N + 1) * (2 * N + 1) * (2 * N + 2));
            N += 1;
        }

        std::cout << std::setw(kTask3SXLength) << sumOfSeries;
        std::cout << std::setw(kTask3NLength) << N - 1 << '\n';
    }
}

void PrintIntermediateCalculations(int n, int steps, int numberOfDecimalPlaces) {
    double intermediateCalculationsLast = 0.0;
    double intermediateCalculationsCurrent = 0.0;

    for (int i = steps; i > -1; --i) {
        intermediateCalculationsCurrent = sqrt(2 * (n - i) + intermediateCalculationsLast);
        intermediateCalculationsLast = intermediateCalculationsCurrent;
    }

    std::cout << std::fixed << std::setprecision(numberOfDecimalPlaces) << "Первые " << steps + 1 << ": " << intermediateCalculationsCurrent << std::endl;
}

void Task4(int n, int numberOfDecimalPlaces) {
    double y = 0.0;

    for (int i = 1; i <= n; ++i) {
        y = sqrt(2 * i + y);
      
    }

    std::cout << std::fixed << std::setprecision(numberOfDecimalPlaces) << y << std::endl;

    std::cout << "Промежуточные вычисления:" << std::endl;

    if (n >= kTask4FirstLimitForIntermediateCalc) {
        PrintIntermediateCalculations(n, (kTask4FirstLimitForIntermediateCalc - 1), numberOfDecimalPlaces);
    }

    if (n >= kTask4SecondLimitForIntermediateCalc) {
        PrintIntermediateCalculations(n, (kTask4SecondLimitForIntermediateCalc - 1), numberOfDecimalPlaces);
    }

    if (n >= kTask4ThirdLimitForIntermediateCalc) {
        PrintIntermediateCalculations(n, (kTask4ThirdLimitForIntermediateCalc - 1), numberOfDecimalPlaces);
    }
}
