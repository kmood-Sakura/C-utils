#ifndef CHAR_TYPE_H
#define CHAR_TYPE_H

#include "../common/status.h"
#include "../common/log.h"
#include "../common/request.h"

#include "string-type.h"
#include "int-type.h"

error toLowerCase(char* c); // convert char to lower case
error getLowerCaseChar(char *c); // get char from user and convert to lower case

#endif // CHAR_TYPE_H