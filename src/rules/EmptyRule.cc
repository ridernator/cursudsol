#include "EmptyRule.h"
#include "Rule.h"

namespace cursudsol {
    SolverReturn EmptyRule::solveStep(Grid&,
                                      const bool) const {
        SolverReturn returnVal(false, {}, {});

        return returnVal;
    }
}
