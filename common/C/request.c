#include "../request.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

code requestConfirm() {
    printf("Comfirm Permission (default is no) 'y'= yes, 'n'= no\n");
    printf("enter : ");
    char c;
    error err = getLowerCaseChar(&c);
    if (err != NULL) {
        Warning("Invalid input, defaulting to no");
        return 0;
    }
    if (c == 'y') {
        return 1;
    }
    if (c == 'n') {
        return 0;
    }
    Warning("Invalid input, defaulting to no");
    return 0;
}

code requestCommand(char* command) {
    if (command == NULL) return 0;
    printf("command : ");
    error err = getLowerCaseChar(command);
    if (err != NULL) {
        return 0;
    }
    return 1;
}

code requestString(string* str, const uint32 maxLength, const string prompt) {
    if (str == NULL || maxLength == 0 || prompt == NULL) return 0;

    printf("%s : ", prompt);
    fflush(stdout);
    
    string input = (string)malloc((maxLength + 1) * sizeof(char));
    if (input == NULL) {
        return 0;
    }
    
    if (fgets(input, maxLength + 1, stdin) == NULL) {
        free(input);
        return 0;
    }

    uint32 len = stringLen(input);
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        free(input);
        return -1;
    }
    
    *str = input;
    return 1;
}