#include "Solution.hpp"
#include <algorithm>
#include <vector>

template <>
void
solve<Day18>(bool part2, std::istream& is, std::ostream& os)
{
  std::vector<uint8_t> a;
  a.emplace_back(false);
  std::transform(std::istream_iterator<uint8_t>(is), {}, std::back_inserter(a), [](uint8_t c) { return c == '^'; });
  a.emplace_back(false);
  std::vector<uint8_t> b(a.size());
  uint64_t safe(std::count(a.begin() + 1, a.end() - 1, false)), limit{part2 ? 400000U : 40U};
  for (uint i{1}; i < limit; ++i) {
    for (uint j{1}; j < a.size() - 1; ++j)
      b[j] = a[j - 1] ^ a[j + 1];
    safe += std::count(b.begin() + 1, b.end() - 1, false);
    a.swap(b);
  }
  os << safe << ' ' << std::endl;
}
