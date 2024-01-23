int main() {
  { /* Start of advice*/
    {
      { printf("Aspect.method"); }
      { printf("Base.method2"); }
      printf("HelloWorld\n");
    }
  } /* End of advice */

  int a = 1;
  int b = 2;
  int sum = a + b;
  return 0;
}