#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *input = fopen("./agro.in", "r");
    if (input == NULL) {
        exit(1);
    }
    size_t count;

    fscanf(input, "%zu", &count);

    uint32_t current_flower;
    uint32_t previous_flower = 0; // не бывает по условию, поэтому безопасно для первого сравнения
    short repeat_count = 0;

    size_t max_row_begin = 1;
    size_t max_count = 1;

    size_t row_begin = 1;
    size_t row_end = 1;

    for (size_t i = 0; i < count; i++) {
        fscanf(input, "%" SCNu32, &current_flower);
        row_end = i + 1;
        if (current_flower == previous_flower) {
            repeat_count += 1;
        } else {
            repeat_count = 0;
        }
        if (repeat_count == 2) {
            if (row_end - row_begin > max_count) {
                max_row_begin = row_begin;
                max_count = row_end - row_begin;
            }
            row_begin = row_end - 1;
            repeat_count = 1;
        }
        previous_flower = current_flower;
    }
    fclose(input);
    if (row_end - row_begin + 1 > max_count) {
        max_row_begin = row_begin;
        max_count = row_end - row_begin + 1;
    }
    FILE *output = fopen("./agro.out", "w");
    fprintf(output, "%zu %zu", max_row_begin, max_row_begin + max_count - 1);
    fclose(output);
    return 0;
}

