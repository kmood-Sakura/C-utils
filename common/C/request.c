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
    
    string input = (string)malloc((maxLength + 1) * sizeof(char)); // Allocate memory for input string
    if (input == NULL) {
        return 0; // Memory allocation failed
    }
    
    // Clear the input buffer
    fgets(input, maxLength + 1, stdin);
    
    uint32 len = strlen(input);
    if (len == 0) {
        free(input);
        return -1; // Empty string
    }
    
    // Remove newline character if present
    if (input[len - 1] == '\n') {
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