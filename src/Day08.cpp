#include "Solution.hpp"
#include "io.hpp"
#include <regex>
#include <valarray>

using Pixels = std::valarray<bool>;

template <>
void
solve<Day08>(bool part2, std::istream& is, std::ostream& os)
{
  const uint64_t   X{50UL}, Y{6};
  const std::regex rect{R"(rect (\d+)x(\d+))"}, row{R"(rotate row y=(\d+) by (\d+))"}, col{R"(rotate column x=(\d+) by (\d+))"};
  std::smatch      m;
  Pixels           s(X * Y);
  for (auto l : io::by<io::line>(is)) {
    if (m = io::regex_parse(l, rect), !m.empty()) {
      uint64_t x{std::stoul(m.str(1))}, y{std::stoul(m.str(2))};
      s[std::gslice(0, {y, x}, {X, 1})] = true;
    } else if (m = io::regex_parse(l, row), !m.empty()) {
      uint64_t y{std::stoul(m.str(1))}, d{std::stoul(m.str(2)) % X};
      auto     i{std::slice(X * y, X, 1)};
      Pixels   o{s[i]};
      std::rotate(std::begin(o), std::end(o) - d, std::end(o));
      s[i] = o;
    } else if (m = io::regex_parse(l, col), !m.empty()) {
      uint64_t x{std::stoul(m.str(1))}, d{std::stoul(m.str(2)) % Y};
      auto     i{std::slice(x, Y, X)};
      Pixels   o{s[i]};
      std::rotate(std::begin(o), std::end(o) - d, std::end(o));
      s[i] = o;
    }
  }
  if (part2)
    for (uint y{0}; os << std::endl, y < Y; ++y)
      for (uint x{0}; x < X; ++x)
        os << (s[y * X + x] ? '#' : ' ');
  else
    os << std::count(std::begin(s), std::end(s), true);
  os << std::endl;
}
