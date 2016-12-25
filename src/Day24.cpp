#include "Solution.hpp"
#include "io.hpp"
#include <algorithm>
#include <map>
#include <numeric>
#include <vector>

const int WIDTH{181}, HEIGHT{43}, POINTS{8};
using Point = std::pair<int, int>;
static const Point DIRS[4] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

Point
operator+(const Point& p1, const Point& p2)
{
  return {p1.first + p2.first, p1.second + p2.second};
}

template <>
void
solve<Day24>(bool part2, std::istream& is, std::ostream& os)
{
  int   x{0}, y{0};
  char  maze[HEIGHT][WIDTH];
  char* data{&maze[0][0]};
  std::map<int, Point> locsByIndex;
  std::map<Point, int> locsByPoint;
  for (char c : io::by<char>(is)) {
    if (c != '.' && c != '#') {
      locsByIndex[c - '0'] = {y, x};
      locsByPoint[{y, x}] = c - '0';
    }
    *data++ = c;
    if (++x == WIDTH)
      x = 0, ++y;
  }
  int dist[POINTS][POINTS];
  bool visited[HEIGHT][WIDTH];
  std::fill(&dist[0][0], &dist[POINTS][0], -1);
  std::vector<Point> queue, next;
  for (int i0{0}; i0 < POINTS; ++i0)
    for (int i1{i0 + 1}; i1 < POINTS; ++i1)
      if (dist[i0][i1] == -1) {
        std::fill(&visited[0][0], &visited[HEIGHT][0], false);
        const Point &START{locsByIndex[i0]}, GOAL{locsByIndex[i1]};
        int          steps{1};
        for (queue.clear(), next.clear(), queue.emplace_back(START);
             queue.size() != 0 && !visited[GOAL.first][GOAL.second];
             queue.swap(next), next.clear(), ++steps)
          for (const auto& q : queue)
            for (const auto& d : DIRS) {
              const auto& n{q + d};
              if (maze[n.first][n.second] != '#' && !visited[n.first][n.second]) {
                if (n == GOAL)
                  dist[i0][i1] = dist[i1][i0] = steps;
                next.emplace_back(n), visited[n.first][n.second] = true;
              }
            }
      }
  int order[POINTS - 1];
  std::iota(order, order + sizeof(order), 1);
  int min{INT_MAX};
  do
    min = std::min(min, std::accumulate(order, order + POINTS - 2,
             dist[0][order[0]] + part2 * dist[0][order[POINTS - 2]],
             [&](int sum, int& idx) {
               return sum + dist[idx][*(&idx + 1)];
             }));
  while (std::next_permutation(&order[0], &order[POINTS - 1]));
  os << min << std::endl;
}
