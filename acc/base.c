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
  /* Start of aspect */
  printf("aspect a=%d\n", a);
  /* End of aspect */
  int x = a;
  int y;
  y = a;
  printf("foo) x = %d\n", x);
  printf("%d", BAR);
  return 0;
}

void bar(float b) {
  /* Start of aspect */
  printf("aspect before execution of bar");
  /* End of aspect */
  b += 0.1;
  return b;
}