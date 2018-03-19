#include <stdio.h>
#include <stdlib.h>
#ifndef MAX_X
#define MAX_X 8
#endif
#ifndef MAX_Y
#define MAX_Y 8
#endif

// int neighbours;
// void start_game;

void start_game(short int* board){
  board[MAX_X*MAX_Y] = 0;
  board[1*MAX_X+3] = 1;
  board[1*MAX_X+4] = 1;
  board[2*MAX_X+3] = 1;
  board[2*MAX_X+4] = 1;
  board[1*MAX_X+3] = 1;
  board[1*MAX_X+4] = 1;
  board[4*MAX_X+3] = 1;
  board[6*MAX_X+3] = 1;
  board[5*MAX_X+2] = 1;
  board[5*MAX_X+4] = 1;
}

void print_board(short int* board){
  int i;
  for(i=0;i<MAX_X*MAX_Y;i++){
    if(i%MAX_X == 0)
    printf("\n");
      printf("%d\t",board[i]);
  }
  printf("\n");
}

void print_num_neighbours(int* num_neighbours){
  int i;
  for(i=0;i<MAX_X*MAX_Y;i++){
    if(i%MAX_X == 0)
    printf("\n");
      printf("%d\t",num_neighbours[i]);
  }
  printf("\n");
}


int* neighbours(short int* board){
  static int num_neighbours[MAX_X*MAX_Y] = {0};
  int i,j;
  for(i=1;i<MAX_X-1;i++){
    for(j=1;j<MAX_X-1;j++){
      num_neighbours[i+MAX_X*j] = board[(i-1)+MAX_X*(j-1)]+board[(i-1)+MAX_X*(j)]+board[(i-1)+MAX_X*(j+1)]+
                       board[(i)+MAX_X*(j-1)]+board[(i)+MAX_X*(j+1)]+
                       board[(i+1)+MAX_X*(j-1)]+board[(i+1)+MAX_X*(j)]+board[(i+1)+MAX_X*(j+1)];
    }
  }

  // bordas
  // borda de cima
  j = 0;
  for(i=0;i<MAX_X;i++){
      num_neighbours[i+MAX_X*j] = board[(i)+MAX_X*(j+1)]+board[(i)+MAX_X*(j)];
      if(i!=0){ // se nao for o canto superior esquerdo
        num_neighbours[i+MAX_X*j] += board[(i-1)+MAX_X*(j)]+board[(i-1)+MAX_X*(j+1)];
      }
      if(i!=MAX_X){// se nao for o canto superior direito
        num_neighbours[i+MAX_X*j] += board[(i+1)+MAX_X*(j)]+board[(i+1)+MAX_X*(j+1)];
      }
  }
  // borda de baixo
  j = MAX_Y-1;
  for(i=0;i<MAX_X;i++){
      num_neighbours[i+MAX_X*j] = board[(i)+MAX_X*(j-1)]+board[(i)+MAX_X*(j)];
      if(i!=0){ // se nao for o canto inferior esquerdo
        num_neighbours[i+MAX_X*j] += board[(i-1)+MAX_X*(j)]+board[(i-1)+MAX_X*(j-1)];
      }
      if(i!=MAX_X){// se nao for o canto inferior direito
        num_neighbours[i+MAX_X*j] += board[(i+1)+MAX_X*(j)]+board[(i+1)+MAX_X*(j-1)];
      }
  }
  //borda da esquerda
  i = 0;
  for(j=1;j<MAX_X-1;j++){
    num_neighbours[i+MAX_X*j] =  board[(i)+MAX_X*(j-1)]+board[(i)+MAX_X*(j+1)]+
                     board[(i+1)+MAX_X*(j-1)]+board[(i+1)+MAX_X*(j)]+board[(i+1)+MAX_X*(j+1)];
  }
  //borda da direita
  i = MAX_X-1;
  for(j=1;j<MAX_X-1;j++){
    num_neighbours[i+MAX_X*j] =  board[(i-1)+MAX_X*(j-1)]+board[(i-1)+MAX_X*(j)]+board[(i-1)+MAX_X*(j+1)]+
                     board[(i)+MAX_X*(j-1)]+board[(i)+MAX_X*(j+1)];
  }
  print_num_neighbours(num_neighbours);
  return num_neighbours;
}

void run_step(short int* board_current,short int* board_next){
  int* neighbours_array = malloc(sizeof(int)*sizeof(board_current)/sizeof(short int));
  neighbours_array = neighbours(board_current);
  int i,j;
  for(i=1;i<MAX_X-1;i++){
    for(j=1;j<MAX_X-1;j++){
      if(neighbours_array[i+MAX_X*j]==3 ){
        board_next[i+MAX_X*j] = 1;
      }
      else{
        if(board_current[i+MAX_X*j]==1 && neighbours_array[i+MAX_X*j]==2 ){
          board_next[i+MAX_X*j] = 1;
        }
        else{
          board_next[i+MAX_X*j] = 0;
        }
      }
    }
  }
}

int main(int argc,char** argv){
  printf("Teste");
  short int *board_current,*board_next;
  board_current = malloc(MAX_X*MAX_Y*sizeof(short int));
  board_next = malloc(MAX_X*MAX_Y*sizeof(short int));
  start_game(board_current);
  print_board(board_current);
  run_step(board_current,board_next);
  printf("------------------ Passo 1 --------------");
  print_board(board_next);
}
