#include "Arena.h"
#include <iostream>

int main() {
    Arena arena(1000);

    auto first = arena.allocate(200, Strategy::FirstFit);
    auto second = arena.allocate(300, Strategy::FirstFit);

    arena.printMap();

    std::cout << "Free memory: "
              << arena.getFreeMemory()
              << " bytes\n";

    std::cout << "Largest free block: "
              << arena.getLargestFreeBlock()
              << " bytes\n";

    std::cout << "Free blocks: "
              << arena.getHoleCount()
              << "\n";

    if (first.has_value()) {
        arena.release(*first);
    }

    arena.printMap();

    if (second.has_value()) {
        arena.release(*second);
    }

    arena.printMap();

    return 0;
}