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

typedef enum OP {
    LITERAL,
    AND,
    OR,
    LSHIFT,
    RSHIFT,
    NOT,
} OP;

typedef struct Node {
    char*    name;
    char     is_memoized;
    uint16_t value;
    OP       op;
    char*    left;
    char*    right;
} Node;

#define NODE_COUNT 339
Node nodes[NODE_COUNT];

Node* lookup(char* name) {
    for (int i = 0; i < NODE_COUNT; i++)
        if (strcmp(name, nodes[i].name) == 0) return &nodes[i];
    printf("Not found: '%s'\n", name);
    exit(1);
}

#define PARSE(op) \
    (isalpha(node->left[0]) ? parse(lookup(node->left)) : atoi(node->left)) \
        op(isalpha(node->right[0]) ? parse(lookup(node->right)) \
                                   : atoi(node->right))

uint16_t parse(Node* node) {
    // printf("debug: '%s'\n", node->name);
    if (node->is_memoized) return node->value;
    switch (node->op) {
        case LITERAL:
            if (isalpha(node->left[0]))
                return parse(lookup(node->left));
            else
                return atoi(node->left);
        case AND:
            node->is_memoized = 1;
            node->value       = PARSE(&);
            break;
        case OR:
            node->is_memoized = 1;
            node->value       = PARSE(|);
            break;
        case LSHIFT:
            node->is_memoized = 1;
            node->value       = PARSE(<<);
            break;
        case RSHIFT:
            node->is_memoized = 1;
            node->value       = PARSE(>>);
            break;
        case NOT:
            node->is_memoized = 1;
            node->value       = ~parse(lookup(node->right));
            break;
    }
    return node->value;
}

int main() {
    char* content = read_entire_file("inputs/day-7");
    for (int i = 0, j = 0; content[j] != '\0'; i++, j++) {
        Node node = {0};
        if (content[j] == 'N') {
            node.op = NOT;
            j += 4;
            node.right = content + j;
            while (isalnum(content[j])) j++;
            content[j++] = '\0';
            goto lit;
        } else {
            node.left = content + j;
            while (isalnum(content[j])) j++;
            content[j++] = '\0';
            switch (content[j]) {
                case '-':
                    node.op = LITERAL;
                    goto lit;
                    break;
                case 'A':
                    node.op = AND;
                    break;
                case 'O':
                    node.op = OR;
                    break;
                case 'L':
                    node.op = LSHIFT;
                    break;
                case 'R':
                    node.op = RSHIFT;
                    break;
            }
            while (isalpha(content[j])) j++;
            node.right = content + ++j;
            while (isalnum(content[j])) j++;
            content[j] = '\0';
        lit:
            while (content[j] != '>') j++;
            j += 2;
            node.name = content + j;
            while (isalpha(content[j])) j++;
            content[j] = '\0';
        }
        nodes[i] = node;
    }

    printf("answer: %i\n", parse(&nodes[311]));
}
