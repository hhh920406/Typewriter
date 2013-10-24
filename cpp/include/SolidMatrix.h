#ifndef SOLIDMATRIX_H
#define SOLIDMATRIX_H
/**
 * The matrix stored linear space with no space optimization.
 *
 * @author ZHG <CyberZHG@gmail.com>
 */

#include "ZMat.h"
#include <vector>
#include "ComplexNumber.h"

ZMAT_BEGIN_NAMESPACE

class SolidMatrix
{
public:
    SolidMatrix();
    virtual ~SolidMatrix();

protected:
    std::vector<int> _size;
    std::vector<ComplexNumber> _data;
};

ZMAT_END_NAMESPACE

#endif // SOLIDMATRIX_H
