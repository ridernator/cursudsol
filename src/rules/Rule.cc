#include "Rule.h"

#include <string>

namespace cursudsol {
    Rule::Rule(const std::string& name) : name(name),
                                          enabled(true) {
    }

    const std::string& Rule::getName() const {
        return name;
    }

    bool Rule::isEnabled() const {
        return enabled;
    }

    void Rule::enable(const bool enabled) {
        this->enabled = enabled;
    }
}
