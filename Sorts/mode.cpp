#include <iostream>
#include <vector>
#include <sys/time.h>


void print_vector(std::vector<int> vec) {
  for (auto it : vec) {
    std::cout << it << ", ";
  }
  std::cout << "\n";
}

int count(std::vector<int> vec, int x) {
  int cnt = 0;

  for (int i = 0; i < vec.size(); i++) {
    if (vec[i] == x) {
      cnt++;
    }
  }
  return cnt;
}


int largest(std::vector<int> vec) {
  int max = 0;

  for (int i = 0; i < vec.size(); i++) {
    if (vec[i] > max) {
      max = vec[i];
    }
  }
  return max;
}


int mode(std::vector<int> vec) {
  int mode = 0, freqs = 0;

  for (int i = 0; i < vec.size(); i++) {
    if (count(vec, vec[i]) > freqs) {
      freqs = count(vec, vec[i]);
      mode = vec[i];
    }
  }
  return mode;
}


std::vector<int> makeVec(int n, int max) {
  std::vector<int> vec(n);

  for (int i = 0; i < n; i++) {
    vec.at(i) = rand() % max;
  }
  return vec;
}


int main() {
  srand(time(nullptr));
  std::vector<int> v1 = makeVec(10, 10);

  std::cout << "Vec:\n\t";
  print_vector(v1);

  std::cout << "\n\nFrequency of 0s: " << count(v1, 0) << "\n";
  std::cout << "Frequency of 1s: " << count(v1, 1) << "\n\n";

  std::cout << "Largest value in Vec: " << largest(v1) << "\n\n";
  std::cout << "Mode: " << mode(v1) << std::endl;

  return 0;
}
