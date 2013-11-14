#ifndef COMPLEX_H
#define COMPLEX_H
/**
 * The basic defination of complex number.
 * The number contains real part and image part.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "ZMat.h"
#include "Complex_io.h"
#include "Complex_math.h"
#include "Complex_arithmetic.h"

ZMAT_BEGIN_NAMESPACE

class Complex
{
public:
    Complex();
    Complex(const double real);
    Complex(const double real, const double image);
    virtual ~Complex();

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

#endif // COMPLEX_H
