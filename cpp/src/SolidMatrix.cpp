#include "SolidMatrix.h"
using namespace std;

ZMAT_BEGIN_NAMESPACE

template<class T>
SolidMatrix<T>::SolidMatrix(const T &value)
{
    this->setSize(1, 1);
    this->setData(1, 1, value);
}

template<class T>
SolidMatrix<T>::SolidMatrix(const int rowNum, const int colNum)
{
    this->setSize(rowNum, colNum);
}

template<class T>
SolidMatrix<T>::SolidMatrix(const vector<int> &size)
{
    this->setSize(size);
}

template<class T>
const vector<int>& SolidMatrix<T>::size() const
{
    return this->_size;
}

template<class T>
const int SolidMatrix<T>::row() const
{
    return this->_size.size() > 0 ? this->_size[0] : -1;
}

template<class T>
const int SolidMatrix<T>::col() const
{
    return this->_size.size() > 1 ? this->_size[1] : -1;
}

template<class T>
void SolidMatrix<T>::setSize(const int rowNum, const int colNum)
{
    this->_size.clear();
    this->_size.push_back(rowNum);
    this->_size.push_back(colNum);
    this->setSize(this->_size);
}

template<class T>
void SolidMatrix<T>::setSize(const vector<int> &size)
{
    this->_size = size;
    int num = 1;
    for (int i = 0; i < size.size(); ++i)
    {
        num *= size[i];
        if (num < 0)
        {
            return;
        }
    }
    while (this->_data.size() < num)
    {
        T data;
        this->_data.push_back(data);
    }
    while (this->_data.size() > num)
    {
        this->_data.pop_back();
    }
}

template<class T>
const T& SolidMatrix<T>::data(const int r, const int c) const
{
    int pos = this->getPosition(r, c);
    if (pos >= 0 && pos < this->_data.size())
    {
        return this->_data[pos];
    }
    T data;
    return data;
}

template<class T>
void SolidMatrix<T>::setData(const int r, const int c, const T &value)
{
    int pos = this->getPosition(r, c);
    if (pos >= 0 && pos < this->_data.size())
    {
        this->_data[pos] = value;
    }
}

template<class T>
int SolidMatrix<T>::getPosition(const int row, const int col) const
{
    return row * this->col() + col;
}

template<class T>
int SolidMatrix<T>::getPosition(const std::vector<int> &pos)
{
    if (pos.size() != this->_size().size())
    {
        return -1;
    }
    int ret = 0;
    int mul = 1;
    for (int i = pos.size() - 1; i >= 0; --i)
    {
        ret += pos[i] * mul;
        mul *= this->_size[i];
    }
    return ret;
}

ZMAT_END_NAMESPACE
