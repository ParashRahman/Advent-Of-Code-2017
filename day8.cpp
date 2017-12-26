#include <iostream>
#include <map>
#include <string>
#include <sstream>

int main() {
  std::map<std::string, int> regvalues;
  std::string line;

  int uber_max = 0;
  
  while (std::getline(std::cin, line)) {
    std::stringstream ss(line);

    std::string reg1, incordec, trash, reg2, op;
    int incordecby, cond2;

    ss >> reg1 >> incordec >> incordecby >> trash >> reg2 >> op >> cond2;

    if (regvalues.find(reg1) == regvalues.end()) {
      regvalues[reg1] = 0;
    }
    if (regvalues.find(reg2) == regvalues.end()) {
      regvalues[reg2] = 0;
    }

    if (incordec == "dec") {
      incordecby *= -1;
    }
    
    int vreg2 = regvalues[reg2];
    if (op == ">") {
      if (vreg2 > cond2) {
	regvalues[reg1] += incordecby;
      }
      if (regvalues[reg1] > uber_max) {
	uber_max = regvalues[reg1];
      }
      continue;
    }
    if (op == "<") {
      if (vreg2 < cond2) {
	regvalues[reg1] += incordecby;
      }
      if (regvalues[reg1] > uber_max) {
	uber_max = regvalues[reg1];
      }
      continue;
    }
    if (op == ">=") {
      if (vreg2 >= cond2) {
	regvalues[reg1] += incordecby;
      }
      if (regvalues[reg1] > uber_max) {
	uber_max = regvalues[reg1];
      }
      continue;
    }
    if (op == "<=") {
      if (vreg2 <= cond2) {
	regvalues[reg1] += incordecby;
      }
      if (regvalues[reg1] > uber_max) {
	uber_max = regvalues[reg1];
      }
      continue;
    }
    if (op == "!=") {
      if (vreg2 != cond2) {
	regvalues[reg1] += incordecby;
      }
      continue;
    }
    if (op == "==") {
      if (vreg2 == cond2) {
	regvalues[reg1] += incordecby;
      }
      if (regvalues[reg1] > uber_max) {
	uber_max = regvalues[reg1];
      }
      continue;
    }
  }
  int max = 0;
  for (auto entry : regvalues) {
    if (entry.second > max) {
      max = entry.second;
    }
  }
  std::cout << uber_max << " " << max << std::endl;
}
