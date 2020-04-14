#ifndef _labelgenerator_h_
#define _labelgenerator_h_

#include <string>

class LabelGenerator {
public:
    LabelGenerator(std::string prefix, int startIndex);

    std::string nextLabel();

private:
    std::string _prefix;
    int _index;
};

#endif
