#ifndef LOG_H
#define LOG_H

#include "../datatype/int-type.h"
#include "../datatype/string-type.h"

#include "status.h"

void Log(const Status* status);
void LogStatus(const Status* status);

void Error(const string msg);
void Warning(const string msg);
void Success(const string msg);
void LogMsg(const string msg);
void Details(const string detail);

#endif// LOG_STATUS_H