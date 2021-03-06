# Ordered Data Structures: Week 3 Assignment: 

Notes extracted from the instructions and while completing the assignment.

## General instructions

- Compile: `make clean`, `make` and `make test`
- Run: `./main`, `./test`
- Templated C++ code: code in header files, specific version generated at compilation, depending on how templates are used in code
- File to edit: `GenericTreeExercises.h`: 2 exercises
- Files to read:
    - `GenericTree.h`: `GenericTree` class.
    - `GenericTreeExercises.h`: look at examples and comments.
    - `main.cpp`: `main`.
    - `tests/week3_tests.cpp`: unit tests; have a look at them.
- For submission: `make zip` and upload

## The `GenericTree` Class

- Template of generic tree
- N-ary tree: each node can have many children
- No balancing implemented
- Nodes contain an `std::vector` of pointers to children and a value/data field
- Simple implementation:
  - pointers visible to nodes to operate on them; usually, that should be avoided
  - copy constructor disabled
- As opposed to horizontal tree diagrams, vertical tree diagrams are plotted
- We can use STL containers: `std::vector`, `std::queue`, `std::stack`

## Exercise 0: Read & Analyze `GenericTree` 

Hints for exercises 1 & 2 are already in the provided code and in the comments.

```
class GenericTree<T> // Implementation separated: in same file, after definition
    (public)
        class TreeNode (all public, nullptr initializations)
            TreeNode* parentPtr
            std::vector< TreeNode* > childrenPtrs
            T data
            TreeNode* addChild(const T& childData)
                TreeNode* newChildPtr = new TreeNode(childData)
                newChildPtr->parentPtr = this
                childrenPtrs.push_back(newChildPtr)
                return newChildPtr
            constructors & co.
            copy disabled
    (private)
        TreeNode* rootNodePtr // initialized to nullptr
    (public)
        TreeNode* createRoot(const T& rootData)
            rootNodePtr = new TreeNode(rootData)
            return rootNodePtr
        TreeNode* getRootPtr()
        void deleteSubtree(TreeNode* targetRoot)
            stack-based node deletion
            and memory de-allocation
            not recursive, to avoid issues with memory stack size
            two stacks (LIFO) are created while going through the tree
                explore stack
                delete stack
        void compress() // remove nullptrs originated after deleteSubtree
            a queue (FIFO) is created with nodes to explore
            staring with root
            for each node, a std::vector with children pointers without nullptr
            is created and swaped
        constructors & co.
        copy disabled
        void clear()
            deleteSubtree(rootNodePtr)
        std::ostream& Print(std::ostream& os) const // vertical tree output
            preOrder traverse is performed through all nodes
            several support stacks are used

```

## Exercise 1: Implement `treeFactory()`

File: `GenericTreeExercises.h`

Modify a passed treed to obtain the following output:

```
4
|
|_ 8
|  |
|  |_ 16
|  |  |
|  |  |_ 42
|  |
|  |_ 23
|
|_ 15
```

```c++
static void treeFactory(GenericTree<int>& tree) {
  tree.clear();
  tree.createRoot(4);
  auto node_4 = tree.getRootPtr();
  auto node_8 = node_4->addChild(8);
  node_4->addChild(15);
  auto node_16 = node_8->addChild(16);
  node_8->addChild(23);
  node_16->addChild(42);
}
```


## Exercise 2: Implement `traverseLevels()` 

File: `GenericTreeExercises.h`

Level-order traversal of the input tree (queues seem a reasonable tool here).

Background discussion notes:
- Pre-, in- and post-order traversals are for depth-breadth traversals
- A level-order traversal is breadth-first and it can be accomplished making use of a queue (FIFO), among other strategies
- Recursive approaches ar every elegant, but if too much recursions are performed, we might hit against the limitations of the stack memory
- In general, we can use hybrid iterative-recursive approaches

Two example functions are provided, one recursive, the other iterative:
- `countNullChildrenRecursive()`
- `countNullChildrenIterative()`

Solution:

```c++
template <typename T>
std::vector<T> traverseLevels(GenericTree<T>& tree) {
  using TreeNode = typename GenericTree<T>::TreeNode;
  std::vector<T> results;

  auto rootNodePtr = tree.getRootPtr();
  if (!rootNodePtr) return results;

  std::queue<TreeNode*> nodesToExplore;
  nodesToExplore.push(rootNodePtr);

  while (!nodesToExplore.empty()) {

    TreeNode* frontNode = nodesToExplore.front();
    nodesToExplore.pop();

    if (frontNode) {
      results.push_back(frontNode->data);
      for (auto childPtr : frontNode->childrenPtrs) {
        nodesToExplore.push(childPtr);
      }
    }
  }
  return results;
}
```