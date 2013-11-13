#ifndef SOLIDMATRIX_H
#define SOLIDMATRIX_H
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
#include "ComplexNumber.h"

ZMAT_BEGIN_NAMESPACE

class SolidMatrix {
public:
    SolidMatrix(const ComplexNumber &value);
    SolidMatrix(const int rowNum, const int colNum);
    virtual ~SolidMatrix();

    const int rowNum() const;
    const int colNum() const;
    void setRowNum(const int rowNum);
    void setColNum(const int colNum);
    void setSize(const int rowNum, const int colNum);

    const ComplexNumber data(const int r, const int c) const;
    void setData(const int r, const int c, const ComplexNumber &value);

protected:
    int _rowNum;
    int _colNum;
    std::vector< std::vector<ComplexNumber> > _data;
};

ZMAT_END_NAMESPACE

#endif // SOLIDMATRIX_H
