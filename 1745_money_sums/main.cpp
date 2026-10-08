#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

int main() {
  int32_t n;
  std::cin >> n;

  std::vector<int32_t> coins(n);
  for (auto& ci : coins) {
    std::cin >> ci;
  }

  std::set<int64_t> sums;
  sums.insert(0);

  for (const auto ci : coins) {
    std::set<int64_t> new_sums;
    for (const auto sum : sums) {
      new_sums.insert(sum + ci);
    }

    sums.merge(new_sums);
  }

  sums.erase(sums.find(0));

  std::cout << sums.size() << '\n';
  std::copy(sums.begin(), sums.end(),
            std::ostream_iterator<int64_t>(std::cout, " "));
  std::cout << '\n';

  return 0;
}
