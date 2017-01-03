#include "Solution.hpp"
#include <cstring>

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
  static bool look[2][26][26];
  ::memset(look, 0, sizeof(bool) * 2 * 26 * 26);
  bool hyper{false};
  for (uint i{0}; i < s.size() - 2; ++i)
    if (hyper ^= (s[i] < 'a'), s[i] == s[i + 2] && s[i] != s[i + 1]) {
      int c1{s[i + hyper] - 'a'}, c2{s[i + !hyper] - 'a'};
      look[hyper][c1][c2] = true;
      if (look[!hyper][c1][c2])
        return true;
    }
  return false;
}

template <>
void
solve<Day07>(bool part2, std::istream& is, std::ostream& os)
{
  int sum{0};
  for (std::string line; std::getline(is, line);)
    sum += (part2 ? aba : abba)(line);
  os << sum << std::endl;
}
