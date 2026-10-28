#include "Arena.h"

Arena::Arena(std::size_t size)
    : totalSize(size) {
    blocks.push_back({0, size, true});
}

std::size_t Arena::getTotalSize() const {
    return totalSize;
}

std::size_t Arena::getFreeMemory() const {
    std::size_t totalFree = 0;

    for (const Block& block : blocks) {
        if (block.free) {
            totalFree += block.size;
        }
    }

    return totalFree;
}