#include "MassiveSort.hpp"
#include <iostream>

namespace{
void Swap(int* lhs, int* rhs){
    int temporaryStorage{};
    temporaryStorage = *lhs;
    *lhs = *rhs;
    *rhs = temporaryStorage;
}


}

namespace MassiveSort{

void TaskChoose(){
    MenuOption option = static_cast<MenuOption>(AskMenuOption());
    switch(option){
        case MenuOption::Static:
            StaticApp();
            break
    }

}

void StartCycle(){
    char Continuation = 'y';
    while(Continuation == 'y'){
        TaskChoose();
        std::cout << "Вы хотите продолжить?(y/n)";
        std::cin >> Continuation;
    }
}
}






