#include <iostream>
#include <ncurses.h>
#include <random>
#define BIT_SET(num,bit)   ((num) |=  (1<<(bit)))
#define BIT_CLEAR(num,bit) ((num) &= ~(1<<(bit)))
#define BIT_CHECK(num,bit) ((num) &   (1<<(bit)))
#define OFFSETR 2
#define OFFSETC 31
#include "connectfour.h"



void printBoardwCursor(connectfour *c, int posR, int posC, bool withCursor){//this took longer than expected...
  if(withCursor){
    attron(A_BOLD);
    attron(COLOR_PAIR(PLAYER_ONE));
    mvprintw(0, 24, "PLAYER ONE");
    attroff(COLOR_PAIR(PLAYER_ONE));
    attron(COLOR_PAIR(PLAYER_TWO));
    mvprintw(0, 43, "PLAYER TWO");
    attroff(COLOR_PAIR(PLAYER_TWO));
    attroff(A_BOLD);
    mvprintw(8, 1,  "PLAYER ONE CONTROLS");
    mvprintw(10, 1, " a       s       d");
    mvprintw(11, 1, "left | place | right");
    mvprintw(8, 59,  "PLAYER TWO CONTROLS");
    mvprintw(10, 59, " j       k       l");
    mvprintw(11, 59, "left | place | right");
    mvprintw(0,0, "q to quit.");
    if(BIT_CHECK(c->grid[1], 15)){
      attron(A_BOLD);
      attron(COLOR_PAIR(PLAYER_ONE));
      mvprintw(posR, posC, "*");
      attroff(COLOR_PAIR(PLAYER_ONE));
      attroff(A_BOLD);
    }
    else{
      attron(A_BOLD);
      attron(COLOR_PAIR(PLAYER_TWO));
      mvprintw(posR, posC, "*");
      attroff(COLOR_PAIR(PLAYER_TWO));
      attroff(A_BOLD);
    }
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

void printBoardwCursor(connectfour *c, int posR, int posC){
  printBoardwCursor(c, posR, posC, true);
}
void initgrid(connectfour *c){
  for(int i = 0; i < ROWS; i++){
    for(int j = 0; j < 15; j++){
      BIT_CLEAR(c->grid[i], j);
    }
  }
}
int checkwin(connectfour *c){
  int connect = 0; //this is used to count how many in a row
  int h = 0; //this is used when moving through the diagonals through columns because the diagonals shorten
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
              return -1;
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
              return -1;
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
  if(BIT_CHECK(c->grid[0], col)){ //if there is a chip in the first row in the specified column. Won't drop.
    return -1;
  }
  else{
    while((!BIT_CHECK(c->grid[row+1], col)) && row < 5) //while there is no chip in the next cell below in specified column then will keep moving down
      row++;
  }
  BIT_SET(c->grid[row], col);
  if(BIT_CHECK(c->grid[1], 15)) //for which player the chip belongs to
    BIT_SET(c->grid[row], col+1);
  return 0;
}

void turn(connectfour *c){//player 1 will go when bit is 1 and player 2 will go when bit is 0, checking 15th bit on second row
  int posR = OFFSETR; // use for how the astrik gets printed
  int posC = OFFSETC + 7; // same as above. + 7 to start in the middle.
  int col = 6;//starting at middle colum
  while(1){
    erase();
    printBoardwCursor(c, posR, posC);
    attron(COLOR_PAIR(TEXT));
    mvprintw(16, 30, BIT_CHECK(c->grid[1], 15) ? "-PLAYER ONE TURN-": "-PLAYER TWO TURN-");
    attroff(COLOR_PAIR(TEXT));
    int key = getch();
    if(!BIT_CHECK(c->grid[1], 15) && key == 'j'){
      if(posC > 32){
        printBoardwCursor(c, posR, posC-=2);
        col+=2;
      }
      else
        printBoardwCursor(c, posR, posC);
    }
    else if(!BIT_CHECK(c->grid[1], 15) && key == 'l'){
      if(posC < 43){
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
      if(posC > 32){
        printBoardwCursor(c, posR, posC-=2);
        col+=2;
      }
      else
        printBoardwCursor(c, posR, posC);
    }
    else if(BIT_CHECK(c->grid[1], 15) && key == 'd'){
      if(posC < 43){
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
  attron(A_BOLD);
  (BIT_CHECK(c->grid[0],14)) ? attron(COLOR_PAIR(PLAYER_TWO)) : attron(COLOR_PAIR(PLAYER_ONE));
  mvprintw(15, 31, (BIT_CHECK(c->grid[0],14)) ? "PLAYER TWO WON!" : "PLAYER ONE WON!");
  mvprintw(0, 16, "PRESS ANY KEY TO EXIT OR PRESS a TO PLAY AGAIN");
  (BIT_CHECK(c->grid[0],14)) ? attroff(COLOR_PAIR(PLAYER_TWO)) : attron(COLOR_PAIR(PLAYER_ONE));
  attroff(A_BOLD);
  printBoardwCursor(c, 0, 0, false);
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
  init_pair(PLAYER_ONE, COLOR_YELLOW, COLOR_BLACK);
  init_pair(PLAYER_TWO, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(BORDER, COLOR_CYAN, COLOR_BLACK);
  init_pair(TEXT, COLOR_GREEN, COLOR_BLACK);
  attron(COLOR_PAIR(BORDER));
  mvprintw(0,28,"WELCOME TO CONNECT FOUR");
  mvprintw(12, 31, "PRESS s TO START!");
  attroff(COLOR_PAIR(BORDER));
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> start(1,2);
  if(start(mt) % 2 == 0) //random person starts
    BIT_SET(c->grid[1], 15);
  while((!BIT_CHECK(c->grid[0],14)) && (!BIT_CHECK(c->grid[0],15))){ //while no one has won
    int key = getch();
    if(key == 's'){
      erase();
      turn(c);
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
