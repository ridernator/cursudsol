#pragma once

#include "Cell.h"
#include "Direction.h"
#include "Grid.h"
#include "Order.h"

#include <set>
#include <string>
#include <tuple>
#include <map>

#define DEFAULT_SOLVER_RETURN() {false, {} ,{}, 100}

namespace cursudsol {
    typedef std::tuple<bool, std::map<Cell*, std::set<IntType>>, std::map<Cell*, std::set<IntType>>, IntType> SolverReturn;

    class Rule {
        public:
            Rule(const std::string& name);

            virtual ~Rule() {}

            virtual SolverReturn solveStep(Grid& grid,
                                           const bool greedy = true) const = 0;

            const std::string& getName() const;

            bool isEnabled() const;

            void enable(const bool enabled = true);

        protected:
            std::set<Cell*> findCellsWithPencilMark(const Cell* cell,
                                                    const Group groupType,
                                                    const IntType pencilMark) const;

            Cell* areCellsInSameGroup(const std::set<Cell*>& cells,
                                      const Group groupType) const;

            Cell* getGroupStart(const Cell* cell,
                                const Group groupType,
                                const Direction direction = Direction::PREVIOUS) const;

        private:
            const std::string name;

            bool enabled;
    };
}
