#include <stdio.h>
#include <string.h>
#include "day10.h"

int get_fewest_button_presses(const char* filename, long long* total){
    *total = 0;
    FILE* in = fopen(filename, "r");
    if (in == NULL) return -1;

    char line[256];
    while (fgets(line, sizeof(line), in) != NULL) {
        int presses = check_machine(line);
        if (presses == -1) {
            fclose(in);
            return -1;
        }
        *total += presses;
    }
    fclose(in);
    return 0;
}

/**
 * Check each line and return fewest button presses needed
 * return -1 on error
 */
int check_machine(const char* line){
    char *ptr = (char*)line;
    // parse diagram
    uint16_t target = convert_diagram(ptr);
    uint16_t buttons[20] = {0};
    int button_count = 0;
    if(target == 0) return -1;
    while (strchr(ptr, '(') != NULL) {
        ptr = strchr(ptr, '(') + 1;
        uint16_t button = convert_buttons(ptr);
        buttons[button_count] = button;
        button_count++;
    }
    // find fewest presses
    return 0;
}

uint16_t convert_diagram(char* diagram){
    printf("Converting diagram: %s\n", diagram);
    uint16_t result = 0;
    while (*diagram != ']') {
        printf("Char: %c\n", *diagram);
        result <<= 1;
        if (*diagram == '#') {
            result |= 1;
        } else if (*diagram != '.') {
            return 0; // invalid character
        }
        diagram++;
    }
    return result;
}

uint16_t convert_buttons(char* buttons){
    return 0;
}


