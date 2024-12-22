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
    const char* name = nullptr;
    double preciseIntegral = 0.;
    double area = 0.;
    int partitionsNumber = 0;
};

void StartProgram();

void SelectMethod();

void StartRectangleMethod();

void RectangleMethod(double (*Function)(double), double a, double b, double epsilon, IntegrationResult& IntegrationResults);

void StartTrapezoidMethod();

void TrapezoidMethod(double (*Function)(double), double a, double b, double epsilon, IntegrationResult& IntegrationResults);
}  // namespace Integration
#endif
