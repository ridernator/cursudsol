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

    std::set<Cell*> Rule::findCellsWithPencilMark(const Cell* cell,
                                                  const Group groupType,
                                                  const IntType pencilMark) const {
        std::set<Cell*> returnVal;

        for (Cell* runner = getGroupStart(cell, groupType); runner != nullptr; runner = runner->getNeighbour(Direction::NEXT, groupType)) {
            if (runner->containsPencilMark(pencilMark)) {
                returnVal.insert(runner);
            }
        }

        return returnVal;
    }

    Cell* Rule::areCellsInSameGroup(const std::set<Cell*>& cells,
                                    const Group groupType) const {
        Cell* groupStart;
        Cell* returnVal = nullptr;

        for (const Cell* cell : cells) {
            groupStart = getGroupStart(cell, groupType);

            if (returnVal == nullptr) {
                returnVal = groupStart;
            } else if (groupStart != returnVal) {
                return nullptr;
            }
        }

        return returnVal;
    }

    Cell* Rule::getGroupStart(const Cell* cell,
                              const Group groupType,
                              const Direction direction) const {
        Cell* returnVal = (Cell*) cell;

        if (returnVal != nullptr) {
            while (returnVal->getNeighbour(direction, groupType) != nullptr) {
                returnVal = returnVal->getNeighbour(direction, groupType);
            }
        }

        return returnVal;
    }
}
