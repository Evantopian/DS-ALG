#include <iostream>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/time.h>
#include <math.h>


void print_vector(std::vector<int> vec) {
  for (auto it : vec) {
    std::cout << it << ", ";
  }
  std::cout << "\n";
}


int find_min(std::vector<int> vec, int begin) {
  int min = begin;
  for (int i = begin; i < vec.size(); i++) {
    if (vec[i] < vec[min]) {
      min = i;
    }
  }
  return min;
}


std::vector<int> ssort(std::vector<int> vec) {
  for (int i = 0; i < vec.size(); i++) {
    int min, tmp;
    min = find_min(vec, i);

    tmp = vec[i];
    vec[i] = vec[min];
    vec[min] = tmp;
  }
  return vec;
}


std::vector<int> merge(std::vector<int> left, std::vector<int> right) {
  std::vector<int> merged;
  int l = 0, r = 0;

  while (l < left.size() && r < right.size()) {
    if (left[l] < right[r]) {
      merged.push_back(left[l]);
      l++;
    } else {
      merged.push_back(right[r]);
      r++;
    }
  }

  while (l < left.size()) {
    merged.push_back(left[l]);
    l++;
  }
  while (r < right.size()) {
    merged.push_back(right[r]);
    r++;
  }

  return merged;
}


// found error with last merge, fixed.
// Was previously slower than quick sort despite being later on.
std::vector<int> msort(std::vector<int> v) {
  if (v.size() < 2) return v;

  int s = v.size();
  std::vector<int> left, right;

  for (int i = 0; i < s; i++) {
    if (i < s / 2) {
      left.push_back(v[i]);
    } else {
      right.push_back(v[i]);
    }
  }
  left = msort(left);
  right = msort(right);

  return merge(left, right);
}


std::vector<int> makeVec(int n, int max) {
  std::vector<int> vec(n);

  for (int i = 0; i < n; i++) {
    vec.at(i) = rand() % max;
  }
  return vec;
}


// qsort from class.
std::vector<int>qsort(std::vector<int> list) {
  int i, j;

  if (list.size() <= 1) return list; // base case

  int pivot = list[0]; // using index 0 as piviot for general testing.

  std::vector<int> lower, upper;

  // min max.
  for (i = 1; i < list.size(); i++) {
    if (list[i] < pivot) {
      lower.push_back(list[i]);
    } else {
      upper.push_back(list[i]);
    }
  }
  // recursive calls to sort vector.
  lower = qsort(lower);
  upper = qsort(upper);

  // shoving new values of lower & upper into list.
  for (i = 0; i < lower.size(); i++)
    list[i] = lower[i];

  list[i] = pivot;
  i++;

  for (j = 0; j < upper.size(); j++) {
    list[i] = upper[j];
    i++;
  }
  return list;
}


// In-place quick sort.
// Credit: https://www.geeksforgeeks.org/iterative-quick-sort/

void swap(int * a, int * b) {
  int temp = * a;
  * a = * b;
  * b = temp;
}


/* This function takes last element as pivot,
   places the pivot element at its correct
   position in sorted  array, and places
   all smaller (smaller than pivot) to left
   of pivot and all greater elements to
   right of pivot */

int partition(std::vector<int> & arr, int l, int h) {
  int x = arr[h];
  int i = (l - 1);

  for (int j = l; j <= h - 1; j++) {
    if (arr[j] <= x) {
      i++;
      swap( & arr[i], & arr[j]);
    }
  }
  swap( & arr[i + 1], & arr[h]);
  return (i + 1);
}


/*
A[] --> Array to be sorted,
l --> Starting index,
h --> Ending index
*/

void qsort2(std::vector<int> & A, int l, int h) {
  if (l < h) {
    /* Partitioning index */
    int p = partition(A, l, h);
    qsort2(A, l, p - 1);
    qsort2(A, p + 1, h);
  }
}


// Arugment passing + Main

void print_help(char * command_name) {
  std::cout << "Usage: " << command_name;
  std::cout << " [-h|-p|-m N|-s N|-a algorithm]\n\n";
  std::cout << " -m MAX_ELEMENT_SIZE\n";
  std::cout << " -s DATA_SET_SIZE\n";
  std::cout << " -a[s|m]: s - selection, m - merge, q - qsort, r - qsort2 (iterative)\n";
}


extern char * optarg;

int main(int argc, char * argv[]) {

  int size = 20;
  int max_val = 100;
  char algorithm = 's' ;
  bool print = false;
  char c;

  while ((c = getopt(argc, argv, "phs:m:a:")) != -1) {

    switch (c) {
    case 'h' :
      print_help(argv[0]);
      exit(0);
      break;
    case 'p' :
      print = true;
      break;
    case 's' :
      size = std::stoi(optarg);
      break;
    case 'm' :
      max_val = std::stoi(optarg);
      break;
    case 'a':
      algorithm = optarg[0];
    }
  }


  srand(time(nullptr));
  std::vector<int> a(size);
  int i;
  for (i = 0; i < size; i++) {
    a[i] = rand() % max_val;
  }


  if (print) {
    print_vector(a);
    std::cout << "\n";
  }

  std::cout << "Starting the sort!\n";
  struct timeval tp;

  gettimeofday( & tp, NULL);
  long start_time = tp.tv_sec * 1000 + tp.tv_usec / 1000;

  switch (algorithm) {
  case 's':
    a = ssort(a);
    break;
  case 'm':
    a = msort(a);
    break;
  case 'q':
    a = qsort(a);
    break;
  case 'r':
    qsort2(a, 0, a.size()-1);
    //qsort2(a, 0, a.size() - 1);

    break;
  }

  gettimeofday( & tp, NULL);
  long current_time = tp.tv_sec * 1000 + tp.tv_usec / 1000;

  long elapsed = current_time - start_time;

  if (print) {
    print_vector(a);
  }

  std::cout << "Algorithm: " << algorithm << "\n";
  std::cout << "Time: " << elapsed << "\n";

  return 0;
}
