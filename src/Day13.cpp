#include "Solution.hpp"
#include "io.hpp"
#include <array>
#include <map>
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
    return p[0] >= 0 && p[1] >= 0 && !(__builtin_popcount(NUM + p[1] * p[1] + 3 * p[1] + 2 * p[1] * p[0] + p[0] + p[0] * p[0]) & 0x1);
  };
  std::set<Point> queue{{INIT}};
  std::map<Point, int> dist{{INIT, 0}};
  while (queue.size() != 0 && (part2 || dist.find(TARGET) == dist.end())) {
    std::set<Point> next;
    for (const auto& q : queue)
      for (const auto& d : DIRS)
        if (valid(q + d) && dist.find(q + d) == dist.end() && (!part2 || dist.at(q) < LIMIT))
          next.insert(q + d), dist.emplace(q + d, dist.at(q) + 1);
    std::swap(queue, next);
  }
  os << (part2 ? dist.size() : dist.at(TARGET)) << std::endl;
}
