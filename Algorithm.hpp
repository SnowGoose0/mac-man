#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>

struct Point {
  int x;
  int y;

  bool operator==(const Point& p) const {
	return x == p.x && y == p.y;
  }

  // manhattan distance
  int operator-(const Point& p) const {
	return std::abs(x - p.x) + std::abs(y - p.y);
  }
};

struct Node {
  Point p;
  int g, h;

  int f() const {
	return g + h;
  }

  bool operator>(const Node& n) const {
	return f() > p.f();
  }
};

namespace std {
  template <>
  struct hash<Point> {
	size_t operator()(const Point& p) const {
	  return hash<int>()(p.x) & hash<int>()(p.y);
	}
  }
}

int heuristic(const Point& p1, const Point& p2) { 
  return p2 - p1;
}


	
