int calc_abs(int num) {
  /* Start of aspect */
  printf("num: %d\n", num);
  /* End of aspect */
  int abs;
  if (num > 0) {
    abs = num;
    /* Start of aspect */
    printf("abs: %d\n", abs);
    /* End of aspect */
    return abs;
  } else {
    abs = num * (-1);
    /* Start of aspect */
    printf("abs: %d\n", abs);
    /* End of aspect */
    return abs;
  }
}