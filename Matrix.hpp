#ifndef MATRIXMANIP
#define MATRIXMANIP
namespace {
const int kLinesNumber = 10;
const int kColumnsNumber = 10;
}  // namespace
namespace Matrix {

enum class MatrixTypes {
    Static = 1,
    Dynamic,
};

enum class OutputType {
    Scientific = 's',
    Float = 'f',
};

double** GetPointersFromStaticMatrix(double staticMatrix[kLinesNumber][kColumnsNumber]);

double** AllocateMemory(int n, int m);

void FreeMemory(double** dynamicMatrix, int n);

void StartProgram();

void ProcessDynamicMatrix();

void FillDynamicMatrix(double** dynamicMatrix, int n, int m);

void ProcessStaticMatrix();

void FillStaticMatrix(double**& staticMatrix);

void PrintMatrix(double** matrix, int linesNumber, int columnsNumber, OutputType floatOrScientificChoice, int precision, MatrixTypes matrixType);
}  // namespace Matrix
#endif  // DEFINE MATRIXMANIP
