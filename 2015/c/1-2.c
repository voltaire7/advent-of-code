#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* file = fopen("./inputs/day-1", "r");
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* str = malloc(fsize + 1);
    fread(str, fsize, 1, file);
    fclose(file);

    str[fsize] = 0;

    int floor = 0;
    for (int i = 0; i < fsize; i++) {
        if (str[i] == '(')
            floor++;
        else if (str[i] == ')')
            floor--;

        if (floor == -1) {
            printf("%i\n", i + 1);
            break;
        }
    }

    free(str);
}
