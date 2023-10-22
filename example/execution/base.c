#include <stdio.h>

void greet() {
  printf("Hello\n");
  return;
}

int calc_abs(int num) {
  int abs;
  if (num > 0) {
    abs = num;
    return abs;
  } else {
    abs = num * (-1);
    return abs;
  }
}

int main() {
  greet();
  printf("%d\n", calc_abs(-10));
  return 0;
}
