#ifndef NONLINEAR_ROOT_SOLVER
#define NONLINEAR_ROOT_SOLVER

namespace NonLinearRootSolver{

double PrecicionInput();
int CoefficientBeforeCosineInput();
int runApplication();
int showMenu();
void halfDivisionMethod();
void newthonMethod();
double iterationMethod(int coefficientBeforeCosine, double precicion);


enum class MenuOption : int{
    IterationMethod = 1,
    NewthonMethod,
    HalfDivisionMethod,
};

}


#endif
