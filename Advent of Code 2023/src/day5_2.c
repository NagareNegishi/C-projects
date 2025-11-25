#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "day5_2.h"

void cleanup(FILE* in, Range* list) {
    if (fclose(in) != 0) {
        perror("Fail to close file.\n");
    }
    free(list);
}

// get the closest location
int get_closest(const char* filename, long long* closest, const char* goal)
{
    *closest = LLONG_MAX;
    FILE *in;
    in = fopen(filename, "r");
    if (in == NULL) {
        perror("Fail to open file.\n");
        return 0;
    }

    // get sources
    int size;
    Range *list = get_source(in, &size);
    if (list == NULL){
        perror("get_source failed.\n");
        fclose(in);
        return 0;
    }

    // read categories and convert
    int is_goal = 0;
    while (!is_goal) {
        int result = read_category(in, goal);
        if (result == 0){
            perror("read_category failed.\n");
            cleanup(in, list);
            return 0;
        } else if (result == 2){
            is_goal = 1;
        }
        list = convert(in, list, &size);
        if (list == NULL){
            perror("convert failed.\n");
            cleanup(in, list);
            return 0;
        }
    }

    // find closest
    for (int i = 0; i < size; i++) {
        if (list[i].start < *closest) {
            *closest = list[i].start;
        }
    }
    cleanup(in, list);
    return 1;
}


// get size of source
Range* get_source(FILE* in, int* size)
{
    // skip title
    *size = 0;
    char buffer[1000];
    if (fgets(buffer, sizeof(buffer), in) == NULL) {
        perror("Fail do not have first line.\n");
        return NULL;
    }
    char *ptr = strchr(buffer, ':');
    if (ptr == NULL) {
        perror("':' not found.\n");
        return NULL;
    }
    ptr++;

    // parse ranges
    int count;
    long long start, range;
    Range* list = NULL;
    while (sscanf(ptr, " %lld %lld%n", &start, &range, &count) == 2) {
        (*size)++;
        Range* p = (Range*)realloc(list, (*size * sizeof(Range)));
        if (p == NULL) {
            perror("realloc failed\n");
            free(list);
            return NULL;
        }
        list = p;
        list[*size - 1].start = start;
        list[*size - 1].range = range;
        ptr += count;
    }

    fgets(buffer, sizeof(buffer), in); // skip empty line
    return list;
}

// read destination category
// return 0: fail, 1: not goal, 2: goal
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


/**
 * Convert Range list according to the rules in the input file.
 * @param in The input file stream containing conversion rules.
 * @param before The original Range list to be converted.
 * @param size Pointer to the size of the Range list.
 * @return The converted Range list, or NULL on failure.
 */
Range* convert(FILE* in, Range* before, int* size)
{
    // track both unchanged ranges
    Range *unmapped = (Range*)malloc((*size) * sizeof(Range));
    if (unmapped == NULL) {
        perror("malloc failed\n");
        return NULL;
    }
    memcpy(unmapped, before, (*size) * sizeof(Range));
    int unmapped_size = *size;

    // track changed ranges
    Range *mapped = NULL;
    int mapped_size = 0;

    // Range can be split, it could be no overlap, partial overlap, full overlap
    long long dest, source, range;
    while (fscanf(in, "%lld %lld %lld\n", &dest, &source, &range) == 3) {
        long long diff = dest - source;
        long long map_start = source;
        long long map_end = map_start + range - 1;

        // go through unmapped list
        int i = 0;;
        while (i < unmapped_size) {
            long long range_start = unmapped[i].start;
            long long range_end = range_start + unmapped[i].range - 1;

            // case no overlap
            if (range_end < map_start || range_start > map_end) {
                i++;
                continue;
            }

            // it's overlapped -> it will be split -> will not check again
            unmapped[i] = unmapped[unmapped_size - 1]; // remove it by switching it with last element
            unmapped_size--;

            // handle left non overlapped part
            if (range_start < map_start) {
                Range *p = realloc(unmapped, sizeof(Range) * (unmapped_size + 1));
                if (p == NULL) {
                    perror("realloc failed\n");
                    free(unmapped);
                    free(mapped);
                    return NULL;
                }
                unmapped = p;
                // last space for left over
                unmapped[unmapped_size].start = range_start;
                unmapped[unmapped_size].range = map_start - range_start;
                unmapped_size++;
            }

            // handle overlapped part (middle)
            long long overlap_start = (range_start < map_start) ? map_start: range_start;
            long long overlap_end = (range_end > map_end) ? map_end : range_end;
            Range *m = realloc(mapped, sizeof(Range) * (mapped_size + 1));
            if (m == NULL) {
                perror("realloc failed\n");
                free(unmapped);
                free(mapped);
                return NULL;
            }
            mapped = m;
            mapped[mapped_size].start = overlap_start + diff;
            mapped[mapped_size].range = overlap_end - overlap_start + 1;
            mapped_size++;

            // handle right non overlapped part
            if (range_end > map_end) {
                Range *p = realloc(unmapped, sizeof(Range) * (unmapped_size + 1));
                if (p == NULL) {
                    perror("realloc failed\n");
                    free(unmapped);
                    free(mapped);
                    return NULL;
                }
                unmapped = p;
                // last space for left over
                unmapped[unmapped_size].start = map_end + 1;
                unmapped[unmapped_size].range = range_end - map_end;
                unmapped_size++;
            }
        }
    }

    // combine mapped and unmapped
    Range *result = realloc(mapped, sizeof(Range) * (mapped_size + unmapped_size));
    if (result == NULL) {
        perror("realloc failed\n");
        free(unmapped);
        free(mapped);
        return NULL;
    }
    memcpy(&result[mapped_size], unmapped, sizeof(Range) * unmapped_size);
    *size = mapped_size + unmapped_size;
    free(unmapped);
    return result;
}


// part 2
int main()
{
    long long closest;
    if (get_closest("input5.txt", &closest, "location") == 1){
        printf("Closest is: %lld\n", closest);
    } else {
        perror("get_closest failed.\n");
    }
}