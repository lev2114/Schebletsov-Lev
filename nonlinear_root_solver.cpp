#include <iostream>
#include <cmath>
#include <iomanip>

#include "nonlinear_root_solver.hpp"
namespace{

double kXFirst = 0;
int kIterationLimit = 10000;

} // namespace


[[nodiscard]] NonLinearRootSolver::Solution NonLinearRootSolver::iterationMethodcount(int coefficientBeforeCosine, double eps){

    int N{};
    double xPrev = kXFirst;
    double xCurr = kXFirst;
    double& x = xCurr;
    NonLinearRootSolver::Solution answer{true,0,0};

    do{
        xPrev = xCurr;
        xCurr = coefficientBeforeCosine * std::cos(xPrev);
        N += 1;
        if  (N > kIterationLimit){
            answer.haveWeFoundAnswer = false;
            return answer;
        }
    } while (std::abs(xCurr - xPrev) > eps);
    answer.solution = x;
    answer.N = N;
    return answer;
}

void NonLinearRootSolver::iterationMethodapp(){

    int coefficientBeforeCosine = NonLinearRootSolver::CoefficientBeforeCosineInput();
    double eps = NonLinearRootSolver::EpsInput();

    NonLinearRootSolver::Solution answer = NonLinearRootSolver::iterationMethodcount(coefficientBeforeCosine, eps);

    if (!answer.haveWeFoundAnswer){
        std::cerr << "Решение с данными параметрами данным методом не сходится или сходится слишком медленно! Пожалуйста, попробуйте другой метод!\n";

    } else{
        std::cout << "Ответ: " << answer.solution << "\n" << "Количество итераций: " << answer.N << "\n";
    }

}


[[nodiscard]] int NonLinearRootSolver::CoefficientBeforeCosineInput(){
    std::cout << "Введите коэффициент перед косинусом\n";
    int coefficientBeforeCosine{};
    std::cin >> coefficientBeforeCosine;
    return coefficientBeforeCosine;
}

[[nodiscard]] double NonLinearRootSolver::EpsInput(){
    std::cout << "Введите погрешность(в формате 1e-k, где k - целое число)\n";
    double precicion{};
    std::cin >> precicion;
    return precicion;
}


[[nodiscard]] int NonLinearRootSolver::showMenu(){
    int menuOption{};
    std::cout << "Введите номер задания:\n1) Метод итераций\n2) Метод Ньютона\n3) Метод половинного деления\n";
    std::cin >> menuOption;
    return menuOption;
}

[[nodiscard]] int NonLinearRootSolver::runApplication(){
    char toLeaveOrNotToLeave = 'n';
    do{

        int menuOption = NonLinearRootSolver::showMenu();
        NonLinearRootSolver::MenuOption option = static_cast<NonLinearRootSolver::MenuOption>(menuOption);

        switch(option) {
            case NonLinearRootSolver::MenuOption::IterationMethod:
                NonLinearRootSolver::iterationMethodapp();
                break;

            case NonLinearRootSolver::MenuOption::HalfDivisionMethod:
                NonLinearRootSolver::halfDivisionMethodapp();
                break;

            case NonLinearRootSolver::MenuOption::NewthonMethod:
                NonLinearRootSolver::newthonMethodapp();
                break;

            default:
                std::cout << "Введены неверные данные!\n";
                return 1;
        }

        std::cout << "Вы хотите продолжить? (y/n)\n";
        std::cin >> toLeaveOrNotToLeave;

        if (toLeaveOrNotToLeave != 'n' && toLeaveOrNotToLeave != 'y'){

            std::cout << "Введены неверные данные!\n";
            return 1;

        }
    } while(toLeaveOrNotToLeave != 'n');

    return 0;
}
