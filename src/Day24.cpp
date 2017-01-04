#include "Solution.hpp"
#include "io.hpp"
#include <algorithm>
#include <numeric>
#include <vector>

struct Point {
  int y, x;
  bool operator==(const Point& o) const {
    return y == o.y && x == o.x;
  }
  Point& operator+=(const Point& o) {
    return y += o.y, x += o.x, *this;
  }
};
Point operator+(const Point& p1, const Point& p2) {
  return Point{p1} += p2;
}

static const int   WIDTH{181}, HEIGHT{43}, POINTS{8};
static const Point DIRS[4] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

template <>
void
solve<Day24>(bool part2, std::istream& is, std::ostream& os)
{
  int   dist[POINTS][POINTS];
  char  maze[HEIGHT][WIDTH];
  bool  visited[HEIGHT][WIDTH];
  Point locsByIndex[POINTS];
  {
    int   x{0}, y{0};
    char* data{&maze[0][0]};
    for (char c : io::by<char>(is)) {
      if (c != '.' && c != '#')
        locsByIndex[c - '0'] = {y, x};
      *data++ = c;
      if (++x == WIDTH)
        x = 0, ++y;
    }
  }
  std::fill(&dist[0][0], &dist[POINTS][0], -1);
  std::vector<Point> queue, next;
  for (int i0{0}; i0 < POINTS; ++i0)
    for (int i1{i0 + 1}; i1 < POINTS; ++i1)
      if (dist[i0][i1] == -1) {
        std::fill(&visited[0][0], &visited[HEIGHT][0], false);
        const Point &START{locsByIndex[i0]}, GOAL{locsByIndex[i1]};
        int          steps{1};
        for (queue.clear(), next.clear(), queue.emplace_back(START);
             queue.size() != 0 && !visited[GOAL.y][GOAL.x];
             queue.swap(next), next.clear(), ++steps)
          for (const auto& q : queue)
            for (const auto& d : DIRS) {
              Point n{q + d};
              if (maze[n.y][n.x] != '#' && !visited[n.y][n.x]) {
                if (n == GOAL)
                  dist[i0][i1] = dist[i1][i0] = steps;
                next.emplace_back(n), visited[n.y][n.x] = true;
              }
            }
      }
  int order[POINTS - 1];
  std::iota(order, order + sizeof(order), 1);
  int min{INT_MAX};
  do min = std::min(min, std::accumulate(order, order + POINTS - 2,
     dist[0][order[0]] + part2 * dist[0][order[POINTS - 2]],
     [&](int sum, int& idx) {
       return sum + dist[idx][*(&idx + 1)];
     }));
  while (std::next_permutation(&order[0], &order[POINTS - 1]));
  os << min << std::endl;
}
