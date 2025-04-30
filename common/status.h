#ifndef STATUS_H
#define STATUS_H

#include "../datatype/int-type.h"
#include "../datatype/string-type.h"

// typedef int8 code; // 0-failed, 1-success, -1-warning

typedef struct Status {
    code code; // 0-failed, 1-success, -1-warning
    string msg; // message
    string details; // detail message
} Status;

Status SetStatus(const code code, const string msg, const string details); // set status
void initStatus(Status* status); // initialize status
error allocateStatus(Status** status); // allocate status
error createStatus(Status* status, const uint8 code, const string msg, const string details); // create status

void FreeStatusContent(Status* status);
void FreeStatus(Status* status); // free status

#endif // STATUS_H