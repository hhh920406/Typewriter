#include "Matrix.h"
using namespace std;

ZMAT_BEGIN_NAMESPACE

Matrix::Matrix(const Complex &value)
{
    this->_rowNum = 0;
    this->_colNum = 0;
    this->setSize(1, 1);
    this->setData(1, 1, value);
}

Matrix::Matrix(const int rowNum, const int colNum)
{
    this->_rowNum = 0;
    this->_colNum = 0;
    this->setSize(rowNum, colNum);
}

Matrix::~Matrix()
{
}

const int Matrix::rowNum() const
{
    return this->_rowNum;
}

const int Matrix::colNum() const
{
    return this->_colNum;
}

void Matrix::setRowNum(const int rowNum)
{
    this->setSize(rowNum, this->_colNum);
}

void Matrix::setColNum(const int colNum)
{
    this->setSize(this->_rowNum, colNum);
}

void Matrix::setSize(const int rowNum, const int colNum)
{
    vector< vector<Complex> > data;
    for (int i = 0; i < rowNum; ++i)
    {
        data.push_back(vector<Complex>());
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

const Matrix Matrix::row(const int r) const
{
    Matrix R(1, this->_colNum);
    for (int i = 1; i <= this->_colNum; ++i)
    {
        R(1, i) = this->data(r, i);
    }
    return R;
}

const Matrix Matrix::col(const int c) const
{
    Matrix C(this->_rowNum, 1);
    for (int i = 1; i <= this->_rowNum; ++i)
    {
        C(i, 1) = this->data(i, c);
    }
    return C;
}

Complex& Matrix::operator ()(const int r, const int c)
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

const Complex Matrix::data(const int r, const int c) const
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

void Matrix::setData(const int r, const int c, const Complex &value)
{
    if (r >= 1 && r <= this->_rowNum)
    {
        if (c >= 1 && c <= this->_colNum)
        {
            this->_data[r - 1][c - 1] = value;
        }
    }
}

istream& operator >>(istream &in, Matrix &mat)
{
    int r, c;
    double temp;
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

ostream& operator <<(ostream &out, const Matrix &mat)
{
    out << "[" << mat.rowNum() << ", " << mat.colNum() << "]" << endl;
    for (int i = 1; i <= mat.rowNum(); ++i)
    {
        for (int j = 1; j <= mat.colNum(); ++j)
        {
            out << mat.data(i, j) << '\t';
        }
        out << endl;
    }
    return out;
}

const Matrix operator +(const Matrix &a, const Matrix &b)
{
    Matrix c(a.rowNum(), a.colNum());
    for (int i = 1; i <= a.rowNum(); ++i)
    {
        for (int j = 1; j <= a.colNum(); ++j)
        {
            c.setData(i, j, a.data(i, j) + b.data(i, j));
        }
    }
    return c;
}

const Matrix operator -(const Matrix &a, const Matrix &b)
{
    Matrix c(a.rowNum(), a.colNum());
    for (int i = 1; i <= a.rowNum(); ++i)
    {
        for (int j = 1; j <= a.colNum(); ++j)
        {
            c.setData(i, j, a.data(i, j) - b.data(i, j));
        }
    }
    return c;
}

const Matrix operator *(const Matrix &a, const Matrix &b)
{
    Matrix c(a.rowNum(), b.colNum());
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

const bool operator ==(const Matrix &a, const Matrix &b)
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
