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