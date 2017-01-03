#include "Solution.hpp"
#include <numeric>
#include <vector>

int
inv(int a, int m)
{
  int u1{1}, u2{0}, u3{a}, v1{0}, v2{0}, v3{m};
  while (v3 != 0) {
    int q{u3 / v3};
    std::tie(v1, v2, v3, u1, u2, u3) = std::make_tuple((u1 - q * v1), (u2 - q * v2), (u3 - q * v3), v1, v2, v3);
  }
  return (m + u1) % m;
}

int
crt(const std::vector<int>& num, const std::vector<int>& rem)
{
  int prod{std::accumulate(num.begin(), num.end(), 1, std::multiplies<int>{})}, result{0};
  for (unsigned int i{0}; i < num.size(); ++i) {
    int p{prod / num[i]};
    result += rem[i] * inv(p, num[i]) * p;
  }
  return result % prod;
}

template <>
void
solve<Day15>(bool part2, std::istream& is, std::ostream& os)
{
  int              N{0};
  std::vector<int> nums, rems;
  for (std::string line; std::getline(is, line); ++N) {
    int num, rem;
    sscanf(line.c_str(), "Disc #%*d has %d positions; at time=0, it is at position %d.", &num, &rem);
    nums.push_back(num), rems.push_back(num - (rem + N + 1) % num);
  }
  if (part2)
    nums.push_back(11), rems.push_back(10 - N);
  os << crt(nums, rems) << std::endl;
}
