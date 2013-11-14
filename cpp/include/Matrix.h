#ifndef MATRIX_H
#define MATRIX_H
/**
 * The matrix with no space optimization.
 *
 * The index of each dimension starts from 1 due to some mathematic
 * reasons. The dimension of matrix will always be 2, higher dimension
 * should be implemented by nested structure. The default value of each
 * data is 0, and the diagonal of unit matrix is 1.
 *
 * @author ZHG <CyberZHG@gmail.com>
 */

#include <vector>
#include "ZMat.h"
#include "Complex.h"
#include "Matrix_io.h"
#include "Matrix_arithmetic.h"

ZMAT_BEGIN_NAMESPACE

class Matrix
{
public:
    Matrix(const Complex &value);
    Matrix(const int rowNum = 1, const int colNum = 1);
    virtual ~Matrix();

    const int rowNum() const;
    const int colNum() const;
    void setRowNum(const int rowNum);
    void setColNum(const int colNum);
    void setSize(const int rowNum, const int colNum);

    const Matrix row(const int r) const;
    const Matrix col(const int c) const;
    Complex& operator ()(const int r, const int c);
    const Complex data(const int r, const int c) const;
    void setData(const int r, const int c, const Complex &value);

protected:
    int _rowNum;
    int _colNum;
    Complex _zero;
    std::vector< std::vector<Complex> > _data;
};

ZMAT_END_NAMESPACE

#endif // MATRIX_H
