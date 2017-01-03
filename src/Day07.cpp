#include "Solution.hpp"
#include <set>

bool
abba(const std::string& s)
{
  bool out{false}, in{false}, hyper{false};
  for (uint i{0}; i < s.size() - 3; ++i)
    if (hyper ^= (s[i] < 'a'), s[i] != s[i + 1] && s[i + 1] == s[i + 2] && s[i] == s[i + 3])
      in |= hyper, out |= !hyper;
  return out && !in;
}

bool
aba(const std::string& s)
{
  std::set<std::pair<char, char>> lookup[2];
  bool hyper{false};
  for (uint i{0}; i < s.size() - 2; ++i)
    if (hyper ^= (s[i] < 'a'), s[i] == s[i + 2] && s[i] != s[i + 1])
      lookup[hyper].emplace(s[i + hyper], s[i + !hyper]);
  for (const auto &ab : lookup[0])
    if (lookup[1].find(ab) != lookup[1].end())
      return true;
  return false;
}

template <>
void
solve<Day07>(bool part2, std::istream& is, std::ostream& os)
{
  int sum{0};
  for (std::string line; std::getline(is, line); )
    sum += (part2 ? aba: abba)(line);
  os << sum << std::endl;
}
