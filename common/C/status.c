#include "../status.h"

#include <stdio.h>
#include <stdlib.h>

void initStatus(Status* status) {
    status->code = 0; // Initialize code to 0
    status->msg = NULL; // Initialize message to NULL
    status->details = NULL; // Initialize details to NULL
}

Status SetStatus(const code code, const string msg, const string details) {
    Status status; // Create a new status object
    status.code = code; // Set the status code
    status.msg = msg; // Set the status message
    status.details = details; // Set the status details
    return status; // Return the created status object
}

error allocateStatus(Status** status) {
    if (status == NULL) {
        return "Status pointer is NULL"; // Invalid status pointer
    }
    if (*status != NULL) {
        return "Status already allocated"; // Status already exists
    }
    *status = (Status*)malloc(sizeof(Status)); // Allocate memory for status
    if (*status == NULL) {
        return "Memory allocation failed"; // Memory allocation failed
    }
    (*status)->code = 0; // Initialize code to 0
    (*status)->msg = NULL; // Initialize message to NULL
    (*status)->details = NULL; // Initialize details to NULL

    return NULL; // Success
}

error createStatus(Status* status, const uint8 code, const string msg, const string details) {
    if (status == NULL) {
        return "Status pointer is NULL"; // Invalid status pointer
    }
    if (status->msg != NULL) {
        FreeString(&status->msg); // Free existing message
        status->msg = NULL; // Reset message
    }
    if (status->details != NULL) {
        FreeString(&status->details); // Free existing details
        status->details = NULL; // Reset details
    }
    status->code = code; // Set code
    error err = allocateString(&status->msg, msg); // Allocate memory for message
    if (err != NULL) {
        return err; // Memory allocation failed
    }
    err = allocateString(&status->details, details); // Allocate memory for details
    if (err != NULL) {
        return err; // Memory allocation failed
    }

    return NULL; // Success
}

void FreeStatusContent(Status* status) {
    if (status == NULL) return; // Invalid status pointer
    if (status->msg != NULL) {
        FreeString(&status->msg); // Free message string
    }
    if (status->details != NULL) {
        FreeString(&status->details); // Free details string
    }
}

void FreeStatus(Status* status) {
    if (status == NULL) return; // Invalid status pointer
    FreeStatusContent(status); // Free status content
    free(status); // Free status structure
    status = NULL; // Reset status pointer
}