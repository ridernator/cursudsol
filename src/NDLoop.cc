#include "NDLoop.h"

#include <cstddef>

namespace cursudsol {
    NDLoop::NDLoop(const std::size_t n,
                   const std::set<IntType> pencilMarks) : pencilMarks(pencilMarks.begin(), pencilMarks.end()),
                                                          n(n) {
        for (std::size_t index = 0; index < n - 1; ++index) {
            indices.push_back(index);
            returnVal.push_back(0);
        }

        indices.push_back(n - 2);
        returnVal.push_back(0);
    }

    std::vector<IntType> NDLoop::next() {
        if (n > pencilMarks.size()) {
            returnVal.clear();
        } else {
            if (++indices[n - 1] == pencilMarks.size()) {
                for (int backIndex = n - 2; backIndex >= 0; --backIndex) {
                    if (++indices[backIndex] < pencilMarks.size() - (n - (backIndex + 1))) {
                        for (std::size_t fwdIndex = backIndex + 1; fwdIndex < n; ++fwdIndex) {
                            indices[fwdIndex] = indices[fwdIndex - 1] + 1;
                        }

                        break;
                    }
                }
            }

            if (indices[0] == pencilMarks.size() - (n - 1)) {
                returnVal.clear();
            } else {
                for (std::size_t rIndex = 0; rIndex < n; ++rIndex) {
                    returnVal[rIndex] = pencilMarks[indices[rIndex]];
                }
            }
        }

        return returnVal;
    }
}
