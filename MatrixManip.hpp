#ifndef MATRIXMANIP
#define MAtRIXMANIP
namespace MatrixManip {

enum class MatrixTypes {
    Static = 1,
    Dynamic,

};

enum class OutputType {
    Scientific = 's',
    Float = 'f',
};



void StartProgram();

void StartDynamicMatrix();

void FillDynamicMatrixNumeric(double** DynamicMatrix, int n, int m);

void StartStaticMatrix();

void FillStaticMatrixNumeric(double StaticMatrix[10][10]);

void PrintMatrix(double StaticMatrix[10][10], double** DynamicMatrix, int linesNumber, int columnsNumber,
                 OutputType FloatOrScientificChoice, int precision, MatrixTypes matrixType);
}  // namespace MatrixManip
#endif
