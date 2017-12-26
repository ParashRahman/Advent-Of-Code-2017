#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

const int L = 0; const int U = 1;
const int R = 2; const int D = 3;

struct Pos {
  int r;
  int c;
  int dir;
};

int get_right(int dir) {
  switch(dir) {
  case U:
    dir = R;
    break;
  case R:
    dir = D;
    break;
  case D:
    dir = L;
    break;
  case L:
    dir = U;
    break;
  }
  
  return dir;
}

int get_left(int dir) {
  switch(dir) {
  case U:
    dir = L;
    break;
  case R:
    dir = U;
    break;
  case D:
    dir = R;
    break;
  case L:
    dir = D;
    break;
  }
  
  return dir;
}

int get_reverse(int dir) {
  switch(dir) {
  case U:
    dir = D;
    break;
  case R:
    dir = L;
    break;
  case D:
    dir = U;
    break;
  case L:
    dir = R;
    break;
  }
  
  return dir;
}

int main() {
  std::vector<std::string> board;
  std::map< std::pair<int,int>, char > eboard;
  
  std::string line;

  while (std::getline(std::cin, line)) {
    board.push_back(line);
  }
  
  Pos curr;
  curr.r = board.size() / 2;
  curr.c = board[0].size() / 2;
  curr.dir = U;

  int count = 0;
  for (int iter = 0; iter < 10000000; ++iter) {
    if (curr.r < 0 || curr.c < 0 || curr.r >= board.size() ||
	curr.c >= board.size()) {
      std::pair<int,int> point = std::make_pair(curr.r, curr.c);
      if (eboard.find(point) == eboard.end() || eboard[point] == '.') {
	curr.dir = get_left(curr.dir);
        eboard[point] = 'W';
      } else if (eboard[point] == '#') {
	curr.dir = get_right(curr.dir);
	eboard[point] = 'F';
      } else if (eboard[point] == 'W') {
	eboard[point] = '#';
	++count;
      } else if (eboard[point] == 'F') {
	eboard[point] = '.';
	curr.dir = get_reverse(curr.dir);
      }
    } else if (board[curr.r][curr.c] == '#') {
      curr.dir = get_right(curr.dir);
      board[curr.r][curr.c] = 'F';
    } else if (board[curr.r][curr.c] == '.') {
      curr.dir = get_left(curr.dir);
      board[curr.r][curr.c] = 'W';
      
    } else if (board[curr.r][curr.c] == 'W') {
      board[curr.r][curr.c] = '#';
      ++count;
    } else if (board[curr.r][curr.c] == 'F') {
      board[curr.r][curr.c] = '.';
      curr.dir = get_reverse(curr.dir);
    }

    switch (curr.dir) {
    case U:
      --curr.r;
      break;
    case R:
      ++curr.c;
      break;
    case D:
      ++curr.r;
      break;
    case L:
      --curr.c;
      break;
    }
  }

  std::cout << board.size() << "  " << board[0].size() << "  " << count << std::endl;
}
