#include "Arena.h"
#include <iostream>

int main() {
    Arena arena(1000);

    std::cout << "Arena size: "
              << arena.getTotalSize()
              << " bytes\n";

    std::cout << "Free memory: "
              << arena.getFreeMemory()
              << " bytes\n";

    return 0;
}