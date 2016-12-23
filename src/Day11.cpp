#include "Solution.hpp"
#include <array>
#include <cstdlib>
#include <cstring>
#include <map>
#include <regex>
#include <string>
#include <unordered_map>
#include <utility>

static uint64_t move_table[4][16];

using state_t = std::pair<uint64_t, uint8_t>;
using GMPair = std::array<uint64_t, 2>;

namespace std {
template <>
struct hash<state_t> {
  std::size_t
  operator()(const state_t &s) const
  {
    return hash<uint64_t>()(std::get<0>(s)) + 33 * hash<uint8_t>()(std::get<1>(s));
  }
};
}

inline int8_t
twoWayBFS(const state_t &start, const state_t &goal)
{
  std::unordered_map<state_t, int8_t> prev, next, curr;
  auto depth_sign = [] (int8_t depth) { return 1 - ((depth < 0) << 1); };
  auto legal_move = [] (uint64_t gm) { return !(gm & 0x8888888888888888); };
  auto compatible = [] (uint64_t gm) { return !(((gm & 0x000000000000ffff) && (gm & 0x000f000f000f0000)) |
                                                ((gm & 0x00000000ffff0000) && (gm & 0x00f000f0000000f0)) |
                                                ((gm & 0x0000ffff00000000) && (gm & 0x0f0000000f000f00)) |
                                                ((gm & 0xffff000000000000) && (gm & 0x0000f000f000f000))); };
  curr.emplace(start, 0), curr.emplace(goal, -1);
  for (int8_t depth{0}; depth >= 0; ++depth, prev.swap(curr), curr.swap(next), next.clear())
    for (const auto &mi0 : curr)
      for (int m0{0}; m0 < 16; ++m0) {
        uint64_t items1{std::get<0>(mi0.first) + move_table[std::get<1>(mi0.first)][m0]};
        if (!legal_move(items1))
          continue;
        uint8_t e(std::get<1>(mi0.first) - ((m0 >> 2) & 2) + 1);
        for (int m1{-1}; m1 < 8; ++m1) {
          uint64_t items2{items1 + (m1 >= 0) * move_table[std::get<1>(mi0.first)][m1 | (m0 & 8)]};
          if (!legal_move(items2) || !compatible(items2))
            continue;
          decltype(prev)::const_iterator mi;
          if (((mi = prev.find(state_t(items2, e))) == prev.end()) && ((mi = curr.find(state_t(items2, e))) == curr.end())
              && ((mi = next.find(state_t(items2, e))) == next.end()))
            next.emplace(state_t{items2, e}, mi0.second + depth_sign(mi0.second));
          else if (depth_sign(mi0.second) != depth_sign(mi->second))
            return std::abs(mi0.second) + std::abs(mi->second);
        }
      }
  return -1;
}

inline auto
parse_input(std::istream &in)
{
  const std::regex re{R"(a (\w+)( generator|-compatible microchip))", std::regex::optimize};
  std::map<std::string, GMPair> elements;
  decltype(elements)::iterator ei;
  uint64_t floor{0};
  for (std::string line; std::getline(in, line); ++floor)
    for (std::sregex_iterator next(line.begin(), line.end(), re), end; next != end; ++next)
      if ((ei = elements.find(next->str(1))) == elements.end())
        elements.emplace(next->str(1), GMPair{{floor, floor}});
      else
        ei->second[next->str(2)[1] == 'c'] = floor;
  return elements;
}

template <>
void
solve<Day11>(bool part2, std::istream &is, std::ostream &os)
{
  auto GM = [](uint64_t g, uint64_t m) { return uint64_t{1} << (g << 4) << (m << 2); };
  auto UDGMO = [](int ud, int gm, int o) { return (ud << 3) | (gm << 2) | o; };
  state_t start(0, 0), goal(0, 3);
  for (const auto &ei : parse_input(is)) {
    std::get<0>(start) += GM(ei.second[0], ei.second[1]);
    std::get<0>(goal) += GM(3, 3);
  }
  std::get<0>(start) += part2 * 2 * GM(0, 0);
  std::get<0>(goal) += part2 * 2 * GM(3, 3);
  memset(move_table, 0x88, sizeof(move_table));
  for (int e{0}; e <= 3; ++e)
    for (int o{0}; o <= 3; ++o) {
      if (e > 0)
        move_table[e][UDGMO(1, 0, o)] = GM(e - 1, o) - GM(e, o), move_table[e][UDGMO(1, 1, o)] = GM(o, e - 1) - GM(o, e);
      if (e < 3)
        move_table[e][UDGMO(0, 0, o)] = GM(e + 1, o) - GM(e, o), move_table[e][UDGMO(0, 1, o)] = GM(o, e + 1) - GM(o, e);
    }
  os << int{twoWayBFS(start, goal)} << std::endl;
}
