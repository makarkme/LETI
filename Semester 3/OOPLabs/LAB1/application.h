#pragma once

#include <iostream>
#include "array.h"

namespace ApplicationClass {
    class Application {
    private:
        ArrayClass::Array data;
        int condition = NULL;
        long long size = NULL;
        double oldElement = 0.0, newElement = 0.0;
    public:
        explicit Application() = default;
        ~Application();

        void PrintMenu();
    };
}