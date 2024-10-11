#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char INPUT[] = "hxbxwxba";
int length = -1;

void increment() {
    for (int i = length - 1;;) {
        if (INPUT[i] == 'z') {
            INPUT[i] = 'a';
            i--;
        } else {
            INPUT[i]++;
            break;
        }
    }
}

bool filter_iol() {
    for (int i = 0; i < length; i++)
        if (INPUT[i] == 'i' || INPUT[i] == 'o' || INPUT[i] == 'l') {
            INPUT[i++]++;
            for (; i < length; i++) INPUT[i] = 'a';
            return false;
        }
    return true;
}

bool check_straight() {
    // possible bug, doesn't check for ascii overflow.
    for (int i = 0; i < length - 2; i++)
        if (INPUT[i + 1] == INPUT[i] + 1 && INPUT[i + 2] == INPUT[i] + 2)
            return true;
    return false;
}

bool check_pairs() {
    for (int i = 0; i < length - 2; i++)
        if (INPUT[i] == INPUT[i + 1]) {
            if (INPUT[i] != INPUT[i + 2]) {
                for (int j = i + 2; j < length; j++)
                    if (INPUT[j] == INPUT[j + 1] && (j + 2 >= length || INPUT[j] != INPUT[j + 2]) && INPUT[i] != INPUT[j]) {
                        return true;
                    }
            } else {
                i += 2;
            }
        }
    return false;
}

int main() {
    length = strlen(INPUT);
    for (;;) {
        if (filter_iol() && check_straight() && check_pairs()) break;
        increment();
    }
    printf("%s\n", INPUT);
}
