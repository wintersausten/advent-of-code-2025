#include "solve.hpp"

#include <iostream>
#include <ranges>
#include <sstream>
#include <string>

long long solve1(std::istream &in) {
  long long result{0};
  std::vector<std::string> lines;
  std::string line;

  while (std::getline(in, line)) {
    lines.push_back(line);
  }

  auto last_line = lines.back();
  std::stringstream iss(last_line);
  std::vector<char> ops;
  char op;
  while (iss >> op) {
    ops.push_back(op);
  }

  std::vector<std::vector<long long>> value_matrix;
  auto all_but_last = lines | std::views::take(lines.size() - 1);
  for (auto &row : all_but_last) {
    std::stringstream iss(row);
    std::vector<long long> values;
    long long value;
    while (iss >> value) {
      values.push_back(value);
    }
    value_matrix.push_back(values);
  }

  int n{static_cast<int>(value_matrix.size())},
      m{static_cast<int>(value_matrix[0].size())};

  for (int col = 0; col < m; col++) {
    auto op = ops[col];
    auto op_func = op == '+' ? [](long long a, long long b) { return a + b; }
                             : [](long long a, long long b) { return a * b; };
    long long col_result{value_matrix[0][col]};
    for (int row = 1; row < n; row++) {
      col_result = op_func(col_result, value_matrix[row][col]);
    }
    result += col_result;
  }

  return result;
}

long long pow10(long long n) {
  long long x = 1;
  while (n--)
    x *= 10;
  return x;
}

long long solve2(std::istream &in) {
  long long result{0};

  std::vector<std::string> lines;
  std::string line;

  while (std::getline(in, line)) {
    lines.push_back(line);
  }

  auto last_line = lines.back();
  auto rows = lines | std::views::take(lines.size() - 1) | std::views::reverse;

  size_t op_pos = last_line.find_first_of("*+");
  while (op_pos != std::string::npos) {
    char op = last_line[op_pos];
    size_t next_op = last_line.find_first_of("*+", op_pos + 1);
    size_t start_pos =
        (next_op == std::string::npos) ? last_line.size() : next_op - 1;

    auto op_func = op == '+' ? [](long long a, long long b) { return a + b; }
                             : [](long long a, long long b) { return a * b; };

    long long sub_result = op == '+' ? 0LL : 1LL;
    for (size_t col :
         std::views::iota(op_pos, start_pos) | std::views::reverse) {
      long long row_result{0};
      int ten_mult{0};
      for (auto &row : rows) {
        if (row[col] != ' ') {
          int digit = row[col] - '0';
          row_result += digit * pow10(ten_mult);
          ten_mult++;
        }
      }
      sub_result = op_func(sub_result, row_result);
    }

    result += sub_result;
    op_pos = next_op;
  }

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
