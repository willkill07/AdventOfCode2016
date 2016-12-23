#include "Solution.hpp"
#include "io.hpp"
#include "util.hpp"
#include <algorithm>
#include <array>
#include <vector>

enum ParamType {Reg, Imm};
struct Param {ParamType t{Reg}; int v{' '}; };
struct Inst {char c{'-'}; Param p[2]; };

template <>
void
solve<Day23>(bool part2, std::istream& is, std::ostream& os)
{
  std::array<int, 4> reg{{part2 ? 12 : 7,0,0,0}};
  std::vector<Inst> instr;
  for (const auto& line : io::by<io::line>(is)) {
    const auto& tok = util::split(line, " ");
    Inst in{tok[0][0], {}};
    for (uint i{0}; i < tok.size() - 1; ++i) {
      bool isR{tok[i + 1][0] >= 'a' && tok[i + 1][0] <= 'd'};
      in.p[i] = { isR ? Reg : Imm, isR ? tok[i + 1][0] : std::stoi(tok[i + 1]) };
    }
    instr.push_back(in);
  }
  // peephole optimizer -- introduce mul instruction
  for (uint p{5}; p < instr.size(); ++p) {
    const auto c{&instr[p - 5]}, i{&instr[p - 4]}, d1{&instr[p - 3]}, j1{&instr[p - 2]}, d2{&instr[p - 1]}, j2{&instr[p]};
    if (c->c == 'c' && i->c == 'i' && d1->c == 'd' && j1->c == 'j' && d2->c == 'd' && j2->c == 'j' &&
        j1->p[1].v == -2  && j2->p[1].v == -5 && j1->p[0].v == d1->p[0].v && j2->p[0].v == d2->p[0].v) {
      auto marg1{c->p[0].v}, marg2{j2->p[0].v}, res{i->p[0].v}, reset{c->p[1].v};
      instr[p - 5] = {'m', {{Reg, marg1}, {Reg, marg2}}};
      instr[p - 4] = {'a', {{Reg, marg2}, {Reg, res}}};
      instr[p - 3] = {'c', {{Imm, 0}, {Reg, marg2}}};
      instr[p - 2] = {'c', {{Imm, 0}, {Reg, reset}}};
      instr[p - 1] = {'n', {{},{}}};
      instr[p - 0] = {'n', {{},{}}};
    }
  }
  auto r = [&reg] (int v) -> int& { return reg[v-'a']; };
  auto get = [&reg,&r] (const Param &p) -> int { return (p.t == Reg) ? r(p.v) : p.v; };
  auto invert = [] (char i) { return (i == 'i' ? 'd' : (i == 't' || i == 'd') ? 'i' : (i == 'j') ? 'c' : (i == 'c') ? 'j' : i); };
  for (int pc{0}; pc < int(instr.size()); ++pc) {
    const auto& i = instr[pc];
    switch (i.c) {
      case 't': {
        int mod{pc + get(i.p[0])};
        if (mod >= 0 && mod < int(instr.size()))
          instr[mod].c = invert(instr[mod].c);
        break;
      }
      case 'i': if (i.p[0].t == Reg) ++r(i.p[0].v); break;
      case 'd': --r(i.p[0].v); break;
      case 'c': if (i.p[1].t == Reg) r(i.p[1].v) = get(i.p[0]); break;
      case 'j': pc += (get(i.p[0]) != 0) * (get(i.p[1]) - 1); break;
      case 'm': r(i.p[1].v) *= get(i.p[0]); break;
      case 'a': r(i.p[1].v) += get(i.p[0]); break;
      default: break;
    }
  }
  os << reg[0] << std::endl;
}
