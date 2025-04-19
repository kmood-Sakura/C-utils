#include "../log-status.h"

#include <stdio.h>

void Log(const Status *status) {
    if (status == NULL) {
        fprintf(stderr, "Error: Status is NULL\n");
        return;
    }
    LogStatus(status);
}

void CheckStatus(const Status *status) {
    if (status == NULL) {
        fprintf(stderr, "Error: Status is NULL\n");
        return;
    }
    if (status->code != 1) {
        LogErrorMsg(status);
        return;
    }
}

void LogStatus(const Status* status) {
    printf("Status Code : %d\n", status->code);
    printf("Message : %s\n", status->msg);
    LogErrorMsg(status);
}

void LogErrorMsg(const Status *status) {
    if (status->code == 0) {
        printf("Error message: %s\n", status->err_msg);
        printf("Details : %s\n", status->details);
        return;
    }
    if (status->code == -1) {
        printf("Warning message: %s\n", status->err_msg);
        return;
    }
}