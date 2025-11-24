#ifndef DAY6_H
#define DAY6_H

typedef struct {
    int time;
    int distance;
    int ways;
} Race;

typedef struct {
    long time;
    long distance;
    long ways;
} LongRace;

// read file and calculate result
int analyse_races(const char* filename, int* result);

// get how many round of races
int get_race_count(const char* line, int* size);

// create Race from lines
int read_Races(Race* races, const int size, const char* times, const char* distances);

// calculate wining ways
void calculate_ways(Race* race);

int close_file(FILE* in);

int analyse_races_part2(const char* filename, int* result);
void read_Races_part2(LongRace* race, const char* times, const char* distances);
void calculate_ways_part2(LongRace* race);

#endif