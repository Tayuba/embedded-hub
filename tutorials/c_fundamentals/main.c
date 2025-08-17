#include <stdio.h>
#include "big_o.h"
#include "math_utils.h"
#include "bitwise_utils.h"

int main(void) {
    printf("=== Big-O Demonstration ===\n");
    big_o_test();

    printf("\n=== Math Utilities ===\n");
    printf("GCD(48, 18) = %d\n", gcd(48, 18));
    printf("LCM(4, 6) = %d\n", lcm(4, 6));
    printf("mod_pow(2, 10, 1000) = %d\n", mod_pow(2, 10, 1000));
    printf("Is 29 prime? %s\n", is_prime(29) ? "Yes" : "No");
    printf("nCr(5, 4) = %lld\n", nCr(5, 4));

    printf("\n=== Bitwise Operations ===\n");
    demonstrate_bitwise_operations();

    return 0;
}
