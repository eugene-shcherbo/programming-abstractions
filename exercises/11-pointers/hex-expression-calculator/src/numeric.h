
#ifndef NUMERIC_H
#define NUMERIC_H

#include <string>

namespace numeric {
    std::string integerToString(int val, int base);
    int stringToInteger(std::string val, int base);
}

#endif // NUMERIC_H
