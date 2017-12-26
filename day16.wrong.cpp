#include <cmath>
#include <iostream>
#include <string>
#include <vector>

int lpow2(long int value) {
  // 0 -> -1
  // 1 -> 0
  // 2 -> 1
  // 3 -> 1
  int ret = -1;
  while (value > 0) {
    value >>= 1;
    ++ret;
  }
  return ret;
}

std::vector<int> get_perm(int pow2, std::vector<int> perm) {
  int pow = 0;
  std::cout << "START" << std::endl;
  while (pow < pow2) {
    for (int f : perm) { std::cout << f << " ";}
    std::vector<int> perm_new;
    for (int dex : perm) {
      perm_new.push_back(perm[dex]);
    }
    std::cout << std::endl;

    perm = perm_new;
    ++pow;
  }
  
  return perm;
}

int main() {
  std::string n = "dcmlhejnifpokgba";

  std::vector<int> perm;
  for (char c : n) {
    perm.push_back(c - 'a');
  }

  n = "abcdefghijklmnop";
  
  long int one_bill = 1000000000L;

  while (one_bill)  {
    int pow2 = lpow2(one_bill);
    if (pow2 < 0) {
      break;
    }
    std::vector<int> p = get_perm(pow2, perm);
    std::string newn = "";
    for (int i = 0; i < (one_bill / (1L << pow2)); ++i) {
      for (int k : p) {
	newn.push_back(n[k]);
      }
      n = newn;
      newn = "";
    }
    one_bill %= (1L << pow2);
  }

  std::cout << n << std::endl;
}
