#ifndef DAY_1_H
#define DAY_1_H

typedef enum {
    RIGHT = 0,
    LEFT = 1,
    NONE = -1
} Direction;

int get_password(const char* filename, int* password);

int process_line(const char* line, int* current);

int get_password_v2(const char* filename, int* password);

int process_line_v2(const char* line, int* current, int* password);

#endif // DAY_1_H