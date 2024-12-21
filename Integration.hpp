#ifndef INTEGRATION
#define INTEGRATION
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>

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

void RectangleMethod(double (*Function)(double), double a, double b, double epsilon, IntegrationResult& IntegrationResults);

void LaunchTrapezoidMethod();

void TrapezoidMethod(double (*Function)(double), double a, double b, double epsilon, IntegrationResult& IntegrationResults);

void TableOut(IntegrationResult array[4], double epsilon);
}  // namespace Integration
#endif
