#include "ConsolePrinter.h"

#include <iostream>

void ConsolePrinter::print(const std::string& content) const {
	std::cout << content << std::endl;
}

