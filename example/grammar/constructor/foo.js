const foo = (func) => {
  func();
};

foo(() => {
  console.log("foo");
});

const bar = (param) => {
  param(1, 2);
};

bar((a, b) => {
  console.log(a + b);
});
