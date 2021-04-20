#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H
#define ROWS 6
#define COLS 7
#define PLAYER_ONE 0
#define PLAYER_TWO 1


class connectfour{
public:
  /*
  Each row contains 14 bits used and 2 unused
  Each cell will contain 2 bits
  So since 2 bits per cell and 7 columns, that's how we get 14
  First bit will say which player, Second bit will say if that spot is used by chip
  */
  uint16_t grid[ROWS];
};
#endif
