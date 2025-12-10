#include <stdio.h>
#include <string.h>
#include <stdbool.h>
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
    int min_presses = find_min_presses(target, buttons, button_count);
    if (min_presses == -1) return -1;
    return min_presses;
}


/**
 * toggle same button twice just cancels out, so I only need to consider pressing each button 0 or 1 times.
 */
int find_min_presses(uint16_t target, uint16_t* buttons, int button_count) {
    if (target == 0) return 0;
    
    for (int n = 1; n <= button_count; n++) {
        if (can_reach_in_n_presses(0, target, buttons, button_count, n, 0)) { // initially all lights off = 0
            return n;
        }
    }
    return -1;
}

bool can_reach_in_n_presses(uint16_t current, uint16_t target, uint16_t* buttons, int button_count, int n, int depth) {
    if (current == target) return true; // reached target
    if (depth == n) return false; // reached max presses -> no solution found
    // try pressing each button
    for (int i = 0; i < button_count; i++) {
        // current ^ buttons[i] toggles the lights corresponding to the button
        if (can_reach_in_n_presses(current ^ buttons[i], target, buttons, button_count, n, depth + 1)) {
            return true;
        }
    }
    return false;
}



uint16_t convert_diagram(char* diagram){
    uint16_t result = 0;
    diagram++; // skip initial '['
    while (*diagram != ']') {
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
    uint16_t result = 0;
    while (*buttons != ')') {
        if (*buttons >= '0' && *buttons <= '9') {
            int index = *buttons - '0';
            result |= (1 << index);
        }
        buttons++;
    }
    return result;
}


