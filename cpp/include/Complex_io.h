#ifndef COMPLEX_IO_H_INCLUDED
#define COMPLEX_IO_H_INCLUDED
/**
 * Provide input and output for complex number.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <iostream>
#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

class Complex;

std::istream& operator >>(std::istream &in, Complex &num);
std::ostream& operator <<(std::ostream &out, const Complex &num);

ZMAT_END_NAMESPACE

#endif // COMPLEX_IO_H_INCLUDED
