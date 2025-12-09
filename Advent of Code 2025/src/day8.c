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

    int parent[point_size];
    int connection_size[point_size];
    for (int i = 0; i < point_size; i++) {
        parent[i] = i;
        connection_size[i] = 1;
    }

    bool visited[point_size][point_size];
    for (int i = 0; i < point_size; i++) {
        for (int j = 0; j < point_size; j++) {
            visited[i][j] = false;
        }
    }

    int target = (point_size <= 20) ? 10 : 1000;
    for (int n = 0; n < target; n++) {
        double min_dist = INFINITY;
        int min_i = -1;
        int min_j = -1;

        for (int i = 0; i < point_size; i++) {
            for (int j = i + 1; j < point_size; j++) {
                if (visited[i][j]) { continue; }
                
                double dist = distance(&points[i], &points[j]);
                if (dist < min_dist) {
                    min_dist = dist;
                    min_i = i;
                    min_j = j;
                }
            }
        }
        if (min_i == -1) {
            break;
        }
        
        visited[min_i][min_j] = true;
        visited[min_j][min_i] = true;

        int root_i = find(min_i, parent);
        int root_j = find(min_j, parent);
        if (root_i != root_j) {
            if (connection_size[root_i] < connection_size[root_j]) {
                parent[root_i] = root_j;
                connection_size[root_j] += connection_size[root_i];
            } else {
                parent[root_j] = root_i;
                connection_size[root_i] += connection_size[root_j];
            }
        }
    }

    int top3_sizes[3] = {0, 0, 0};
    for (int i = 0; i < point_size; i++) {
        int root = find(i, parent);
        if (root != i) { continue; }
        int size = connection_size[root];
        for (int j = 0; j < 3; j++) {
            if (size > top3_sizes[j]) {
                for (int k = 2; k > j; k--) {
                    top3_sizes[k] = top3_sizes[k - 1];
                }
                top3_sizes[j] = size;
                break;
            }
        }
    }
    
    *answer = (long long)top3_sizes[0] * top3_sizes[1] * top3_sizes[2];
    return 0;
}


// int get_answer(const char* filename, long long* answer){
//     *answer = 0;
//     int point_size = 0;
//     Point points[MAX_N] = {0};
//     if (generate_points(filename, points, &point_size) != 0) {
//         return 1;
//     }

//     // initialize connection tracking arrays
//     int parent[point_size];
//     // int connection_count[point_size]; // upto 2 connections
//     int connection_size[point_size]; // size of each connection
//     for (int i = 0; i < point_size; i++) {
//         parent[i] = i; // each point's is its own parent initially
//         // connection_count[i] = 0;
//         connection_size[i] = 1; // each point is a connection of size 1
//     }

//     // bit wasteful but C have disadvantages
//     bool visited[point_size][point_size];
//     for (int i = 0; i < point_size; i++) {
//         for (int j = 0; j < point_size; j++) {
//             visited[i][j] = false;
//         }
//     }

//     // find first 1000 shortest connections
//     for (int n = 0; n < 1000; n++) { // 10 for test, 1000 for real
//         double min_dist = INFINITY;
//         int min_i = -1;
//         int min_j = -1;

//         for (int i = 0; i < point_size; i++) {
//             // skip if already has 2 connections
//             // if (connection_count[i] >= 2) { continue; }
//             for (int j = i + 1; j < point_size; j++) {
//                 // skip if already has 2 connections or already visited
//                 // if (connection_count[j] >= 2) { continue; }
//                 if (visited[i][j]) { continue; }
                
//                 double dist = distance(&points[i], &points[j]);
//                 if (dist < min_dist) {
//                     min_dist = dist;
//                     min_i = i;
//                     min_j = j;
//                 }
//             }
//         }
//         if (min_i == -1) { // no more valid connections
//             break;
//         }
//         // mark this pair as visited and update connection counts
//         // if (visited[min_i][min_j] == false) {
//             visited[min_i][min_j] = true;
//             visited[min_j][min_i] = true;
//             // connection_count[min_i]++;
//             // connection_count[min_j]++;

//             // check if this connection merges two different groups
//             int root_i = find(min_i, parent);
//             int root_j = find(min_j, parent);
//             if (root_i != root_j) {
//                 // merge smaller group into larger group
//                 if (connection_size[root_i] < connection_size[root_j]) {
//                     parent[root_i] = root_j;
//                     connection_size[root_j] += connection_size[root_i];
//                 } else {
//                     parent[root_j] = root_i;
//                     connection_size[root_i] += connection_size[root_j];
//                 }
//             }
//         // }
//     }

//     // find top 3
//     int top3_roots[3] = {-1, -1, -1};
//     int top3_sizes[3] = {0, 0, 0};
//     for (int i = 0; i < point_size; i++) {
//         int root = find(i, parent);
//         if (root != i) { continue; } // only consider root nodes
//         int size = connection_size[root];
//         for (int j = 0; j < 3; j++) {
//             if (size > top3_sizes[j]) {
//                 // shift down
//                 for (int k = 2; k > j; k--) {
//                     top3_sizes[k] = top3_sizes[k - 1];
//                     top3_roots[k] = top3_roots[k - 1];
//                 }
//                 top3_sizes[j] = size;
//                 top3_roots[j] = root;
//                 break;
//             }
//         }
//     }
//     printf("Top 3 connection sizes: %d, %d, %d\n", top3_sizes[0], top3_sizes[1], top3_sizes[2]);
//     *answer = (long long)top3_sizes[0] * top3_sizes[1] * top3_sizes[2];
//     return 0;
// }

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
