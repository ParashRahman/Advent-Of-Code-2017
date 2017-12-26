#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

int balance(std::map<std::string, int>& weight,
	     std::map<std::string, std::vector<std::string>>& g,
	    std::string word) {
 
  int sum = 0;
  std::vector<int> v;
  
  for (std::string s : g[word]) {
    int w =  balance(weight, g, s) ;
    v.push_back(w);
    sum += w;
  }

  if (v.size() > 1) {
    std::map<int, int> count;
    std::set<int> keys;
    for (int i = 0; i < v.size(); ++i) {
      count[v[i]] += 1;
      keys.insert(v[i]);
    }

    if (keys.size() > 1) {
      
      if (count[*keys.begin()] > 1) {
	auto iter = keys.begin();
	std::advance(iter, 1);
	int val = (*iter);
	int val2 = (*keys.begin());
	int dex = std::find(v.begin(), v.end(), val) - v.begin();
	int dex2 = std::find(v.begin(), v.end(), val2) - v.begin();
	std::cout << g[word][dex] << " " << weight[g[word][dex]] << " " << -1 *(*iter - *keys.begin()) <<  std::endl;
	std::cout << val << " " << val2 << std::endl;
      } else {
	auto iter = keys.begin();
	std::advance(iter, 1);
	int val = (*keys.begin());
	int val2 = (*iter);
	int dex = std::find(v.begin(), v.end(), val) - v.begin();
	int dex2 = std::find(v.begin(), v.end(), val2) - v.begin();
	std::cout << g[word][dex] << " " << weight[g[word][dex]] << " " <<  (*iter - *keys.begin()) << std::endl;
	std::cout << val << " " << val2  << std::endl;
      }
    }
    
  }
  
  return weight[word] + sum;
}

int main() {
  std::map<std::string, std::string> rev_g;
  std::map<std::string, std::vector<std::string>> g;
  std::vector<std::string> ws; 
  std::map<std::string, int> weight;
  
  std::string word;
  std::string inp;
  while (std::cin >> inp) {
    if (inp == "->") {
      std::string nword;
      std::cin >> nword;
      while (nword[nword.size()-1] == ',') {
	nword.pop_back();

	g[word].push_back(nword);
	
	rev_g[nword] = word;
	std::cin >> nword;
      }
      g[word].push_back(nword);
      rev_g[nword] = word;
    } else {
      word = inp;
      char c;
      int num;
      std::cin >> c >> num >> c;
      weight[word] = num;
      ws.push_back(word);
    }    
  }

  for (std::string w : ws) {
    if (rev_g.find(w) == rev_g.end()) {
      std::cout << w << std::endl;
      balance(weight, g, w);
      break;
    }
  }

}
