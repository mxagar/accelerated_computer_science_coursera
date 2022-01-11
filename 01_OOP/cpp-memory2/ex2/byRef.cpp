/**
 * C++ program sending a Cube by reference.
 * 
 * @author
 *   Wade Fagen-Ulmschneider <waf@illinois.edu>
 */

#include "../Cube.h"
#include <iostream>

using uiuc::Cube;

bool sendCube(Cube & c) {    
  // ... logic to send a Cube somewhere ...
  return true;
}

int main() {
  // Create a 1,000-valued cube
  Cube c(10);

  // Send the cube to someone
  sendCube(c);

  // Effect: we pass a reference, an alias, no copies are made!

  return 0;
}
