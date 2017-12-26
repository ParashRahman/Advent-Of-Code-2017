#include <iostream>
#include <string>
#include <vector>

struct d{
  int a;
  int b;
};

int main() {
  std::vector<d> stuff;
  
  std::string in;
  int in2;
  while (std::cin >> in >> in2) {
    in.pop_back();
    int in1 = std::stoi(in);

    d i;
    i.a = in1;
    i.b = in2;

    stuff.push_back(i);
  }

  int delay = 0;
  bool winner = false;
  
  while (true) {
    for (d D : stuff) {      
      int modder = 2 * (D.b - 1);
      if ( (D.a + delay) % modder == 0) {
	++delay;
	std::cout << delay << std::endl;
	break;
      } 
    }

  }
}

//309985
