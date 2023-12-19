#include <stdio.h>

int main() {
  { /* Start of advice*/
    { printf("GrandParent\n"); }
  } /* End of advice */

  printf("Hello World\n");
  return 0;
}