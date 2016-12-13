#include "Solution.hpp"
#include "io.hpp"
#include "util.hpp"
#include <algorithm>
#include <array>
#include <vector>

enum ParamType {Reg, Imm};
struct Param {ParamType t{Reg}; int v{' '}; };
struct Inst {char c{'-'}; Param p[2]; };

void print(const Inst& i) {
  printf("%c", i.c);
  for (int j{0}; j < 2; ++j)
    printf(i.p[j].t == Reg ? " %c" : " %d", i.p[j].v);
  printf("\n");
}

template <>
void
solve<Day12>(bool part2, std::istream& is, std::ostream& os)
{
  std::array<int, 4> reg{{0,0,(part2 ? 1 : 0),0}};
  std::vector<Inst> instr;
  std::transform (io::as<io::line>(is), {}, std::back_inserter(instr), [] (const auto& line) {
    const auto& tok = util::split(line, " ");
    Inst in{tok[0][0], {}};
    for (uint i{0}; i < tok.size() - 1; ++i) {
      bool isR{tok[i + 1][0] >= 'a' && tok[i + 1][0] <= 'd'};
      in.p[i] = { isR ? Reg : Imm, isR ? tok[i + 1][0] : std::stoi(tok[i + 1]) };
    }
    return in;
  });
  // peephole optimizer -- introduce add instruction
  for (uint p{2}; p < instr.size(); ++p) {
    const auto i{&instr[p - 2]}, d{&instr[p - 1]}, j{&instr[p]};
    if (i->c == 'i' && d->c == 'd' && j->c == 'j' && j->p[1].v == -2 && d->p[0].v == j->p[0].v) {
      instr[p-2] = {'a', {{Reg, d->p[0].v}, {Reg,i->p[0].v}}};
      instr[p-1] = {'c', {{Imm, 0}, {Reg, d->p[0].v}}};
      instr[p] = {'n', {{},{}}};
    }
  }
  auto get = [&reg] (const Param &p) -> int { return (p.t == Reg) ? reg[p.v-'a'] : p.v; };
  for (uint pc{0}; pc < instr.size();) {
    const auto& i = instr[pc++];
    switch (i.c) {
      case 'i': ++reg[i.p[0].v-'a'];; break;
      case 'd': --reg[i.p[0].v-'a'];; break;
      case 'c': reg[i.p[1].v-'a'] = get(i.p[0]); break;
      case 'j': pc += (get(i.p[0]) != 0) * (i.p[1].v - 1); break;
      case 'a': reg[i.p[1].v-'a'] += get(i.p[0]); break;
      default: break;
    }
  }
  os << reg[0] << std::endl;
}
