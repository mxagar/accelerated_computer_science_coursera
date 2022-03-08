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

Instead of creating the adjacency list using pointers, STL containers are used, following this scheme:

- Each vertex object has a unique key. We create a map where each vertex has a separate entry based on its own key.
- 
- Each vertex should be mapped to a set of other keys, one key for each adjacent vertex (connected by an edge, implicitly).

See `GridGraph.h`.

#### `GridGraph`

`GridGraph` is an undirected graph on a 2D grid with 2D points as vertices. It has the following properties:

- A vertex is an `IntPair`: `row, column`.
- Edges are only horizontal or vertical (i.e., unit distance allowed only).
- Isolated points (i.e., without edges) are possible.
- We can plot them with `plot()` or `<<`.
- Edges are not explicitly defined, but they are represented with two `IntPairs` or an `IntPairPair`. However, note that `IntPairPair` hashes differently a pair of points with different order, even though they represent the same edge! That needs to be taken into account manually when counting edges...

Some members of `GridGraph`:

```c++
// Adjancency set: each vertex has one set of neighbor vertices
using NeighborSet = std::unordered_set<IntPair>;
// Adjacency map: list of vertices with their neighbor/adjacent vertices
// i.e., connected with an edge.
// If vertex X has adjacent Y, the reverse must be also true
// If a key exists, the point exists
std::unordered_map<IntPair, GridGraph::NeighborSet> adjacencyMap;
// A key is created with [p]
insertPoint(const IntPair& p);
// A key is created and a neighbor vertex is inserted with [p1].insert(p2);
insertEdge(const IntPair& p1, const IntPair& p2);
// Only horizontal/vertical edges allowed
checkUnitDistance(const IntPair& p1, const IntPair& p2);
// Erase point / edge
removeEdge(const IntPair& p1, const IntPair& p2);
removePoint(const IntPair& p1);
// Does graph contain this point / edge
hasPoint(const IntPair& p);
hasEdge(const IntPair& p1, const IntPair& p2);
// Count
countVertices();
countEdges();
// Plot
plot();
```

### Graph Search Algorithms

Note that many problems could be modelled as graphs: puzzle solving (e.g., rubik's cube), path finding on maps, etc.

Breadth-First-Search (BFS) is used. List of search algorithms that work on both directed and undirected graphs:

- Breadth-First-Search (BSF): used for shortest path detection, if all edges have same length/weight. The algorithm works expanding the frontier of search; length-1 vertices are visited before length-2 ones.
- Dijkstra's algorithm: also for shortest paths, but with different edge lengths or weights.
- Depth-First-Search (DFS): It could be used for shortest path search.
- A*: similar to Dijkstra's algorithm, but a heuristic is used to guess which nodes to try next. A* and its improved versions are common when graphs describe states (vertices) and transitions (edges) between them, because we can simplify the search when the space of states is very large (as commonly happens).
- Bellman-Ford: similar to BFS; slower and requires more memory, but negative lengths allowed.

## Exercises: `GraphSearchExercises.cpp`

### Exercise 1: `countEdges()`, `removePoint()`

Implement the following functions:

- `GridGraph::countEdges()`: take into account that edges are not stored, but neighbor vertices; thus, we double count them if we just count the neighbors. Look at `GridGraph::printDetails` for an alternative.
- `GridGraph::removePoint(IntPair)`: point and all references (neighbors / edges) erased.

```c++
int GridGraph::countEdges() const {
  int numEdges = 0;
  if (adjacencyMap.empty()) {
    return (0);
  }
  std::unordered_set<IntPairPair> edgeSet;
  // Loop over key-value pairs
  for (const auto& kv : adjacencyMap) {
    // key: point
    const auto& p1 = kv.first;
    // value: neighbor point set
    const auto& p1_neighbors = kv.second;
    if (!p1_neighbors.empty()) {
      // edge (A,B) == (B,A)
      // we can take care of this ordering A & B
      // and inserting to the set the ascending sequence always
      // (a set inserts only new and unique items)
      // note that "<" is possible because it is defined for std::pair<int,int>
      for (const auto& p2 : p1_neighbors) {
        IntPairPair edge;
        if (p1 < p2) {
          edge = std::make_pair(p1,p2);
        }
        else {
          edge = std::make_pair(p2,p1);
        }
        edgeSet.insert(edge);
      }
    }
  }
  return (edgeSet.size());
}

void GridGraph::removePoint(const IntPair& p1) {
  if (!hasPoint(p1)) return;
  // Security: make a copy of the container we're modifying and iterating simultaneously
  const GridGraph::NeighborSet originalNeighbors = adjacencyMap.at(p1);
  // Recall:
  // using NeighborSet = std::unordered_set<IntPair>;
  // std::unordered_map<IntPair, GridGraph::NeighborSet> adjacencyMap;
  for (const auto& kv : originalNeighbors) {
    // key: point / IntPair
    adjacencyMap.at(kv).erase(p1);
  }
  adjacencyMap.erase(p1);
}

```

### Exercise 2: `graphBFS()`

Finish the missing small parts from `graphBFS()`, which performs a Breadth-First-Search (BFS).

Details of the implementation in contrast to pseudocode in theory:

- Goal: shortest path between two points.
- Labelling of visited points is implemented with `std::unordered_set<IntPair>`.
- Exploring = visiting = discovering = stepping to a successor of a point/node/vertex.
- We store predecessor nodes in an `std::unordered_map pred`: this encodes implicitly the edges of the path.
- `dist` is used to record the shortest path.
- A dequeued set of vertices is also used to avoid mistakes and infinite loops.

Note that in practice, we would have opted for another implementation, rather than BFS, such as any of the improved/modified versions of A*.

See solution in `GraphSearchExercises.cpp`. The function is easy but interesting. The exercise is even easier, because some minor lines needed to be added. The task was more about reading and understanding the code.

### Exercise 3: `puzzleBFS()`