#include <iostream>
#include <string>

int main() {
  std::string nums;
  std::cin >> nums;

  long long sum = 0;
  
  for (size_t i = 0; i < nums.size(); ++i) {
    if (nums[i] == nums[(i+nums.size()/2)%nums.size()]) {
      sum += (nums[i] - '0');
    }
  }

  std::cout << sum << std::endl;
}
