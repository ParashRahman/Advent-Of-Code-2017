#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

int sp(std::vector<std::string>& dirs) {
  float n, e, ne, nw, se, sw, s, w;
  n = e = s = w = ne = nw = se = sw= 0;
  
  for (std::string str : dirs) {
    if (str == "n") {
      ++n;
    }
    else if (str == "s") {
      ++s;
    }
    else if (str == "ne") {
      ++ne;
      n += 0.5;
      ++e;
    }
    else if (str == "nw") {
      ++nw;
      n += 0.5;
      ++w;
    }
    else if (str == "sw") {
      ++sw;
      s += 0.5;
      ++w;
    }
    else if (str == "se") {
      ++se;
      s += 0.5;
      ++e;
    }
  }

  float horiz = std::abs(w - e), vert = std::abs(n - s);

  for (int h = 0; h < horiz; ++h) {
    if (std::abs(vert - 0.5) > std::abs(vert + 0.5)) {
      vert += 0.5;
    } else {
      vert -= 0.5;
    }
  }

  return horiz + vert;
}

int main() {
  std::string line;

  std::getline(std::cin, line);

  std::vector<std::string> dirs;
  std::string str = "";
  int dex = 0;

  int maxi = -1;
  
  while (dex < line.size()) {
    if (line[dex] == ',') {
      dirs.push_back(str);
      int res = sp(dirs);
      if (res > maxi) {
	maxi = res;
      }
      
      str = "";
    } else {
      str += line[dex];
    }
    ++dex;
  }
  dirs.push_back(str);

  std::cout << sp(dirs) << " " << maxi << std::endl;
}
