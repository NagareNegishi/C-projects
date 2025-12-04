#include "error.h"
#include <string.h>
#include <errno.h>

// Define the thread-local variable once
_Thread_local error_context_t g_error = {0};

void set_error_internal(int code, const char *file, int line) {
    g_error.code = code;
    strncpy(g_error.message, strerror(code), sizeof(g_error.message) - 1);
    g_error.message[sizeof(g_error.message) - 1] = '\0';
    g_error.file = file;
    g_error.line = line;
}

void clear_error(void) {
    g_error.code = 0;
    g_error.message[0] = '\0';
    g_error.file = NULL;
    g_error.line = 0;
}

int has_error(void) {
    return g_error.code != 0;
}

void print_error(void) {
    if (has_error()) {
        fprintf(stderr, "Error at %s:%d: %s (code: %d)\n",
                g_error.file, g_error.line, g_error.message, g_error.code);
    }
}
