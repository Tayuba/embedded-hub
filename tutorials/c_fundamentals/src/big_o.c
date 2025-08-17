#include <stdio.h>
#include <time.h>
#include "big_o.h"

void big_o_test(void){
    const int num = 1000000;
    clock_t start, end;
    double time_taken;

    start = clock();
    volatile long sum = 0;

    // O(n)
    for (int i = 0; i < num; i++){
        sum += 1;
    }

    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("O(n) loop took: %0.f seconds\n", time_taken);

    // O(n^2)
    start = clock();
    volatile long sum1 = 0;
    for (int i = 0; i < 2000; i++) {
        for (int j = 0; j < 2000; j++) {
            sum1 += (i + j);
        }
    }
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("O(n^2) loop took: %.6f seconds\n", time_taken);
}