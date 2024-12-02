#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INPUT_SIZE 1000
#define MAX_LEVELS 9

int arr[INPUT_SIZE][MAX_LEVELS] = {};

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

char **split(char *content) {
    static char *reports[INPUT_SIZE];
    for (int i = 0, j = 0, k = 0; content[i]; i++) {
        if (content[i] == '\n') {
            content[i] = 0;
            reports[j++] = content + k;
            k = i + 1;
        }
    }
    return reports;
}

void to_array(char **reports) {
    for (int i = 0; i < INPUT_SIZE; i++) {
        for (int j = 0; *reports[i]; j++) {
            arr[i][j] = strtol(reports[i], reports + i, 10);
        }
    }
}

int count(int reports[INPUT_SIZE][MAX_LEVELS]) {
    int count = 0;

    for (int i = 0; i < INPUT_SIZE; i++) {
        bool is_safe = true;
        int *report = reports[i];
        int skip = -1;

        do {
            int prev_level = -1;
            State state = -1;

            for (int j = 0; j < MAX_LEVELS; j++) {
                if (j == skip) continue;

                int next_level = report[j];
                if (next_level == 0) {
                    if (!is_safe) {
                        is_safe = true;
                        skip = -1;
                    }
                    break;
                }
                if (prev_level == -1) {
                    prev_level = next_level;
                    continue;
                }

                int diff = next_level - prev_level;
                if (state == -1) state = diff > 0 ? Ascending : Descending;

                bool is_zero = diff == 0;
                bool is_valid_state = state == Descending && diff > 0 || state == Ascending && diff < 0;
                bool is_valid_diff_range = diff > 3 || diff < -3;

                if (is_zero || is_valid_state || is_valid_diff_range) {
                    is_safe = false;
                    skip++;
                    break;
                }

                prev_level = next_level;
            }
        } while (skip != -1 && skip < MAX_LEVELS && report[skip] != 0);

        if (is_safe) count++;
    }
    return count;
}

int main() {
    char *content = read_entire_file("inputs/day-2");
    char **lines = split(content);
    to_array(lines);
    printf("count: %i\n", count(arr));
}
