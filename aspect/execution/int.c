#include <stdio.h>

typedef unsigned int uint;

uint foo() {
  { /* Start of advice*/
    printf("before execution\n");
  } /* End of advice */

  { /* Start of advice*/
    printf("before execution\n");
  } /* End of advice */

  { /* Start of advice*/
    printf("before execution\n");
  } /* End of advice */

  printf("void foo\n");
  return 1;
}

int main() {
  int num = foo();
  printf("num = %d\n", num);
  return 0;
}