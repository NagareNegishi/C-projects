#include <stdio.h>
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
int check_machine(const char* line);

uint16_t convert_diagram(const char* diagram);
uint16_t convert_buttons(const char* buttons);


