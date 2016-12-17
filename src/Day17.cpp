#include "Solution.hpp"
#include "io.hpp"
#include "md5.hpp"
#include <array>
#include <list>

using Point = std::array<int, 2>;

inline Point
operator+(const Point& p1, const Point& p2)
{
  return {{std::get<0>(p1) + std::get<0>(p2), std::get<1>(p1) + std::get<1>(p2)}};
}

inline bool
inRange(const Point& p, const Point&& low, const Point&& high)
{
  return p[0] >= low[0] && p[0] <= high[0] && p[1] >= low[1] && p[1] <= high[1];
}

struct State {
  Point       point{{0, 0}};
  std::string path{};
};

template <>
void
solve<Day17>(bool part2, std::istream& is, std::ostream& os)
{
  const std::array<State, 4> DIRS{{{{{-1, 0}}, "U"}, {{{1, 0}}, "D"}, {{{0, -1}}, "L"}, {{{0, 1}}, "R"}}};
  std::string prefix; prefix.reserve(1000); is >> prefix;
  md5str_t         hash;
  std::list<State> queue, found;
  for (queue.push_back(State{}); queue.size() != 0 && (part2 || found.size() == 0); queue.pop_front()) {
    const auto& curr = queue.front();
    std::copy(curr.path.begin(), curr.path.end(), prefix.end());
    md5str((uint8_t*)prefix.data(), prefix.size() + curr.path.size(), &hash);
    for (uint i{0}; i < 4; ++i) {
      if (hash.c[i] > 'a') {
        State toAdd{curr.point + DIRS[i].point, curr.path + DIRS[i].path};
        if (inRange(toAdd.point, Point{{0, 0}}, Point{{3, 3}}))
          (toAdd.point == Point{{3, 3}} ? found : queue).emplace_back(toAdd);
      }
    }
  }
  os << (part2 ? std::to_string(found.back().path.size()) : found.front().path) << std::endl;
}
