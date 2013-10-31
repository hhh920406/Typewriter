#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H
/**
 * The complex number.
 * @author ZHG <CyberZHG@gmail.com>
 */

#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

class ComplexNumber {
public:
    ComplexNumber(void);
    ComplexNumber(const double real);
    ComplexNumber(const double real, const double image);
    virtual ~ComplexNumber();

    void setReal(const double real);
    void setImage(const double image);
    void setValue(const double real, const double image);
    const double real(void) const;
    const double image(void) const;

    void print(void) const;
    void printLine(void) const;

    const double abs(void) const;
    const double norm(void) const;
    const double angle(void) const;
    const ComplexNumber conjugate(void) const;

    friend const ComplexNumber operator -(const ComplexNumber &a);
    friend const ComplexNumber operator +(const ComplexNumber &a, const ComplexNumber &b);
    friend const ComplexNumber operator -(const ComplexNumber &a, const ComplexNumber &b);
    friend const ComplexNumber operator *(const ComplexNumber &a, const ComplexNumber &b);
    friend const ComplexNumber operator /(const ComplexNumber &a, const ComplexNumber &b);

    bool operator ==(const ComplexNumber &cn);

protected:
    double _real;
    double _image;
};

ZMAT_END_NAMESPACE

#endif // COMPLEXNUMBER_H
