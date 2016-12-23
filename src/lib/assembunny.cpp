#include "assembunny.hpp"
#include "io.hpp"
#include "util.hpp"

int dummy;

int&
Instruction::reg(int idx)
{
  if (p[idx].t == Reg)
    return interpreter->ref(p[idx].v);
  return dummy;
}

int
Instruction::val(int idx)
{
  if (p[idx].t == Reg)
    return interpreter->get(p[idx].v);
  return p[idx].v;
}

Assembunny::Assembunny(std::istream& is)
{
  for (const auto& line : io::by<io::line>(is)) {
    const auto& tok = util::split(line, " ");
    Instruction in{this, tok[0][0], {}};
    for (uint i{0}; i < tok.size() - 1; ++i) {
      bool isR{tok[i + 1][0] >= 'a' && tok[i + 1][0] <= 'd'};
      in.p[i] = {isR ? Reg : Imm, isR ? tok[i + 1][0] : std::stoi(tok[i + 1])};
    }
    ins.push_back(in);
  }
}

Assembunny&
Assembunny::optMul()
{
  for (uint p{5}; p < ins.size(); ++p) {
    const auto c{&ins[p - 5]}, i{&ins[p - 4]}, d1{&ins[p - 3]}, j1{&ins[p - 2]}, d2{&ins[p - 1]}, j2{&ins[p]};
    if (c->c == 'c' && i->c == 'i' && d1->c == 'd' && j1->c == 'j' && d2->c == 'd' && j2->c == 'j'
        && j1->p[1].v == -2 && j2->p[1].v == -5
        && j1->p[0].v == d1->p[0].v && j2->p[0].v == d2->p[0].v) {
      auto marg1{c->p[0].v}, marg2{j2->p[0].v}, res{i->p[0].v}, reset{c->p[1].v};
      ins[p - 5] = {this, 'm', {{Reg, marg1}, {Reg, marg2}}};
      ins[p - 4] = {this, 'a', {{Reg, marg2}, {Reg, res}}};
      ins[p - 3] = {this, 'c', {{Imm, 0}, {Reg, marg2}}};
      ins[p - 2] = {this, 'c', {{Imm, 0}, {Reg, reset}}};
      ins[p - 1] = {this, 'n', {{}, {}}};
      ins[p - 0] = {this, 'n', {{}, {}}};
    }
  }
  return *this;
}

Assembunny&
Assembunny::optAdd()
{
  for (uint p{2}; p < ins.size(); ++p) {
    const auto i{&ins[p - 2]}, d{&ins[p - 1]}, j{&ins[p]};
    if (i->c == 'i' && d->c == 'd' && j->c == 'j' && j->p[1].v == -2 && d->p[0].v == j->p[0].v) {
      ins[p - 2] = {this, 'a', {{Reg, d->p[0].v}, {Reg, i->p[0].v}}};
      ins[p - 1] = {this, 'c', {{Imm, 0}, {Reg, d->p[0].v}}};
      ins[p - 0] = {this, 'n', {{}, {}}};
    }
  }
  return *this;
}

char
Assembunny::invert(char i)
{
  switch (i) {
    case 'i':
      return 'd';
    case 't':
    case 'd':
      return 'i';
    case 'j':
      return 'c';
    case 'c':
      return 'j';
    default:
      return i;
  }
}

Assembunny&
Assembunny::run()
{
  for (int pc{0}; pc < int(ins.size()); ++pc) {
    auto& i = ins[pc];
    switch (i.c) {
      case 't':
        if (pc + i.val(0) >= 0 && pc + i.val(0) < int(ins.size()))
          ins[pc + i.val(0)].c = invert(ins[pc + i.val(0)].c);
        break;
      case 'i':
        ++i.reg(0);
        break;
      case 'd':
        --i.reg(0);
        break;
      case 'c':
        i.reg(1) = i.val(0);
        break;
      case 'j':
        pc += (i.val(0) != 0) * (i.val(1) - 1);
        break;
      case 'm':
        i.reg(1) *= i.val(0);
        break;
      case 'a':
        i.reg(1) += i.val(0);
        break;
      default:
        break;
    }
  }
  return *this;
}

int&
Assembunny::ref(char c)
{
  return regs[c];
}

int
Assembunny::get(char c)
{
  return ref(c);
}

Assembunny&
Assembunny::set(char c, int v)
{
  ref(c) = v;
  return *this;
}
