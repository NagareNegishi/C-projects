#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "day10.h"

int get_fewest_button_presses(const char* filename, long long* total){
    *total = 0;
    FILE* in = fopen(filename, "r");
    if (in == NULL) return 1;

    char line[256];
    while (fgets(line, sizeof(line), in) != NULL) {
        int presses = check_machine(line);
        if (presses == -1) {
            fclose(in);
            return 1;
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
    // parse diagram and get number of lights
    int num_lights = 0;
    char *temp = ptr + 1;  // skip '['
    while (*temp != ']') {
        if (*temp != '.' && *temp != '#') return -1;
        num_lights++;
        temp++;
    }
    
    uint16_t target = convert_diagram(ptr);
    uint16_t buttons[20] = {0};
    int button_count = 0;
    if(target == 0 && num_lights == 0) return -1;
    
    while (strchr(ptr, '(') != NULL) {
        ptr = strchr(ptr, '(') + 1;
        uint16_t button = convert_buttons(ptr, num_lights);
        buttons[button_count] = button;
        button_count++;
    }
    
    int min_presses = find_min_presses(target, buttons, button_count);
    if (min_presses == -1) return -1;
    return min_presses;
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



uint16_t convert_buttons(char* buttons, int nums){
    uint16_t result = 0;
    while (*buttons != ')') {
        if (*buttons >= '0' && *buttons <= '9') {
            int light_index = *buttons - '0';  // Light index from left (0-based)
            int bit_position = nums - 1 - light_index;  // Convert to bit position
            result |= (1 << bit_position);
        }
        buttons++;
    }
    return result;
}


#include <stdlib.h>

typedef struct {
    uint16_t state;
    int presses;
} QueueNode;

int find_min_presses(uint16_t target, uint16_t* buttons, int button_count) {
    if (target == 0) return 0;
    
    // BFS
    QueueNode* queue = malloc(sizeof(QueueNode) * 100000);
    bool* visited = calloc(65536, sizeof(bool));
    
    int front = 0, back = 0;
    queue[back++] = (QueueNode){0, 0};
    visited[0] = true;
    
    while (front < back) {
        QueueNode current = queue[front++];
        
        for (int i = 0; i < button_count; i++) {
            uint16_t new_state = current.state ^ buttons[i];
            
            if (new_state == target) {
                int result = current.presses + 1;
                free(queue);
                free(visited);
                return result;
            }
            
            if (!visited[new_state]) {
                visited[new_state] = true;
                queue[back++] = (QueueNode){new_state, current.presses + 1};
            }
        }
    }
    
    free(queue);
    free(visited);
    return -1;
}
