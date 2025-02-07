#ifndef TFUNCTION_H
#define TFUNCTION_H
#include "polynom.h"
#include "array.h"

using namespace std;
using namespace ArrayClass;

template <class number>
class Function : protected Polynom<number> {
public:
    Function(unsigned int degree, Array<number> derivatives) {
        Array<number> coefficients;
        coefficients.Resize(degree+1);
        coefficients.setElement(0, derivatives.getElement(0));

        long long factorial = 1;
        for (unsigned int i = 0; i <= degree; ++i) {
            factorial = factorial * (i+1);
            coefficients.setElement(i, number(derivatives.getElement(i) / factorial));
        }
        this->createPolynom(coefficients);
        this->setPrintMode(PrintModeCanonic);
    }

    number operator()(number x) {
        return this->countValue(x);
    }
};

#endif // TFUNCTION_H
