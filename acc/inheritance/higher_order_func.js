const func = (param) => {
  param(1, 2);
};

func((a, b) => {
  console.log(a + b);
});
