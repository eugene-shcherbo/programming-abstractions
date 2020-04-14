#include "labelgenerator.h"
#include "strlib.h"

LabelGenerator::LabelGenerator(std::string prefix, int index) {
    _prefix = prefix;
    _index = index;
}

std::string LabelGenerator::nextLabel() {
    return _prefix + integerToString(_index++);
}
