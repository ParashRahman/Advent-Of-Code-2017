#include <iostream>
#include <string>
#include <vector>

const int L = 0;
const int R = 1;
const int D = 2;
const int U = 3;

struct point {
  int r;
  int c;
  int dir;
};

int main() {
  std::vector<std::string> graph;

  std::string line;
  while (std::getline(std::cin, line)) {
    graph.push_back(line);
  }
  
  point curr;
  curr.r = 0;
  curr.c = 0;
  while (graph[curr.r][curr.c] != '|') {++curr.c;}
  curr.dir = D;

  std::vector<char> letters;
  int ss = 0;
  
  while (true) {
    std::cout << graph[curr.r][curr.c] << std::endl;
    char ccur;
    switch (curr.dir) {
    case L:
      do {--curr.c; ++ss;} while (graph[curr.r][curr.c] == '|');
      ccur = graph[curr.r][curr.c];
      if ((ccur >= 'a' && ccur <= 'z') ||
	  (ccur >= 'A' && ccur <= 'Z')) {
	letters.push_back(ccur);
      } else if (ccur == '+') {
	if (curr.c - 1 < 0 || graph[curr.r][curr.c - 1] == ' ') {
	  std::cout << "LAST THING" << std::endl;
	  if (curr.r - 1 >= 0 && graph[curr.r - 1][curr.c] != ' ') {
	    std::cout << "DISS" << std::endl;
	    curr.dir = U;
	  } else {
	    std::cout << "OR DISS" << std::endl;
	    curr.dir = D;
	  }
	}
      }
      break;
    case R:
      do {++curr.c; ++ss;} while (graph[curr.r][curr.c] == '|');
      ccur = graph[curr.r][curr.c];
      if ((ccur >= 'a' && ccur <= 'z') ||
	  (ccur >= 'A' && ccur <= 'Z')) {
	letters.push_back(ccur);
      } else if (ccur == '+') {
	if (curr.c + 1 >= graph[curr.r].size() || graph[curr.r][curr.c + 1] == ' ') {
	  if (curr.r - 1 >= 0 && graph[curr.r - 1][curr.c] != ' ') {
	    curr.dir = U;
	  } else {
	    curr.dir = D;
	  }
	}
      }
      break;
    case U:
      do {--curr.r; ++ss;} while (graph[curr.r][curr.c] == '-');
      ccur = graph[curr.r][curr.c];
      if ((ccur >= 'a' && ccur <= 'z') ||
	  (ccur >= 'A' && ccur <= 'Z')) {
	letters.push_back(ccur);
      } else if (ccur == '+') {
	if (curr.r - 1 < 0 || graph[curr.r - 1][curr.c] == ' ') {
	  if (curr.c - 1 >= 0 && graph[curr.r][curr.c - 1] != ' ') {
	    curr.dir = L;
	  } else {
	    curr.dir = R;
	  }
	}
      }
      break;
    case D:
      do {++curr.r; ++ss;} while (graph[curr.r][curr.c] == '-');

      ccur = graph[curr.r][curr.c];
      if ((ccur >= 'a' && ccur <= 'z') ||
	  (ccur >= 'A' && ccur <= 'Z')) {
	letters.push_back(ccur);
      } else if (ccur == '+') {
	if (curr.r + 1 >= graph.size() || graph[curr.r + 1][curr.c] == ' ') {
	  if (curr.c - 1 >= 0 && graph[curr.r][curr.c - 1] != ' ') {
	    curr.dir = L;
	  } else {
	    curr.dir = R;
	  }
	}
      }
      break;
    }

    if (ccur == 'Y') {
      break;
    }
  }

  for (char le : letters) {
    std::cout << le;
  }
  std::cout << std::endl;
  std::cout << ss << std::endl;
}
