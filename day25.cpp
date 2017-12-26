#include <iostream>
#include <map>

std::map<int, bool> slots;

int main() {
  char curr_state = 'A';
  int curr_pos = 0;

  int i = 0;
  while (i < 12683008) {
    ++i;
    
    if (curr_state == 'A') {
      if (slots[curr_pos] == 0) {
	slots[curr_pos] = 1;
	++curr_pos;
	curr_state = 'B';
      } else {
	slots[curr_pos] = 0;
	--curr_pos;
	curr_state = 'B';
      }
    }

    else if (curr_state == 'B') {
      if (slots[curr_pos] == 0) {
	slots[curr_pos] = 1;
	--curr_pos;
	curr_state = 'C';
      } else {
	slots[curr_pos] = 0;
	++curr_pos;
	curr_state = 'E';
      }
    }

    else if (curr_state == 'C') {
      if (slots[curr_pos] == 0) {
	slots[curr_pos] = 1;
	++curr_pos;
	curr_state = 'E';
      } else {
	slots[curr_pos] = 0;
	--curr_pos;
	curr_state = 'D';
      }
    }

    else if (curr_state == 'D') {
      slots[curr_pos] = 1;
      --curr_pos;
      curr_state = 'A';
    }

    else if (curr_state == 'E') {
      if (slots[curr_pos] == 0) {
	curr_state = 'A';
      } else {
	curr_state = 'F';
      }
      slots[curr_pos] = 0;
      ++curr_pos;
    }

    else if (curr_state == 'F') {
      if (slots[curr_pos] == 0) {
	curr_state = 'E';
      } else {
	curr_state = 'A';
      }
      
      slots[curr_pos] = 1;
      ++curr_pos;
    }
    if (i % 100000 == 0) {
      std::cout << i << std::endl;
    }
  }

  int checksum = 0;
  std::cout << slots.size() << std::endl;
  for (auto entry : slots) {
    checksum += entry.second;
  }

  std::cout << checksum << std::endl;
}
