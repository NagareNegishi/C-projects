#ifndef DAY8_H
#define DAY8_H

/**
 * Plan:
 * Create a array of 3D points, it need:
 * - store x,y,z
 * - store connected points (upto 2)
 * - between distance method
 *
 * since C does not have Collections, which is perfect for this task,
 * I will use a fixed size array and knowledge of input file.
 * - For point, array[1000]
 * - To keep track of visited points, array[1000][1000] of bool
 * - array[1000] for parent/leader of each point
 * - array[1000] for size of each connection
 *
 * Unfortunately, this quiz is not suitable for unit testing due to its nature.
 * So the test will be minimal.
 */

#define MAX_N 1000

typedef struct {
    double x, y, z;
} Point;


#endif // DAY8_H