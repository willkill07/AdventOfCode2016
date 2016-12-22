#include "Solution.hpp"
#include <array>
#include <map>
#include <utility>
#include <regex>

const std::regex FS{R"(^/dev/grid/node-x(\d+)-y(\d+)\s+(\d+)T\s+(\d+)T\s+(\d+)T\s+\d+%$)", std::regex::optimize};

struct Node {
  int size, used, avail;
};

const int WIDTH{37}, HEIGHT{25};
using Grid = std::array<std::array<Node,WIDTH>,HEIGHT>;

template <>
void
solve<Day22>(bool part2, std::istream& is, std::ostream& os)
{
  std::smatch match;
  Grid nodes;
  int pairs{0},emptyX{0},emptyY{0};
  for (std::string line; std::getline(is, line); )
    if (std::regex_match(line, match, FS))
      nodes[std::stoi(match.str(2))][std::stoi(match.str(1))] = {std::stoi(match.str(3)), std::stoi(match.str(4)), std::stoi(match.str(5))};
  Node* n = &nodes[0][0];
  for (int n1{0}; n1 < WIDTH * HEIGHT; ++n1)
    if(part2) {
      if (n[n1].used == 0)
        emptyX = (n1 % WIDTH), emptyY = (n1 / WIDTH);
    } else
      for (int n2{0}; !part2 && n2 < WIDTH * HEIGHT; ++n2)
        pairs += ((n1 != n2) && (n[n1].used != 0) && (n[n1].used <= n[n2].avail));
  os << (part2 ? ((emptyX + emptyY + WIDTH - 1) + (WIDTH - 2) * 5) : pairs) << std::endl;
}
