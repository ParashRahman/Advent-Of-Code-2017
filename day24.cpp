#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

typedef std::pair<int,int> piece;
std::map<piece, bool> visited;
std::vector<piece> pcs;

std::map<int, std::vector<piece>> references;

int maxi_trail = 0;
int curr_trail = 0;

int maxi_len_strength = 0;
int maxi_len = 0;

void back_track(int connector, int length) {
  curr_trail += connector;
  maxi_trail = curr_trail > maxi_trail ? curr_trail : maxi_trail;

  if (length >= maxi_len) {
    maxi_len = length;
    maxi_len_strength = curr_trail > maxi_len_strength ? curr_trail : maxi_len_strength;
  }
  
  for (auto pie : references[connector]) {
    if (visited.find(pie) == visited.end() || visited[pie] == false) {
      visited[pie] = true;
      curr_trail += connector;
      if (length >= maxi_len) {
	maxi_len = length;
	maxi_len_strength = curr_trail > maxi_len_strength ? curr_trail : maxi_len_strength;
      }
      maxi_trail = curr_trail > maxi_trail ? curr_trail : maxi_trail;
      back_track(pie.first == connector ? pie.second : pie.first, length + 1);
      curr_trail -= connector;
      visited[pie] = false;
    }
  }
  
  curr_trail -= connector;
}

int main() {
  std::string line;
  
  while (std::getline(std::cin, line)) {
    std::string s1 = "", s2 = "";

    int dex = 0;
    while (line[dex] != '/') {
      s1.push_back(line[dex]);
      ++dex;
    }
    ++dex;
    while (dex < line.size()) {
      s2.push_back(line[dex]);
      ++dex;
    }

    int a1 = std::stoi(s1), a2 = std::stoi(s2);
    int mini = a1 < a2 ? a1 : a2, maxi = a1 > a2 ? a1 : a2; 

    piece pce = std::make_pair(mini, maxi);
    references[mini].push_back(pce);
    if (mini != maxi) {
      references[maxi].push_back(pce);
    }
    pcs.push_back(pce);
  }

  std::sort(pcs.begin(), pcs.end());
  for (auto p : pcs) {
    std::cout << p.first << " " << p.second << std::endl;
  }

  std::cout << "BACKTRACKING" << std::endl;
  
  //for (auto entry : references) {
  back_track(0, 0);
    /*    std::cout << entry.first << std::endl;
	  }*/

  std::cout << "maxi trail: " << maxi_trail << std::endl;
  std::cout << "maxi length strength " << maxi_len_strength << std::endl;
}
