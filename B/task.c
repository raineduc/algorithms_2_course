#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

enum letter_type {
    ANIMAL = 0,
    TRAP,
};

struct letter {
    enum letter_type type;
    char character;
    uint32_t type_index;
};

struct letter_stack {
    struct letter letter;
    size_t index;
    struct letter_stack *next;
};

void letter_stack_push(struct letter_stack **old, const struct letter letter) {
    size_t current_index = *old ? (*old)->index + 1 : 0;
    struct letter_stack *new = malloc(sizeof(struct letter_stack));
    *new = (struct letter_stack) {.letter = letter, .index = current_index, .next = *old};
    *old = new;
}

void letter_stack_pop(struct letter_stack **old) {
    if (*old) {
        struct letter_stack *destroyed = *old;
        *old = (*old)->next;
        free(destroyed);
    }
}

void destroy_stack(struct letter_stack **stack) {
    while (*stack != NULL) {
        letter_stack_pop(stack);
    }
}

char *read_input(FILE *in) {
    char *input = NULL;
    char buffer[10000];
    size_t templen, inputlen = 0;
    do {
        fgets(buffer, 10000, in);
        templen = strlen(buffer);
        input = realloc(input, inputlen + templen + 1);
        strcpy(input + inputlen, buffer);
        inputlen += templen;
    } while (templen == 10000 - 1 && buffer[10000 - 2] != '\n');
    return input;
}

int main() {
    FILE *input = fopen("./input.txt", "r");
    if (input == NULL) {
        exit(1);
    }

    uint32_t current_animal_index = 0;
    uint32_t current_trap_index = 0;

    FILE *output = fopen("./output.txt", "w");

    struct letter_stack *stack = NULL;
    char *str = read_input(input);
    size_t str_len = strlen(str);
    fclose(input);

    if (str_len == 0 || *str == '\n' || *str == '\r') {
        fprintf(output, "Impossible");
        free(str);
        fclose(output);
        return 0;
    }

    uint32_t *animal_indices = malloc(str_len * sizeof(uint32_t));
    size_t indices_access_count = 0;

    char *last_letter = str + str_len - 1;

    for (char *letter = str; letter <= last_letter; letter++) {
        if (*letter == '\r' || *letter == '\n') break;
        if (stack && stack->letter.type == ANIMAL && toupper(stack->letter.character) == *letter) {
            current_trap_index += 1;
            indices_access_count += 1;
            animal_indices[current_trap_index - 1] = stack->letter.type_index;
            letter_stack_pop(&stack);
            continue;
        } else if (stack && stack->letter.type == TRAP && tolower(stack->letter.character) == *letter) {
            current_animal_index += 1;
            indices_access_count += 1;
            animal_indices[stack->letter.type_index - 1] = current_animal_index;
            letter_stack_pop(&stack);
            continue;
        }
        struct letter new_letter;
        if (isupper(*letter)) {
            current_trap_index += 1;
            new_letter = (struct letter)
                    {.type = TRAP, .character = *letter, .type_index = current_trap_index};
        } else {
            current_animal_index += 1;
            new_letter = (struct letter)
                    {.type = ANIMAL, .character = *letter, .type_index = current_animal_index};
        }
        letter_stack_push(&stack, new_letter);
    }

    if (stack == NULL) {
        fprintf(output, "Possible\n");
        for (size_t i = 0; i < indices_access_count; i++) {
            fprintf(output, "%" PRIu32 " ", animal_indices[i]);
        }
    } else {
        fprintf(output, "Impossible");
    }
    fclose(output);
    free(animal_indices);
    free(str);
    destroy_stack(&stack);

    return 0;
}



