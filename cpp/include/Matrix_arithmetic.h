#ifndef MATRIX_ARITHMETIC_H_INCLUDED
#define MATRIX_ARITHMETIC_H_INCLUDED
/**
 * The arithmetic operations about matrix.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "ZMat.h"
#include <vector>

ZMAT_BEGIN_NAMESPACE

class Matrix;

const Matrix operator +(const Matrix &a, const Matrix &b);
const Matrix operator -(const Matrix &a, const Matrix &b);
const Matrix operator *(const Matrix &a, const Matrix &b);

const bool operator ==(const Matrix &a, const Matrix &b);

ZMAT_END_NAMESPACE

#endif // MATRIX_ARITHMETIC_H_INCLUDED
