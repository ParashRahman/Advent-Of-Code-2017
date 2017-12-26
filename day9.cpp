#include <iostream>
#include <stack>

int main() {
  std::stack<int> S;

  char c;
  char trash;
  bool garbage_mode = false;

  int score = 0;
  int gscore = 0;
  
  while (std::cin >> c) {
    if (garbage_mode && c == '!') {
      std::cin >> trash;
      continue;
    }

    if (garbage_mode && c == '>') {
      garbage_mode = false;
    } else if (garbage_mode) {
      ++gscore;
      continue;
    }

    if (c == '<') {
      garbage_mode = true;
    }

    if (c == '{') {
      S.push('{');
    }

    if (c == '}') {
      score += S.size();
      S.pop();
    }
    
    std::cout << c;
  }

  std::cout << std::endl << score << std::endl << gscore << std::endl;
}
