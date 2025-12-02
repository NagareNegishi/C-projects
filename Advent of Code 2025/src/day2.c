#include <stdio.h>
#include "day2.h"
#include "helper.h"

int get_total_invalid_IDs(const char* filename, long long* total){
    *total = 0;
    FILE* in = fopen(filename, "r");
    if (in == NULL) {
        return 1;
    }

    // Read a line from the file
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), in) == NULL) {
        fclose(in);
        return 1;
    }
    fclose(in);

    // Process the line
    if (process_ID_range(buffer, total) != 0) {
        return 1;
    }
    return 0;
}


int process_ID_range(char* line, long long* total){
    long long start, end;
    char* ptr = line;
    int count = 0;
    while (ptr != '\n') {
        if (sscanf(ptr, "%lld-%lld%n", &start, &end, &count) != 2) {
            return 1;
        }
        // printf("Parsed range: %lld - %lld, total so far: %lld\n", start, end, *total);
        if (find_repeated_sequence(start, end, total) != 0) {
            return 1;
        }
        ptr += count;
        if (*ptr == ',') {
            ptr++;
        } else {
            break;
        }
    }
    return 0;
}

int find_repeated_sequence(const long long start, const long long end, long long* total){
    // to repeat a sequence, the digits must be even in length
    int start_len = count_digits(start);
    int end_len = count_digits(end);
    long long true_start = start;
    long long true_end = end;
    if (start_len % 2 != 0) {
        true_start = next_power_of_10(start);
        start_len += 1;
    }
    if (end_len % 2 != 0) {
        true_end = next_power_of_10((end/10)) - 1;
        end_len -= 1;
    }
    if (true_start > true_end) { // no valid range to check
        return 0;
    }

    // // it seems no wider range check is needed for the test cases
    // if (count_digits(true_end) - count_digits(true_start) >= 2) {
    //     printf("!!!recursion needed from %lld to %lld\n", true_start, true_end);
    //     long long next_end = next_power_of_10((true_end/10)) - 1;
    //     find_repeated_sequence(true_start, next_end, total);
    // }
    long long first_half;
    long long candidate = get_candidate(true_start, start_len, &first_half);
    while (candidate <= true_end) {
        if (candidate >= start && candidate <= end) {
            *total += candidate;
        }
        first_half += 1;
        candidate = get_next_candidate(first_half, start_len);
    }
    return 0;
}

long long get_candidate(long long num, int digit_len, long long* first_half){
    long long half_power = 1;
    for (int i = 0; i < (digit_len / 2); i++) {
        half_power *= 10;
    }
    long long half = num / half_power;
    long long candidate = half * half_power + half;
    *first_half = half;
    return candidate;
}

long long get_next_candidate(long long first_half, int digit_len){
    long long half_power = 1;
    for (int i = 0; i < (digit_len / 2); i++) {
        half_power *= 10;
    }
    long long candidate = first_half * half_power + first_half;
    return candidate;
}