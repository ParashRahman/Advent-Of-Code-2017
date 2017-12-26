#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

const int SZ = 256;

std::string hexi(int n) {
  std::string ret;
  while (n) {
    ret.push_back(n%16 < 10 ? '0' + n%16 : 'a' + (n%16-10));
    n /= 16;
  }
  std::reverse(ret.begin(), ret.end());
  return ret;
}

// end >= start for [start,end]
int reverse(int mat[SZ], int start, int end) {
  for (int i = 0; i < (end - start + 1)/2; ++i) {
    int temp = mat[(start + i) % SZ];
    mat[(start + i) % SZ] = mat[(end - i) % SZ];
    mat[(end - i) % SZ] = temp;
  }
}

int main() {
  int mat[SZ];
  for (int i = 0; i < SZ; ++i) mat[i] = i;

  int curr = 0, skip = 0, len;

  std::string ls;

  std::getline(std::cin, ls);

  ls.push_back(17);
  ls.push_back(31);
  ls.push_back(73);
  ls.push_back(47);
  ls.push_back(23);

  int iter = 0;
  while (iter < 64) {
    int i = 0;
    while (i < ls.size()) {
      reverse(mat, curr, curr+ls[i]-1);
      
      curr += (ls[i] + skip);
      curr %= SZ;
      ++skip;
      ++i;
    }
    ++iter;
  }

  int dense_hash[SZ/16];
  for (int i = 0; i < SZ/16; ++i) {
    for (int j = i * 16; j < (i+1) * 16; ++j) {
      if (j == i*16) {
	dense_hash[i] = mat[j];
      } else {
	dense_hash[i] ^= mat[j];
      }
    }
  }

  for (int i = 0; i < SZ/16; ++i) {
    std::cout << hexi(dense_hash[i]);
  }
  std::cout << std::endl;
}
