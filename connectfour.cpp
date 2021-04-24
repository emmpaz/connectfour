#include <iostream>
#include <ncurses.h>
#define BIT_SET(num,bit)   ((num) |=  (1<<(bit)))
#define BIT_CLEAR(num,bit) ((num) &= ~(1<<(bit)))
#define BIT_CHECK(num,bit) ((num) &   (1<<(bit)))
#define OFFSETR 2
#define OFFSETC 28
#include "connectfour.h"



void printBoardwCursor(connectfour *c, int posR, int posC){//this took longer than expected...
  attron(COLOR_PAIR(PLAYER_ONE));
  mvprintw(0, 15, "PLAYER ONE = RED");
  attroff(COLOR_PAIR(PLAYER_ONE));
  attron(COLOR_PAIR(PLAYER_TWO));
  mvprintw(0, 39, "PLAYER TWO = WHITE");
  attroff(COLOR_PAIR(PLAYER_TWO));
  if(BIT_CHECK(c->grid[1], 15)){
    attron(COLOR_PAIR(PLAYER_ONE));
    mvprintw(posR, posC, "*");
    attroff(COLOR_PAIR(PLAYER_ONE));
  }
  else{
    attron(COLOR_PAIR(PLAYER_TWO));
    mvprintw(posR, posC, "*");
    attroff(COLOR_PAIR(PLAYER_TWO));
  }
  int row=0;
  int index=0;
  for(int i = 0; index < ROWS; i+=2,index++){
    int col=COLS*2;
    for(int j = 0; j <= 12; j+=2){
      attron(COLOR_PAIR(BORDER));
      mvprintw(i+1 + OFFSETR, col + OFFSETC, "|");
      attroff(COLOR_PAIR(BORDER));
      if(BIT_CHECK(c->grid[index], j)){
        if(BIT_CHECK(c->grid[index], j+1)){
          attron(COLOR_PAIR(PLAYER_ONE));
          mvprintw(row+1 + OFFSETR, col-1 + OFFSETC, "*");
          attroff(COLOR_PAIR(PLAYER_ONE));
        }
        else{
          attron(COLOR_PAIR(PLAYER_TWO));
          mvprintw(row+1 + OFFSETR, col-1 + OFFSETC, "*");
          attroff(COLOR_PAIR(PLAYER_TWO));
        }
      }
      else{
        mvprintw(row+1 + OFFSETR, col-1 + OFFSETC, " ");
      }
      attron(COLOR_PAIR(BORDER));
      mvprintw(row+2 + OFFSETR, col-1 + OFFSETC, "-");
      attroff(COLOR_PAIR(BORDER));
      col-=2;
    }
    attron(COLOR_PAIR(BORDER));
    mvprintw(i+1 + OFFSETR, col + OFFSETC, "|");
    attroff(COLOR_PAIR(BORDER));
    row+=2;
  }
}

void initgrid(connectfour *c){
  for(int i = 0; i < ROWS; i++){
    for(int j = 0; j < 15; j++){
      BIT_CLEAR(c->grid[i], j);
    }
  }
}
int checkwin(connectfour *c){
  int connect = 0;
  int h = 0;
  if(BIT_CHECK(c->grid[1], 15)){//for player 1
    for(int i = 0; i < (COLS-3)*2; i+=2){ //algorithm to check diagonal moving though columns(0-3, right to left)
      for(int j = 0, k =i; j < ROWS-h; j++, k+=2){
        if(BIT_CHECK(c->grid[j], k)){
          if(BIT_CHECK(c->grid[j], k+1)){
            connect++;
            if(connect >= 4)
              return 1;
          }
          else
            connect = 0;
        }
        else
          connect = 0;
      }
      if(i>=6)
        h++;
    }
    if(connect >= 4)
      return 1;
    connect = 0;
    h=0;
    for(int i = 1; i < ROWS - 3; i++){ //algorithm to check diagonl moving through rows(1-2, top to bottom)
      for(int j = i, k = 0; j < ROWS; k+=2, j++){
        if(BIT_CHECK(c->grid[j], k)){
          if(BIT_CHECK(c->grid[j], k+1)){
            connect++;
            if(connect >= 4)
              return 1;
          }
          else
            connect = 0;
        }
        else
          connect = 0; 
      }
    }
    if(connect >= 4)
      return 1;
    connect = 0;
    for(int i = 12; i > 4; i-=2){ //algorithm to check diagonal moving though columns(0-3, left to right)
      for(int j = 0, k =i; j < ROWS-h; j++, k-=2){
        if(BIT_CHECK(c->grid[j], k)){
          if(BIT_CHECK(c->grid[j], k+1)){
            connect++;
            if(connect >= 4)
              return 1;
          }
          else
            connect = 0;
        }
        else
          connect = 0;
      }
      if(i<=10)
        h++;
    }
    if(connect >= 4)
      return 1;
    connect = 0;
    h =0;
    for(int i = 1; i < ROWS - 3; i++){ //algorithm to check diagonl moving through rows(1-2, top to bottom)
      for(int j = i, k = 12; j < ROWS; k-=2, j++){
        if(BIT_CHECK(c->grid[j], k)){
          if(BIT_CHECK(c->grid[j], k+1)){
            connect++;
            if(connect >= 4)
              return 1;
          }
          else
            connect = 0;
        }
        else
          connect = 0; 
      }
    }
    if(connect >= 4)
      return 1;
    connect = 0;
    for(int i = 0; i < COLS*2; i+=2){ //checking top to bottom all columns
      for(int j = 0; j < ROWS; j++){
        if(BIT_CHECK(c->grid[j], i)){
          if(BIT_CHECK(c->grid[j], i+1)){
            connect++;
            if(connect >= 4)
              return 1;
          }
          else
            connect = 0;
        }
        else
          connect = 0;
      }
    }
    if(connect >= 4)
      return 1;
    connect = 0;
    for(int i = 0; i < ROWS; i++){ //checking right to left all rows
      for(int j = 0; j < COLS*2; j+=2){
        if(BIT_CHECK(c->grid[i], j)){
          if(BIT_CHECK(c->grid[i], j+1)){
            connect++;
            if(connect >= 4)
              return 1;
          }
          else
            connect = 0;
        }
        else
          connect = 0;
      }
    }
    if(connect >= 4)
      return 1;
  }
  else{//for player 2
    for(int i = 0; i < (COLS-3)*2; i+=2){ //algorithm to check diagonal moving though columns(0-3, right to left)
      for(int j = 0, k =i; j < ROWS-h; j++, k+=2){
        if(BIT_CHECK(c->grid[j], k)){
          if(!BIT_CHECK(c->grid[j], k+1)){
            connect++;
            if(connect >= 4)
              return -1;
          }
          else
            connect = 0;
        }
        else
          connect = 0;
      }
      if(i>=6)
        h++;
    }
    if(connect >= 4)
      return -1;
    connect = 0;
    h = 0;
    for(int i = 1; i < ROWS - 3; i++){ //algorithm to check diagonl moving through rows(1-2, top to bottom)
      for(int j = i, k = 12; j < ROWS; k+=2, j++){
        if(BIT_CHECK(c->grid[j], k)){
          if(!BIT_CHECK(c->grid[j], k+1)){
            connect++;
            if(connect >= 4)
              return -1;
          }
          else
            connect = 0;
        }
        else
          connect = 0; 
      }
    }
    if(connect >= 4)
      return -1;
    connect = 0;
    for(int i = 12; i > 4; i-=2){ //algorithm to check diagonal moving though columns(0-3, left to right)
      for(int j = 0, k =i; j < ROWS-h; j++, k-=2){
        if(BIT_CHECK(c->grid[j], k)){
          if(!BIT_CHECK(c->grid[j], k+1)){
            connect++;
            if(connect >= 4)
              return 1;
          }
          else
            connect = 0;
        }
        else
          connect = 0;
         //BIT_SET(c->grid[j], k);
      }
      if(i<=10)
        h++;
    }
    if(connect >= 4)
      return 1;
    connect = 0;
    h=0;
    for(int i = 1; i < ROWS - 3; i++){ //algorithm to check diagonl moving through rows(1-2, top to bottom)
      for(int j = i, k = 12; j < ROWS; k-=2, j++){
        if(BIT_CHECK(c->grid[j], k)){
          if(!BIT_CHECK(c->grid[j], k+1)){
            connect++;
            if(connect >= 4)
              return 1;
          }
          else
            connect = 0;
        }
        else
          connect = 0;  
        
         //BIT_SET(c->grid[j], k);
      }
    }
    if(connect >= 4)
      return 1;
    connect = 0;
    for(int i = 0; i < COLS*2; i+=2){ //checking top to bottom all columns
      for(int j = 0; j < ROWS; j++){
        if(BIT_CHECK(c->grid[j], i)){
          if(!BIT_CHECK(c->grid[j], i+1)){
            connect++;
            if(connect >= 4)
              return -1;
          }
          else
            connect = 0;
        }
        else
          connect = 0;
      }
    }
    if(connect >= 4)
      return -1;
    connect = 0;
    for(int i = 0; i < ROWS; i++){ //checking right to left all rows
      for(int j = 0; j < COLS*2; j+=2){
        if(BIT_CHECK(c->grid[i], j)){
          if(!BIT_CHECK(c->grid[i], j+1)){
            connect++;
            if(connect >= 4)
              return -1;
          }
          else
            connect = 0;
        }
        else
          connect = 0;
      }
    }
    if(connect >= 4)
      return -1;
  }
    return 0;
}

int drop(connectfour *c, int col){
  int row = 0;
  if(BIT_CHECK(c->grid[0], col)){
    return -1;
  }
  else{
    while((!BIT_CHECK(c->grid[row+1], col)) && row < 5)
      row++;
  }
  BIT_SET(c->grid[row], col);
  if(BIT_CHECK(c->grid[1], 15))
    BIT_SET(c->grid[row], col+1);
  return 0;
}

void turn(connectfour *c){//player 1 will go when bit is 1 and player 2 will go when bit is 0, checking 15th bit on second row
  int posR = OFFSETR;
  int posC = OFFSETC + 7;
  int col = 6;//starting at middle colum
  while(1){
    erase();
    printBoardwCursor(c, posR, posC);
    mvprintw(10, 0, BIT_CHECK(c->grid[1], 15) ? "PLAYER ONE TURN": "PLAYER TWO TURN");
    int key = getch();
    if(!BIT_CHECK(c->grid[1], 15) && key == 'j'){
      //erase();
      //mvprintw(10, 0, BIT_CHECK(c->grid[1], 15) ? "PLAYER ONE TURN": "PLAYER TWO TURN");
      if(posC > 30){
        printBoardwCursor(c, posR, posC-=2);
        col+=2;
      }
      else
        printBoardwCursor(c, posR, posC);
      
    }
    else if(!BIT_CHECK(c->grid[1], 15) && key == 'l'){
      //erase();
      //mvprintw(10, 0, BIT_CHECK(c->grid[1], 15) ? "PLAYER ONE TURN": "PLAYER TWO TURN");
      if(posC < 41){
        printBoardwCursor(c, posR, posC+=2);
        col-=2;
      }
      else
        printBoardwCursor(c, posR, posC);
    }
    else if(!BIT_CHECK(c->grid[1], 15) && key == 'k'){
      //drop and switch turn
      int dropped = drop(c, col);
      if(dropped == 0){
        int win = checkwin(c);
        if(win == -1){
          BIT_SET(c->grid[0],14);
          return;
        }
        posR = OFFSETR;
        posC = OFFSETC + 7;
        col = 6;
        BIT_SET(c->grid[1], 15);
      }

    }
    if(BIT_CHECK(c->grid[1], 15) && key == 'a'){
      //erase();
      //mvprintw(10, 0, BIT_CHECK(c->grid[1], 15) ? "PLAYER ONE TURN": "PLAYER TWO TURN");
      if(posC > 30){
        printBoardwCursor(c, posR, posC-=2);
        col+=2;
      }
      else
        printBoardwCursor(c, posR, posC);
    }
    else if(BIT_CHECK(c->grid[1], 15) && key == 'd'){
      //erase();
      //mvprintw(10, 0, BIT_CHECK(c->grid[1], 15) ? "PLAYER ONE TURN": "PLAYER TWO TURN");
      if(posC < 41){
        printBoardwCursor(c, posR, posC+=2);
        col-=2;
      }
      else
        printBoardwCursor(c, posR, posC);
    }
    else if(BIT_CHECK(c->grid[1], 15) && key == 's'){
      //drop and switch turn
      int dropped = drop(c, col);
      if(dropped == 0){
        int win = checkwin(c);
        if(win == 1){
          BIT_SET(c->grid[0],15);
          return;
        }
        posR = OFFSETR;
        posC = OFFSETC + 7;
        col = 6;
        BIT_CLEAR(c->grid[1], 15);
      }
    }
    else if(key == 'q'){
      endwin();
      exit(0);
    }
    
  }
}

void printWin(connectfour *c){
  erase();
  attron(COLOR_PAIR(BORDER));
  mvprintw(10, 28, (BIT_CHECK(c->grid[0],14)) ? "PLAYER TWO WON" : "PLAYER ONE WON");
  mvprintw(20, 20, "PRESS ANY KEY TO EXIT OR PRESS a TO PLAY AGAIN");
  attroff(COLOR_PAIR(BORDER));
  int anykey = getch();
  if(anykey == 'a'){
    connectfour game;
    gameloop(&game);
  }
}

void gameloop(connectfour *c){
  erase();
  initgrid(c);
  initscr();
	raw();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
  start_color();
  init_pair(PLAYER_ONE, COLOR_RED, COLOR_BLACK);
  init_pair(PLAYER_TWO, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(BORDER, COLOR_CYAN, COLOR_BLACK);
  mvprintw(0,25,"WELCOME TO CONNECT FOUR");
  mvprintw(12, 28, "PRESS s TO START!");
  while((!BIT_CHECK(c->grid[0],14)) && (!BIT_CHECK(c->grid[0],15))){
    int key = getch();
    if(key == 's'){
      erase();
      turn(c);
      //checkwin(c);
      //printBoardwCursor(c, OFFSETR, OFFSETC+7);
    }
    else if(key == 'q'){
      endwin();
      exit(0);
    }
  }
  printWin(c);
}


int main(int argc, char *argv[]){
  connectfour game;

  gameloop(&game);
  endwin();
    




  return 0;
}
