#ifndef SOLIDMATRIX_H
#define SOLIDMATRIX_H
/**
 * The matrix with no space optimization.
 *
 * Regulation:
 * The index of each dimension starts from 1 due to some mathematic
 * reasons. The dimension of matrix will always be 2, higher dimension
 * should be implemented by nested structure. The default value of each
 * data is 0, and the diagonal of unit matrix is 1.
 *
 * Template:
 * The class of the template should implement the overload of '+', '-',
 * '*', '/', and could covert 0 and 1 to proper values. Note that '-' has
 * two overloads.
 *
 * @author ZHG <CyberZHG@gmail.com>
 */

#include "ZMat.h"
#include <vector>

ZMAT_BEGIN_NAMESPACE

template <typename T>
class SolidMatrix {
public:
    /**
     * Create a matrix with single value.
     * @param value The value in the matrix.
     */
    SolidMatrix(const T &value);
    /**
     * Create a matrix with given row and column number.
     * @param rowNum The number of rows.
     * @param colNum The number of cols.
     */
    SolidMatrix(const int rowNum, const int colNum);
    virtual ~SolidMatrix();

    /**
     * @return The number of rows.
     */
    const int rowNum() const;
    /**
     * @return The number of columns.
     */
    const int colNum() const;
    /**
     * Set the number of rows.
     * @param rowNum The number of rows.
     */
    void setRowNum(const int rowNum);
    /**
     * Set the number of columns.
     * @param colNum The number of columns.
     */
    void setColNum(const int colNum);
    /**
     * Set the size of the matrix.
     * The operation will try to keep the original data in the same position.
     * @param rowNum The number of rows.
     * @param colNum The number of cols.
     */
    void setSize(const int rowNum, const int colNum);

    /**
     * Get data from matrix.
     * @param r Row index.
     * @param c Column index.
     * @return The specific data.
     */
    const T& data(const int r, const int c) const;
    /**
     * Set the data of the matrix.
     * @param r Row index.
     * @param c Column index.
     * @param value The value to set.
     */
    void setData(const int r, const int c, const T &value);

protected:
    int _rowNum;
    int _colNum;
    std::vector< std::vector<T> > _data;
};

ZMAT_END_NAMESPACE

#endif // SOLIDMATRIX_H
