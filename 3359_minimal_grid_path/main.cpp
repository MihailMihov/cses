#include <iostream>
#include <vector>

int main() {
  size_t n;
  std::cin >> n;

  std::vector<std::string> grid(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> grid[i];
  }

  std::vector<std::vector<std::string>> mem(
      n + 1, std::vector<std::string>(n + 1, "Z"));
  mem[n - 1][n - 1] = grid[n - 1][n - 1];
  for (ssize_t i = n - 1; i >= 0; --i) {
    for (ssize_t j = n - 1; j >= 0; --j) {
      mem[i][j] = grid[i][j] + std::min(mem[i + 1][j], mem[i][j + 1]);
    }
  }

  std::string result = mem[0][0];
  result.pop_back();

  std::cout << result << std::endl;

  return 0;
}
