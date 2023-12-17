#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <unordered_set>

#include "Common.hpp"

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
  Node* parent;

  int f() const {
	return g + h;
  }

  bool operator>(const Node& n) const {
	return f() > n.f();
  }

  bool operator<(const Node& n) const {
	return f() < n.f();
  }

  bool operator==(const Node& n) const {
	return p == n.p;
  }
};

struct NodeComparator {
  bool operator()(const Node* lhs, const Node* rhs) const {
	return lhs->f() > rhs->f();
  }
};
  
// class Graph {
// public:
//   static const int width = 19;
//   static const int height = 21;
  
//   Graph(Map& m);
//   ~Graph();

//   std::vector<Point> computePath(int x1, int y1, int x2, int y2);
//   std::vector<Point> computePath(sf::Vector2f& start, sf::Vector2f& end);

// private:
//   std::vector<Point> aStar(Point& start, Point& end);
  
//   bool traversable(const Point& p);

//   int heuristic(const Point& p1, const Point& p2);

//   std::vector<Point> getNeighbors(const Node& node);

//   void freeNodeList(std::vector<Node*> list);

// private:
//   std::array<std::array<GameCell, width>, height> _graph;
// };

namespace std {
  template <>
  struct hash<Node> {
	size_t operator()(const Node& n) const {
	  return hash<int>()(n.p.x) & hash<int>()(n.p.y);
	}
  };
}
