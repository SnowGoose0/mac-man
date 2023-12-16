#include <iostream>

#include "Map.hpp"
#include "Algorithm.hpp"
#include "Common.hpp"

int main() {

  Map m = Map(MapDefault, 19, 25);
  Graph g = Graph(m);

  std::vector<Point> v = g.computePath(1,1,4,1);

  std::cout << "The Path Is" << std::endl;

  for (auto it = v.begin(); it != v.end(); it++) {
	std::cout << "(" << (*it).x << ", " << (*it).y << ")" << std::endl;
  }

  return 0;

}
