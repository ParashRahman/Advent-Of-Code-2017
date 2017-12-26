#include <iostream>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <vector>

int bfs(std::map<int, std::vector<int>>& G) {
  // bfs
  std::queue<int> Q;
  std::set<int> visited;
  
  Q.push(0);
  
  
  while (!Q.empty()) {
    int curr = Q.front();
    Q.pop();
    if (visited.find(curr) != visited.end()) {
      continue;
    }

    visited.insert(curr);
    
    std::vector<int> n = G[curr];

    for (int v : n) {
      if (visited.find(v) == visited.end()) {
	Q.push(v);
      }
    }
  }
}

void explore(int v, std::map<int, std::vector<int>>& G, std::set<int>& visited) {
  if (visited.find(v) != visited.end()) {
    return;
  }
  visited.insert(v);
  std::vector<int> n = G[v];

  for (int e : n) {
    explore(e, G, visited);
  }
}

int cc(std::map<int, std::vector<int>>& G) {
  std::set<int> visited;
  int num_cc = 0;
  for (int i = 0; i < G.size(); ++i) {
    if (visited.find(i) == visited.end()) {
      ++num_cc;
      explore(i, G, visited);
    }
  }
  return num_cc;
}

int main() {
  std::map<int, std::vector<int>> G;

  int vert;
  while (std::cin >> vert) {
    std::string neigh;
    std::cin >> neigh;
    while (std::cin >> neigh) {
      if (neigh[neigh.size() - 1] == ',') {
	neigh.pop_back();
	G[vert].push_back(std::stoi(neigh));
      } else {
	G[vert].push_back(std::stoi(neigh));
	break;
      }
    }
  }

  std::cout << cc(G) << std::endl;
}
