#ifndef SOLIDMATRIX_H
#define SOLIDMATRIX_H
/**
 * The matrix stored linear space with no space optimization.
 *
 * @author ZHG <CyberZHG@gmail.com>
 */

#include <vector>

namespace zmat
{
    class SolidMatrix
    {
    public:
        SolidMatrix();
        virtual ~SolidMatrix();

    protected:
        std::vector<int> _size;
        std::vector<double> _data;
    };
};

#endif // SOLIDMATRIX_H
