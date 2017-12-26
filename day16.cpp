#include <algorithm>
#include <iostream>
#include <string>
#include <utility>

struct PS {
  int res;
  bool eOF;
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

int main() {
  std::string progs = "";
  for (int i = 0; i < 16; ++i) {progs.push_back('a' + i);}
  
  while (true) {
    PS r, r1;
    char in;
    std::cin >> in;
    switch(in) {
    case 's':
      r = get_one_param();
      s(r.res, progs);
      break;
    case 'x':
      r1 = get_one_param();
      r = get_one_param();
      x(r1.res, r.res, progs);
      break;
    case 'p':
      char c1, c2;
      std::cin >> c1 >> c2 >> c2;
      p(c1, c2, progs);
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
 
  for (char p : progs) {
    std::cout << p;
  }
  std::cout << std::endl;
}
