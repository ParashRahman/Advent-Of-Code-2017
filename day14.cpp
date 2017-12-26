#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <set>

const int SZ = 256;

std::string hexi(int n) {
  std::string ret;
  while (n) {
    ret.push_back(n%16 < 10 ? '0' + n%16 : 'a' + (n%16-10));
    n /= 16;
  }

  while (ret.size() < 2) {
    ret.push_back('0');
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

std::string get_bin_char(unsigned char ch) {
  std::string res = "";

  int c;

  if (ch >= 'a' && ch <= 'f') {
    c = ch - 'a' + 10;
  } else {
    c = ch - '0';
  }
  
  while (c) {
    if (c % 2 == 0) {
      res.push_back('0');
    } else {
      res.push_back('1');
    }
    c >>= 1;
  }

  while(res.size() < 4) {
    res.push_back('0');
  }
  std::reverse(res.begin(), res.end());
  return res;
}

int num_bits_hex_char(unsigned char c) {
  unsigned int nc;
  
  if (c >= 'a' && c <= 'f') {
    nc = c - 'a' + 10;
  } else {
    nc = c - '0';
  }
  unsigned int count;

  for (count = 0; nc; ++count) {
    nc &= nc - 1; 
  }
  return count;
}

std::string knot_hash(std::string ls) {
  int mat[SZ];
  for (int i = 0; i < SZ; ++i) mat[i] = i;

  int curr = 0, skip = 0, len;

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

  std::string hex = "";
  for (int i = 0; i < SZ/16; ++i) {
    std::string kh = hexi(dense_hash[i]);
    hex.insert(hex.end(), kh.begin(), kh.end());
  }
  return hex;
}

void explore(int r, int c, int RMAX, int CMAX, std::vector<std::string>& G, std::set<std::pair<int,int>>& visited) {
  if (r >= 0 && r < RMAX && c >= 0 && c < CMAX && G[r][c] == '1' && visited.find(std::make_pair(r,c)) == visited.end()) {
  } else {
    return;
  }
  visited.insert(std::make_pair(r,c));
  
  explore(r-1,c,RMAX,CMAX,G,visited);
  explore(r+1,c,RMAX,CMAX,G,visited);
  explore(r,c-1,RMAX,CMAX,G,visited);
  explore(r,c+1,RMAX,CMAX,G,visited);
}

int cc(std::vector<std::string>& G) {
  std::set<std::pair<int,int>> visited;

  int RMAX = G.size();
  int CMAX = G[0].size();

  int CC = 0;
  for (int r = 0; r < RMAX; ++r) {
    for (int c = 0; c < CMAX; ++c) {
      if (visited.find(std::make_pair(r,c)) == visited.end() && G[r][c] == '1') {
	explore(r,c,RMAX,CMAX,G,visited);
	++CC;
      }
    }
  }

  return CC;
}

int main() {
  int num_1 = 0;
  std::string str;
  std::cin >> str;

  std::vector<std::string> mesh;
  for (int i = 0; i < 128; ++i) {
    std::string key = str + "-" + std::to_string(i);
    std::string kh = knot_hash(key);
    std::string row = "";
    for (int j = 0; j < kh.size(); ++j) {
      std::string res = get_bin_char(kh[j]);
      row.insert(row.end(), res.begin(), res.end());
    }
    mesh.push_back(row);
  }

  for (int i = 0; i < 10; ++i) {
    std::cout << get_bin_char('0' + i) << std::endl;
  }
  
  std::cout << cc(mesh) << std::endl;
}
