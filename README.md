# Memory Allocation Simulator

A C++ memory allocation simulator that demonstrates common dynamic memory placement strategies, block splitting, deallocation, free-block coalescing, and fragmentation-related statistics.

The project models a fixed-size memory arena and allows allocations to be made using First Fit, Best Fit, or Worst Fit strategies.

## Features

- Fixed-size simulated memory arena
- First Fit allocation
- Best Fit allocation
- Worst Fit allocation
- Block splitting during allocation
- Memory release by allocation offset
- Automatic coalescing of adjacent free blocks
- Human-readable memory map
- Free-memory reporting
- Largest-free-block reporting
- Free-block/hole counting
- Automated tests for allocation, deallocation, coalescing, and placement strategies

## Example

```cpp
Arena arena(1000);

auto first = arena.allocate(200, Strategy::FirstFit);
auto second = arena.allocate(300, Strategy::BestFit);

arena.printMap();

if (first.has_value()) {
    arena.release(*first);
}
```

Example memory map:

```text
Memory map:
[0 - 199] USED (200 bytes)
[200 - 499] USED (300 bytes)
[500 - 999] FREE (500 bytes)

Free memory: 500 bytes
Largest free block: 500 bytes
Free blocks: 1
```

After both allocations are released, adjacent free blocks are coalesced back into a single region:

```text
Memory map:
[0 - 999] FREE (1000 bytes)
```

## Allocation Strategies

### First Fit

Selects the first free block large enough to satisfy the requested allocation.

### Best Fit

Selects the smallest available free block that is large enough for the request.

### Worst Fit

Selects the largest available free block that can satisfy the request.

These strategies make it possible to observe how different placement decisions affect the layout of free and allocated memory.

## Project Structure

```text
memory-allocation-simulator/
├── include/
│   └── Arena.h
├── src/
│   ├── Arena.cpp
│   └── main.cpp
├── tests/
│   └── ArenaTests.cpp
├── CMakeLists.txt
├── README.md
└── .gitignore
```

## Building

This project requires:

- C++17-compatible compiler
- CMake 3.16 or newer

Configure the project:

```bash
cmake -S . -B build
```

Build it:

```bash
cmake --build build
```

### Windows

When using Visual Studio Build Tools, the executable will normally be located at:

```powershell
.\build\Debug\memory_allocation_simulator.exe
```

Run it with:

```powershell
.\build\Debug\memory_allocation_simulator.exe
```

## Running Tests

The project includes a lightweight test executable using standard C++ assertions.

Build the project first:

```bash
cmake --build build
```

On Windows:

```powershell
.\build\Debug\memory_allocation_tests.exe
```

Successful execution should report:

```text
All tests passed.
```

The tests currently cover:

- Initial arena state
- Successful allocation
- Failed oversized allocation
- Zero-size allocation rejection
- Memory release
- Adjacent free-block coalescing
- First Fit behavior
- Best Fit behavior
- Worst Fit behavior

## Design

Memory is represented internally as an ordered collection of blocks. Each block stores:

- Starting offset
- Size
- Whether the block is free or allocated

Allocating memory splits an available block when necessary. Releasing memory marks the corresponding block as free, after which adjacent free regions are automatically merged.

Allocations return simulated memory offsets rather than raw operating-system pointers. This keeps the project focused on allocation behavior and memory-layout concepts without attempting to replace the system allocator.

## Concepts Demonstrated

- C++17
- Object-oriented design
- Dynamic memory allocation concepts
- Allocation algorithms
- Memory fragmentation
- Block splitting
- Free-block coalescing
- STL containers
- `std::optional`
- CMake
- Automated testing
- Git version control

## Academic Integrity

This is an independent project built from operating-systems concepts I studied in university coursework.

I have intentionally not published my original graded assignment solutions, assignment specifications, instructor-provided test files, or course-provided code. This repository is a separate implementation with its own interface, structure, tests, and documentation.

The goal is to demonstrate the underlying systems-programming concepts while respecting academic-integrity requirements for university coursework.

## Future Improvements

Potential extensions include:

- Workload-driven comparison of allocation strategies
- Additional fragmentation metrics
- Allocation performance benchmarks
- Interactive command-line controls
- Memory-layout visualization over time