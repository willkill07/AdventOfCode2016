#include "Solution.hpp"
#include "io.hpp"
#include <chrono>
#include <map>
#include <set>
#include <thread>
#include <vector>
using namespace std::chrono_literals;

template <>
void
solve<Day10>(bool part2, std::istream& is, std::ostream& os)
{
  const static std::regex VALUE{R"(value (\d+) goes to bot (\d+))", std::regex::optimize};
  const static std::regex BOT{R"(bot (\d+) gives low to (\w+) (\d+) and high to (\w+) (\d+))", std::regex::optimize};
  std::vector<std::pair<int, int>> values;
  std::vector<std::thread> bots;
  std::map<int, int> ids;
  std::map<std::string,std::map<int, std::set<int>>> data;
  std::mutex lock;
  std::smatch match;
  for (const auto& line : io::by<io::line>(is))
    if (line[0] == 'v') {
      std::regex_match(line, match, VALUE);
      std::lock_guard<std::mutex> guard(lock);
      int val{std::stoi(match.str(1))}, bot{std::stoi(match.str(2))};
      data["bot"][bot].insert(val);
    } else {
      std::regex_match(line, match, BOT);
      int bot{std::stoi(match.str(1))}, v1{std::stoi(match.str(3))}, v2{std::stoi(match.str(5))};
      std::string t1{match.str(2)}, t2{match.str(4)};
      ids.emplace(bot, bots.size());
      bots.emplace_back([bot,v1,v2,t1,t2,part2,&data,&os,&lock]() {
        while (true) {
          std::this_thread::sleep_for(10us);
          std::lock_guard<std::mutex> guard(lock);
          size_t size{data["bot"][bot].size()};
          if (size != 2)
            continue;
          auto ptr = data["bot"][bot].begin();
          int low{*ptr}, high{*++ptr};
          if (!part2 && (low == 17 && high == 61))
            os << bot << std::endl;
          data[t1][v1].insert(low);
          data[t2][v2].insert(high);
          break;
        }
      });
    }
  for (auto& b : bots)
    b.join();
  if (part2) {
    auto get = [&] (int i) { return *data["output"][i].begin(); };
    os << (get(0) * get(1) * get(2)) << std::endl;
  }
}
