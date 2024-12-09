#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *content;

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

int calculate_size(int old_size) {
    int new_size = 0;
    for (int i = 0; i < old_size; i++) {
        new_size += content[i] - '0';
    }
    return new_size;
}

int *expand(int old_size, int new_size) {
    int *blocks = malloc((new_size+1) * sizeof(int));
    for (int i = 0, j = 0, k = 0; i < old_size; i++) {
        int n = content[i] - '0';
        for (; n--; k++) {
            blocks[k] = i % 2 ? -1 : j;
        }
        if (i % 2) j++;
    }
    blocks[new_size] = 0;
    return blocks;
}

void compact(int *expanded, int size) {
    for (int j = size - 1; 0 < j; j--) {
        if (expanded[j] == -1) continue;

        int n = expanded[j], count_needed = 1;
        while (expanded[--j] == n) count_needed++;

        for (int i = 0; i < j; i++) {
            if (expanded[i] != -1) continue;

            int count_available = 1;
            while (expanded[++i] == -1) count_available++;

            if (count_needed <= count_available) {
                i -= count_available + 1;
                while (count_needed--) {
                    expanded[++i] = expanded[++j];
                    expanded[j] = -1;
                }
                goto done;
            }
        }
        j++;
    done:;
    }
}

int main() {
    content = read_entire_file("2024/inputs/day-9");
    int old_size = strlen(content)-1;
    int new_size = calculate_size(old_size);
    int *expanded = expand(old_size, new_size);
    compact(expanded, new_size);
    long sum = 0;
    for (int i = 0; i < new_size; i++) {
        if (expanded[i] != -1) sum += i * expanded[i];
    }
    printf("answer: %li\n", sum);
}
