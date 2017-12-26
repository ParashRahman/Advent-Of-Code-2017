#include <iostream>

struct node {
  int val;
  node *next;
};

int main() {
  node *head = new node;
  head->val = 0;
  head->next = head;

  node *curr = head;

  for (int i = 1; i <= 50000000; ++i) {
    if (i % 1000000 == 0) {
      std::cout << i << std::endl;
    }
    node *nnode = new node;
    nnode->val = i;

    for (int t = 0; t < 376; ++t) {
      curr = curr->next;
    }

    node *temp = curr->next;
    curr->next = nnode;
    nnode->next = temp;
    curr = nnode;
  }

  while (curr->val != 0) {
    curr = curr->next;
  }

  std::cout << curr->next->val << std::endl;
}
