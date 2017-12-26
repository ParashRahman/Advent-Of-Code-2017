#include <cmath>
#include <iostream>

bool isprime(int num) {
  for (int i = 2; i <= std::sqrt(num); ++i) {
    if (num % i == 0) {
      return false;
    }
  }
  return true;
}

int main() {
  std::cout << std::sqrt(9) << " " << isprime(5) << std::endl;
  int h = 0;
  for (int b = 109900; b <= 126900; b += 17) {
    h += !isprime(b);
  }
  std::cout << h << std::endl;
}
