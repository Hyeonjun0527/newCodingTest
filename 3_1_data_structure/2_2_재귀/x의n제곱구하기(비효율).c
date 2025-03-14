#include <stdio.h>

double slow_power(double x, int n) {
  int i;
  double result = 1.0;
  for (i = 0; i < n; i++)
    result *=x;
  return result;
}

double slow_power_recursive(double x, int n) {
  if (n==0) return 1;
  return x * slow_power_recursive(x,n - 1);
}

int main() {

}