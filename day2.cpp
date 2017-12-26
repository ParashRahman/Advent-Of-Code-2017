#include <algorithm>
#include <iostream>
#include <limits> 
#include <sstream>

int main() {

  long long sum = 0;
  
  std::string line;
  while (std::getline(std::cin, line)) {
    std::stringstream io;
    io.str(line);

    int num;
    int max = -1;
    int min = std::numeric_limits<int>::max();
    while (io >> num) {
      if (num > max) {
	max = num;
      }

      if (num < min) {
	min = num;
      }
    }

    sum += (max - min);
  }
  std::cout  << sum;

}
