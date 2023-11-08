#include <stdio.h>

void foo() {
  int x = 5;
  {
    // int x = 1 + 2;
    // return 10;
    x = 3;
  }
  printf("foo: %d\n", x);
}

int main() {
  foo();
  return 0;
}