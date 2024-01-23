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
  printf("baaaaaz");
  return;
}

void foo(int a) {
  printf("foo) a = %d\n", a);
  return;
}

int bar(float b) {
  printf("bar) b = %f\n", b);
  return 0;
  // end of bar definition.
}

void hoge() {
  printf("hoge\n");
  return;
}