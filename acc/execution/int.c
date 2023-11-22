#include <stdio.h>

int foo() {
  printf("void foo\n");
  return 1;
}

int main() {
  int num = foo();
  printf("num = %d\n", num);
  return 0;
}