#include "../status.h"

#include <stdio.h>
#include <stdlib.h>

void initStatus(Status* status) {
    status->code = 0;
    status->msg = NULL;
    status->details = NULL;
}

Status SetStatus(const code code, const string msg, const string details) {
    Status status;
    status.code = code;
    status.msg = msg;
    status.details = details;
    return status;
}

error allocateStatus(Status** status) {
    if (status == NULL) {
        return "Status pointer is NULL";
    }
    if (*status != NULL) {
        return "Status already allocated";
    }
    *status = (Status*)malloc(sizeof(Status));
    if (*status == NULL) {
        return "Memory allocation failed";
    }
    (*status)->code = 0;
    (*status)->msg = NULL;
    (*status)->details = NULL;

    return NULL;
}

error createStatus(Status* status, const uint8 code, const string msg, const string details) {
    if (status == NULL) {
        return "Status pointer is NULL";
    }
    if (status->msg != NULL) {
        FreeString(&status->msg);
        status->msg = NULL;
    }
    if (status->details != NULL) {
        FreeString(&status->details);
        status->details = NULL;
    }
    status->code = code;
    error err = allocateString(&status->msg, msg);
    if (err != NULL) {
        return err;
    }
    err = allocateString(&status->details, details);
    if (err != NULL) {
        return err;
    }

    return NULL;
}

void FreeStatusContent(Status* status) {
    if (status == NULL) return;
    if (status->msg != NULL) {
        FreeString(&status->msg);
    }
    if (status->details != NULL) {
        FreeString(&status->details);
    }
}

void FreeStatus(Status* status) {
    if (status == NULL) return;
    FreeStatusContent(status);
    free(status);
    status = NULL;
}