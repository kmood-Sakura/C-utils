#ifndef LOG_STATUS_H
#define LOG_STATUS_H

#include "../struct/status-code.h"

void CheckStatus(const Status *status);
void LogStatus(const Status* status);
void LogErrorMsg(const Status *status);
void Log(const Status *status);

#endif// LOG_STATUS_H