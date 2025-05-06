#ifndef REQUEST_H
#define REQUEST_H

#include "log.h" 
#include "../datatype/char-type.h"
#include "../datatype/int-type.h"
#include "../datatype/string-type.h"

code requestConfirm();
code requestCommand(char* command);
code requestString(string* str, const uint32 maxLength, const string prompt);

#endif