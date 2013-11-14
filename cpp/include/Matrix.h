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

ZMAT_BEGIN_NAMESPACE

template<typename T = Complex>
class Matrix
{
public:
    // Constructor
    Matrix(const T &value)
    {
        this->_zero = 0.0;
        this->_rowNum = 0;
        this->_colNum = 0;
        this->setSize(1, 1);
        this->setData(1, 1, value);
    }

    Matrix(const int rowNum = 1, const int colNum = 1)
    {
        this->_zero = 0.0;
        this->_rowNum = 0;
        this->_colNum = 0;
        this->setSize(rowNum, colNum);
    }

    // Size
    const int rowNum() const
    {
        return this->_rowNum;
    }

    const int colNum() const
    {
        return this->_colNum;
    }

    void setRowNum(const int rowNum)
    {
        this->setSize(rowNum, this->_colNum);
    }

    void setColNum(const int colNum)
    {
        this->setSize(this->_rowNum, colNum);
    }

    void setSize(const int rowNum, const int colNum)
    {
        std::vector< std::vector<T> > data;
        for (int i = 0; i < rowNum; ++i)
        {
            data.push_back(std::vector<T>());
            for (int j = 0; j < colNum; ++j)
            {
                if (i < this->_rowNum && j < this->_colNum)
                {
                    data[i].push_back(this->_data[i][j]);
                }
                else
                {
                    data[i].push_back(this->_zero);
                }
            }
        }
        this->_data = data;
        this->_rowNum = rowNum;
        this->_colNum = colNum;
    }

    // Data
    const Matrix<T> row(const int r) const
    {
        Matrix<T> R(1, this->_colNum);
        for (int i = 1; i <= this->_colNum; ++i)
        {
            R(1, i) = this->data(r, i);
        }
        return R;
    }

    const Matrix<T> col(const int c) const
    {
        Matrix<T> C(this->_rowNum, 1);
        for (int i = 1; i <= this->_rowNum; ++i)
        {
            C(i, 1) = this->data(i, c);
        }
        return C;
    }

    T& operator ()(const int r, const int c)
    {
        if (r >= 1 && r <= this->_rowNum)
        {
            if (c >= 1 && c <= this->_colNum)
            {
                return this->_data[r - 1][c - 1];
            }
        }
        return this->_zero;
    }

    const T data(const int r, const int c) const
    {
        if (r >= 1 && r <= this->_rowNum)
        {
            if (c >= 1 && c <= this->_colNum)
            {
                return this->_data[r - 1][c - 1];
            }
        }
        return this->_zero;
    }

    void setData(const int r, const int c, const T &value)
    {
        if (r >= 1 && r <= this->_rowNum)
        {
            if (c >= 1 && c <= this->_colNum)
            {
                this->_data[r - 1][c - 1] = value;
            }
        }
    }

protected:
    int _rowNum;
    int _colNum;
    T _zero;
    std::vector< std::vector<T> > _data;
};

template<typename T>
std::istream& operator >>(std::istream &in, Matrix<T> &mat)
{
    int r, c;
    T temp;
    in >> r >> c;
    mat.setSize(r, c);
    for (int i = 1; i <= r; ++i)
    {
        for (int j = 1; j <= c; ++j)
        {
            in >> temp;
            mat.setData(i, j, temp);
        }
    }
    return in;
}

template<typename T>
std::ostream& operator <<(std::ostream &out, const Matrix<T> &mat)
{
    out << "[" << mat.rowNum() << ", " << mat.colNum() << "]" << std::endl;
    for (int i = 1; i <= mat.rowNum(); ++i)
    {
        for (int j = 1; j <= mat.colNum(); ++j)
        {
            out << mat.data(i, j) << '\t';
        }
        out << std::endl;
    }
    return out;
}

template<typename T>
const Matrix<T> operator +(const Matrix<T> &a, const Matrix<T> &b)
{
    Matrix<T> c(a.rowNum(), a.colNum());
    for (int i = 1; i <= a.rowNum(); ++i)
    {
        for (int j = 1; j <= a.colNum(); ++j)
        {
            c.setData(i, j, a.data(i, j) + b.data(i, j));
        }
    }
    return c;
}

template<typename T>
const Matrix<T> operator -(const Matrix<T> &a, const Matrix<T> &b)
{
    Matrix<T> c(a.rowNum(), a.colNum());
    for (int i = 1; i <= a.rowNum(); ++i)
    {
        for (int j = 1; j <= a.colNum(); ++j)
        {
            c.setData(i, j, a.data(i, j) - b.data(i, j));
        }
    }
    return c;
}

template<typename T>
const Matrix<T> operator *(const Matrix<T> &a, const Matrix<T> &b)
{
    Matrix<T> c(a.rowNum(), b.colNum());
    for (int i = 1; i <= a.rowNum(); ++i)
    {
        for (int j = 1; j <= b.colNum(); ++j)
        {
            c.setData(i, j, 0.0);
            for (int k = 1; k <= a.colNum(); ++k)
            {
                c.setData(i, j, a.data(i, k) * b.data(k, j) + c.data(i, j));
            }
        }
    }
    return c;
}

template<typename T>
const bool operator ==(const Matrix<T> &a, const Matrix<T> &b)
{
    for (int i = 1; i <= a.rowNum(); ++i)
    {
        for (int j = 1; j <= a.colNum(); ++j)
        {
            if (!(a.data(i, j) == b.data(i, j)))
            {
                return false;
            }
        }
    }
    return true;
}

ZMAT_END_NAMESPACE

#endif // MATRIX_H
