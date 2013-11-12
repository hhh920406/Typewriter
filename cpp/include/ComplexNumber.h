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

protected:
    double _real;
    double _image;
};

class ostream;

ostream& operator <<(ostream& out, const ComplexNumber &num);

const double abs(const ComplexNumber &num);
const double norm(const ComplexNumber &num);
const double angle(const ComplexNumber &num);
const ComplexNumber conjugate(const ComplexNumber &num);

const ComplexNumber operator +(const ComplexNumber &a, const ComplexNumber &b);
const ComplexNumber operator -(const ComplexNumber &a, const ComplexNumber &b);
const ComplexNumber operator *(const ComplexNumber &a, const ComplexNumber &b);
const ComplexNumber operator /(const ComplexNumber &a, const ComplexNumber &b);

bool operator ==(const ComplexNumber &a, const ComplexNumber &b);

ZMAT_END_NAMESPACE

#endif // COMPLEXNUMBER_H
