#include <iostream>
#include <string>
#include <map>
#include <vector>

struct ins {
  std::string truction;
  char cp1;
  long np1;
  bool p1_ischar;
  char cp2;
  long np2;
  bool p2_ischar;
};

bool is_char(std::string param) {
  if (param.size() == 1 && param[0] >= 'a' && param[0] <= 'z') {
    return true;
  }
}

std::map<char, long> regs;

long get_p2_val(ins i) {
  if (i.p2_ischar) {
    return regs[i.cp2];
  } else {
    return i.np2;
  }
}

long get_p1_val(ins i) {
  if (i.p1_ischar) {
    return regs[i.cp1];
  } else {
    return i.np1;
  }
}

int main() {
  regs['a'] = 1;
  std::string truc, sp1, sp2;
  std::vector<ins> all;
  while (std::cin >> truc >> sp1 >> sp2) {
    ins new_ins;

    new_ins.truction = truc;
    new_ins.p1_ischar = is_char(sp1);
    if (new_ins.p1_ischar) {
      new_ins.cp1 = sp1[0];
    } else {
      new_ins.np1 = std::stoi(sp1);
    }

    new_ins.p2_ischar = is_char(sp2);
    if (new_ins.p2_ischar) {
      new_ins.cp2 = sp2[0];
    } else {
      new_ins.np2 = std::stoi(sp2);
    }

    all.push_back(new_ins);
  }

  int curr = 0;
  int cmul = 0;
  while (curr >= 0 && curr < all.size()) {
    ins i = all[curr];
    if (i.truction == "set") {
      regs[i.cp1] = get_p2_val(i);
    } else if (i.truction == "sub") {
      regs[i.cp1] -= get_p2_val(i);
    } else if (i.truction == "mul") {
      regs[i.cp1] *= get_p2_val(i);
      ++cmul;
    } else if (i.truction == "jnz") {
      if (get_p1_val(i) != 0) {
	curr += get_p2_val(i);
	continue;
      }
    }
    ++curr;
    std::cout << curr << std::endl;
  }

  std::cout << regs['h'] << std::endl;
  std::cout << cmul << std::endl;
}
