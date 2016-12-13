#include "Solution.hpp"
#include "io.hpp"
#include <array>
#include <set>

using Point = std::array<int, 2>;

inline Point
operator+(const Point& p1, const Point& p2)
{
  return {{std::get<0>(p1) + std::get<0>(p2), std::get<1>(p1) + std::get<1>(p2)}};
}

template <>
void
solve<Day13>(bool part2, std::istream& is, std::ostream& os)
{
  const int LIMIT{50}, NUM{std::stoi(io::as_string(is))};
  const std::array<Point, 4> DIRS{{{{-1, 0}}, {{1, 0}}, {{0, -1}}, {{0, 1}}}};
  const Point INIT{{1, 1}}, TARGET{{39, 31}};
  auto valid = [NUM](const Point& p) -> bool {
    return p[1] >= 0 && p[0] >= 0 && !(__builtin_popcount(p[1] * (p[1] + 3) + p[0] * (p[1] + p[1] + p[0] + 1) + NUM) & 0x1);
  };
  int steps{0};
  std::set<Point> queue{{INIT}}, seen{queue}, next;
  while (queue.size() != 0 && (part2 || !seen.count(TARGET)) && (!part2 || steps != LIMIT)) {
    for (const auto& q : queue)
      for (const auto& d : DIRS)
        if (valid(q + d) && !seen.count(q + d))
          next.emplace(q + d), seen.emplace(q + d);
    next.swap(queue), next.clear(), ++steps;
  }
  os << (part2 ? seen.size() : steps) << std::endl;
}
