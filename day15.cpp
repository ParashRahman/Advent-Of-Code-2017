#include <iostream>

bool cmp(long int a, long int b) {
  for (int i = 0; i < 16; ++i) {
    if (a % 2 != b % 2) {
      return false;
    }
    a >>= 1;
    b >>= 1;
  }
  return true;
}

int main() {
  long int A = 783;
  long int B = 325;

  int count = 0;
  
  for (long int i = 0; i < 5000000; ++i) {
    do {
      A = (A * 16807) % 2147483647L;
    } while (A % 4 != 0);
    do {
      B = (B * 48271) % 2147483647L;
    } while (B % 8 != 0);
    count += cmp(A,B);    
  }

  std::cout << count << std::endl;
}
