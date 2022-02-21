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
// key-values are stored as std::pair
std::unordered_map<std::string, int> myMap;

// Assignment
// Watch out: only with non-const maps, since [] returns modifiable reference
// If key doesn't exist, it is created! Thus, use at() or count() instead
myMap["five"] = 5;
// Lookup
std::cout << myMap["five"] << std::endl; // output: 5

// Number of keys assigned
std::cout << "Map size: " << myMap.size() << std::endl;

// Use count to check whether a key was assigned
// otherwise, it will be assigned when checking with []
// count() returns 0 or 1
if (myMap.count("five")>0)
    std::cout << "Key 'five' exists." << std::endl;
else
    std::cout << "Key 'five' does not exist." << std::endl;

// Create with {{},{}} pairs
std::unordered_map<std::string,int> mymap = {
            { "Mars", 3000},
            { "Saturn", 60000},
            { "Jupiter", 70000 } };

// at: reference to the mapped value
// equivalent to [], but exception is thrown
// if key not found without modifying map
mymap.at("Mars") = 3396;
mymap.at("Saturn") += 272;
mymap.at("Jupiter") = mymap.at("Saturn") + 9638;

for (auto& x: mymap) {
    std::cout << x.first << ": " << x.second << std::endl;
}

// find() returns an iterator if key found
// unordered_map::end otherwise
std::unordered_map<std::string,double>::const_iterator got = mymap.find("Venus");
if (got == mymap.end())
    std::cout << "not found";
else
    std::cout << got->first << " is " << got->second;

// erase(): remove the key-value pair entirely
mymap.erase ( mymap.begin() );      // erasing by iterator
mymap.erase ("Mars");             // erasing by key
mymap.erase ( mymap.find("Mars"), mymap.end() ); // erasing by range

```

### `std::pair`

Two types can be joined in a singles class type with `std::pair`. It is used for the key-value pairs used in maps.

```c++
#include <utility> // for std::pair

// Create a pair:
// 1) first, second
std::pair<std::string, int> myPair;
myPair.first = "Hello, this is the string element."; myPair.second = 42;
// 2) make_pair
std::pair<std::string, int> anotherPair = std::make_pair("sevens", 777);
// 3) {}
std::pair<std::string, int> yetAnotherPair = {"sevens", 777};

// Often, an alias is created
using StringIntPair = std::pair<std::string, int>;
StringIntPair thisPair = {"sevens", 777};

// We can initialize unordered_maps with pairs
std::unordered_map<int, int> lookupTable = {{1, 10}, {2, 20}, {3, 30}};

```

### Hashing

Good hash functions are very difficult to create from the scratch, so the general recommendation is top use available ones from `std::hash`. However, STL provides hash functions for basic types (`int`, `std::string`, etc.). Therefore, one solution is to convert into strings any complex data structures we might have. If our hashes are not for cryptography, but for hash tables, that is a good practical approach.

The file `IntPair.h` shows how this is done: the STL template `std::hash` is *specialized* for our class `IntPair`; `std::hash` is a `struct` that can act as a function, thus its `operator()` is defined as follows:

- The member variables of `IntPair` are converted to strings (an arbitrary sequence of bytes) with a separator between them.
- A `std::hash<std::string>` has function is instantiated.
- We pass our *stringified* `IntPair` to that has function.

`IntPair.h`:

```c++
#include <functional> // for std::hash
#include <utility> // for std::pair
#include <string> // for std::string

using IntPair = std::pair<int, int>;

namespace std {
  template <>
  struct hash<IntPair> {
    std::size_t operator() (const IntPair& p) const {
      std::string uniqueIntPairString = std::to_string(p.first) + "##" + std::to_string(p.second);
      std::hash<std::string> stringHasher;
      return stringHasher(uniqueIntPairString);
    }
  };
}

```

### Memoization

Memoization consists in storing in a hash table solutions to recurring sub-problems in a bigger problem. Such bigger problems are often solved through recursion or iteration, and if at any step any of the cached problems arise, the solution is grabbed from the hash table. That accelerates the solving of the bigger problem. In such approaches, it is also common to have reconstruction functions that build the solution from the memoization table. Theses approaches are using in dynamic programming.

## Notes on the Provided Code

### `UnorderedMapCommon.h`, `UnorderedMapCommon.cpp`

In the following, my personal notes after going through the code are displayed in an indented informal style:

```

Structure and alias definition
    StringVec
    StringIntPair
    StringIntMap
    StringIntPairVec
    LengthMemo: std::unordered_map<IntPair, int>
        memoization for the palindrome problem

loadBookStrings()
    load book TXT as a vector of word strings

wordCountComparator(x, y)
    x.second < y.second

sortWordCounts()
    create a sorted vector or items
    of a map with word/string:count pairs
    std::sort() is used in combination with wordCountComparator()

makeWordCounts()
    EXERCISE
    take a vector of strings and count unique strings/words

lookupWithFallback()
    EXERCISE
    read-only lookups in std::unordered_map

getBottomWordCounts()
getTopWordCounts()
    std::vectors with most/less common words (based on their counts)

longestPalindromeLength()
    brute-force palindrome computation
    clock used internally to prevent running too long

memoizedLongestPalindromeLength()
    EXERCISE
    memoized version of longestPalindromeLength()

reconstructPalindrome()
    it uses memoizedLongestPalindromeLength()

```

### `main.cpp`

This file tests the implementation of the rest of the files, and particularly, the implementation of the exercises.

## Exercises

### Exercise 1: `makeWordCounts`

Given an `std::vector<std::string>` of the whole text (each `string` element is a word), create a `std::unordered_map<std::string, int>` with the words.

```c++
StringIntMap makeWordCounts(const StringVec& words) {
  StringIntMap wordcount_map;
  for (auto& word: words) {
    if (wordcount_map.count(word)>0) {
      wordcount_map.at(word) += 1;
    } else {
      wordcount_map[word] = 1;
    }
  }
  return wordcount_map;
}
```

### Exercise 2: `lookupWithFallback`

Given an `std::unordered_map<std::string, int>` and a `string` key, return its associated `int` value-map if the key exists, otherwise the default fallback value. Do not modify the map.

```c++
int lookupWithFallback(const StringIntMap& wordcount_map, const std::string& key, int fallbackVal) {

  StringIntMap::const_iterator found = wordcount_map.find(key);
  if (found == wordcount_map.end())
    return (fallbackVal);
  else
    return (found->second);

}
```

### Exercise 3: Memoizing a Function

`using LengthMemo = std::unordered_map<IntPair, int>`

`"xyzwDADxyzw"`
`IntPair: (0,10)`
`Value: 3`