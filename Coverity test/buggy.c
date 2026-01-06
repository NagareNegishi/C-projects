// buggy.c
#include <stdlib.h>
#include <string.h>

void memory_leak() {
    char *ptr = malloc(100);
    // forgot to free!
}

void null_deref() {
    char *str = malloc(10);
    if (str == NULL) {
        strcpy(str, "test");  // NULL pointer dereference
    }
}

void buffer_overflow() {
    char buf[10];
    strcpy(buf, "this is way too long");  // buffer overflow
}

int main() {
    memory_leak();
    null_deref();
    buffer_overflow();
    return 0;
}