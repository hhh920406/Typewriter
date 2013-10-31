#ifndef SOLIDMATRIX_H
#define SOLIDMATRIX_H
/**
 * The matrix stored linear space with no space optimization.
 *
 * @author ZHG <CyberZHG@gmail.com>
 */

#include "ZMat.h"
#include <vector>

ZMAT_BEGIN_NAMESPACE

template<class T>
class SolidMatrix
{
public:
    SolidMatrix(const T &value);
    SolidMatrix(const int rowNum, const int colNum);
    SolidMatrix(const std::vector<int> &size);
    virtual ~SolidMatrix();

    const std::vector<int>& size() const;
    const int row() const;
    const int col() const;
    void setSize(const int rowNum, const int colNum);
    void setSize(const std::vector<int> &size);

    const T& data(const int r, const int c) const;
    void setData(const int r, const int c, const T &value);

protected:
    std::vector<int> _size;
    std::vector<T> _data;

    int getPosition(const int row, const int col) const;
    int getPosition(const std::vector<int> &pos);
};

ZMAT_END_NAMESPACE

#endif // SOLIDMATRIX_H
