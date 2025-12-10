#include <stdio.h>
#include "day10.h"

int get_fewest_button_presses(const char* filename, long long* total);

/**
 * Check each line and return fewest button presses needed
 * return -1 on error
 */
int check_machine(const char* line);

uint16_t convert_diagram(const char* diagram);
uint16_t convert_buttons(const char* buttons);
