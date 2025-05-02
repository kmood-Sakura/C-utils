#include "../request.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

code requestConfirm() {
    printf("Comfirm Permission (default is no) 'y'= yes, 'n'= no\n");
    printf("enter : ");
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

code requestCommand(char* command, const string prompt) {
    if (command == NULL) {
        return 0; // Invalid command pointer
    }
    printf("Options : \n%s\ncommand : ",prompt);
    error err = getLowerCaseChar(command); // Get user input
    if (err != NULL) {
        return 0;
    }
    if (*command == 'e'){ // default exit command
        return 0; // Exit command
    }
    return 1; // Success
}

code requestString(string* str, const uint32 maxLength, const string prompt) {
    if (str == NULL || maxLength == 0 || prompt == NULL) {
        return 0; // Invalid parameters
    }

    printf("%s : ", prompt);
    fflush(stdout);
    
    string input = (string)malloc((maxLength + 1) * sizeof(char));
    if (input == NULL) {
        return 0; // Memory allocation failed
    }
    
    // Do not use fflush(stdin) as it's not standard compliant
    
    // Read input
    if (fgets(input, maxLength + 1, stdin) == NULL) {
        free(input);
        return 0; // Read error
    }

    uint32 len = stringLen(input);
    
    // Remove newline character if present
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }
    
    // Check if string is now empty
    if (len == 0) {
        free(input);
        return -1; // Empty string
    }
    
    *str = input; // Assign input to str
    return 1; // Success
}