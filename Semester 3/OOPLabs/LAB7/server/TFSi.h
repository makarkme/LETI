#ifndef TFSI_H
#define TFSI_H
#include "TFunction.h"

using namespace std;
using namespace ArrayClass;

template <class number>
class TFSi : public Function<number> {
    static Array<number> calculateDerivatives(unsigned int degree) {
        Array<number> derivatives;
        derivatives.Resize(degree+1);
        for (unsigned int i = 0; i <= degree; ++i) {
            if (i % 4 == 3 || i % 4 == 1)
                derivatives.setElement(i, number(0.0,0.0));
            else if (i % 4 == 2){
                derivatives.setElement(i, number(-1.0 / (i+1), 0.0));
            }
            else if (i % 4 == 0)
                derivatives.setElement(i, number(1.0/(i+1),0.0));
        }
        return derivatives;
    }

public:
    TFSi(unsigned int degree)
        : Function<number>(degree, calculateDerivatives(degree)) {}
};

#endif // TFSI_H
