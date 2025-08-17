#include "math_utils.h"

// Greatest Common Divisor (Euclidean algorithm)
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b; 
        a = t; 
    }
    return a;
}

// Least Common Multiple
int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

// Modular exponentiation (fast power)
int mod_pow(int base, int exp, int mod) {
    long long result = 1;
    long long b = base % mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * b) % mod;
        }
        b = (b * b) % mod;
        exp >>= 1;
    }
    return (int)result;
}

// Prime check
int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// Combinations (nCr)
long long nCr(int n, int r) {
    if (r > n) return 0;
    if (r == 0 || r == n) return 1;
    long long res = 1;
    for (int i = 1; i <= r; i++) {
        res = res * (n - r + i) / i; // 1-2, 2-3, 3-4. 4-
    }
    return res;
}
