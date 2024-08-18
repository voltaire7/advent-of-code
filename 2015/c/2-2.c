#include <stdio.h>
#include <stdlib.h>

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
    char* content = read_entire_file("inputs/day-2") - 1;

    int total = 0;
    for (;;) {
        int l = strtol(content + 1, &content, 10);
        if (!l) break;
        int w = strtol(content + 1, &content, 10);
        int h = strtol(content + 1, &content, 10);

        int lwp = (l + w) * 2;
        int whp = (w + h) * 2;
        int hlp = (h + l) * 2;
        total += (lwp < whp ? (lwp < hlp ? lwp : hlp) : (whp < hlp ? whp : hlp))
            + l * w * h;
    }
    printf("%i\n", total);
}
