#ifndef INTEGRATION
#define INTEGRATION
#include <cmath>
#include <iostream>
#include <cstring>
#include <iomanip>

namespace Integration {
enum class MethodsIntegration {
    Rectangle = 1,
    Trapezoid,
};

struct IntegrationResult {
    char* name;
    double preciseIntegral = 0.;
    double area = 0.;
    int partitionsNumber = 0;
};

void StartProgram();

void SelectMethod();

void LaunchRectangleMethod();

void IntegrateFunctionRectangleMethod(double (*function)(double), double left, double rigth, double epsilon, IntegrationResult array[4], size_t i);

void LaunchTrapezoidMethod();

void IntegrateFunctionTrapezoidMethod(double (*function)(double), double left, double rigth, double epsilon, IntegrationResult array[4], size_t i);

void TableOut(IntegrationResult array[4]);
}  // namespace Integration
#endif
