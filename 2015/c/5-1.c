#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char* content = read_entire_file("inputs/day-5");
    int   len     = strlen(content);

    int nice = 0;
    for (int i = 0; i < len; i += 17) {
        int j      = i;
        int vowelc = 0;
        int dupc   = 0;
        for (; j - i < 16; j++) {
            if (content[j] == 'a' && content[j + 1] == 'b') break;
            if (content[j] == 'c' && content[j + 1] == 'd') break;
            if (content[j] == 'p' && content[j + 1] == 'q') break;
            if (content[j] == 'x' && content[j + 1] == 'y') break;

            if (content[j] == 'a' || content[j] == 'e' || content[j] == 'i'
                || content[j] == 'o' || content[j] == 'u')
                vowelc++;
            if (content[j] == content[j + 1]) dupc++;
        }
        if (j - i == 16 && vowelc >= 3 && dupc != 0) nice++;
    }
    printf("nice: %i\n", nice);
}
