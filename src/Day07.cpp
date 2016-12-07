#include "Solution.hpp"
#include "io.hpp"
#include <numeric>
#include <set>

int
abba(int val, const std::string& s)
{
  bool out{false}, in{false}, hyper{false};
  for (uint i{0}; i < s.size() - 3; ++i) {
    hyper ^= (s[i] < 'a');
    if (s[i] == s[i + 3] && s[i + 1] == s[i + 2] && s[i] != s[i + 1])
      in |= hyper, out |= !hyper;
  }
  return val + (out && !in);
}

int
aba(int val, const std::string& s)
{
  std::set<std::pair<char, char>> lookup[2];
  bool hyper{false};
  for (uint i{0}; i < s.size() - 2; ++i) {
    hyper ^= (s[i] < 'a');
    if (s[i] == s[i + 2] && s[i] != s[i + 1])
      lookup[hyper].emplace(s[i + hyper], s[i + !hyper]);
  }
  for (auto ab : lookup[0])
    if (lookup[1].find(ab) != lookup[1].end())
      return val + 1;
  return val;
}

template <>
void
solve<Day07>(bool part2, std::istream& is, std::ostream& os)
{
  os << std::accumulate(io::as<io::line>(is), {}, 0, (part2 ? aba : abba)) << std::endl;
}
