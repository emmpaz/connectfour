#include <iostream>
#include <ncurses.h>

#include "connectfour.h"


void printBoard(connectfour *c){
  for(int i = 0; i < COLS*2; i++){
    mvprintw(3,i,"-");
  }
  for(int i = 4; i < ROWS+4; i++){
    for(int j = 0; j < COLS*2; j+=2){
      mvprintw(i,j,"|");
    }
    mvprintw(i,COLS-1,"|");
  }
  for(int i = 0; i < COLS*2; i++){
    mvprintw(10,i,"-");
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
