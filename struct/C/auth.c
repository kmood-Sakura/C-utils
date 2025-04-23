#include "../auth.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Auth initAuth() {
    Auth auth;
    auth.studentId = NULL;
    auth.password = NULL;
    auth.userData = NULL;
}

code getAuth(Auth* auth) {
    if (verifyAuth(auth)) {
        return -1;
    }
    string input;
    input = requestString(MAX_STUDENT_ID, "studentId");
    if(input == NULL || input == '\0') {
        return 0;
    }
    input = requestString(MAX_PASSWORD_LEN, "password");
    if(input == NULL || input == '\0') {
        auth->studentId = NULL;
        return 0;
    }
}

code verifyAuth(const Auth* auth) {
    if (auth == NULL) {
        return 0; // Invalid auth
    }
    if (auth->studentId == NULL || auth->password == NULL) {
        return 0; // Invalid student ID or password
    }
    return 1; // Success
}