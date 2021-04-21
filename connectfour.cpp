#include <iostream>
#include <ncurses.h>
#define BIT_SET(num,bit)   ((num) |=  (1<<(bit)))
#define BIT_CLEAR(num,bit) ((num) &= ~(1<<(bit)))
#define BIT_CHECK(num,bit) ((num) &   (1<<(bit)))
#define OFFSETR 2
#define OFFSETC 28
#include "connectfour.h"


void printBoard(connectfour *c){//this took longer than expected...
   int row=0;
   int index=0;
  for(int i = 0; index < ROWS; i+=2,index++){
    int col=COLS*2;
    BIT_SET(c->grid[index], 3);
    for(int j = 0; j <= 12; j+=2){
      mvprintw(i+1 + OFFSETR, col + OFFSETC, "|");
      if(1){//replace with BIT_CHECK(c->grid[i], j)
        if(BIT_CHECK(c->grid[index], j+1)){
          attron(COLOR_PAIR(PLAYER_ONE));
          mvprintw(row+1 + OFFSETR, col-1 + OFFSETC, "1");
          attroff(COLOR_PAIR(PLAYER_ONE));
        }
        else{
          attron(COLOR_PAIR(PLAYER_TWO));
          mvprintw(row+1 + OFFSETR, col-1 + OFFSETC, "2");
          attroff(COLOR_PAIR(PLAYER_TWO));
        }
      }
      mvprintw(row+2 + OFFSETR, col-1 + OFFSETC, "-");
      col-=2;
    }
    mvprintw(i+1 + OFFSETR, col + OFFSETC, "|");
    row+=2;
  }
}

void testerpoints(connectfour *c){
  for(int i = 0; i < ROWS; i++){
    BIT_SET(c->grid[i], 0);
    for(int j = 0; j <= 12; j+=2){
      std::cout << bool(BIT_CHECK(c->grid[i], j)) << std::endl;
    }
    std::cout << "split" << std::endl;
  }
}

void initgrid(connectfour *c){
  for(uint16_t i: c->grid){
    i = 0;
  }
}

void gameloop(connectfour *c){
  initscr();
	raw();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
  start_color();
  init_pair(PLAYER_ONE, COLOR_BLUE, COLOR_BLACK);
  init_pair(PLAYER_TWO, COLOR_RED, COLOR_BLACK);
  mvprintw(0,25,"WELCOME TO CONNECT FOUR");
  printBoard(c);
  while(1){
    int key = getch();
    if(key == 'y'){
      endwin();
      exit(0);
    }
  }
}


int main(int argc, char *argv[]){
  connectfour game;

  initgrid(&game);

  gameloop(&game);





  return 0;
}
