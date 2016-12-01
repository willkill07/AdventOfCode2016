#include "Solution.hpp"
#include <cmath>
#include <set>

template <>
void
solve<Day01>(bool part2, std::istream& is, std::ostream& os)
{
  std::set<std::pair<int, int>> visited;
  int  index{1}, x{0}, y{0}, dist;
  char d;
  for (; is >> d >> dist; is.ignore(1, ',')) {
    // wrap-around turning; implicit direction order is E,N,W,S
    index = (index + 4 + ((d == 'R') ? -1 : 1)) % 4;
    int  sign = (index & 0b10) ? -1 : 1;
    int& face = (index & 0b01) ? y : x;
    for (int i{0}; i < dist; ++i) {
      face += sign;
      if (part2 && !visited.emplace(x, y).second) {
        os << (std::abs(x) + std::abs(y)) << std::endl;
        return;
      }
    }
  }
  os << (std::abs(x) + std::abs(y)) << std::endl;
}
