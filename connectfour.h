#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H
#define ROWS 6
#define COLS 7
#define PLAYER_ONE 1
#define PLAYER_TWO 4
#define BORDER 2
#define TEXT 3


class connectfour{
public:
  /*
                                   least sig. bit
                                      |  
  00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 |  <- each row is a unsigned 16 bit int.
     | --   --   --   --   --   --   -- |   
  00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 |
     | --   --   --   --   --   --   -- |  
  00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 |
     | --   --   --   --   --   --   -- |
  00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 |
     | --   --   --   --   --   --   -- |
  00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 |
     | --   --   --   --   --   --   -- |
  00 | 00 | 00 | 00 | 00 | 00 | 00 | 00 |
     | --   --   --   --   --   --   -- |
  
  - each cell contains 2 bits. so 00 is a cell.
    the right bit will determine if the cell is a bit.
    the left bit will determine which player owns the cell.
    for example:
        00 - cell is not used
        01 - cell is owned by player 2.
        11 - cell is owned by player 1.

  - (0,0) cell (14th and 15th bit of row 0) will determine if someone has won.
    if player 1 wins the 15th bit will be 1.
    if player 2 wins the 14th bit will be 1.
    they cannot both be 1.

  - (1,0) cell (14th and 15th bit of row 1) the 15th bit will determine whose turn is it.
    if it is player 1's turn the 15th bit will be 1.
    if it is player 2's turn the 15th bit will be 0.



  */
  uint16_t grid[ROWS];
};
/*
  this will be calling the game function and acts as start page
*/
void gameloop(connectfour *c);
/*
  this will print the winning screen once game is over
*/
void printWin(connectfour *c);
/*
  runs algorithm to check if there is a winner
*/
int checkwin(connectfour *c);
/* 
  declare all bits in grid to 0
*/
void initgrid(connectfour *c);
/*
  prints board and if withCursor is true, it will print with the cursor and controls
*/
void printBoardwCursor(connectfour *c, int posR, int posC, bool withCursor);
/* 
  calls the function above with true
*/
void printBoardwCursor(connectfour *c, int posR, int posC);
#endif
