#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INPUT_SIZE 1000

typedef enum State {
    Ascending,
    Descending,
} State;

char* read_entire_file(char* filename) {
    FILE* file = fopen(filename, "r");
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* str = malloc(fsize + 1);
    fread(str, fsize, 1, file);
    fclose(file);

    str[fsize] = 0;
    return str;
}

int main() {
    char *content = read_entire_file("inputs/day-2");
    char *reports[INPUT_SIZE];

    for (int i = 0, j = 0, k = 0; content[i]; i++) {
        if (content[i] == '\n') {
            content[i] = 0;
            reports[j++] = content + k;
            k = i + 1;
        }
    }

    int count = 0;
    for (int i = 0; i < INPUT_SIZE; i++) {
        int prev = -1;
        State state = -1;
        bool is_safe = true;

        do {
            int next = strtol(reports[i], reports + i, 10);
            if (prev == -1) {
                prev = next;
                continue;
            }


            int diff = next - prev;
            if (diff == 0) {
                is_safe = false;
                break;
            }

            if (state == -1) state = diff > 0 ? Ascending : Descending;

            if (state == Descending && diff > 0 || state == Ascending && diff < 0) {
                is_safe = false;
                break;
            } else if (diff > 3 || diff < -3) {
                is_safe = false;
                break;
            }
            prev = next;
        } while (*reports[i]);

        if (is_safe) count++;
    }
    printf("count: %i\n", count);
}
