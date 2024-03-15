#include "Grid.h"
#include "Direction.h"
#include "Group.h"
#include "Order.h"
#include <cstdlib>

namespace cursudsol {
    Grid::Grid() {
        flatData[0].removePencilMark(0);
        flatData[0].removePencilMark(1);
        flatData[0].removePencilMark(2);
        flatData[0].removePencilMark(3);
        flatData[0].removePencilMark(4);
        flatData[0].removePencilMark(5);
        flatData[0].removePencilMark(6);
        flatData[0].removePencilMark(7);

        // for (std::uint_fast8_t index = 0; index < Order::orderSq; ++index) {
        //     *(*(groups + Group::ROW) + index) = flatData + (index * Order::orderSq);
        //     *(*(groups + Group::COLUMN) + index) = flatData + index;
        //
        //     int blockStartRow = Order::order * (index / Order::order);
        //     int blockStartCol = index % Order::order;
        //     *(*(groups + Group::BLOCK) + index) = flatData + blockStartCol + (blockStartRow * Order::orderSq);
        // }
        //
        // for (std::uint_fast8_t index = 0; index < Order::orderSq * Order::orderSq; ++index) {
        //     if (index % Order::orderSq != Order::orderSq - 1) {
        //         (*(flatData + index)).setDirectionInGroup(Direction::NEXT, Group::ROW, flatData + index + 1);
        //         (*(flatData + index)).setDirectionInGroup(Direction::NEXT, Group::BLOCK, flatData + index + 1);
        //     }
        //
        //     if (index % Order::orderSq != 0) {
        //         (*(flatData + index)).setDirectionInGroup(Direction::PREVIOUS, Group::ROW, flatData + index - 1);
        //         (*(flatData + index)).setDirectionInGroup(Direction::PREVIOUS, Group::BLOCK, flatData + index - 1);
        //     }
        //
        //     if (index < Order::orderSq * (Order::orderSq - 1)) {
        //         (*(flatData + index)).setDirectionInGroup(Direction::NEXT, Group::COLUMN, flatData + index + Order::orderSq);
        //     }
        //
        //     if (index < Order::orderSq) {
        //         (*(flatData + index)).setDirectionInGroup(Direction::PREVIOUS, Group::COLUMN, flatData + index - Order::orderSq);
        //     }
        //
        // }
    }

    Cell* Grid::getFlatData() {
        return flatData;
    }

    Cell* Grid::getGroup(const Group group,
                         const std::size_t index) {
        return *(getGroups(group) + index);
    }

    Cell** Grid::getGroups(const Group group) {
        return *(groups + group);
    }

    Cell* Grid::getRow(const std::size_t index) {
        return getGroup(Group::ROW, index);
    }

    Cell** Grid::getRows() {
        return getGroups(Group::ROW);
    }

    Cell* Grid::getColumn(const std::size_t index) {
        return getGroup(Group::COLUMN, index);
    }

    Cell** Grid::getColumns() {
        return getGroups(Group::COLUMN);
    }

    Cell* Grid::getBlock(const std::size_t index) {
        return getGroup(Group::BLOCK, index);
    }

    Cell** Grid::getBlocks() {
        return getGroups(Group::BLOCK);
    }
}
