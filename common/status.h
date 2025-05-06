#ifndef STATUS_H
#define STATUS_H

#include "../datatype/int-type.h"
#include "../datatype/string-type.h"

typedef struct Status {
    code code; // 0-failed, 1-success, -1-warning
    string msg;
    string details;
} Status;

Status SetStatus(const code code, const string msg, const string details);
void initStatus(Status* status);
error allocateStatus(Status** status);
error createStatus(Status* status, const uint8 code, const string msg, const string details);

void FreeStatusContent(Status* status);
void FreeStatus(Status* status);

#endif