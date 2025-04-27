#include "../auth.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// allocated at main page only

void initAuth(Auth* auth) {
    auth->studentId = NULL; // Initialize student ID
    auth->password = NULL; // Initialize password
    auth->userData = NULL; // Initialize user data
}

error createAuth(Auth* auth, const string studentId, const string password) {
    if (auth == NULL) {
        return "Auth pointer is required"; // Invalid auth pointer
    }
    if (studentId == NULL || password == NULL) {
        return "Student ID and password are required"; // Invalid parameters
    }
    error err = NULL;
    err = allocateString(&auth->studentId, studentId); // Allocate memory for student ID
    if (err != NULL) {
        return err; // Memory allocation failed
    }
    
    err = allocateString(&auth->password, password); // Allocate memory for password
    if (err != NULL) {
        FreeString(&auth->studentId); // Free student ID
        return err; // Memory allocation failed
    }
    
    return NULL; // Success
}

error createUserData(UserData** userData, NotificationList* notificationList, CalendarList* calendarList, LEB2* leb2) {
    if (userData == NULL) {
        return "User data pointer is required"; // Invalid user data pointer
    }

    *userData = (UserData*)malloc(sizeof(UserData)); // Allocate memory for user data
    if (*userData == NULL) {
        return "Memory allocation failed"; // Memory allocation failed
    }

    (*userData)->notificationList = notificationList; // Set notification list
    (*userData)->calendarList = calendarList; // Set calendar list
    (*userData)->leb2 = leb2; // Set LEB2 data
    
    return NULL; // Success
}

code isAuthExist(const Auth* auth) {
    if (auth == NULL) {
        return 0; // Invalid auth
    }
    if (auth->studentId == NULL && auth->password == NULL) {
        return 0; // Invalid student ID or password
    }
    return 1; // Success
}

void FreeAuthContent(Auth* auth) {
    if (auth == NULL) {
        return; // Invalid auth
    }
    if (auth->studentId != NULL) {
        FreeString(&auth->studentId); // Free student ID
    }
    if (auth->password != NULL) {
        FreeString(&auth->password); // Free password
    }
    if (auth->userData != NULL) {
        FreeUserData(auth->userData); // Free user data
    }
}

void FreeAuth(Auth* auth) {
    if (auth == NULL)return; // Invalid auth
    FreeAuthContent(auth); // Free auth content
    free(auth); // Free auth structure
}

void FreeUserDataContent(UserData* userData) {
    if (userData == NULL) return;

    if (userData->notificationList != NULL) {
        FreeNotificationList(userData->notificationList); // Free notifications
    }
    if (userData->calendarList != NULL) {
        FreeCalendarList(userData->calendarList); // Free calendars
    }
    if (userData->leb2 != NULL) {
        FreeLEB2(userData->leb2); // Free LEB2 data
    }
}

void FreeUserData(UserData* userData) {
    if (userData == NULL) {
        return; // Invalid user data
    }
    FreeUserDataContent(userData); // Free user data content
    free(userData); // Free user data structure
}