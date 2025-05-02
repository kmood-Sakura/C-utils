#include "../char-type.h"

#include <stdio.h>
#include <stdlib.h>

error toLowerCase(char *c) {
    if (c == NULL) {
        return "Character pointer is NULL";
    }
    if (*c >= 'A' && *c <= 'Z') {
        *c += 32; // Convert to lowercase
    }
    return NULL;
}

error getLowerCaseChar(char *c) {
    if (c == NULL) {
        return "Character pointer is NULL";
    }
    
    int32 input = getchar();
    if (input == EOF) {
        *c = '\0';  // Set to null character on EOF
        return NULL;  // Success
    }
    
    *c = (char)input;
    
    if (*c >= 'A' && *c <= 'Z') {
        *c += 32;  // Convert to lowercase
    }
    // Consume the newline character that follows
    int32 next = getchar();
    if (next != '\n' && next != EOF) {
        // If there are more characters on this line, put them back
        // (though this is not standard C, it works in many implementations)
        ungetc(next, stdin);
    }
    return NULL;  // Success
}