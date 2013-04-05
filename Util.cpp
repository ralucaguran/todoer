#include "Util.h"

#include <sstream>

std::string intToString(int i) {
    std::ostringstream out;
    out << i;
    return out.str();
}

