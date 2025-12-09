#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "day8.h"

double distance(Point* a, Point* b){
    int dx = a->x - b->x;
    int dy = a->y - b->y;
    int dz = a->z - b->z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

int get_answer(const char* filename, long long* answer){
    *answer = 0;
    int point_size = 0;
    Point points[MAX_N] = {0};
    if (generate_points(filename, points, &point_size) != 0) {
        return 1;
    }

    // initialize connection tracking arrays
    int parent[point_size];
    int connection_count[point_size]; // upto 2 connections
    int connection_size[point_size]; // size of each connection
    for (int i = 0; i < point_size; i++) {
        parent[i] = i; // each point's is its own parent initially
        connection_count[i] = 0;
        connection_size[i] = 1; // each point is a connection of size 1
    }

    bool visited[point_size][point_size]; // bit wasteful but C have disadvantages

    // find first 1000 shortest connections
    for (int n = 0; n < 1000; n++) {
        double min_dist = INFINITY;
        int min_i = -1;
        int min_j = -1;

        for (int i = 0; i < point_size; i++) {
            // skip if already has 2 connections
            if (connection_count[i] >= 2) { continue; }
            for (int j = i + 1; j < point_size; j++) {
                // skip if already has 2 connections or already visited
                if (connection_count[j] >= 2) { continue; }
                if (visited[i][j]) { continue; }
                
                double dist = distance(&points[i], &points[j]);
                if (dist < min_dist) {
                    min_dist = dist;
                    min_i = i;
                    min_j = j;
                }
            }
        }
        if (min_i == -1) { // no more valid connections
            break;
        }
        // mark this pair as visited and update connection counts
        if (visited[min_i][min_j] == false) {
            visited[min_i][min_j] = true;
            visited[min_j][min_i] = true;
            connection_count[min_i]++;
            connection_count[min_j]++;
        }
    }


    return 0;
}

// recursively find and update the leader/parent of x
int find(int x, int* parent) {
    if (parent[x] != x) {
        parent[x] = find(parent[x], parent);
    }
    return parent[x];
}



int generate_points(const char* filename, Point* points, int* point_size){
    FILE* in = fopen(filename, "r");
    if(in == NULL){
        return 1;
    }
    *point_size = 0;
    char buffer[256];
    
    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        if(*point_size >= MAX_N){
            perror("Exceeded maximum number of points");
            break;
        }
        if (sscanf(buffer, "%d,%d,%d", &points[*point_size].x, &points[*point_size].y, &points[*point_size].z) != 3) {
            perror("Invalid point format");
            fclose(in);
            return 1;
        }
        (*point_size)++;
    }
    fclose(in);
    return 0;
}