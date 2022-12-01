#include <iostream>
#include <unistd.h>


// recursively code knight's tour.


void print_arr(int * * arr, int n) {
  std::cout << "\n";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%3d", arr[i][j]);
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}


void k_tour(int * * board, int n, int r, int c, int mov, bool & goal) {

  if (mov == n * n + 1) {
    goal = false;
    return;
  }

  if (r < 0 || c < 0 || r >= n || 
      c >= n || board[r][c] != 0) {
    return;
  }

  board[r][c] = mov;

  if (goal) k_tour(board, n, r - 2, c + 1, mov + 1, goal);
  if (goal) k_tour(board, n, r - 1, c + 2, mov + 1, goal);
  if (goal) k_tour(board, n, r + 2, c - 1, mov + 1, goal);
  if (goal) k_tour(board, n, r + 1, c - 2, mov + 1, goal);
  if (goal) k_tour(board, n, r + 2, c + 1, mov + 1, goal);
  if (goal) k_tour(board, n, r + 1, c + 2, mov + 1, goal);
  if (goal) k_tour(board, n, r - 2, c - 1, mov + 1, goal);
  if (goal) k_tour(board, n, r - 1, c - 2, mov + 1, goal);

  if (goal) board[r][c] = 0;
}


int main() {
  // init arr
  int n = 5;
  int * * board;
  board = new int * [n];

  for (int i = 0; i < n; i++) {
    board[i] = new int[n];
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      board[i][j] = 0;
    }
  }

  // (2, 2) works

  bool valid = true;
  std::cout << "Solution Using: R = 1, C = 1\n";
  k_tour(board, n, 1, 1, 1, valid);
  print_arr(board, n);


  for (int i = 0; i < n; i++) {
    delete [] board[i];
  }
  delete board;

  std::cout << std::endl;
}
