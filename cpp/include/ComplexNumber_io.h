#ifndef COMPLEXNUMBER_IO_H_INCLUDED
#define COMPLEXNUMBER_IO_H_INCLUDED
/**
 * Provide input and output for complex number.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <iostream>
#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

class ComplexNumber;

void input(ComplexNumber &num);
void output(const ComplexNumber &num);
void outputLine(const ComplexNumber &num);

std::istream& operator >>(std::istream &in, ComplexNumber &num);
std::ostream& operator <<(std::ostream &out, const ComplexNumber &num);

ZMAT_END_NAMESPACE

#endif // COMPLEXNUMBER_IO_H_INCLUDED
