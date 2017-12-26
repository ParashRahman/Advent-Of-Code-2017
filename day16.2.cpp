#include <algorithm>
#include <iostream>
#include <string>
#include <utility>

struct PS {
  int res;
  bool eOF;
};

struct instr {
  char func;
  int param1;
  int param2;
  char cparam1;
  char cparam2;
};

PS get_one_param() {
  PS ret;

  ret.res = 0;

  char in;
  while (std::cin >> in) {
    if (in == ',' || in == '/') {
      ret.eOF = false;
      return ret;
    }
    ret.res *= 10;
    ret.res += (in - '0');
  }
  
  ret.eOF = true;
  return ret;  
}

void s(int num, std::string& ps) {
  std::reverse(ps.end() - num, ps.end());
  std::reverse(ps.begin(), ps.end() - num);
  std::reverse(ps.begin(), ps.end());
}

void x(int i1, int i2, std::string& ps) {
  char temp = ps[i1];
  ps[i1] = ps[i2];
  ps[i2] = temp;
}

void p(char p1, char p2, std::string& ps) {
  for (int i = 0; i < ps.size(); ++i) {
    if (ps[i] == p1) {
      ps[i] = p2;
    } else if (ps[i] == p2) {
      ps[i] = p1;
    }
  }
}

int call_instr(instr i, std::string& progs) {
  switch(i.func) {
  case 's':
    s(i.param1, progs);
    break;
  case 'x':
    x(i.param1, i.param2, progs);
    break;
  case 'p':
    p(i.cparam1, i.cparam2, progs);
    break;
  }
}

int main() {
  std::string progs = "";
  for (int i = 0; i < 16; ++i) {progs.push_back('a' + i);}
  std::string orig_progs = progs;
  
  std::vector<instr> ins;
  
  while (true) {
    PS r, r1;
    char in;
    instr instruction;
    
    std::cin >> in;
    switch(in) {
    case 's':
      r = get_one_param();
      instruction.func = 's';
      instruction.param1 = r.res;
      ins.push_back(instruction);
      break;
    case 'x':
      r1 = get_one_param();
      r = get_one_param();
      instruction.func = 'x';
      instruction.param1 = r1.res;
      instruction.param2 = r.res;
      ins.push_back(instruction);
      break;
    case 'p':
      char c1, c2;
      std::cin >> c1 >> c2 >> c2;
      instruction.func = 'p';
      instruction.cparam1 = c1;
      instruction.cparam2 = c2;
      ins.push_back(instruction);
      if (std::cin >> c1) {
	r.eOF = false;
      } else {
	r.eOF = true;
      }
      
      break;
    }
    if (r.eOF) { 
      break;
    }
  }

  long iter = 0;
  do {
    for (instr i : ins) {
      call_instr(i, progs);
    }
    ++iter;
  } while (progs != orig_progs);

  std::cout << progs << std::endl;
  for (int iter = 0; iter < 16; ++iter) {
    for (instr i : ins) {
      call_instr(i, progs);
    }
  }
  std::cout << progs << std::endl;
  std::cout << iter << std::endl;
}
