#pragma once

#include <iostream>
#include "array.h"
#include "polynom.h"

static char key = 'c';

namespace ApplicationClass {
    class Application {
    private:
        Polynom polinom;
        ArrayClass::Array data;
        int condition = NULL;
        int condition2 = NULL;
        long long size = NULL;
        Complex oldElement{}, newElement{}, value{};
    public:
        explicit Application() = default;
        ~Application();
        void PrintMenu();
    };
}