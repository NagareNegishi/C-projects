#ifndef DAY10_H
#define DAY10_H
#include <stdint.h>
#include <stdbool.h>

/**
 * [.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}
 * for part 1, completely ignore joltage requirements {}
 * both light diagram [.##.]
 * and buttons (3) (1,3) (2) (2,3) (0,2) (0,1)
 * can be represented as binary numbers, where # is 1 and . is 0
 */

int get_fewest_button_presses(const char* filename, long long* total);

/**
 * Check each line and return fewest button presses needed
 * return -1 on error
 */
int check_machine(const char* line);

uint16_t convert_diagram(char* diagram);
uint16_t convert_buttons(char* buttons);

int find_min_presses(uint16_t target, uint16_t* buttons, int button_count);

#endif // DAY10_H