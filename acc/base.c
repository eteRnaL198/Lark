#include <stdio.h>

void foo(int a) {
  int x = a;
  printf("foo) x = %d\n", x);
}

int main() {
  printf("main) hello world\n");
  foo(1);
  return 0;
}
