#include <stdio.h>

#include "bar.h"

int main() {
  printf("main) hello world\n");
  int var;
  var = 2;
  foo(1);
  return 0;
}

int foo(int a) {
  int x = a;
  int y;
  y = a;
  printf("foo) x = %d\n", x);
  printf("%d", BAR);
  return 0;
}

void bar() { return 2; }