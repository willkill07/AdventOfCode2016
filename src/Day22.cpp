#include "Solution.hpp"
#include <array>

struct Node {
  int size, used, avail;
};

template <>
void
solve<Day22>(bool part2, std::istream& is, std::ostream& os)
{
  static const int WIDTH{37}, HEIGHT{25};
  std::array<std::array<Node,WIDTH>,HEIGHT> nodes;
  int pairs{0}, emptyX{0}, emptyY{0};
  for (std::string line; std::getline(is, line); ) {
    Node n;
    int x, y;
    if (sscanf(line.c_str(), "/dev/grid/node-x%d-y%d %dT %dT %dT %*d%%", &x, &y, &n.size, &n.used, &n.avail))
      nodes[y][x] = n;
  }
  Node* n = &nodes[0][0];
  for (int n1{0}; n1 < WIDTH * HEIGHT; ++n1)
    if(part2) {
      if (n[n1].used == 0)
        emptyX = (n1 % WIDTH), emptyY = (n1 / WIDTH);
    } else
      for (int n2{0}; n2 < WIDTH * HEIGHT; ++n2)
        pairs += ((n1 != n2) && (n[n1].used != 0) && (n[n1].used <= n[n2].avail));
  os << (part2 ? ((emptyX + emptyY + WIDTH - 1) + (WIDTH - 2) * 5) : pairs) << std::endl;
}
