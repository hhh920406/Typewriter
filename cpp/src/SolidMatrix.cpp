#include "SolidMatrix.h"
using namespace std;

ZMAT_BEGIN_NAMESPACE

SolidMatrix::SolidMatrix(const ComplexNumber &value) {
    this->setSize(1, 1);
    this->setData(1, 1, value);
}

SolidMatrix::SolidMatrix(const int rowNum, const int colNum) {
    this->setSize(rowNum, colNum);
}

SolidMatrix::~SolidMatrix() {
}

const int SolidMatrix::rowNum() const {
    return this->_rowNum;
}

const int SolidMatrix::colNum() const {
    return this->_colNum;
}

void SolidMatrix::setRowNum(const int rowNum) {
    this->setSize(rowNum, this->_colNum);
}

void SolidMatrix::setColNum(const int colNum) {
    this->setSize(this->_rowNum, colNum);
}

void SolidMatrix::setSize(const int rowNum, const int colNum) {
    vector< vector<ComplexNumber> > data;
    for (int i = 0; i < rowNum; ++i) {
        data.push_back(vector<ComplexNumber>());
        for (int j = 0; j < colNum; ++j) {
            if (i < this->_rowNum && j < this->_colNum) {
                data[i].push_back(this->_data[i][j]);
            } else {
                data[i].push_back(0.0);
            }
        }
    }
    this->_data = data;
    this->_rowNum = rowNum;
    this->_colNum = colNum;
}

const ComplexNumber SolidMatrix::data(const int r, const int c) const {
    if (r >= 1 && r <= this->_rowNum) {
        if (c >= 1 && c <= this->_colNum) {
            return this->_data[r - 1][c - 1];
        }
    }
    return 0;
}

void SolidMatrix::setData(const int r, const int c, const ComplexNumber &value) {
    if (r >= 1 && r <= this->_rowNum) {
        if (c >= 1 && c <= this->_colNum) {
            this->_data[r - 1][c - 1] = value;
        }
    }
}

ZMAT_END_NAMESPACE
