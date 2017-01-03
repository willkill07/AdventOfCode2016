#include "Solution.hpp"
#include <unordered_map>
#include <valarray>

static const std::unordered_map<uint, char> OCR{
{{0x19297A52, 'a'}, {0x392E4A5C, 'b'}, {0x1928424C, 'c'}, {0x39294A5C, 'd'}, {0x3D0E421E, 'e'}, {0x3D0E4210, 'f'}, {0x19285A4E, 'g'},
 {0x252F4A52, 'h'}, {0x1C42108E, 'i'}, {0x0C210A4C, 'j'}, {0x254C5292, 'k'}, {0x2108421E, 'l'}, {0x23BAC631, 'm'}, {0x252D5A52, 'n'},
 {0x19294A4C, 'o'}, {0x39297210, 'p'}, {0x19295A4D, 'q'}, {0x39297292, 'r'}, {0x1D08305C, 's'}, {0x1C421084, 't'}, {0x25294A4C, 'u'},
 {0x2318A944, 'v'}, {0x231AD6AA, 'w'}, {0x22A22951, 'x'}, {0x23151084, 'y'}, {0x3C22221E, 'z'}, {0x00000000, ' '}}};

template <>
void
solve<Day08>(bool part2, std::istream& is, std::ostream& os)
{
  const unsigned int X{50}, Y{6}, W{5};
  std::valarray<int> s(X * Y);
  auto slice = [X, Y](char type, unsigned int idx) { return (type == 'y') ? std::slice{X * idx, X, 1} : std::slice{idx, Y, X}; };
  for (std::string line; std::getline(is, line);) {
    char         c;
    unsigned int a, b;
    sscanf(line.c_str(), "rotate %*s %c=%d by %d", &c, &a, &b) || sscanf(line.c_str(), "%c%*s %dx%d", &c, &a, &b);
    if (c == 'r')
      s[std::gslice{0, {b, a}, {X, 1}}] = 1;
    else
      s[slice(c, a)] = std::valarray<int>{s[slice(c, a)]}.cshift(-b);
  }
  if (!part2)
    os << s.sum();
  else
    for (unsigned int i{0}; i < X / W; ++i) {
      unsigned int j{W * Y - 1}, val{0};
      for (const auto v : std::valarray<int>{s[std::gslice{i * W, {Y, W}, {X, 1}}]})
        val |= (v << j--);
      os << OCR.at(val);
    }
  os << std::endl;
}
