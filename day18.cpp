#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

struct ins {
  std::string s;
  char reg;
  long val;
  bool vr;
};

std::map<char, long> regs;
std::map<char, long> regs1;

long get_val(long c, bool zero=false) {
  if (c < 'a' || c > 'z') {
    std::cout << "ERRRRRRRR" << std::endl;
  }

  if (!zero) {
    return regs[c];
  } else {
    return regs1[c];
  }
}

int main() {
  regs['p'] = 0;
  regs1['p'] = 1;
  
  std::vector<ins> tructions;

  std::string s;
  char c;
  long n;
  ins i;
  
  while (std::cin >> s) {
    if (s == "set") {
      std::cin >> c >> n;
      if (! std::cin) {
	std::cin.clear();
	char ch;
	std::cin >> ch;
	std::cout << "ERR: " << ch << std::endl;
	n = ch;
	i.vr = true;
      } else {
	i.vr = false;
      }
      i.s = "set";
      i.reg = c;
      i.val = n;
      tructions.push_back(i);
    } else if (s == "add") {
      std::cin >> c >> n;
      if (! std::cin) {
	std::cin.clear();
	char ch;
	std::cin >> ch;
	std::cout << "ERR: " << ch << std::endl;
	n = ch;
	i.vr = true;
      } else {
	i.vr = false;
      }
      i.s = "add";
      i.reg = c;
      i.val = n;
      tructions.push_back(i);
    } else if (s == "mul") {
      std::cin >> c >> n;
      if (! std::cin) {
	std::cin.clear();
	char ch;
	std::cin >> ch;
	std::cout << "ERR: " << ch << std::endl;
	n = ch;
	i.vr = true;
      } else {
	i.vr = false;
      }
      i.s = "mul";
      i.reg = c;
      i.val = n;
      tructions.push_back(i);
    } else if (s == "mod") {
      std::cin >> c >> n;
      if (! std::cin) {
	std::cin.clear();
	char ch;
	std::cin >> ch;
	std::cout << "ERR: " << ch << std::endl;
	n = ch;
	i.vr = true;
      } else {
	i.vr = false;
      }
      i.s = "mod";
      i.reg = c;
      i.val = n;
      tructions.push_back(i);
    } else if (s == "snd") {
      std::cin >> c;
      i.s = "snd";
      i.val = c;
      i.vr = true;
      tructions.push_back(i);
    } else if (s == "rcv") {
      std::cin >> c;
      i.s = "rcv";
      i.val = c;
      i.vr = true;
      tructions.push_back(i);
    } else if (s == "jgz") {
      std::cin >> c >> n;
      if (! std::cin) {
	std::cin.clear();
	char ch;
	std::cin >> ch;
	std::cout << "ERR: " << ch << std::endl;
	n = ch;
	i.vr = true;
      } else {
	i.vr = false;
      }
      i.s = "jgz";
      i.reg = c;
      i.val = n;
      tructions.push_back(i);
    } else {
      std::cout << "ERRERERREE" << std::endl;
      return 0;
    }
  }
  
  long curr = 0;
  long curr1 = 0;
  
  std::queue<long> data;
  std::queue<long> data1;

  int cr0 = 0, cr1 = 0, cs0 = 0, cs1 = 0;
  
  int c1 = 0;
  while (true) {
    ins t = tructions[curr];
    ins t1 = tructions[curr1];
    
    bool wait = false, wait1 = false;
    
    if (curr >= 0 && curr < ((int)tructions.size())) {
      if (t.s == "snd") {
	data1.push(get_val(t.val));
	++cs0;
	++curr;
      } else if (t.s == "set") {
	regs[t.reg] = t.vr ? get_val(t.val) : t.val;
	++curr;
      } else if (t.s == "add") {
	regs[t.reg] += t.vr ? get_val(t.val) : t.val;
	++curr;
      } else if (t.s == "mul") {
	regs[t.reg] *= t.vr ? get_val(t.val) : t.val;
	++curr;
      } else if (t.s == "mod") {
	regs[t.reg] %= t.vr ? get_val(t.val) : t.val;
	++curr;
      } else if (t.s == "rcv") {
	if (data.size() > 0) {
	  ++cr0;
	  regs[t.val] = data.front();
	  data.pop();
	  ++curr;
	} else {
	  wait = true;
	}
      } else if (t.s == "jgz") {
	if (regs[t.reg] > 0) {
	  curr += t.vr ? get_val(t.val) : t.val;
	} else {
	  ++curr;
	}
      } 
    } else {
      wait = true;
    }

    if (curr1 >= 0 && curr1 < ((int)tructions.size())) {
      if (t1.s == "snd") {
	data.push(get_val(t1.val, true));
	++c1;
	++cs1;
	++curr1;
      } else if (t1.s == "set") {
	regs1[t1.reg] = t1.vr ? get_val(t1.val, true) : t1.val;
	++curr1;
      } else if (t1.s == "add") {
	regs1[t1.reg] += t1.vr ? get_val(t1.val, true) : t1.val;
	++curr1;
      } else if (t1.s == "mul") {
	regs1[t1.reg] *= t1.vr ? get_val(t1.val, true) : t1.val;
	++curr1;
      } else if (t1.s == "mod") {
	regs1[t1.reg] %= t1.vr ? get_val(t1.val, true) : t1.val;
	++curr1;
      } else if (t1.s == "rcv") {
	if (data1.size() > 0) {
	  ++cr1;
	  regs1[t1.val] = data1.front();
	  data1.pop();
	  ++curr1;
	} else {
	  wait1 = true;
	}
      } else if (t1.s == "jgz") {
	if (regs1[t1.reg] > 0) {
	  curr1 += t1.vr ? get_val(t1.val, true) : t1.val;
	} else {
	  ++curr1;
	}
      }
    } else {
      wait1 = true;
    }
    
    if (wait && wait1) {
      break;
    }

    //std::cout << cs0 << " " << cr1 << " " << cs1 << " " << cr0 << std::endl;
    std::cout << curr << " " << curr1 << " " << data.size() << " " << data1.size() << " "  << regs['i'] << " " << regs1['i'] << std::endl; 
  }

  std::cout << c1 << std::endl;  
}
