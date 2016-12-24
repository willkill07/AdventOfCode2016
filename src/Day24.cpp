#include "Solution.hpp"
#include "io.hpp"
#include <algorithm>
#include <array>
#include <map>
#include <numeric>
#include <set>

using Point = std::pair<int, int>;
static const std::array<Point, 4> DIRS{{{0, 1}, {0, -1}, {-1, 0}, {1, 0}}};

Point
operator+(const Point& p1, const Point& p2)
{
  return {p1.first + p2.first, p1.second + p2.second};
}

template <>
void
solve<Day24>(bool part2, std::istream& is, std::ostream& os)
{
  std::array<std::array<char, 181>, 43> maze;
  std::map<int, Point> locsByIndex;
  std::map<Point, int> locsByPoint;
  int   x{0}, y{0};
  char* data{&maze[0][0]};
  for (char c : io::by<char>(is)) {
    if (c != '.' && c != '#') {
      locsByIndex[c - '0'] = {y, x};
      locsByPoint[{y, x}] = c - '0';
    }
    *data++ = c;
    if (++x == 181)
      x = 0, ++y;
  }

  std::map<std::pair<int, int>, int> dist;
  for (int i0{0}; i0 < 8; ++i0)
    for (int i1{i0 + 1}; i1 < 8; ++i1)
      if (dist.find({i0, i1}) == dist.end()) {
        int             steps{1};
        const Point &   START{locsByIndex[i0]}, GOAL{locsByIndex[i1]};
        std::set<Point> queue{{START}}, seen{queue}, next;
        while (queue.size() != 0 && !seen.count(GOAL)) {
          for (const auto& q : queue)
            for (const auto& d : DIRS) {
              const auto& n{q + d};
              if (maze[n.first][n.second] != '#' && !seen.count(n)) {
                auto waypnt = locsByPoint.find(n);
                if (waypnt != locsByPoint.end())
                  dist[{i0, waypnt->second}] = dist[{waypnt->second, i0}] = steps;
                if (n == GOAL)
                  dist[{i0, i1}] = dist[{i1, i0}] = steps;
                next.emplace(n), seen.emplace(n);
              }
            }
          next.swap(queue), next.clear(), ++steps;
        }
      }

  std::array<int, 7> order;
  std::iota(order.begin(), order.end(), 1);
  int min{INT_MAX};
  do min = std::min(min, std::accumulate(order.begin(), order.end() - 1,
             dist[{0, order[0]}] + part2 * dist[{0, order[6]}],
             [&](int sum, int& idx) {
               return sum + dist[{idx, *(&idx + 1)}];
             }));
  while (std::next_permutation(order.begin(), order.end()));
  os << min << std::endl;
}
