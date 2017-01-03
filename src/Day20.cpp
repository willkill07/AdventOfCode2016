#include "Solution.hpp"
#include <set>
#include <utility>
#include <vector>

template <>
void
solve<Day20>(bool part2, std::istream& is, std::ostream& os)
{
  std::vector<std::pair<int64_t, int64_t>> data;
  for (std::string line; std::getline(is, line);) {
    uint64_t a, b;
    sscanf(line.c_str(), "%llu-%llu", &a, &b);
    data.emplace_back(a, b);
  }
  std::sort(data.begin(), data.end());
  int64_t MAX{4294967295}, total{0}, last{-1}, first{-1};
  for (const auto& d : data) {
    int64_t c{std::max(int64_t{0}, d.first - last - 1)};
    if (!part2 && first == -1 && c)
      first = last + 1;
    if (part2)
      total += c;
    last = std::max(last, d.second);
  }
  total += std::max(int64_t{0}, MAX - last);
  os << (part2 ? total : first) << std::endl;
}
