#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

typedef struct {
    int code;
    char message[256];
    const char *file;
    int line;
} error_context_t;

// Declare as extern in header
extern _Thread_local error_context_t g_error;

// Function declarations
void set_error_internal(int code, const char *file, int line);
void clear_error(void);
int has_error(void);
void print_error(void);

// Macros that call the functions
#define set_error(code) set_error_internal(code, __FILE__, __LINE__)

#endif // ERROR_H