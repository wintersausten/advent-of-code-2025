#include "solve.hpp"

#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

struct Coord {
  int x;
  int y;
  int z;
};

struct DSU {
  std::vector<int> parent;
  std::vector<int> sz;
  DSU(int n) : parent(n), sz(n, 1) {
    for (int i = 0; i < n; ++i)
      parent[i] = i;
  }

  int find(int x) {
    if (parent[x] == x)
      return x;
    return parent[x] = find(parent[x]);
  }

  bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b)
      return false;

    if (sz[a] < sz[b])
      std::swap(a, b);
    parent[b] = a;
    sz[a] += sz[b];
    return true;
  }

  int size(int x) { return sz[find(x)]; }

  std::vector<int> set_sizes() {
    std::vector<int> sizes;
    for (int i = 0; i < sz.size(); i++)
      if (find(i) == i)
        sizes.push_back(sz[i]);
    return sizes;
  }
};

struct Pair {
  int i, j;
  long long d;
};

struct ByLargestDistance {
  bool operator()(const Pair &a, const Pair &b) const { return a.d < b.d; }
};

long long squared_distance(Coord &a, Coord &b) {
  long long dx{a.x - b.x}, dy{a.y - b.y}, dz{a.z - b.z};
  return dx * dx + dy * dy + dz * dz;
}

int solve1(std::istream &in) {
  std::string line;
  std::vector<Coord> coords;
  int x, y, z;
  char _;

  while (std::getline(in, line)) {
    std::stringstream ss(line);
    ss >> x >> _ >> y >> _ >> z;
    coords.push_back({x, y, z});
  }

  int n = static_cast<int>(coords.size());
  int k = 1000;

  std::priority_queue<Pair, std::vector<Pair>, ByLargestDistance> pq;

  // get k smallest distances
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      long long d = squared_distance(coords[i], coords[j]);
      if ((int)pq.size() < k) {
        pq.push({i, j, d});
      } else if (d < pq.top().d) {
        pq.pop();
        pq.push({i, j, d});
      }
    }
  }

  // sort smallest to largest
  std::vector<Pair> sorted_pairs;
  while (!pq.empty()) {
    sorted_pairs.push_back(pq.top());
    pq.pop();
  }
  std::reverse(sorted_pairs.begin(), sorted_pairs.end());

  // add all to the DSU
  DSU dsu(coords.size());
  for (int i = 0; i < k; i++) {
    Pair pair = sorted_pairs[i];
    if (dsu.find(pair.i) == dsu.find(pair.j)) {
      continue;
    }
    dsu.unite(pair.i, pair.j);
  }

  // sort the DSU sets, get 3 biggest
  std::vector<int> set_sizes = dsu.set_sizes();
  std::sort(set_sizes.begin(), set_sizes.end(), std::greater<int>());
  // multiply
  int result{1};
  for (int i = 0; i < 3; i++) {
    result *= set_sizes[i];
  }

  return result;
}

long long solve2(std::istream &in) {
  std::string line;
  std::vector<Coord> coords;
  int x, y, z;
  char _;

  while (std::getline(in, line)) {
    std::stringstream ss(line);
    ss >> x >> _ >> y >> _ >> z;
    coords.push_back({x, y, z});
  }

  int n = static_cast<int>(coords.size());

  std::priority_queue<Pair, std::vector<Pair>, ByLargestDistance> pq;

  // get k smallest distances
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      long long d = squared_distance(coords[i], coords[j]);
      pq.push({i, j, d});
    }
  }

  // sort smallest to largest
  std::vector<Pair> sorted_pairs;
  while (!pq.empty()) {
    sorted_pairs.push_back(pq.top());
    pq.pop();
  }
  std::reverse(sorted_pairs.begin(), sorted_pairs.end());

  // add all to the DSU
  DSU dsu(coords.size());
  for (const auto &pair : sorted_pairs) {
    if (dsu.find(pair.i) == dsu.find(pair.j)) {
      continue;
    }
    dsu.unite(pair.i, pair.j);
    if (dsu.size(pair.i) == n) {
      return 1LL * coords[pair.i].x * coords[pair.j].x;
    }
  }

  return -1;
}

Result solve(std::istream &in) {
  Result res{0, 0};
  res.part1 = solve1(in);
  in.clear();
  in.seekg(0);
  res.part2 = solve2(in);
  return res;
}
