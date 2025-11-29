#include <stdio.h>
#include "point.h"

// search for the next point based on the current direction and position
Point search_option(Direction from, const char* lines,
    const int row, const int col, const int max_row, const int max_col){
        Point result = {
        .row = row,
        .col = col,
        .in = NONE,
        .out = NONE,
        .tile = GROUND,
        .is_vaild = false
        };

        if (from != NONE) {
            result.in = convert_direction(from);
            int offset = row * max_col + col;
            char target = lines[offset];
            result.tile = convert_tile(target);
            result.out = find_out(result.in, target);
            if (result.out != NONE && result.tile != GROUND) {
                result.is_vaild = true;
            } else {
                result.is_vaild = false;
            }

        } else { // then its start
            result.tile = START;
            bool vaild = check_around(lines, row, col, max_row, max_col, &result.in, &result.out);
            result.is_vaild = vaild;
        }
        return result;
    }


// check all around the point for possible directions, its used for start point
bool check_around(const char* lines, const int row, const int col, const int max_row, const int max_col, Direction* in, Direction* out){
    // UP
    if (is_range(row - 1, col, max_row, max_col)) {
        int offset = (row - 1) * max_col + col;
        char target = lines[offset];
        if (target == '|' || target == '7' || target == 'F') {
            *in = UP; // fill "in" first
        }
    }
    // RIGHT
    if (is_range(row, col + 1, max_row, max_col)) {
        int offset = row * max_col + (col + 1);
        char target = lines[offset];
        if (target == '-' || target == 'J' || target == '7') {
            if (*in == NONE) {
                *in = RIGHT;
            } else {
                *out = RIGHT; // find both in and out
                return true;
            }
        }
    }
    // DOWN
    if (is_range(row + 1, col, max_row, max_col)) {
        int offset = (row + 1) * max_col + col;
        char target = lines[offset];
        if (target == '|' || target == 'J' || target == 'L') {
            if (*in == NONE) {
                *in = DOWN;
            } else {
                *out = DOWN; // find both in and out
                return true;
            }
        }
    }
    // LEFT
    if (is_range(row, col - 1, max_row, max_col)) {
        int offset = row * max_col + (col - 1);
        char target = lines[offset];
        if (target == '-' || target == 'L' || target == 'F') {
            if (*in == NONE) {
                *in = LEFT;
                return false; // found only in
            } else {
                *out = LEFT; // find both in and out
                return true;
            }
        }
    }
    return false; // found only in or none
}


// check if the given row and col are within the grid range
bool is_range(const int row, const int col, const int max_row, const int max_col){
    return (row >= 0 && row < max_row) && (col >= 0 && col < max_col);
}

// convert direction to its opposite
Direction convert_direction(Direction from){
    switch (from) {
        case UP:
            return DOWN;
        case RIGHT:
            return LEFT;
        case DOWN:
            return UP;
        case LEFT:
            return RIGHT;
        default:
            return NONE;
    }
}

// convert character to Tile enum
Tile convert_tile(const char tile_char){
    switch (tile_char) {
        case '|':
            return VERTICAL;
        case '-':
            return HORIZONTAL;
        case 'L':
            return N_E;
        case 'J':
            return N_W;
        case 'F':
            return S_E;
        case '7':
            return S_W;
        case '.':
            return GROUND;
        case 'S':
            return START;
        default:
            return GROUND; // default to GROUND for unknown characters
    }
}


// check if current point is the start point
bool is_start(Point *current, Point *start){
    // return (current->row == start->row) && (current->col == start->col);
    return start->tile == START;
}

// check if current point can connect to target tile
bool can_connect(Point *current, const char target){
    switch (current->out) {
        case UP:
            return target == '|' || target == '7' || target == 'F';
        case RIGHT:
            return target == '-' || target == 'J' || target == '7';
        case DOWN:
            return target == '|' || target == 'J' || target == 'L';
        case LEFT:
            return target == '-' || target == 'L' || target == 'F';
        default:
            return false;
    }
}

// find the outgoing direction based on incoming direction and tile type
Direction find_out(Direction in, const char tile){
    switch (in) {
        case UP:
            if (tile == '|' ) return DOWN;
            if (tile == 'L' ) return RIGHT;
            if (tile == 'J' ) return LEFT;
            break;
        case RIGHT:
            if (tile == '-' ) return LEFT;
            if (tile == 'F' ) return DOWN;
            if (tile == 'L' ) return UP;
            break;
        case DOWN:
            if (tile == '|' ) return UP;
            if (tile == '7' ) return LEFT;
            if (tile == 'F' ) return RIGHT;
            break;
        case LEFT:
            if (tile == '-' ) return RIGHT;
            if (tile == 'J' ) return UP;
            if (tile == '7' ) return DOWN;
            break;
        default:
            return NONE;
    }
    return NONE;
}
