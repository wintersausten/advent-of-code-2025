#include "solve.hpp"

#include <filesystem>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

void add_beam(std::unordered_set<size_t> &beams, size_t pos, size_t n) {
  if (0 <= pos && pos < n) {
    beams.insert(pos);
  }
}

long long solve1(std::istream &in) {
  long long result{0};

  std::string line;
  std::getline(in, line);

  size_t start_pos = line.find('S');

  std::unordered_set<size_t> active_beams{start_pos};
  while (std::getline(in, line)) {
    std::unordered_set<size_t> frozen_active_beams = active_beams;
    size_t n = line.size();

    for (size_t i = 0; i < line.size(); i++) {
      if (frozen_active_beams.count(i) == 1 && line[i] == '^') {
        result += 1;
        add_beam(active_beams, i + 1, n);
        add_beam(active_beams, i - 1, n);
        active_beams.erase(i);
      }
    }
  }

  return result;
}

using Grid = std::vector<std::vector<bool>>;
using MemoGrid = std::vector<std::vector<long long>>;

long long backtrack(const Grid &splitter_matrix, int n, int m, int row_pos,
                    int col_pos, MemoGrid &memo) {
  if (col_pos < 0 || col_pos >= m) {
    return 0;
  }
  if (row_pos == n) {
    return 1;
  }
  if (memo[row_pos][col_pos] != -1) {
    return memo[row_pos][col_pos];
  }

  long long result{0LL};
  if (splitter_matrix[row_pos][col_pos]) {
    result += backtrack(splitter_matrix, n, m, row_pos + 1, col_pos - 1, memo);
    result += backtrack(splitter_matrix, n, m, row_pos + 1, col_pos + 1, memo);
  } else {
    result = backtrack(splitter_matrix, n, m, row_pos + 1, col_pos, memo);
  }
  memo[row_pos][col_pos] = result;
  return result;
}

long long solve2(std::istream &in) {
  Grid splitter_matrix;

  std::string line;
  std::getline(in, line);

  size_t start_pos = line.find('S');

  while (std::getline(in, line)) {
    std::vector<bool> splitter_row;
    for (auto c : line) {
      splitter_row.push_back(c == '^');
    }
    splitter_matrix.push_back(splitter_row);
  }

  int n{static_cast<int>(splitter_matrix.size())},
      m{static_cast<int>(splitter_matrix[0].size())};
  MemoGrid memo;
  memo.assign(n, std::vector<long long>(m, -1));

  return backtrack(splitter_matrix, n, m, 1, start_pos, memo);
}

Result solve(std::istream &in) {
  Result res{0, 0};
  res.part1 = solve1(in);
  in.clear();
  in.seekg(0);
  res.part2 = solve2(in);
  return res;
}
