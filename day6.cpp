#include <iostream>
#include <set>
#include <vector>

void redist(std::vector<int>& config) {
  int max_dex = 0;

  for (int i = 0; i < config.size(); ++i) {
    if (config[max_dex] < config[i]) {
      max_dex = i;
    }
  }

  int amount = config[max_dex];
  int curr_dex = (max_dex + 1) % config.size();
  config[max_dex] = 0;
  while (amount) {
    ++config[curr_dex];
    ++curr_dex;
    curr_dex %= config.size();
    --amount;
  }
  
}

int main() {
  std::vector<int> config;
  int num;

  std::set< std::vector<int> > cs;
  
  while (std::cin >> num) {
    config.push_back(num);
  }

  std::vector<int> goal({1, 1, 0, 15, 14, 13, 12, 10, 10, 9, 8, 7, 6, 4, 3, 5});
  
  int count = 0;
  while (cs.find(config) == cs.end()) {
    cs.insert(config);
    
    redist(config);
    
    ++count;
    if (config == goal) {
      std::cout << count << std::endl;
    }
    
  }

  std::cout << count << std::endl;
}
