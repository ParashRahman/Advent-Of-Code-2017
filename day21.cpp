#include <iostream>
#include <map>
#include <string>
#include <vector>

std::map<std::vector< std::vector<char> >, std::vector< std::vector<char> > > rule_dict;
struct Rule {
  std::vector< std::vector<char> > from;
  std::vector< std::vector<char> > to;

  Rule(std::string f, std::string t) {
    int dex = 0;
    from.push_back(std::vector<char>());
    while (dex < f.size()) {
      if (f[dex] != '/') {
	from[from.size() - 1].push_back(f[dex]);
      } else {
	from.push_back(std::vector<char>());
      }
      ++dex;
    }
    dex = 0;
    to.push_back(std::vector<char>());
    while (dex < t.size()) {
      if (t[dex] != '/') {
	to[to.size() - 1].push_back(t[dex]);
      } else {
	to.push_back(std::vector<char>());
      }
      ++dex;
    }
  }
};

/**
   
   0 1 2    6 3 0
   3 4 5 -> 7 4 1
   6 7 8    8 5 2

   0 1 2    6 7 8    8 7 6
   3 4 5 -> 3 4 5 -> 5 4 3
   6 7 8    0 1 2    2 1 0

   0 1 2    0 3 6    6 3 0
   3 4 5 -> 1 4 7 -> 7 4 1
   6 7 8    2 5 8    8 5 2

   0 1 2    2 1 0    6 3 0
   3 4 5 -> 5 4 3 -> 7 4 1
   6 7 8    8 7 6    8 5 2

   01 -> 23 
   23    01

   01 -> 10
   23    32
 **/

void flip_vert(std::vector< std::vector<char> >& v) {
  for (int c = 0; c < v.size()/2; ++c) {
    for (int r = 0; r < v.size(); ++r) {
      char temp = v[r][v.size()-c-1];
      v[r][v.size()-c-1] = v[r][c];
      v[r][c] = temp;
    }
  }
}

void flip_diag(std::vector< std::vector<char> >& v) {
  for (int c = 0; c < v.size(); ++c) {
    for (int r = 0; r < v.size() - c;++r) {
      char temp = v[v.size()-c-1][v.size()-r-1];
      v[v.size()-c-1][v.size()-r-1] = v[r][c];
      v[r][c] = temp;
    }
  }
}

std::vector< std::vector<char> > dict_result(std::vector< std::vector<char> > key) {
  std::vector< std::vector<char> > result;
  for (int i = 0; i < 4; ++i) {
    if (rule_dict.find(key) != rule_dict.end()) {
      result = rule_dict[key];      
      return result;
    }
    flip_vert(key);
    flip_diag(key);
  }
  
  flip_vert(key);
  
  for (int i = 0; i < 4; ++i) {
    if (rule_dict.find(key) != rule_dict.end()) {
      result = rule_dict[key];
      return result;
    }
    flip_vert(key);
    flip_diag(key);
  }
}

std::vector< std::vector<char> > next_iter(std::vector< std::vector<char> > first_iter) {
  int divider = first_iter.size() % 2 == 0 ? 2 : 3;
  
  std::vector< std::vector<char> > ret_iter(first_iter.size() + first_iter.size() / divider, std::vector<char>(first_iter.size() + first_iter.size() / divider));

  for (int r = 0; r < ret_iter.size() / (divider + 1); ++r) {
    for (int c = 0; c < ret_iter.size() / (divider + 1); ++c) {
      std::vector< std::vector<char> > from(divider, std::vector<char>(divider));

      for (int fr = 0; fr < divider; ++fr) {
	for (int fc = 0; fc < divider; ++fc) {
	  from[fr][fc] = first_iter[divider*r+fr][divider*c+fc];
	}
      }
      
      std::vector< std::vector<char> > value = dict_result(from);

      for (int tr = 0; tr < divider + 1; ++tr) {
	for (int tc = 0; tc < divider + 1; ++tc) {
	  ret_iter[tr + r * (divider+1)][tc + c * (divider+1)] = value[tr][tc];
	}
      }
    }
  }

  return ret_iter;
}

int main() {
  std::string from, trash, to;
  while (std::cin >> from >> trash >> to) {
    Rule r(from, to);
    rule_dict[r.from] = r.to;
  }

  std::vector< std::vector<char> > ation = { {'.', '#', '.'},
					     {'.', '.', '#'},
					     {'#', '#', '#'} };

  for (int iter = 0; iter < 18; ++iter) {
    ation = next_iter(ation);
    int count = 0;
    for (int r = 0; r < ation.size(); ++r) {
      for (int c = 0; c < ation.size(); ++c) {
	if (ation[r][c]=='#') {
	  ++count;
	}
	std::cout << ation[r][c];
      }
      std::cout << std::endl;
    }

    std::cout << count << std::endl;
  }
  
}
