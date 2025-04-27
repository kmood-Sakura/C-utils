#include "../request.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

code requestConfirm() {
    printf("Comfirm Permission (default is no) 'y'= yes, 'n'= no\n");
    printf("Please enter your choice : ");
    char c;
    error err = getLowerCaseChar(&c); // Get user input
    if (err != NULL) {
        Warning("Invalid input, defaulting to no");
        return 0; // Default to no
    }
    if (c == 'y') {
        return 1; // Yes
    }
    if (c == 'n') {
        return 0; // No
    }
    Warning("Invalid input, defaulting to no");
    return 0; // Default to no
}

code requestCommand(char* command, const string commandKeys) {
    if (command == NULL) {
        return 0; // Invalid command pointer
    }
    if (commandKeys == NULL) {
        return 0; // Invalid command keys
    }

    printf("Please enter your command : ");
    error err = getLowerCaseChar(command); // Get user input
    if (err != NULL) {
        return 0;
    }
    for (uint8 i = 0; i < stringLen(commandKeys); i++) {
        if (*command == commandKeys[i]) {
            return 1; // Valid command
        }
    }
    Warning("Invalid command");
    return -1; // Invalid command
}

code requestString(string* str, const uint32 maxLength, const string prompt) {
    if (str == NULL) {
        return 0; // Invalid string pointer
    }
    if (maxLength == 0) {
        return 0; // Invalid max length
    }
    if (prompt == NULL) {
        return 0; // Invalid prompt
    }

    printf("%s : ", prompt);
    fgets(*str, maxLength + 1, stdin); // Read string from user
    uint32 len = stringLen(*str);
    if (len == 0) {
        return -1; // Empty string
    }
    if (*str[len - 1] == '\n') {
        *str[len - 1] = '\0'; // Remove newline character
    }else{
        *str[len] = '\0'; // Ensure null termination
    }
    if (len > maxLength) {
        *str[maxLength] = '\0'; // Ensure null termination
    }

    return 1; // Success
}