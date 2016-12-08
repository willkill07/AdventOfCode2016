#include "Solution.hpp"
#include <algorithm>
#include <numeric>
#include <regex>
#include <unordered_map>
#include <valarray>

const static std::unordered_map<std::uint32_t, char> OCR{{
  {0x19297A52, 'a'}, {0x392E4A5C, 'b'}, {0x1928424C, 'c'}, {0x39294A5C, 'd'}, {0x3D0E421E, 'e'},
  {0x3D0E4210, 'f'}, {0x19285A4E, 'g'}, {0x252F4A52, 'h'}, {0x1C42108E, 'i'}, {0x0C210A4C, 'j'},
  {0x254C5292, 'k'}, {0x2108421E, 'l'}, {0x19294A4C, 'o'}, {0x39297210, 'p'}, {0x39297292, 'r'},
  {0x1D08305C, 's'}, {0x1C421084, 't'}, {0x25294A4C, 'u'}, {0x23151084, 'y'}, {0x3C22221E, 'z'}
}};

template <>
void
solve<Day08>(bool part2, std::istream& is, std::ostream& os)
{
  const std::uint32_t X{50}, Y{6}, W{5};
  const std::regex rect{R"(^rect (\d+)x(\d+))"}, row{R"(^rotate row y=(\d+) by (\d+))"}, col{R"(^rotate column x=(\d+) by (\d+))"};
  std::valarray<bool> s(X * Y);
  for (std::string line; std::getline(is, line);) {
    std::smatch m;
    if (std::regex_search(line, m, rect)) {
      std::uint32_t x(std::stoi(m.str(1))), y(std::stoi(m.str(2)));
      s[std::gslice{0, {y, x}, {X, 1}}] = true;
    } else if (std::regex_search(line, m, row)) {
      std::uint32_t y(std::stoi(m.str(1))), d(std::stoi(m.str(2)) % X);
      std::slice idx{X * y, X, 1};
      std::valarray<bool> r{s[idx]};
      std::rotate(std::begin(r), std::end(r) - d, std::end(r));
      s[idx] = r;
    } else if (std::regex_search(line, m, col)) {
      std::uint32_t x(std::stoi(m.str(1))), d(std::stoi(m.str(2)) % X);
      std::slice idx{x, Y, X};
      std::valarray<bool> c{s[idx]};
      std::rotate(std::begin(c), std::end(c) - d, std::end(c));
      s[idx] = c;
    }
  }
  if (part2) {
    for (std::uint32_t i{0}; i < X / W; ++i) {
      std::uint32_t j{W * Y - 1}, val{0};
      for (bool v : std::valarray<bool>{s[std::gslice{i * W, {Y, W}, {X, 1}}]})
        val |= (v << j--);
      os << OCR.at(val);
    }
  } else {
    os << std::accumulate(std::begin(s), std::end(s), 0);
  }
  os << std::endl;
}
