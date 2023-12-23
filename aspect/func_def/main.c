int main() {
  { /* Start of advice*/
    { printf("I'm Foo\n"); }
    return 0;
  } /* End of advice */
}

int add(int a, int b) {
  // hoge
  { /* Start of advice*/
    { printf("I'm Foo\n"); }
    return 0;
  } /* End of advice */
}
