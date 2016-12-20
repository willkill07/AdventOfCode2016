#include "Solution.hpp"
#include "io.hpp"
#include <set>

template <>
void
solve<Day20>(bool part2, std::istream& is, std::ostream& os)
{
  std::vector<std::pair<int64_t,int64_t>> data;
  const std::regex PARSE{R"((\d+)-(\d+))"};
  for (std::string line; std::getline(is, line); ) {
    std::smatch match;
    if (std::regex_match(line, match, PARSE))
      data.emplace_back(std::stoull(match.str(1)), std::stoull(match.str(2)));
  }
  std::sort(data.begin(), data.end());
  int64_t MAX{4294967295}, total{0}, last{-1}, first{-1};
  for (const auto &d : data) {
    int64_t c {std::max(0LL, d.first - last - 1)};
    if (!part2 && first == -1 && c)
      first = last + 1;
    if (part2)
      total += c;
    last = std::max(last, d.second);
  }
  total += std::max(0LL, MAX - last);
  os << (part2 ? total : first) << std::endl;
}
