#include "solve.hpp"

#include <iostream>
#include <string>

int sum_surrounding(int x, int y, std::vector<std::vector<bool>> grid) {
  int sum{0};
  int m{static_cast<int>(grid.size())}, n{static_cast<int>(grid[0].size())};
  for (int dy = -1; dy <= 1; dy++) {
    for (int dx = -1; dx <= 1; dx++) {
      if (dy == 0 && dx == 0) {
        continue;
      }

      int i = x + dx;
      int j = y + dy;

      if (i < 0 || i >= m || j < 0 || j >= n) {
        continue;
      }

      sum += grid[i][j];
    }
  }
  return sum;
}

int solve1(std::istream &in) {
  int result{0};

  std::vector<std::vector<bool>> grid;

  std::string line;
  while (std::getline(in, line)) {
    std::vector<bool> row;
    for (char c : line) {
      row.push_back(c == '@');
    }
    grid.push_back(row);
  }

  int m{static_cast<int>(grid.size())}, n{static_cast<int>(grid[0].size())};
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] && sum_surrounding(i, j, grid) < 4) {
        result++;
      }
    }
  }

  return result;
}

long long solve2(std::istream &in) {
  int result{0};

  std::vector<std::vector<bool>> grid;

  std::string line;
  while (std::getline(in, line)) {
    std::vector<bool> row;
    for (char c : line) {
      row.push_back(c == '@');
    }
    grid.push_back(row);
  }

  int m{static_cast<int>(grid.size())}, n{static_cast<int>(grid[0].size())};
  int remove_count;
  do {
    remove_count = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] && sum_surrounding(i, j, grid) < 4) {
          result++;
          grid[i][j] = false;
          remove_count++;
        }
      }
    }
  } while (remove_count > 0);

  return result;
}

Result solve(std::istream &in) {
  Result res{0, 0};
  res.part1 = solve1(in);
  in.clear();
  in.seekg(0);
  res.part2 = solve2(in);
  return res;
}
