#ifndef NONLINEAR_ROOT_SOLVER
#define NONLINEAR_ROOT_SOLVER

namespace NonLinearRootSolver{

struct Solution{
    bool haveWeFoundAnswer;
    double solution;
    int N;
};


double EpsInput();
int CoefficientBeforeCosineInput();
int runApplication();
int showMenu();
void halfDivisionMethodapp();
[[nodiscard]] Solution halfDivisionMethodcount();
void newthonMethodapp();
[[nodiscard]] Solution newthonMethodcount();
void iterationMethodapp();
[[nodiscard]] Solution iterationMethodcount(int coefficientBeforeCosine, double eps);



enum class MenuOption : int{
    IterationMethod = 1,
    NewthonMethod,
    HalfDivisionMethod,
};


}


#endif
