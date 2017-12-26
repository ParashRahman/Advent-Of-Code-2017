#include <iostream>

int main() {
  int dex = 0;
  int sz = 1;

  int d1 = -1;
  
  for (int i = 1; i <= 50000000; ++i) {
    dex += 376;
    dex %= sz;
    if (dex == 0) {
      d1 = i;
    }
    ++dex;
    ++sz;
  }

  std::cout << d1 << std::endl;
  
}
