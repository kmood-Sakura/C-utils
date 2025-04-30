#ifndef AUTH_H
#define AUTH_H

#include "../datatype/string-type.h"
#include "../datatype/int-type.h"
#include "../datatype/char-type.h"
#include "../datatype/date-type.h"

#include "calendar.h"
#include "notification.h"
#include "leb2.h"
#include "path.h"

#define MAX_STUDENT_ID 11+1 // max student ID length
#define MAX_PASSWORD_LEN 30 // max password length

typedef struct UserData UserData;
typedef struct Auth Auth;

void initAuth(Auth* auth);

error createUserData(UserData** userData, NotificationList* notificationList, CalendarList* calendarList, LEB2* leb2);
error createAuth(Auth* auth, const string studentId, const string password);
code isAuthExist(const Auth* auth);

void FreeAuthContent(Auth* auth);
void FreeAuth(Auth* auth);
void FreeUserDataContent(UserData* userData);
void FreeUserData(UserData* userData);

typedef struct UserData {
    NotificationList* notificationList; // list of notifications
    CalendarList* calendarList; // list of calendars
    LEB2* leb2; // list of courses
} UserData;

typedef struct Auth {
    string studentId; // student ID
    string password; // password
    UserData* userData; // user data
    DataPath* dataPath; // data path
} Auth;

#endif // AUTH_H