#include "SolidMatrix.h"
using namespace std;

ZMAT_BEGIN_NAMESPACE

template <typename T>
SolidMatrix<T>::SolidMatrix(const T &value) {
    this->setSize(1, 1);
    this->setData(1, 1, value);
}

template <typename T>
SolidMatrix<T>::SolidMatrix(const int rowNum, const int colNum) {
    this->setSize(rowNum, colNum);
}

template <typename T>
SolidMatrix<T>::~SolidMatrix() {
}

template <typename T>
inline const int SolidMatrix<T>::rowNum() const {
    return this->_rowNum;
}

template <typename T>
inline const int SolidMatrix<T>::colNum() const {
    return this->_colNum;
}

template <typename T>
void SolidMatrix<T>::setRowNum(const int rowNum) {
    this->_setSize(rowNum, this->_colNum);
}

template <typename T>
void SolidMatrix<T>::setColNum(const int colNum) {
    this->_setSize(this->_rowNum, colNum);
}

template <typename T>
void SolidMatrix<T>::setSize(const int rowNum, const int colNum) {
    vector< vector<T> > data;
    for (int i = 0; i < rowNum; ++i) {
        data.push_back(vector<T>());
        for (int j = 0; j < colNum; ++j) {
            if (i < this->_rowNum && j < this->_colNum) {
                data.push_back(this->_data[i][j]);
            } else {
                data.push_back(0);
            }
        }
    }
    this->_data = data;
    this->_rowNum = rowNum;
    this->_colNum = colNum;
}

template <typename T>
const T& SolidMatrix<T>::data(const int r, const int c) const {
    if (r >= 1 && r <= this->_rowNum) {
        if (c >= 1 && c <= this->_colNum) {
            return this->_data[r - 1][c - 1];
        }
    }
    return 0;
}

template <typename T>
void SolidMatrix<T>::setData(const int r, const int c, const T &value) {
    if (r >= 1 && r <= this->_rowNum) {
        if (c >= 1 && c <= this->_colNum) {
            this->_data[r - 1][c - 1] = value;
        }
    }
}

ZMAT_END_NAMESPACE
