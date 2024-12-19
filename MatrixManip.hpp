#ifndef MATRIXMANIP
#define MAtRIXMANIP
namespace MatrixManip {
struct NAndMValues {
    int n{};
    int m{};
};

enum class MatrixTypes {
    Dynamic = 1,
    Static,
};

void StartProgram();

void StartDynamicMatrix();

void FillDynamicMatrixNumeric(double** DynamicMatrix, int n, int m);

void StartStaticMatrix();

void FillStaticMatrixNumeric(double** StaticMatrix);

void PrintMatrix(double** Matrix, int linesNumber, int columnsNumber, bool printNumbersInMathematical, int precision, MatrixTypes matrixType);
}  // namespace MatrixManip
#endif