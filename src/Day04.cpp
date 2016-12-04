#include "Solution.hpp"
#include "io.hpp"
#include <map>
#include <set>

template <>
void
solve<Day04>(bool part2, std::istream& is, std::ostream& os)
{
  std::regex parse{R"(^([a-z-]+)-(\d+)\[([a-z]*)\]$)"};
  int sum{0}, sector;
  for (auto& line : io::by<io::line>(is)) {
    auto m = io::regex_parse(line, parse);
    std::string input{m.str(1)}, check{m.str(3)};
    sector = std::stoi(m.str(2));
    if (part2) {
      for (char &c : input)
        c = (c=='-') ? c : ((c - 'a' + sector) % 26) + 'a';
      if (input.find("north") != std::string::npos)
        break;
    } else {
      std::map<char, int> m;
      for (char c : input)
        if (c != '-')
          ++m[c];
      std::map<int, std::set<char>, std::greater<int>> s;
      for (auto _ : m)
        s[std::get<1>(_)].insert(std::get<0>(_));
      auto find = [&] {
        std::string c;
        for (const auto& _ : s)
          for (const auto& m : std::get<1>(_))
            if (c += m, c.size() == check.size())
              return (c == check);
        return false;
      };
      sum += find() * sector;
    }
  }
  os << (part2 ? sector : sum) << std::endl;
}
