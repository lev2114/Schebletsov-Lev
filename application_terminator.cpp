#include <iostream>
#include <cmath>
#include <iomanip>

#include "nonlinear_root_solver.hpp"
namespace{

double kXFirst = 0.5;

}

int NonLinearRootSolver::CoefficientBeforeCosineInput(){
    std::cout << "Введите коэффициент перед косинусом\n";
    int coefficientBeforeCosine{};
    std::cin >> coefficientBeforeCosine;
    return coefficientBeforeCosine;
}

double NonLinearRootSolver::iterationMethod(int coefficientBeforeCosine, double precicion){

}

double NonLinearRootSolver::PrecicionInput(){
    std::cout << "Введите погрешность\n";
    double precicion{};
    std::cin >> precicion;
    return precicion;
}


int NonLinearRootSolver::showMenu(){
    int menuOption{};
    std::cout << "Введите номер задания:\n1) Метод итераций\n2) Метод Ньютона\n3) Метод половинного деления\n";
    std::cin >> menuOption;
    return menuOption;
}

int NonLinearRootSolver::runApplication(){
    char toLeaveOrNotToLeave = 'n';
    do{

        int menuOption = NonLinearRootSolver::showMenu();
        NonLinearRootSolver::MenuOption option = static_cast<NonLinearRootSolver::MenuOption>(menuOption);

        switch(option) {
            case NonLinearRootSolver::MenuOption::HalfDivisionMethod:
                NonLinearRootSolver::halfDivisionMethod();
                break;

            case NonLinearRootSolver::MenuOption::IterationMethod:
                NonLinearRootSolver::iterationMethod(CoefficientBeforeCosineInput(),PrecicionInput());
                break;

            case NonLinearRootSolver::MenuOption::NewthonMethod:
                NonLinearRootSolver::newthonMethod();
                break;

            default:
                std::cout << "Введены неверные данные!";
                return 1;
        }

        std::cout << "Вы хотите продолжить? (y/n)\n";
        std::cin >> toLeaveOrNotToLeave;

        if (toLeaveOrNotToLeave != 'n' && toLeaveOrNotToLeave != 'y'){

            std::cout << "Введены неверные данные!";
            return 1;

        }
    } while(toLeaveOrNotToLeave != 'n');

    return 0;
}
