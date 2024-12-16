#ifndef INTEGRATION
#define INTEGRATION
namespace Integration{
enum class Method{
    squareMethod = 1,
    trapezioidMethod,
};

void StartProgram();
void StartIntegration(int a,int b, double precicion);
void StartTrapezioidIntegration(int a,int b,double precicion);

}



#endif
