#include "Solution.hpp"
#include <map>
#include <vector>

struct Data {
  int  min{INT_MAX}, max{INT_MIN}, size{0};
  bool vis{false};
  Data& insert(int v) {
    if (size == 2)
      return *this;
    int& toInsert = (size == 0 || v < min) ? min : max;
    if (size == 1 && v < min)
      std::swap(min, max);
    toInsert = v, ++size;
    return *this;
  }
  Data& visit() {
    vis = true;
    return *this;
  }
  bool ready() const {
    return size == 2 && !vis;
  }
};

template <>
void
solve<Day10>(bool part2, std::istream& is, std::ostream& os)
{
  std::map<char, std::map<int, Data>> data;
  std::vector<std::function<int()>> bots;
  std::map<int, int> ids;
  for (std::string line; std::getline(is, line); ) {
    int bot, v1, v2;
    char t1, t2;
    if (sscanf(line.c_str(), "value %d goes to bot %d", &v1, &bot))
      data['b'][bot].insert(v1);
    else if (sscanf(line.c_str(), "bot %d gives low to %c%*s %d and high to %c%*s %d", &bot, &t1, &v1, &t2, &v2)) {
      ids.emplace(bot, bots.size());
      bots.push_back([part2, bot, v1, v2, t1, t2, &data, &ids, &bots]() {
        auto& d = data['b'][bot].visit();
        int ret{0};
        if (!part2 && (d.min == 17 && d.max == 61))
          ret = bot;
        if (data[t1][v1].insert(d.min).ready() && t1 == 'b')
          ret += bots[ids[v1]]();
        if (data[t2][v2].insert(d.max).ready() && t2 == 'b')
          ret += bots[ids[v2]]();
        return ret;
      });
    }
  }
  for (auto& b : data['b'])
    if (b.second.ready()) {
      auto res = bots[ids[b.first]]();
      auto get = [&data](int i) { return data['o'][i].min; };
      os << (part2 ? get(0) * get(1) * get(2) : res) << std::endl;
      return;
    }
}
