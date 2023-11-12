#include <stdio.h>

#include "bar.h"

int main() {
  printf("main) hello world\n");
  int var;
  var = 2;
  foo(1);
  return bar(1.0);
}

void baz() {
  print("baaaaaz");
  return;
}

void foo(int a) {
  printf("foo) a = %d\n", a);
  return;
}

int bar(float b) {
  printf("bar) b = %f\n", b);
  if (b > 0.0) {
    return 0;
  } else {
    return -1;
  }
  // end of bar definition.
}
