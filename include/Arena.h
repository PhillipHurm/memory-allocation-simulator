#pragma once

#include <cstddef>
#include <optional>
#include <vector>

enum class Strategy {
    FirstFit,
    BestFit,
    WorstFit
};

class Arena {
public:
    explicit Arena(std::size_t size);

    std::optional<std::size_t> allocate(
        std::size_t size,
        Strategy strategy
    );

    bool release(std::size_t offset);

    void printMap() const;

    std::size_t getTotalSize() const;
    std::size_t getFreeMemory() const;
    std::size_t getLargestFreeBlock() const;
    std::size_t getHoleCount() const;

private:
    struct Block {
        std::size_t offset;
        std::size_t size;
        bool free;
    };

    std::size_t totalSize;
    std::vector<Block> blocks;

    std::optional<std::size_t> findBlock(
        std::size_t size,
        Strategy strategy
    ) const;

    void splitBlock(std::size_t blockIndex, std::size_t requestedSize);
    void coalesce();
};