#include <stdio.h>

#include "bar.h"

int main() {
  printf("main) hello world\n");
  int var;
  var = 2;
  foo(1);
  return bar(1.0);
}

void foo(int a) {
  int x = a;
  int y;
  y = a;
  printf("foo) x = %d\n", x);
  printf("%d", BAR);
}

int bar(float b) {
  if (b > 0.0) {
    return 0;
  } else {
    return -1;
  }
  // end of bar definition.
}