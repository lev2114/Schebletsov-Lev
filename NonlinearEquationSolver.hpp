#ifndef NONLINEAREQUATIONSOLVER
#define NONLINEAREQUATIONSOLVER

namespace NonLinearEquationSolver {
enum class Method : int {
    Iteration = 1,
    Newthon,
    HalfDivision,
};

struct Answer {
    bool xValid = true;
    double x = 0;
    int iterations = 0;
};

void StartLoop();
void ExecuteMethod();

void HalfDivisionMethodApp();
void NewthonMethodApp();
void IterationMethodApp();

[[nodiscard]] Answer CalculateHalfDivisionMethod(int cosineCoefficient, double eps, double a, double b);
[[nodiscard]] Answer CalculateIterationMethod(int cosineCoefficient, double eps);
[[nodiscard]] Answer CalculateNewthonMethod(int cosineCoefficient, double eps);
}  // namespace NonLinearEquationSolver

#endif  // DEFINE NONLINEAREQATIONSOLVER
