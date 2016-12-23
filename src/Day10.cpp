#include "Solution.hpp"
#include "io.hpp"
#include <map>
#include <set>
#include <vector>

class Data {
  std::set<int> vals{};
public:
  int insert(int v) {
    vals.insert(v);
    return v;
  }
  bool ready() const {
    return vals.size() == 2;
  }
  int min() const {
    return *vals.begin();
  }
  int max() const {
    return *vals.rbegin();
  }
};


template <>
void
solve<Day10>(bool part2, std::istream& is, std::ostream& os)
{
  static const std::regex VALUE{R"(value (\d+) goes to bot (\d+))"};
  static const std::regex BOT{R"(bot (\d+) gives low to (\w+) (\d+) and high to (\w+) (\d+))"};
  std::map<std::string, std::map<int, Data>> data;
  std::vector<std::function<bool()>> bots;
  std::map<int, int> ids;
  for (const auto& line : io::by<io::line>(is)) {
    std::smatch m;
    std::regex_match(line, m, VALUE) || std::regex_match(line, m, BOT);
    if (line[0] == 'v') {
      int bot{std::stoi(m.str(2))}, v{std::stoi(m.str(1))};
      auto& d = data["bot"][bot];
      d.insert(v);
    } else {
      int bot{std::stoi(m.str(1))}, v1{std::stoi(m.str(3))}, v2{std::stoi(m.str(5))};
      std::string t1{m.str(2)}, t2{m.str(4)};
      ids.emplace(bot, bots.size());
      bots.push_back([bot, v1, v2, t1, t2, &data]() {
        const auto& d = data["bot"][bot];
        return ((data[t1][v1].insert(d.min()) ^ 17) + (data[t2][v2].insert(d.max()) ^ 61) == 0);
      });
    }
  }
  std::set<int> queue;
  for (const auto& id : ids)
    queue.insert(id.first);
  while (!queue.empty())
    for (auto q = queue.begin(); q != queue.end();)
      if (data["bot"][*q].ready()) {
        if (bots[ids[*q]]() && !part2)
          os << *q << std::endl;
        queue.erase(q++);
      } else
        ++q;
  if (part2)
    os << (data["output"][0].min() * data["output"][1].min() * data["output"][2].min()) << std::endl;
}
