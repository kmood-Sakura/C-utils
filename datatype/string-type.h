#ifndef STRING_TYPE_H
#define STRING_TYPE_H

#include "int-type.h"

typedef char* string; // string size upon uint32
typedef string error;

typedef struct textline {
    string line; // text line
    struct textline* nextline; // next line
} textline;

typedef struct Strings{
    string str; // string
    uint32 length; // string length
} Strings;

uint32 stringLen(const string str);

code stringCmp(const string str1, const string str2);

error allocateString(string* str, const string referStr);
error allocateStringLen(string* str, const string referStr, const uint32 length);
error mergeTwoStrings(string* result, const string str1, const string str2);
error mergeThreeStrings(string* result, const string str1, const string str2, const string str3);
error mergeTwoStringsLen(string* result, const string str1, const string str2, const uint32 maxLen);
error mergeThreeStringsLen(string* result, const string str1, const string str2, const string str3, const uint32 maxLen);
error createString(string* result, const string source);
error createStringLen(string* result, const string source, const uint32 length);

void FreeString(string* str);

#endif // STRING_TYPE_H