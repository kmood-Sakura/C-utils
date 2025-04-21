#ifndef AUTH_H
#define AUTH_H

#include "../datatype/string-type.h"
#include "leb2.h"
#include "file.h"
#include "path.h"
#include "calendar.h"
#include "notification.h"

typedef struct Auth {
    string studentId; // student ID
    string password; // password
    UserData* userData; // user data
} Auth;

typedef struct UserData {
    Notification* notifications; // list of notifications
    Calendar* calendars; // list of calendars
    LEB2* leb2; // list of courses
} UserData;

#endif // AUTH_H