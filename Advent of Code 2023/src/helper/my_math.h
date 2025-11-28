#ifndef MY_MATH_H
#define MY_MATH_H

/**
 * GCD (Greatest Common Divisor) of two integers using Euclidean algorithm.
 * @param a First integer.
 * @param b Second integer.
 * @return The GCD of a and b.
 */
long long gcd(long long a, long long b);

/**
 * LCM (Least Common Multiple) of two integers.
 * @param a First integer.
 * @param b Second integer.
 * @return The LCM of a and b.
 */
long long lcm(long long a, long long b);

/**
 * Finds the smallest value that satisfies all cycle patterns.
 * @param offsets Array of offset values, where condition meet first time
 * @param steps Array of step values, representing the cycle lengths
 * @param count Number of equations
 * @return The smallest value satisfying all equations
 */
long long find_sync_point(int* offsets, int* steps, int count);

#endif // MY_MATH_H