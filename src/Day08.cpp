#include "Solution.hpp"
#include "io.hpp"
#include <regex>
#include <valarray>

template <>
void
solve<Day08>(bool part2, std::istream& is, std::ostream& os)
{
  uint                X{50}, Y{6}, x, y, d;
  const std::regex    rect{R"(rect (\d+)x(\d+))"}, row{R"(rotate row y=(\d+) by (\d+))"}, col{R"(rotate column x=(\d+) by (\d+))"};
  std::smatch         m;
  std::slice          i;
  std::valarray<bool> s(X * Y);
  for (auto l : io::by<io::line>(is)) {
    if (m = io::regex_parse(l, rect), !m.empty()) {
      x = std::stoi(m.str(1)), y = std::stoi(m.str(2));
      s[std::gslice{0, {y, x}, {X, 1}}] = true;
    } else if (m = io::regex_parse(l, row), !m.empty()) {
      y = std::stoi(m.str(1)), d = std::stoi(m.str(2)) % X, i = std::slice{X * y, X, 1};
      std::valarray<bool> o{s[i]};
      std::rotate(std::begin(o), std::end(o) - d, std::end(o));
      s[i] = o;
    } else if (m = io::regex_parse(l, col), !m.empty()) {
      x = std::stoi(m.str(1)), d = std::stoi(m.str(2)) % X, i = std::slice{x, Y, X};
      std::valarray<bool> o{s[i]};
      std::rotate(std::begin(o), std::end(o) - d, std::end(o));
      s[i] = o;
    }
  }
  if (part2)
    for (y = 0; os << std::endl, y < Y; ++y)
      for (x = 0; x < X; ++x)
        os << (s[y * X + x] ? '#' : ' ');
  else
    os << std::count(std::begin(s), std::end(s), true);
  os << std::endl;
}
