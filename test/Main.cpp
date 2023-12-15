#include <iostream>

#include "Map.hpp"
#include "Algorithm.hpp"
#include "Common.hpp"

int main() {

  Map m = Map(MapDefault, 19, 25);
  Graph g = Graph(m);

  std::cout << "Hello World\n";

  return 0;

}
