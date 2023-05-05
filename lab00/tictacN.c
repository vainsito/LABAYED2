#include <stdlib.h>  
#include <stdio.h>   
#include <stdbool.h> 

#include <assert.h>  

#define SIZE 100

#define CELL_MAX (SIZE * SIZE - 1)

void print_sep(int length) {
    printf("\t ");
    for (int i=0; i < length;i++) printf("................");
    printf("\n");

}

void print_board(char board[SIZE][SIZE])
{
    int cell = 0;

    print_sep(SIZE);
    for (int row = 0; row < SIZE; ++row) {
        for (int column = 0; column < SIZE; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(SIZE);
    }
}

char comp(char a[SIZE]){
    bool igual = true;
    char res = '-';
    for (int i = 1; i < SIZE ; i++){
      igual = igual && (a[i]==a[i-1]);
    }
    if(igual){
      res=a[0];
    }
    return res;
  }

char get_winner(char board[SIZE][SIZE])
{
  char winner = '-'; 
  char cells[SIZE];

    for (int i=0;i < SIZE && winner=='-';i++ ){ 
       
      for(int j=0;j < SIZE && winner=='-';j++ ){
        cells[j]=board[i][j]; 
      }

      if (comp(cells) == 'X'){
        winner = 'X';
      } else if (comp(cells) == 'O'){
        winner = 'O';
      } 
    }
    
  

    for ( int i = 0 ;i < SIZE && winner=='-';i++ ){ 
      for(int j=0;j < SIZE && winner=='-';j++ ){
        cells[j]=board[j][i]; 
      }

      if (comp(cells) == 'X'){
        winner = 'X';
      } else if (comp(cells) == 'O'){
        winner = 'O';
      } 
    }

    if(winner=='-'){
    for(int j=0;j < SIZE && winner=='-';j++ ){
        cells[j]=board[j][j]; 
      }
      if (comp(cells) == 'X'){
        winner = 'X';
      } else if (comp(cells) == 'X'){
        winner = 'O';
      }
    }
      
    if(winner=='-'){

    for(int i=0,j=(SIZE-1);i < SIZE && j > -1 && winner=='-';i++,j--){
        cells[i]=board[i][j]; 
      }
      if (comp(cells) == 'X'){
        winner = 'X';
      } else if (comp(cells) == 'O'){
        winner = 'O';
      }
  }
    return winner;
}

bool has_free_cell(char board[SIZE][SIZE])
{
    bool free_cell=false;

    for ( int i=0;i < SIZE && !free_cell;i++ ){
      for ( int j=0;j < SIZE && !free_cell;j++ ){
        free_cell=(board[i][j] =='-');
      }
    } 
   
    return free_cell;
}

int main(void)
{
    printf("TicTacToe [InCoMpLeTo :'(]\n");

    char board[SIZE][SIZE];
    for ( int i=0;i < SIZE ;i++ ){
    for ( int j=0;j < SIZE ;j++ ){
        board[i][j]='-';
      }
    } 

    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);
        printf("\nTurno %c - Elija posición (número del 0 al %d): ", turn,
               CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0) {
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX) {
            int row = cell / SIZE;
            int colum = cell % SIZE;
            if (board[row][colum] == '-') {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            } else {
                printf("\nCelda ocupada!\n");
            }
        } else {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Ganó %c\n", winner);
    }
    return 0;
}