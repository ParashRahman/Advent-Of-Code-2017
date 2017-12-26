#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<int> jumps;
  int num;
  
  int curr = 0;

  while (std::cin >> num) {
    jumps.push_back(num);
  }

  int moves = 0;
  while (curr < jumps.size() && curr >= 0) {
    if (jumps[curr] >= 3) {
      --jumps[curr];
      curr += (jumps[curr] + 1);
    } else {
      ++jumps[curr];
      curr += (jumps[curr] - 1);
    }
    ++moves;
  }

  std::cout << moves << std::endl;
  
}
