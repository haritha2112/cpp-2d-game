#include <iostream>
int i = 7;

namespace MySpace {
  void f(int x) {
    x = x + 1;
  }
  int i = 17;
}

void f(int x) {
  x = x + 1;
}

int main() {
  int i = 99;
  f(i);
  std::cout << "i is: " << i << std::endl;
}
