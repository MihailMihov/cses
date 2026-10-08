#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

int32_t main() {
  size_t n;
  std::cin >> n;

  std::vector<int32_t> x(n);
  for (auto& xi : x) std::cin >> xi;

  std::vector<std::vector<int64_t>> mem(n, std::vector<int64_t>(n));
  for (size_t l = 1z; l <= n; ++l) {
    for (size_t i = 0z; i <= n - l; ++i) {
      size_t j = i + l - 1;
      mem[i][j] = std::max(
          x[i] + std::min(i + 2 < n ? mem[i + 2][j] : 0,
                          i + 1 < n && j >= 1 ? mem[i + 1][j - 1] : 0),
          x[j] + std::min(j >= 2 ? mem[i][j - 2] : 0,
                          i + 1 < n && j >= 1 ? mem[i + 1][j - 1] : 0));
    }
  }

  std::cout << mem[0][n - 1] << '\n';

  return 0;
}
