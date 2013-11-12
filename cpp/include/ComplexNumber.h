#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H
/**
 * The basic defination of complex number.
 * The number contains real part and image part.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

class ComplexNumber {
public:
    ComplexNumber();
    ComplexNumber(const double real);
    ComplexNumber(const double real, const double image);
    virtual ~ComplexNumber();

    void setReal(const double real);
    void setImage(const double image);
    void setValue(const double real, const double image);
    const double real() const;
    const double image() const;

protected:
    double _real;
    double _image;
};

ZMAT_END_NAMESPACE

#endif // COMPLEXNUMBER_H
