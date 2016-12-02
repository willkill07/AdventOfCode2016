#include "Solution.hpp"
#include <algorithm>
#include <initializer_list>
#include <type_traits>
#include <utility>

template <int R, int C>
struct Pad {
  constexpr static const int Rows{R};
  constexpr static const int Cols{C};
  char btns[R][C];

  Pad(std::initializer_list<char>&& l)
  {
    std::copy(l.begin(), l.end(), &btns[0][0]);
  }
};

const Pad<3, 3> P1{'1', '2', '3', '4', '5', '6', '7', '8', '9'};
const Pad<5, 5> P2{' ', ' ', '1', ' ', ' ', ' ', '2', '3', '4', ' ', '5', '6', '7', '8', '9', ' ', 'A', 'B', 'C', ' ', ' ', ' ', 'D', ' ', ' '};

template <>
void
solve<Day02>(bool part2, std::istream& is, std::ostream& os)
{
  auto clamp = [] (auto value, auto min, auto max) {
    return std::max(min, std::min(max, value));
  };
  auto runner = [&] (auto& pad, int x, int y) {
    using PadT = std::decay_t<decltype(pad)>;
    for (std::string line; std::getline(is, line); os << pad.btns[y][x])
      for (char d : line) {
        int y1 = clamp(y + (d == 'D') - (d == 'U'), 0, PadT::Rows - 1);
        int x1 = clamp(x + (d == 'R') - (d == 'L'), 0, PadT::Cols - 1);
        if (pad.btns[y1][x1] != ' ')
          y = y1, x = x1;
      }
  };
  part2 ? runner(P2, 0, 2) : runner(P1, 1, 1);
  os << std::endl;
}
