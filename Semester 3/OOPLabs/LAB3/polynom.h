#pragma once

#include "number.h"
#include "array.h"
#include <cmath>
#include <iostream>

enum PrintMode { PrintModeClassic = 1, PrintModeCanonic = 2 };

class Polynom {
	PrintMode printMode;
private:
	ArrayClass::Array data;
public:
	explicit Polynom() = default;
	void setPrintMode(PrintMode);
	void printPolynom() const;
	void createPolynom(ArrayClass::Array arr);
	ArrayClass::Array getData();
	number countValue(number value, char key);
};