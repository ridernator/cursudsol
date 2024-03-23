#include "Rule.h"

#include <string>

namespace cursudsol {
    Rule::Rule(const std::string& name) : name(name) {
    }

    const std::string& Rule::getName() const {
        return name;
    }
}
