#include "Solution.hpp"
#include "md5.hpp"
#include <algorithm>
#include <array>
#include <list>

struct State {
  int         x, y;
  std::string path{};
};

template <>
void
solve<Day17>(bool part2, std::istream& is, std::ostream& os)
{
  const std::array<int, 4> DX{{-1, 1, 0, 0}}, DY{{0, 0, -1, 1}};
  const std::string PATH{"UDLR"};
  std::string       prefix;
  md5str_t          hash;
  std::list<State>  queue, found;
  int               max{0};
  is >> prefix;
  for (queue.push_back(State{0, 0, prefix}); queue.size() != 0 && (part2 || found.size() == 0); queue.pop_front()) {
    const auto& curr = queue.front();
    md5str((uint8_t*)curr.path.data(), curr.path.size(), &hash);
    for (uint i{0}; i < 4; ++i) {
      if ((hash.c[i] > 'a') && (!DX[i] || !((curr.x + DX[i]) >> 2)) && (!DY[i] || !((curr.y + DY[i]) >> 2))) {
        State next{curr.x + DX[i], curr.y + DY[i], curr.path + PATH[i]};
        ((next.x == 3 && next.y == 3) ? max = std::max(max, int(next.path.size())), found : queue).push_back(next);
      }
    }
  }
  os << (part2 ? std::to_string(max - prefix.size()) : found.front().path.substr(prefix.size())) << std::endl;
}
