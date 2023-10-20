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
  /* Start of aspect */
  printf("I'm Buzz Lightyear");
  /* End of aspect */
}

void foo(int a) {
  /* Start of aspect */
  printf("aspect a=%d\n", a);
  /* End of aspect */
  int x = a;
  int y;
  y = a;
  printf("foo) x = %d\n", x);
  printf("%d", BAR);
}

int bar(float b) {
  printf("bar) b = %f\n", b);
  if (b > 0.0) {
    /* Start of aspect */
    printf("aspect before execution of bar");
    /* End of aspect */
    return 0;
  } else {
    /* Start of aspect */
    printf("aspect before execution of bar");
    /* End of aspect */
    return -1;
  }
  // end of bar definition.
}
