# Unordered Data Structures: Week 1 Assignment: Hash Tables & Unordered Maps

Notes extracted from the instructions and while completing the assignment.

Topics covered:
- `std::unordered_map`
- `std::pair`
- "memoization"

## General instructions

- Compile: `make clean`, `make` and `make test`
- Run: `./main`, `./test`
- File to edit: `UnorderedMapExercises.cpp`
- Files to read:
    - `through_the_looking_glass.txt`: full text of the book Through the Looking-Glass by Lewis Carroll, loaded in the exercises.
    - `main.cpp`
    - `UnorderedMapCommon.h`, `UnorderedMapCommon.cpp`: type and helper function definition.
    - `IntPair.h`: pair of `ints` type based on STL.
    - `tests/week1_tests.cpp`: configuration of the test program.
- For submission: `make zip` and upload

## Notes from the Instructions: `std::unordered_map`, `std::pair`, Hashing, Memoization

### `std::unordered_map`

In C++, dictionaries are called maps.
We have two useful data structures in C++ to create dictionaries/maps:

- `std::map`: balanced tree (suwth sorted elements) with `O(log(n))` complexity for lookup.
- `std::unordered_map`: hash table with `O(1)` lookup time; much faster, but rehashing is performed if we exceed allocated size. We're going to use this.

```c++

#include <unordered_map>

// Create a single map instance where each string is mapped to one int
// key: std::string; data structure must have the operator '=' defined
// hashing is defined for basic data types, but we need to deal with custom structures separately
// value: int
std::unordered_map<, int> myMap;

// Assignment
myMap["five"] = 5;
// Lookup
std::cout << myMap["five"] << std::endl; // output: 5

```

## Exercises

### Exercise 1: `makeWordCounts`

### Exercise 2: `lookupWithFallback`

### Exercise 3: Memoizing a Function

