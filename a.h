#ifndef A_H
#define A_H
#include <cmath>
#include <iomanip>
#include <iostream>
#endif

void task1(int n, int m) {
    int DivisionCriterion = 5;
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (i % m != 0 && i % DivisionCriterion == 0) {
            sum += i;
        }
    }
    std::cout << sum << std::endl;
}

void task2(int a) {
    int prod = 1;
    if (a >= 0) {
        int Leave = 8;
        for (int i = 2; i <= Leave; i += 2) {
            prod *= i * i;
            prod -= a;
        }
    } else {
        int Leave = 9;
        for (int i = 3; i <= Leave; i += 3) {
            prod *= (i - 2);
        }
    }
    std::cout << prod << std::endl;
}

void task3(double h) {
    std::cout << "| x |     y     |     S(x)     |  N  |\n";
    long double x{};
    long double y{};
    long double eps = 1e-6;
    int N{};
    long double SumOfSeries{};
    long double NextSumOfSeries{};
    for (int i = 0; i <= 5; ++i) {
        x = i * h;
        std::cout << '|' << std::setw(3) << x << '|';
        y = (1 - x * x / 2) * cos(x) - x / 2 * sin(x);
        std::cout << std::setw(11) << y << '|';
        N = 1;
        SumOfSeries = 1.0;
        NextSumOfSeries = -1 * (3 * x * x / 2);
        while (std::fabs(NextSumOfSeries) >= eps) {
            SumOfSeries += NextSumOfSeries;
            NextSumOfSeries *= (-x * x * (2 * N * N + 1)) / ((2 * N + 1) * (2 * N + 2));
            N += 1;
        }
        std::cout << std::setw(14) << SumOfSeries << '|';
        std::cout << std::setw(5) << N - 1 << '|' << '\n';
    }
}

void task4(int n, int NumberOfDecimalPlaces) {
    double LastValue{};
    double CurrentValue{};
    for (int i = 1; i <= n; ++i) {
        CurrentValue = sqrt(2 * i + LastValue);
        LastValue = CurrentValue;
    }
    std::cout << std::fixed << std::setprecision(NumberOfDecimalPlaces) << CurrentValue << std::endl;
    std::cout << "Промежуточные вычисления:" << std::endl;
    double IntermediateCalculationsLast{};
    double IntermediateCalculationsCurrent{};
    if (n >= 3) {
        for (int i = 2; i > -1; --i) {
            IntermediateCalculationsCurrent = sqrt(2 * (n - i) + IntermediateCalculationsLast);
            IntermediateCalculationsLast = IntermediateCalculationsCurrent;
        }
        std::cout << std::fixed << std::setprecision(NumberOfDecimalPlaces) << "Первые 3: " << IntermediateCalculationsCurrent << std::endl;
    } else {
        std::cout << "n<3\n";
    }
    if (n >= 5) {
        IntermediateCalculationsLast = 0.0;
        for (int i = 4; i > -1; --i) {
            IntermediateCalculationsCurrent = sqrt(2 * (n - i) + IntermediateCalculationsLast);
            IntermediateCalculationsLast = IntermediateCalculationsCurrent;
        }
        std::cout << std::fixed << std::setprecision(NumberOfDecimalPlaces) << "Первые 5: " << IntermediateCalculationsCurrent << std::endl;
    } else {
        std::cout << "n<5\n";
    }
    if (n >= 10) {
        IntermediateCalculationsLast = 0.0;
        for (int i = 9; i > -1; --i) {
            IntermediateCalculationsCurrent = sqrt(2 * (n - i) + IntermediateCalculationsLast);
            IntermediateCalculationsLast = IntermediateCalculationsCurrent;
        }
        std::cout << std::fixed << std::setprecision(NumberOfDecimalPlaces) << "Первые 10: " << IntermediateCalculationsCurrent << std::endl;
    } else {
        std::cout << "n<10\n";
    }
}
