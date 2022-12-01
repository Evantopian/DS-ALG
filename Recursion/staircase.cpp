#include <iostream>


int steps(int n) {
  if (n == 0)
    return 1;

  int result = 0;
  for (int i = 1; i <= 3; i++) {
    int ways = n - i;

    if (ways >= 0)
      result += steps(ways);
  }

  return result;
}


int steps_iter(int n) {
  if (n < 2)
    return 1;

  int a = 1, b = 1, c = 2;
  int result = 0;

  while (n > 2) {
    result = a + b + c;
    a = b;
    b = c;
    c = result;
    n--;
  }
  return c;
}


int steps_tail(int n, int a, int b, int c) {
  if (n == 0) {
    return a;
  } else {
    return steps_tail(n - 1, b, c, a + b + c);
  }
}


int step_table[10000];

int step_dyn(int n) {
  if (n < 2) {
    return 1;
  } else if (step_table[n] != 0) {
    return step_table[n];
  } else {
    int tmp = steps_tail(n, 1, 1, 2);
    step_table[n] = tmp;
    return tmp;
  }
}


int main() {
  int n = 7;
  //std::cout << steps(n) << std::endl;
  //std::cout << steps_iter(n) << std::endl;
  //std::cout << steps_tail(n, 1, 1, 2) << std::endl;
  std::cout << step_dyn(7);
}
