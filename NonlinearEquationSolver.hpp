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

[[nodiscard]] Answer HalfDivisionMethodCount(int cosineCoefficient, double eps, double a, double b);
[[nodiscard]] Answer IterationMethodCount(int cosineCoefficient, double eps);
[[nodiscard]] Answer NewthonMethodCount(int cosineCoefficient, double eps);
}  // namespace NonLinearEquationSolver

#endif // DEFINE NONLINEAREQATIONSOLVER
