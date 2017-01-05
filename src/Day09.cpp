#include "Solution.hpp"

long
decode(std::string::const_iterator s0, std::string::const_iterator s1, bool part2)
{
  auto i1 = s0;
  while (i1 != s1 && *i1 != '(')
    ++i1;
  if (i1 == s1)
    return std::distance(s0, s1);
  auto i0 = i1;
  int  l{0}, r{0};
  while (*++i1 != 'x')
    l *= 10, l += (*i1 - '0');
  while (*++i1 != ')')
    r *= 10, r += (*i1 - '0');
  auto s = ++i1 + l;
  return std::distance(s0, i0) + r * (part2 ? decode(i1, s, true) : std::distance(i1, s)) + decode(s, s1, part2);
}

template <>
void
solve<Day09>(bool part2, std::istream& is, std::ostream& os)
{
  std::string input;
  is >> input;
  os << decode(input.begin(), input.end(), part2) << std::endl;
}
