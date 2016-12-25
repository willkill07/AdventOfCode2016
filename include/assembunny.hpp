#include <iostream>
#include <map>
#include <vector>

enum ParamType { Reg, Imm };

struct Param {
  ParamType t{Reg};
  int       v{' '};
};

class Assembunny;

struct Instruction {
  Assembunny* interpreter{nullptr};
  char        c{'-'};
  Param       p[2];

  int&
  reg(int);
  int
  val(int);
};

class Assembunny {
  std::map<char, int> regs;
  std::vector<Instruction> ins;
  std::string out;
  int outLimit{INT_MAX};

  char
  invert(char);

  public:
  Assembunny(std::istream& is);

  Assembunny&
  optAdd();

  Assembunny&
  optMul();

  Assembunny&
  run();

  int
  get(char);

  int&
  ref(char);

  Assembunny&
  set(char, int);

  Assembunny&
  setOutputBufferLimit(int);

  std::string
  getOuputBuffer();

  Assembunny&
  clearOutputBuffer();
};
