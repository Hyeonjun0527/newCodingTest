int fib_iter(int n) {
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;
  int result = 0;
  int pp = 0; // n-2값보관
  int p = 1;  // n-1값보관
  for (int i = 2; i <= n; i++) {
    result = p + pp; // 현재항값계산
    pp = p;          // n-2값보관
    p = result;      // n-1값보관
  }
  return result;
}

int mem_fib[50] = {
    0,
};
int fib(int n) {
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;
  if (mem_fib[n] == 0)
    mem_fib[n] = (fib(n - 1) + fib(n - 2));
  return mem_fib[n];
}
