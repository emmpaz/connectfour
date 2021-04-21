#include <iostream>
#include <ncurses.h>
#define BIT_SET(num,bit)   ((num) |=  (1<<(bit)))
#define BIT_CLEAR(num,bit) ((num) &= ~(1<<(bit)))
#define BIT_CHECK(num,bit) ((num) &   (1<<(bit)))

#include "connectfour.h"


void printBoard(connectfour *c){
  for(int i = 0; i < COLS*2+1; i++){
    mvprintw(0,i,"-");
  }
  for(int i = 0; i < ROWS; i++){
    int col=COLS*2;
    int row=0;
    BIT_SET(c->grid[i], 3);
    for(int j = 0; j <= 12; j+=2){
      mvprintw(i+1, col, "|");
      if(1){//replace with BIT_CHECK(c->grid[i], j)
        if(BIT_CHECK(c->grid[i], j+1)){
          attron(COLOR_PAIR(PLAYER_ONE));
          mvprintw(row, col-1, "1");
          attroff(COLOR_PAIR(PLAYER_ONE));
        }
        else{
          attron(COLOR_PAIR(PLAYER_TWO));
          mvprintw(row, col-1, "2");
          attroff(COLOR_PAIR(PLAYER_TWO));
        }
      }
      mvprintw(row, col-1, "-");
      col-=2;
    }
    mvprintw(i+1, col, "|");
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
