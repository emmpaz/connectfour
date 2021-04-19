#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H
#define ROWS 6
#define COLS 7




class cell{
public:
  int color;
  int gridRow;
  int gridCol;

};

class connectfour{
public:
  cell grid[ROWS][COLS];
};
#endif
