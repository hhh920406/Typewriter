#include "Matrix.h"
using namespace std;

ZMAT_BEGIN_NAMESPACE

Matrix::Matrix(const Complex &value) {
    this->_rowNum = 0;
    this->_colNum = 0;
    this->setSize(1, 1);
    this->setData(1, 1, value);
}

Matrix::Matrix(const int rowNum, const int colNum) {
    this->_rowNum = 0;
    this->_colNum = 0;
    this->setSize(rowNum, colNum);
}

Matrix::~Matrix() {
}

const int Matrix::rowNum() const {
    return this->_rowNum;
}

const int Matrix::colNum() const {
    return this->_colNum;
}

void Matrix::setRowNum(const int rowNum) {
    this->setSize(rowNum, this->_colNum);
}

void Matrix::setColNum(const int colNum) {
    this->setSize(this->_rowNum, colNum);
}

void Matrix::setSize(const int rowNum, const int colNum) {
    vector< vector<Complex> > data;
    for (int i = 0; i < rowNum; ++i) {
        data.push_back(vector<Complex>());
        for (int j = 0; j < colNum; ++j) {
            if (i < this->_rowNum && j < this->_colNum) {
                data[i].push_back(this->_data[i][j]);
            } else {
                data[i].push_back(this->_zero);
            }
        }
    }
    this->_data = data;
    this->_rowNum = rowNum;
    this->_colNum = colNum;
}

Complex& Matrix::operator ()(const int r, const int c) {
    if (r >= 1 && r <= this->_rowNum) {
        if (c >= 1 && c <= this->_colNum) {
            return this->_data[r - 1][c - 1];
        }
    }
    return this->_zero;
}

const Complex Matrix::data(const int r, const int c) const {
    if (r >= 1 && r <= this->_rowNum) {
        if (c >= 1 && c <= this->_colNum) {
            return this->_data[r - 1][c - 1];
        }
    }
    return this->_zero;
}

void Matrix::setData(const int r, const int c, const Complex &value) {
    if (r >= 1 && r <= this->_rowNum) {
        if (c >= 1 && c <= this->_colNum) {
            this->_data[r - 1][c - 1] = value;
        }
    }
}

ZMAT_END_NAMESPACE
