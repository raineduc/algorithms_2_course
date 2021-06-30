#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int32_t min_value(int32_t a, int32_t b) {
    return a > b ? b : a;
}

int main() {
    FILE *input = fopen("./chaos.in", "r");
    if (input == NULL) {
        exit(1);
    }
    uint16_t a, b, c, d;
    uint64_t k;
    fscanf(input, "%" SCNu16 " %" SCNu16 " %" SCNu16 " %" SCNu16, &a, &b, &c, &d);
    fscanf(input, " %" SCNu64, &k);
    size_t count = 0;

    if (a*b > c) {
        int32_t rest = min_value(a * b - c, d);
        int32_t previous_rest = rest;
        for (uint64_t i = 2; i <= k; i++) {
            rest = min_value(rest * b - c, d);
            if (rest <= 0) {
                rest = 0;
                break;
            }
            if (rest == previous_rest) {
                break;
            }
            previous_rest = rest;
        }
        count = rest;
    }

    fclose(input);

    FILE *output = fopen("./chaos.out", "w");
    fprintf(output, "%zu", count);
    fclose(output);

    return 0;
}

