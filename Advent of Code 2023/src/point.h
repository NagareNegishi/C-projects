#ifndef POINT_H
#define POINT_H
#include <stdbool.h>

typedef enum {
    UP = 0,
    RIGHT,
    DOWN,
    LEFT,
    NONE
} Direction;

typedef enum {
    VERTICAL = 0,
    HORIZONTAL,
    N_E,
    N_W,
    S_E,
    S_W,
    GROUND,
    START
} Tile;

typedef struct {
    int row;
    int col;
    Direction in;
    Direction out;
    Tile tile;
    bool is_vaild;
} Point;

Point search_option(Direction from, const char* lines,
    const int row, const int col, const int max_row, const int max_col);

bool is_start(Point *current, Point *start);

bool can_connect(Point *current, const char target);

// convert direction to its opposite
Direction convert_direction(Direction from);

Tile convert_tile(const char tile_char);

// check if the given row and col are within the grid range
bool is_range(const int row, const int col, const int max_row, const int max_col);

// check all around the point for possible directions
bool check_around(const char* lines, const int row, const int col, const int max_row, const int max_col, Direction* in, Direction* out);

Direction find_out(Direction in, const char tile);

#endif // POINT_H