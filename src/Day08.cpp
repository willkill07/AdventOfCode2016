#include "Solution.hpp"
#include <algorithm>
#include <numeric>
#include <regex>
#include <unordered_map>
#include <valarray>

const static std::unordered_map<uint, char> OCR {{
  {0x0C210A4C, 'j'}, {0x1928424C, 'c'}, {0x19285A4E, 'g'}, {0x19294A4C, 'o'}, {0x19297A52, 'a'},
  {0x1C421084, 't'}, {0x1C42108E, 'i'}, {0x1D08305C, 's'}, {0x2108421E, 'l'}, {0x23151084, 'y'},
  {0x25294A4C, 'u'}, {0x252F4A52, 'h'}, {0x254C5292, 'k'}, {0x39294A5C, 'd'}, {0x39297210, 'p'},
  {0x39297292, 'r'}, {0x392E4A5C, 'b'}, {0x3C22221E, 'z'}, {0x3D0E4210, 'f'}, {0x3D0E421E, 'e'}
}};

template <>
void
solve<Day08>(bool part2, std::istream& is, std::ostream& os)
{
  const uint X{50}, Y{6}, W{5};
  const std::regex rect{R"(^(r)ect (\d+)x(\d+))"}, row{R"(^rotate row (y)=(\d+) by (\d+))"}, col{R"(^rotate column (x)=(\d+) by (\d+))"};
  std::valarray<int> s(X * Y);
  auto slice = [X,Y](char type, uint idx) {
    return (type == 'y') ? std::slice{X * idx, X, 1} : std::slice{idx, Y, X};
  };
  for (std::string line; std::getline(is, line);) {
    std::smatch m;
    std::regex_search(line, m, rect) || std::regex_search(line, m, row) || std::regex_search(line, m, col);
    char c{m.str(1).at(0)};
    uint a(std::stoi(m.str(2))), b(std::stoi(m.str(3)));
    if (c == 'r')
      s[std::gslice{0, {b, a}, {X, 1}}] = 1;
    else
      s[slice(c, a)] = std::valarray<int>{s[slice(c, a)]}.cshift(-b);
  }
  if (!part2)
    os << s.sum();
  else
    for (std::uint32_t i{0}; i < X / W; ++i) {
      std::uint32_t j{W * Y - 1}, val{0};
      for (auto v : std::valarray<int>{s[std::gslice{i * W, {Y, W}, {X, 1}}]})
        val |= (v << j--);
      os << OCR.at(val);
    }
  os << std::endl;
}
