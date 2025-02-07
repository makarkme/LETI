#pragma once

#include <iostream>
#include "array.h"

namespace ApplicationClass {
    class Application {
    private:
        ArrayClass::Array data;
        int condition = NULL;
        long long size = NULL;
        Complex oldElement{}, newElement{}; // тип данных теперь не double, а Complex
    public:
        explicit Application() = default;

        ~Application();

        void PrintMenu();
    };
}