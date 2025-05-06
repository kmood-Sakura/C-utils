#include "../string-type.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32 stringLen(const string str) {
    if (str == NULL) {
        return 0;
    }
    
    uint32 length = 0;
    while (str[length] != '\0') {
        length++;
    }
    
    return length;
}

string stringCopyN(string dest, const string src, uint32 n) {
    if (dest == NULL || src == NULL) {
        return NULL;
    }
    
    uint32 i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    
    return dest;
}

code stringEndsWith(const string str, const string suffix) {
    if (str == NULL || suffix == NULL)
        return 0;
    
    size_t strLen = stringLen(str);
    size_t suffixLen = stringLen(suffix);
    
    if (suffixLen > strLen)
        return 0;
    
    return stringCmp(str + strLen - suffixLen, suffix);
}

code stringCmp(const string str1, const string str2) {
    if (str1 == NULL || str2 == NULL) {
        fprintf(stderr, "NULL string\n");
        return 0;
    }
    
    int32 result = strcmp(str1, str2);
    return (result == 0) ? 1 : 0;
}

error allocateString(string* str, const string referStr) {
    if (str == NULL) {
        return "required string pointer to allocate";
    }
    
    if (*str != NULL) {
        return "string already allocated";
    }
    
    if (referStr == NULL) {
        return "required reference string";
    }
    
    uint32 length = stringLen(referStr);
    if (length == 0) {
        return "reference string is empty";
    }
    
    *str = (string)malloc((length + 1) * sizeof(char));
    if (*str == NULL) {
        return "Memory allocation failed";
    }
    
    strcpy(*str, referStr);
    return NULL;
}

error allocateStringLen(string* str, const string referStr, const uint32 length) {
    if (str == NULL) {
        return "required string pointer to allocate";
    }
    
    if (*str != NULL) {
        return "string already allocated";
    }
    
    if (length == 0 || referStr == NULL) {
        return "reference string required";
    }

    *str = (string)malloc((length + 1) * sizeof(char));
    if (*str == NULL) {
        return "Memory allocation failed";
    }

    strncpy(*str, referStr, length);
    (*str)[length] = '\0';

    return NULL;
}

error mergeTwoStrings(string* result, const string str1, const string str2) {
    if (result == NULL) {
        return "required result pointer";
    }
    
    if (*result != NULL) {
        return "string already exists";
    }
    
    if (str1 == NULL || str2 == NULL) {
        if (str1 == NULL && str2 == NULL) {
            return "at least one string required";
        }
        if (str1 == NULL) {
            return allocateString(result, str2);
        }
        return allocateString(result, str1);
    }

    uint32 totalLength = stringLen(str1) + stringLen(str2);
    if (totalLength == 0) {
        return "required reference string";
    }

    *result = (string)malloc((totalLength + 1) * sizeof(char));
    if (*result == NULL) {
        return "Memory allocation failed";
    }

    (*result)[0] = '\0'; 
    strcpy(*result, str1);
    strcat(*result, str2);

    (*result)[totalLength] = '\0';

    return NULL;
}

error mergeThreeStrings(string* result, const string str1, const string str2, const string str3) {
    if (result == NULL) {
        return "required result pointer";
    }
    
    if (*result != NULL) {
        return "result string already exists";
    }
    
    if (str1 == NULL || str2 == NULL || str3 == NULL) {
        if (str1 == NULL && str2 == NULL && str3 == NULL) {
            return "at least one string required";
        }
        if (str1 == NULL) {
            return mergeTwoStrings(result, str2, str3);
        }
        if (str2 == NULL) {
            return mergeTwoStrings(result, str1, str3);
        }
        return mergeTwoStrings(result, str1, str2);
    }

    uint32 totalLength = stringLen(str1) + stringLen(str2) + stringLen(str3);
    if (totalLength == 0) {
        return "required reference string";
    }

    *result = (string)malloc((totalLength + 1) * sizeof(char));
    if (*result == NULL) {
        return "Memory allocation failed";
    }

    (*result)[0] = '\0';
    strcpy(*result, str1);
    strcat(*result, str2);
    strcat(*result, str3);

    (*result)[totalLength] = '\0';

    return NULL;
}

error mergeTwoStringsLen(string* result, const string str1, const string str2, const uint32 maxLen) {
    if (result == NULL) {
        return "required result pointer";
    }
    
    if (*result != NULL) {
        return "result string already exists";
    }
    
    if (str1 == NULL || str2 == NULL) {
        if (str1 == NULL && str2 == NULL) {
            return "at least one string required";
        }
        if (str1 == NULL) {
            return allocateStringLen(result, str2, maxLen);
        }
        return allocateStringLen(result, str1, maxLen);
    }

    *result = (string)malloc((maxLen + 1) * sizeof(char));
    if (*result == NULL) {
        return "Memory allocation failed";
    }

    (*result)[0] = '\0';
    strcpy(*result, str1);
    strcat(*result, str2);
    
    (*result)[maxLen] = '\0';

    return NULL;
}

error mergeThreeStringsLen(string* result, const string str1, const string str2, const string str3, const uint32 maxLen) {
    if (result == NULL) {
        return "required result pointer";
    }
    
    if (*result != NULL) {
        return "result string already exists";
    }
    
    if (str1 == NULL || str2 == NULL || str3 == NULL) {
        if (str1 == NULL && str2 == NULL && str3 == NULL) {
            return "at least one string required";
        }
        if (str1 == NULL) {
            return mergeTwoStringsLen(result, str2, str3, maxLen);
        }
        if (str2 == NULL) {
            return mergeTwoStringsLen(result, str1, str3, maxLen);
        }
        return mergeTwoStringsLen(result, str1, str2, maxLen);
    }

    *result = (string)malloc((maxLen + 1) * sizeof(char));
    if (*result == NULL) {
        return "Memory allocation failed";
    }

    (*result)[0] = '\0';
    strcpy(*result, str1);
    strcat(*result, str2);
    strcat(*result, str3);

    (*result)[maxLen] = '\0';

    return NULL;
}

error createString(string* result, const string source) {
    if (result == NULL) {
        return "required result pointer";
    }
    
    if (*result == NULL) {
        return "string not located yet";
    }

    uint32 length = stringLen(source);
    if (length == 0) {
        return "source string required";
    }
    strcpy(*result, source);
    return NULL;
}

error createStringLen(string* result, const string source, const uint32 length) {
    if (result == NULL) {
        return "required result pointer";
    }
    
    if (*result == NULL) {
        return "string not located yet";
    }

    if (length == 0 || source == NULL) {
        return "source string required";
    }

    strncpy(*result, source, length);
    (*result)[length] = '\0';

    return NULL;
}

void FreeString(string *str) {
    if (str == NULL) return;
    if (*str == NULL) return;
    free(*str);
    *str = NULL;
}