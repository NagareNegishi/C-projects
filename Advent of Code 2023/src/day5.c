#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "day5.h"

// get the closest location
int get_closest(const char* filename, long long* closest, const char* goal)
{
    *closest = LLONG_MAX;
    FILE *in;
    in = fopen(filename, "r");
    if (in == NULL) {
        perror("Fail to open file.\n");
        return 1;
    }

    // get source sizes and sources
    char buffer[1000];
    if (fgets(buffer, sizeof(buffer), in) == NULL) {
        perror("Fail do not have first line.\n");
        return 1;
    }
    int size;
    if (get_source_size(buffer, &size) == 0) {
        perror("get_source_size failed.\n");
        return 1;
    }
    long long sources[size];
    if (get_source(buffer, size, sources) == 0){
        perror("get_source failed.\n");
    }

    // read categories and convert
    int is_goal = 0;
    fgets(buffer, sizeof(buffer), in); // skip empty line
    while (!is_goal) {
        int result = read_category(in, goal);
        if (result == 0){
            perror("read_category failed.\n");
            return 1;
        } else if (result == 2){
            is_goal = 1;
        }
        if (convert(in, sources, size) == 0){
            perror("convert failed.\n");
            return 1;
        }
    }

    // find closest
    for (int i = 0; i < size; i++) {
        if (sources[i] < *closest) {
            *closest = sources[i];
        }
    }
    if (fclose(in) != 0) {
        perror("Fail to close file.\n");
        return 1;
    }
    return 0;
}

// get size of source
int get_source_size(const char* sources, int* size) {
    char *ptr = strchr(sources, ':');
    *size = 0;
    if (ptr == NULL) {
        perror("':' not found.\n");
        return 0;
    }
    ptr++;
    int num;
    int count;
    while (sscanf(ptr, " %d%n", &num, &count) == 1) {
        (*size)++;
        ptr += count;
    }
    return 1;
}

// get size of source
int get_source(const char* sources, int size, long long* array) {
    char *ptr = strchr(sources, ':');
    if (ptr == NULL) {
        perror("':' not found.\n");
        return 0;
    }
    ptr++;
    int count;
    for (int i = 0; i < size; i++) {
        if (sscanf(ptr, " %lld%n", &array[i], &count) != 1) {
            perror("Fail to parse expected size.\n");
            return 0;
        }
        ptr += count;
    }
    return 1;
}

// read destination category
int read_category(FILE* in, const char* goal){
    char buffer[50];
    if (fgets(buffer, sizeof(buffer), in) == NULL) {
        perror("Fail, category do not have title line.\n");
    return 0;
    }
    char *ptr = strstr(buffer, goal);
    if (ptr != NULL){
        return 2;
    }
    return 1;
}

// convert to next type
int convert(FILE* in, long long* before, const int size) {
    long long dest;
    long long source;
    long long range;
    // create a copy of original array
    long long temp[size];
    memcpy(temp, before, size * sizeof(long long));
    while (fscanf(in, "%lld %lld %lld\n", &dest, &source, &range) == 3) {
        long long diff = dest - source;
        long long limit = source + range - 1;
        for (int i = 0; i < size; i++) {
            if (source <= before[i] && before[i] <= limit) {
                temp[i] = before[i] + diff;
            }
        }
    }
    // update original array
    memcpy(before, temp, size * sizeof(long long));
    return 1;
}


int main()
{
    long long closest;
    if (get_closest("input5.txt", &closest, "location") == 0){
        printf("Closest is: %lld\n", closest);
    } else {
        perror("get_closest failed.\n");
    }
}