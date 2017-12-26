#include <iostream>
#include <string>

const int SZ = 86;

int main() {
  int sz[SZ];
  int dex[SZ];
  bool dir[SZ];
  for (int i = 0; i < SZ; ++i) {dir[i]=false;sz[i]=0;dex[i]=0;}
  
  
  std::string in;
  int in2;

  while (std::cin >> in >> in2) {
    in.pop_back();
    int in1 = std::stoi(in);
    sz[in1] = in2;
  }

  int cost = 0;
  int delay = 0; 

  for (int pico = -1 * delay; pico < SZ; ++pico) {
    if (pico >= 0 && sz[pico] == 0) {
    }
    else if (pico >= 0 && dex[pico] == 0) {
      cost += pico * sz[pico];
    }
    
    // update errthing
    for (int i = 0; i < SZ; ++i) {
      if (sz[i] <= 1) {
	continue;
      }
      
      if (dir[i] == false) {
	if (dex[i] < sz[i] - 1) {
	  ++dex[i];
	} else {
	  dir[i] = true;
	  --dex[i];
	}
      } else {
	if (dex[i] > 0) {
	  --dex[i];
	} else {
	  dir[i] = false;
	  ++dex[i];
	}
      }
    }
  }
  std::cout << cost << std::endl;
}

