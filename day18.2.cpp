#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>

struct instruct {
  std::string str;
  char param1;
  long int param2;
  bool p2reg;
  bool isspecial; // jgz 1 3
};

std::map<char, long int> reg0, reg1;

int main() {
  std::vector<instruct> ions;

  std::string name;
  while (std::cin >> name) {
    instruct i;
    i.str = name;
    if (name == "jgz") {
      int spec1, spec2;
      if (std::cin >> spec1) {
	std::cin >> spec2;
	i.isspecial = true;
	ions.push_back(i);
	continue;
      }
      std::cin.clear();
    }
    i.isspecial = false;
    if (name == "snd" || name == "rcv") {
      std::cin >> i.param1;
    } else {
      std::cin >> i.param1;
      char p2;
      int ip2;
      if (!(std::cin >> ip2)) {
	std::cin.clear();
	std::cin >> p2;
	i.param2 = p2;
	i.p2reg = true;
      } else {
	i.param2 = ip2;
	i.p2reg = false;
      }
    }

    ions.push_back(i);
  }

  for (instruct i : ions) {
    if (i.str != "snd" && i.str != "rcv") {
      if ( i.p2reg) {
      std::cout << i.str << " " << i.param1 << " " << (char) i.param2 << std::endl;
      } else {
	std::cout << i.str << " " << i.param1 << " " << (i.param2) << std::endl;
      }
    } else {
      std::cout << i.str << " " << i.param1 << std::endl;
    }
  }

  
  reg0['p'] = 0;
  reg1['p'] = 1;

  std::queue<long int> q0;
  std::queue<long int> q1;

  long int curr0 = 0, curr1 = 0;

  int count = 0;
  
  while (true) {
    bool wait0 = false, wait1 = false;
    
    instruct i0 = ions[curr0], i1 = ions[curr1];

    if (curr0 < 0 || curr0 >= ((long int) ions.size())) {
      wait0 = true;
    } else if (i0.isspecial) {
      curr0 += 3;
    } else if (i0.str == "set") {
      reg0[i0.param1] = i0.p2reg ? reg0[i0.param2] : i0.param2; ++curr0;
    } else if (i0.str == "add") {
      reg0[i0.param1] += i0.p2reg ? reg0[i0.param2] : i0.param2; ++curr0;
    } else if (i0.str == "mul") {
      reg0[i0.param1] *= i0.p2reg ? reg0[i0.param2] : i0.param2; ++curr0;
    } else if (i0.str == "mod") {
      reg0[i0.param1] %= i0.p2reg ? reg0[i0.param2] : i0.param2; ++curr0;
    } else if (i0.str == "snd") {
      q1.push(reg0[i0.param1]); ++curr0;
    } else if (i0.str == "rcv") {
      if (q0.empty()) {
	wait0 = true;
      } else {
	reg0[i0.param1] = q0.front();
	q0.pop(); ++curr0;
      }
    } else if (i0.str == "jgz") {
      if (reg0[i0.param1] > 0) {
	curr0 += (i0.p2reg ? reg0[i0.param2] : i0.param2);
      } else {
	++curr0;
      }
    } else {
      //      std::cout << "WTF " << i0.str << std::endl;
    }

    if (curr1 < 0 || curr1 >= ((long int) ions.size())) {
      wait1 = true;
    } else if (i1.isspecial) {
      curr1 += 3;
    } else if (i1.str == "set") {
      reg1[i1.param1] = i1.p2reg ? reg1[i1.param2] : i1.param2; ++curr1;
    } else if (i1.str == "add") {
      reg1[i1.param1] += i1.p2reg ? reg1[i1.param2] : i1.param2; ++curr1;
    } else if (i1.str == "mul") {
      reg1[i1.param1] *= i1.p2reg ? reg1[i1.param2] : i1.param2; ++curr1;
    } else if (i1.str == "mod") {
      reg1[i1.param1] %= i1.p2reg ? reg1[i1.param2] : i1.param2; ++curr1;
    } else if (i1.str == "snd") {
      q0.push(reg1[i1.param1]); ++curr1;
      ++count;
    } else if (i1.str == "rcv") {
      if (q1.empty()) {
	wait1 = true;
      } else {
	reg1[i1.param1] = q1.front();
	q1.pop(); ++curr1;
      }
    } else if (i1.str == "jgz") {
      if (reg1[i1.param1] > 0) {
	curr1 += (i1.p2reg ? reg1[i1.param2] : i1.param2);
      } else {
	++curr1;
      }
    } else {
      std::cout << "WTFFFF" << std::endl;
    }

    if (wait0 && wait1) {
      break;
    }
    //std::cout << curr0 << " " << curr1 << " " << wait0 << " " << wait1 << std::endl;
    //std::cout << q0.size() << " " << q1.size() << " " << ((int)q0.size()) - ((int) q1.size()) << std::endl;
  }
  
  std::cout << count << std::endl;
}

/**
  for (instruct i : ions) {
    if (i.str != "snd" && i.str != "rcv") {
      if ( i.p2reg) {
      std::cout << i.str << " " << i.param1 << " " << (char) i.param2 << std::endl;
      } else {
	std::cout << i.str << " " << i.param1 << " " << (i.param2) << std::endl;
      }
    } else {
      std::cout << i.str << " " << i.param1 << std::endl;
    }
  }
**/
