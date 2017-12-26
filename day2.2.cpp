#include <algorithm>
#include <iostream>
#include <limits> 
#include <sstream>
#include <vector>

int main() {

  long long sum = 0;
  
  std::string line;
  while (std::getline(std::cin, line)) {
    std::stringstream io;
    io.str(line);

    
    std::vector<int> nums;
    int num1;
    int num2;
    int num;
    while (io >> num) {
      nums.push_back(num);
    }

    std::sort(nums.begin(), nums.end());

    bool tobreak = false;
    for (int n1 = 0; n1 < nums.size(); ++n1) {
      for (int n2 = n1 + 1; n2 < nums.size(); ++n2) {
	if (nums[n2] % nums[n1] == 0) {
	  sum += nums[n2] / nums[n1];
	  tobreak = true;
	  break;
	}
      }
      if (tobreak) {
	break;
      }
    }

  }
  std::cout << sum << std::endl;
}
