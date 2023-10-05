#include <stdio.h>

#include "bar.h"

void foo(int a) {
  int x = a;
  int y;
  y = a;
  printf("foo) x = %d\n", x);
  printf("%d", BAR);
}

int main() {
  printf("main) hello world\n");
  foo(1);
  int var;
  var = 2;
  return 0;
}
