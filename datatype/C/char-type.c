#include "../char-type.h"

#include <stdio.h>
#include <stdlib.h>

error toLowerCase(char *c) {
    if (c == NULL) {
        return "Character pointer is NULL";
    }
    if (*c >= 'A' && *c <= 'Z') {
        *c += 32;
    }
    return NULL;
}

error getLowerCaseChar(char *c) {
    if (c == NULL) {
        return "Character pointer is NULL";
    }
    
    int32 input = getchar();
    if (input == EOF) {
        *c = '\0';
        return NULL;
    }
    
    *c = (char)input;
    
    if (*c >= 'A' && *c <= 'Z') {
        *c += 32;
    }
    int32 next = getchar();
    if (next != '\n' && next != EOF) {
        ungetc(next, stdin);
    }
    return NULL;
}
