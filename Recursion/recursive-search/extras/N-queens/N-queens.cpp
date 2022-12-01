#include <iostream>

std::string field = " . ";
std::string q_path = " x ";
std::string queen = " Q ";


void print_arr(std::string **arr, int n){
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      std::cout << arr[i][j] << " \n"[j == n-1];
    }
  }
  std::cout << "\n";
}


void n_queens(std::string **board, int n, int r, int c){
  
  if (n == 0) return;
  
  // if out of bounds for queen:
  if (r < n-1 || c < n-1 || 
      r > n || c > n || board[r][c] == q_path)
    return;
  

  // current queen location, make walls for vert, hori, & diag.
  if (board[r][c] != q_path && board[r][c] == field){
    board[r][c] = queen;
  } 

  print_arr(board, n);

  // Possible queen movements:

  // vertical
  
  for (int i = 0; i < n; i++){

    n_queens(board, n, r-i, c);
  }

  // horizontal
  for (int i = 0; i < n; i++)
    n_queens(board, n, r, c-i);
  
  // diagonal right
  for (int i = n; i > 0; i--)
    n_queens(board, n, r-i, c-i);

  // diagonal left
  for (int i = 0; i < n ; i++)
    n_queens(board, n, r-i, c-i);

}


int main(){

  // init arr
  int n = 5;
  std::string **board;
  board = new std::string *[n];

  for (int i = 0; i < n; i++){
    board[i] = new std::string[n];
  }

  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      board[i][j] = field;
    }
  }

  n_queens(board, n, n-(n/2), n-(n/2)); 


}
