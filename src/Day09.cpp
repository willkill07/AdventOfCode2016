#include "Solution.hpp"
#include "io.hpp"

long
decode(std::string && s, bool part2)
{
  static const std::regex PATTERN{R"(\((\d+)x(\d+)\))", std::regex::optimize};
  std::smatch m;
  if (!std::regex_search(s, m, PATTERN))
    return s.size();
  long start{m.position()}, len{std::stoi(m.str(1))}, times{std::stoi(m.str(2))}, ptr{start + m.length()};
  return start + (part2 ? decode(s.substr(ptr, len), part2) : len) * times + decode(s.substr(ptr + len), part2);
}

template <>
void
solve<Day09>(bool part2, std::istream& is, std::ostream& os)
{
  os << (decode(io::as_string(is), part2) - 1) << std::endl;
}
