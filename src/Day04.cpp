#include "Solution.hpp"
#include <algorithm>
#include <vector>

template <>
void
solve<Day04>(bool part2, std::istream& is, std::ostream& os)
{
  int sum{0}, sector;
  for (std::string line; std::getline(is, line); ) {
    auto numLoc = std::find_if(line.begin(), line.end(), ::isdigit);
    auto checkLoc = ++std::find(numLoc, line.end(), '[');
    std::string input{line.begin(), numLoc - 1}, check{checkLoc, checkLoc + 5}, res;
    sector = ::atoi(&*numLoc);
    if (part2) {
      for (char &c : input)
        c = (c == '-') ? c : ((c - 'a' + sector) % 26) + 'a';
      if (input.find("north") != std::string::npos)
        break;
    } else {
      std::vector<std::pair<char, int>> s(26);
      for(int i{0}; i < 26; ++i)
        s[i] = {'a' + i, 0};
      for (char c : input)
        (c != '-') && ++s[c - 'a'].second;
      std::stable_sort(s.begin(), s.end(), [](auto p1, auto p2) {
        return p1.second > p2.second;
      });
      for (auto& p : s)
        res += p.first;
      sum += sector * !res.compare(0, check.size(), check);
    }
  }
  os << (part2 ? sector : sum) << std::endl;
}
