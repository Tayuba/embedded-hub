#include <stdio.h>
#include "bitwise_utils.h"

void demonstrate_bitwise_operations(void) {
    unsigned char a = 0b10101010;
    unsigned char b = 0b11001100;

    printf("a & b = 0x%02X\n", a & b);
    printf("a | b = 0x%02X\n", a | b);
    printf("a ^ b = 0x%02X\n", a ^ b);
    printf("~a = 0x%02X\n", (unsigned char)~a);
    printf("a << 1 = 0x%02X\n", a << 1);
    printf("b >> 2 = 0x%02X\n", b >> 2);
}
