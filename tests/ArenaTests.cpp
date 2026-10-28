#include "Arena.h"

#include <cassert>
#include <iostream>

void testInitialState() {
    Arena arena(1000);

    assert(arena.getTotalSize() == 1000);
    assert(arena.getFreeMemory() == 1000);
    assert(arena.getLargestFreeBlock() == 1000);
    assert(arena.getHoleCount() == 1);
}

void testAllocation() {
    Arena arena(1000);

    auto first = arena.allocate(200, Strategy::FirstFit);

    assert(first.has_value());
    assert(*first == 0);
    assert(arena.getFreeMemory() == 800);
}

void testReleaseAndCoalescing() {
    Arena arena(1000);

    auto first = arena.allocate(200, Strategy::FirstFit);
    auto second = arena.allocate(300, Strategy::FirstFit);

    assert(first.has_value());
    assert(second.has_value());

    arena.release(*first);

    assert(arena.getFreeMemory() == 700);
    assert(arena.getHoleCount() == 2);

    arena.release(*second);

    assert(arena.getFreeMemory() == 1000);
    assert(arena.getLargestFreeBlock() == 1000);
    assert(arena.getHoleCount() == 1);
}

void testFailedAllocation() {
    Arena arena(500);

    auto result = arena.allocate(600, Strategy::FirstFit);

    assert(!result.has_value());
    assert(arena.getFreeMemory() == 500);
}

void testZeroAllocation() {
    Arena arena(500);

    auto result = arena.allocate(0, Strategy::FirstFit);

    assert(!result.has_value());
}

void testBestFit() {
    Arena arena(1000);

    auto a = arena.allocate(100, Strategy::FirstFit);
    auto b = arena.allocate(300, Strategy::FirstFit);
    auto c = arena.allocate(100, Strategy::FirstFit);
    auto d = arena.allocate(200, Strategy::FirstFit);
    auto e = arena.allocate(100, Strategy::FirstFit);

    assert(a && b && c && d && e);

    arena.release(*b);
    arena.release(*d);

    auto result = arena.allocate(180, Strategy::BestFit);

    assert(result.has_value());
    assert(*result == 500);
}

void testWorstFit() {
    Arena arena(1000);

    auto a = arena.allocate(100, Strategy::FirstFit);
    auto b = arena.allocate(300, Strategy::FirstFit);
    auto c = arena.allocate(100, Strategy::FirstFit);
    auto d = arena.allocate(200, Strategy::FirstFit);
    auto e = arena.allocate(100, Strategy::FirstFit);

    assert(a && b && c && d && e);

    arena.release(*b);
    arena.release(*d);

    auto result = arena.allocate(180, Strategy::WorstFit);

    assert(result.has_value());
    assert(*result == 100);
}

int main() {
    testInitialState();
    testAllocation();
    testReleaseAndCoalescing();
    testFailedAllocation();
    testZeroAllocation();
    testBestFit();
    testWorstFit();

    std::cout << "All tests passed.\n";

    return 0;
}