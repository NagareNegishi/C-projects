#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "day6.h"

int close_file(FILE* in){
    if (fclose(in) != 0) {
        perror("Fail to close file.\n");
        return 0;
    }
    return 1;
}


// read file and calculate result
int analyse_races(const char* filename, int* result)
{
    *result = 0;
    FILE *in;
    in = fopen(filename, "r");
    if (in == NULL) {
        perror("Fail to open file.\n");
        return 0;
    }
    char time_buffer[500];
    if (fgets(time_buffer, sizeof(time_buffer), in) == NULL) {
        perror("Fail to read input.\n");
        close_file(in);
        return 0;
    }
    // get number of races
    int size;
    if (get_race_count(time_buffer, &size) == 0) {
        perror("get_race_count failed.\n");
        close_file(in);
        return 0;
    }

    // read distance line
    char distance_buffer[500];
    if (fgets(distance_buffer, sizeof(distance_buffer), in) == NULL) {
        perror("Fail to read input.\n");
        close_file(in);
        return 0;
    }
    close_file(in);

    // create Race
    Race *races = (Race*) calloc(size, sizeof(Race));
    if (races == NULL) {
        perror("Memory allocation failed.\n");
        return 0;
    }
    if (read_Races(races, size, time_buffer, distance_buffer) == 0) {
        perror("read_Races failed.\n");
        free(races);
        return 0;
    }
    for (Race *ptr = races; ptr < races + size; ptr++) {
        calculate_ways(ptr);
    }
    // calculate total
    for (Race *ptr = races; ptr < races + size; ptr++) {
        if (*result == 0) {
            *result = ptr->ways;
        } else {
        *result *= ptr->ways;
        }
    }
    free(races);
    return 1;
}

// get how many round of races
int get_race_count(const char* line, int* size)
{
    *size = 0;
    char *ptr = strchr(line, ':');
    if (ptr == NULL) {
        perror("Line missing ':'\n");
        return 0;
    }
    ptr++; // skip :
    int num;
    int count;
    while (sscanf(ptr, " %d%n", &num, &count) == 1) {
        (*size)++;
        ptr += count;
    }
    return 1;
}

// create Race from lines
int read_Races(Race* races, const int size, const char* times, const char* distances)
{
    char *t = strchr(times, ':');
    char *d = strchr(distances, ':');
    if (t == NULL || d == NULL) {
        perror("Line missing ':'\n");
        return 0;
    }
    t++;  // skip ':'
    d++;  // skip ':'
    int t_count;
    int d_count;
    for (Race *race = races; race < races + size; race++) {
        sscanf(t, " %d%n", &(race->time), &t_count);
        sscanf(d, " %d%n", &(race->distance), &d_count);
        t += t_count;
        d += d_count;
    }
    return 1;
}

// calculate wining ways
void calculate_ways(Race* race){
    // could skip min/max case, but race with distance 0 may exist
    for (int t = 0; t <= race->time; t++) {
        int time_remain = race->time - t;
        if ((long long)time_remain * t > race->distance) {
            (race->ways)++;
        }
    }
}


// read file and calculate result
int analyse_races_part2(const char* filename, int* result)
{
    *result = 0;
    FILE *in;
    in = fopen(filename, "r");
    if (in == NULL) {
        perror("Fail to open file.\n");
        return 0;
    }
    // read lines
    char time_buffer[500];
    if (fgets(time_buffer, sizeof(time_buffer), in) == NULL) {
        perror("Fail to read input.\n");
        close_file(in);
        return 0;
    }
    char distance_buffer[500];
    if (fgets(distance_buffer, sizeof(distance_buffer), in) == NULL) {
        perror("Fail to read input.\n");
        close_file(in);
        return 0;
    }
    close_file(in);

    // create Race
    LongRace race = {0,0,0};
    read_Races_part2(&race, time_buffer, distance_buffer);
    calculate_ways_part2(&race);
    *result = race.ways;
    return 1;
}

// (int)log10(num) + 1 can tell digit number too
// create Race from lines
void read_Races_part2(LongRace* race, const char* times, const char* distances)
{
    // concatenate digits only then convert to long
    char t_buffer[100];
    char d_buffer[100];
    int t_count = 0;
    int d_count = 0;
    for (int i = 0; times[i] != '\n'; i++) {
        if (isdigit(times[i])) {
            t_buffer[t_count] = times[i];
            t_count++;
        }
    }
    t_buffer[t_count] = '\0';
    for (int i = 0; distances[i] != '\n'; i++) {
        if (isdigit(distances[i])) {
            d_buffer[d_count] = distances[i];
            d_count++;
        }
    }
    d_buffer[d_count] = '\0';
    long time = atol(t_buffer);
    long distance = atol(d_buffer);
    race->time = time;
    race->distance = distance;
}

// calculate wining ways
void calculate_ways_part2(LongRace* race){
    for (long t = 0; t <= race->time; t++) {
        long time_remain = race->time - t;
        long long dist = (long long)time_remain * t;
        if (dist > race->distance) {
            (race->ways)++;
        }
    }
}


int main() {
    int result;
    if (analyse_races_part2("input6.txt", &result) == 0) {
        perror("analyse_races Failed\n");
        return 1;
    }
    printf("Result is : %d\n", result);
    return 0;
}