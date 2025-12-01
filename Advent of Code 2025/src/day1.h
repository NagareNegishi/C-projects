#ifndef DAY_1_H
#define DAY_1_H

typedef enum {
    RIGHT = 0,
    LEFT = 1,
    NONE = -1
} Direction;

int get_password(const char* filename, int* password);

int process_line(const char* line, int* current);

#endif // DAY_1_H