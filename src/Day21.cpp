#include "Solution.hpp"
#include "io.hpp"
#include <algorithm>

const std::regex SWAP{R"(swap (\S+)\S+ (\S+) with \S+ (\S+))", std::regex::optimize},
  ROTI{R"(rotate (\w+) (\d+) steps?)", std::regex::optimize},
  ROTL{R"(rotate based on position of letter (\w))", std::regex::optimize},
  MOVP{R"(move position (\d+) to position (\d+))", std::regex::optimize},
  REVP{R"(reverse positions (\d+) through (\d+))", std::regex::optimize};

template <>
void
solve<Day21>(bool part2, std::istream& is, std::ostream& os)
{
  std::string pass{part2 ? "fbgdceah" : "abcdefgh"};
  std::smatch m;
  auto to_char = [&m](int i) { return m.str(i)[0]; };
  auto to_int = [&m](int i) { return std::stoi(m.str(i)); };
  std::vector<std::string> input{io::as<io::line>(is), {}};
  for (const auto& line : (part2 ? io::reverser(input) : input)) {
    if (std::regex_match(line, m, SWAP)) { // reversible
      auto rev = [&](int i) { return (to_char(1) == 'l') ? pass.find(to_char(i)) : to_int(i); };
      std::swap(pass[rev(2)], pass[rev(3)]);
    } else if (std::regex_match(line, m, ROTI)) {
      int steps{to_int(2)}, dir(to_char(1) ^ (part2 * ('l' ^ 'r')));
      std::rotate(pass.begin(), (dir == 'l') ? pass.begin() + steps : pass.end() - steps, pass.end());
    } else if (std::regex_match(line, m, ROTL)) {
      int i(pass.find(to_char(1))), rot{(part2 ? (i / 2 + (i % 2 || !i ? 1 : 5)) : (i + 1 + (i >= 4 ? 1 : 0))) % int(pass.size())};
      std::rotate(pass.begin(), part2 ? pass.begin() + rot : pass.end() - rot, pass.end());
    } else if (std::regex_match(line, m, MOVP)) {
      int p0{to_int(1)}, p1{to_int(2)};
      std::swap(p0, part2 ? p1 : p0);
      char letter{pass[p0]};
      pass.erase(p0, 1), pass.insert(p1, 1, letter);
    } else if (std::regex_match(line, m, REVP)) { // reversible
      std::reverse(pass.begin() + to_int(1), pass.begin() + to_int(2) + 1);
    }
  }
  os << pass << std::endl;
}
