#include <stdio.h>
#include "my_math.h"

/**
 * GCD (Greatest Common Divisor) of two integers using Euclidean algorithm.
 * @param a First integer.
 * @param b Second integer.
 * @return The GCD of a and b.
 */
long long gcd(long long a, long long b){
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/**
 * LCM (Least Common Multiple) of two integers.
 * @param a First integer.
 * @param b Second integer.
 * @return The LCM of a and b.
 */
long long lcm(long long a, long long b){
    // obviously case & avoid division by zero
    if (a == 0 || b == 0) {
        return 0;
    }
    // LCM(a, b) = (a × b) / GCD(a, b)
    // However, to avoid overflow, divide first
    return (a / gcd(a, b)) * b;
}


/**
 * Finds the smallest value that satisfies all cycle patterns.
 * @param offsets Array of offset values, where condition meet first time
 * @param steps Array of step values, representing the cycle lengths
 * @param count Number of equations
 * @return The smallest value satisfying all equations
 */
long long find_sync_point(int* offsets, int* steps, int count) {
    if (count == 0) return 0;
    
    long long value = offsets[0];
    long long step = steps[0];
    
    for (int i = 1; i < count; i++) {
        // Find when value aligns with equation i
        while ((value - offsets[i]) % steps[i] != 0) {
            value += step;
        }
        // Update step to maintain alignment with all previous equations
        step = lcm(step, steps[i]);
    }
    return value;
}