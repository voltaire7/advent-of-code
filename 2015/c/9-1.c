#include <ctype.h>
#include <stdint.h>
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

typedef enum Location {
    Faerun,
    Norrath,
    Tristram,
    AlphaCentauri,
    Arbre,
    Snowdin,
    Tambi,
    Straylight,
} Location;

typedef struct Distance {
    uint8_t  to;
    uint8_t  from;
    uint16_t value;
} Distance;

Distance distances[28] = {0};

#define IF_MACRO(field) \
    if (content[j] == 'F') \
        distances[i].field = Faerun; \
    else if (content[j] == 'N') \
        distances[i].field = Norrath; \
    else if (content[j] == 'T' && content[j + 1] == 'r') \
        distances[i].field = Tristram; \
    else if (content[j] == 'A' && content[j + 1] == 'l') \
        distances[i].field = AlphaCentauri; \
    else if (content[j] == 'A' && content[j + 1] == 'r') \
        distances[i].field = Arbre; \
    else if (content[j] == 'S' && content[j + 1] == 'n') \
        distances[i].field = Snowdin; \
    else if (content[j] == 'S' && content[j + 1] == 't') \
        distances[i].field = Straylight; \
    else \
        distances[i].field = Tambi

void parse_content(char* content) {
    for (int i = 0, j = 0; content[j]; i++, j++) {
        IF_MACRO(from);
        while (isalpha(content[++j]));
        j += 4;
        IF_MACRO(to);
        while (isalpha(content[++j]));
        j += 3;
        distances[i].value = atoi(content + j);
        while (isdigit(content[++j]));
    }
}

int16_t lookup(uint8_t city1, uint8_t city2) {
    if (city1 == (uint8_t) -1 || city2 == (uint8_t) -1) return 0;
    for (int i = 0; i < 28; i++) {
        if ((distances[i].from == city1 && distances[i].to == city2)
            || (distances[i].from == city2 && distances[i].to == city1))
            return distances[i].value;
    }
    exit(1);
}

// holy fuck. it's 8 citys so I can use a bitmap (8 bits!)
uint16_t minmax(uint8_t* visited, uint16_t distance, uint8_t last_city) {
    uint8_t cond = visited[0] && visited[1] && visited[2] && visited[3]
        && visited[4] && visited[5] && visited[6] && visited[7];
    if (cond) return distance;

    uint8_t inner[8];
    memcpy(inner, visited, 8);
    uint16_t smallest = -1;
    for (int i = 0; i < 8; i++) {
        if (inner[i]) continue;
        inner[i]++;
        uint16_t ret = minmax(inner, distance + lookup(last_city, i), i);
        if (smallest > ret) smallest = ret;
        inner[i]--;
    }
    return smallest;
}

int32_t main() {
    char* content = read_entire_file("inputs/day-9");
    parse_content(content);

    uint8_t  visited[8] = {0};
    uint16_t smallest   = minmax(visited, 0, -1);
    printf("smallest: %i\n", smallest);
}
