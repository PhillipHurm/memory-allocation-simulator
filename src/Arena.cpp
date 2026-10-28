#include "Arena.h"
#include <iostream>

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

std::size_t Arena::getLargestFreeBlock() const {
    std::size_t largest = 0;

    for (const Block& block : blocks) {
        if (block.free && block.size > largest) {
            largest = block.size;
        }
    }

    return largest;
}

std::size_t Arena::getHoleCount() const {
    std::size_t holes = 0;

    for (const Block& block : blocks) {
        if (block.free) {
            ++holes;
        }
    }

    return holes;
}

void Arena::printMap() const {
    std::cout << "\nMemory map:\n";

    for (const Block& block : blocks) {
        std::cout
            << "[" << block.offset
            << " - " << (block.offset + block.size - 1)
            << "] "
            << (block.free ? "FREE" : "USED")
            << " (" << block.size << " bytes)\n";
    }

    std::cout << "\n";
}

std::optional<std::size_t> Arena::findBlock(
    std::size_t size,
    Strategy strategy
) const {
    std::optional<std::size_t> chosenBlock;

    for (std::size_t i = 0; i < blocks.size(); ++i) {
        if (!blocks[i].free || blocks[i].size < size) {
            continue;
        }

        if (strategy == Strategy::FirstFit) {
            return i;
        }

        if (!chosenBlock.has_value()) {
            chosenBlock = i;
            continue;
        }

        if (strategy == Strategy::BestFit &&
            blocks[i].size < blocks[*chosenBlock].size) {
            chosenBlock = i;
        }

        if (strategy == Strategy::WorstFit &&
            blocks[i].size > blocks[*chosenBlock].size) {
            chosenBlock = i;
        }
    }

    return chosenBlock;
}

void Arena::splitBlock(
    std::size_t blockIndex,
    std::size_t requestedSize
) {
    Block original = blocks[blockIndex];

    blocks[blockIndex] = {
        original.offset,
        requestedSize,
        false
    };

    if (original.size > requestedSize) {
        Block remaining = {
            original.offset + requestedSize,
            original.size - requestedSize,
            true
        };

        blocks.insert(
            blocks.begin() + blockIndex + 1,
            remaining
        );
    }
}

std::optional<std::size_t> Arena::allocate(
    std::size_t size,
    Strategy strategy
) {
    if (size == 0) {
        return std::nullopt;
    }

    auto blockIndex = findBlock(size, strategy);

    if (!blockIndex.has_value()) {
        return std::nullopt;
    }

    std::size_t offset = blocks[*blockIndex].offset;

    splitBlock(*blockIndex, size);

    return offset;
}

bool Arena::release(std::size_t offset) {
    for (Block& block : blocks) {
        if (block.offset == offset && !block.free) {
            block.free = true;
            coalesce();
            return true;
        }
    }

    return false;
}

void Arena::coalesce() {
    for (std::size_t i = 0; i + 1 < blocks.size();) {
        if (blocks[i].free && blocks[i + 1].free) {
            blocks[i].size += blocks[i + 1].size;
            blocks.erase(blocks.begin() + i + 1);
        } else {
            ++i;
        }
    }
}