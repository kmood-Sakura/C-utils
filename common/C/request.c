#include "../request.h"

#include <stdio.h>

code requestConfirm() {
    printf("Comfirm Permission (default is no) 'y'= yes, 'n'= no\n");
    printf("Please enter your choice : ");
    char c = getLowerCaseChar();
    if (c == 'y') {
        return 1; // Yes
    }
    if (c == 'n') {
        return 0; // No
    }
    Warning("Invalid input, defaulting to no");
    return 0; // Default to no
}

char requestCommand(const string commandKeys) {
    if (commandKeys == NULL) {
        Warning("Command Key patterns required");
        return '\0'; // Invalid command keys
    }
    printf("Please enter your command : ");
    char c = getLowerCaseChar();
    for (uint8 i = 0; i < stringLen(commandKeys); i++) {
        if (c == commandKeys[i]) {
            return c; // Valid command
        }
    }
    Warning("Invalid command");
    return '\0';
}

string requestString(const uint32 maxLength, const string prompt) {
    if (maxLength == 0) {
        Warning("Max length required");
        return NULL; // Invalid max length
    }
    string str = (string)malloc((maxLength + 1) * sizeof(char)); // +1 for null terminator
    if (str == NULL) {
        Error("Memory allocation failed");
        return NULL; // Memory allocation failed
    }
    if (prompt != NULL) {
        printf("%s : ", prompt); // Print prompt if provided
    }
    fgets(str, maxLength + 1, stdin); // Read string from input
    str[stringLen(str)] = '\0'; // Remove newline character
    return str;
}
