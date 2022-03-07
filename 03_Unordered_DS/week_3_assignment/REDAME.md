# Unordered Data Structures: Week 3 Assignment: Graph Search Project

Notes extracted from the instructions and while completing the assignment.

Topics covered:


## General instructions

- Compile: `make clean`, `make` and `make test`
- Run: `./main`, `./test`
- File to edit: `GraphSearchExercises.cpp`: 3 exercises
- Files to read:
    - `main.cpp`
    - `GraphSearchCommon.h`: type and helper function definition.
    - `IntPair2.h`: pair of `ints` type based on STL.
    - `GridGraph.h`, `GridGraph.cpp`: `GridGraph` class -- `IntPair` vertices connected in a graph embedded in a 2D grid. STL containers used for adjacency lists.
    - `PuzzleState.h`, `PuzzleState.cpp`: `PuzzleState` class -- "8-puzzle" representation soved using graphs and Breadth-First-Search (BFS).
    - `tests/week1_tests.cpp`: configuration of the test program.
- For submission: `make zip` and upload

## Notes from the Instructions

### `std::unordered_set`

It is a hash map which can contain unique items; it has the following properties:

- If we insert an item more than once, it has no effect.
- The item class/type needs to have the operator `==` define for the usage of `std::hash`.
- Unlike `std::unordered_map`, it contains no associated value! We only care whether a key has been inserted or not. **Therefore, one of its uses is labelling: label whether a vertex was visited or not.**
- The alternative is `std::set`, which is a set based on a binary tree; it has pros & cons, depending on the application.

```c++
std::unordered_set<int> favoriteNumbers;
avoriteNumbers.insert(7);
favoriteNumbers.insert(42);
// Inserting again doesn’t change anything:
favoriteNumbers.insert(42);
bool isEmpty = favoriteNumbers.empty(); // false
std::cout << favoriteNumbers.count(7) << std::endl; // output: 1
favoriteNumbers.erase(7);
std::cout << favoriteNumbers.count(7) << std::endl; // output: 0
```

### `IntPair2.h`

See the Week 2 assignment.

`IntPair` is basically a `std::pair<int, int>`.

`IntPairPair`is `std::pair<IntPair, IntPair>`.

Hash functions are defined extending `std::hash` for both.

### Adjacency Lists: `GridGraph`