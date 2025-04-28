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

code stringCmp(const string str1, const string str2) {
    if (str1 == NULL || str2 == NULL) {
        fprintf(stderr, "NULL string\n");
        return 0; // Invalid comparison
    }
    
    int32 result = strcmp(str1, str2);
    return (result == 0) ? 1 : 0; // 1 for equal, 0 for not equal
}

error allocateString(string* str, const string referStr) {
    if (str == NULL) {
        return "required string pointer to allocate"; // Invalid string pointer
    }
    
    if (*str != NULL) {
        return "string already allocated"; // String already exists
    }
    
    if (referStr == NULL) {
        return "required reference string"; // No reference string
    }
    
    uint32 length = stringLen(referStr);
    if (length == 0) {
        return "reference string is empty"; // Empty reference string
    }
    
    *str = (string)malloc((length + 1) * sizeof(char));
    if (*str == NULL) {
        return "Memory allocation failed"; // Memory allocation failed
    }
    
    strcpy(*str, referStr);
    return NULL; // Success
}

error allocateStringLen(string* str, const string referStr, const uint32 length) {
    if (str == NULL) {
        return "required string pointer to allocate"; // Invalid string pointer
    }
    
    if (*str != NULL) {
        return "string already allocated"; // String already exists
    }
    
    if (length == 0 || referStr == NULL) {
        return "reference string required"; // Invalid length or NULL reference
    }

    *str = (string)malloc((length + 1) * sizeof(char));
    if (*str == NULL) {
        return "Memory allocation failed";
    }

    strncpy(*str, referStr, length); // Copy up to length characters
    (*str)[length] = '\0'; // Null-terminate the string

    return NULL; // Success
}

error mergeTwoStrings(string* result, const string str1, const string str2) {
    if (result == NULL) {
        return "required result pointer"; // Invalid result pointer
    }
    
    if (*result != NULL) {
        return "string already exists"; // Invalid result string pointer
    }
    
    if (str1 == NULL || str2 == NULL) {
        if (str1 == NULL && str2 == NULL) {
            return "at least one string required"; // Both strings are NULL
        }
        if (str1 == NULL) {
            return allocateString(result, str2); // Allocate result with str2
        }
        return allocateString(result, str1); // Allocate result with str1
    }

    uint32 totalLength = stringLen(str1) + stringLen(str2);
    if (totalLength == 0) {
        return "required reference string"; // Both strings are empty
    }

    *result = (string)malloc((totalLength + 1) * sizeof(char));
    if (*result == NULL) {
        return "Memory allocation failed";
    }

    (*result)[0] = '\0'; // Initialize with empty string
    strcpy(*result, str1); // Copy str1 to result
    strcat(*result, str2); // Concatenate str2 to result

    (*result)[totalLength] = '\0'; // Ensure null termination

    return NULL; // Success
}

error mergeThreeStrings(string* result, const string str1, const string str2, const string str3) {
    if (result == NULL) {
        return "required result pointer"; // Invalid result pointer
    }
    
    if (*result != NULL) {
        return "result string already exists"; // Invalid result string pointer
    }
    
    if (str1 == NULL || str2 == NULL || str3 == NULL) {
        if (str1 == NULL && str2 == NULL && str3 == NULL) {
            return "at least one string required"; // All strings are NULL
        }
        if (str1 == NULL) {
            return mergeTwoStrings(result, str2, str3); // Merge str2 and str3
        }
        if (str2 == NULL) {
            return mergeTwoStrings(result, str1, str3); // Merge str1 and str3
        }
        return mergeTwoStrings(result, str1, str2); // Merge str1 and str2
    }

    uint32 totalLength = stringLen(str1) + stringLen(str2) + stringLen(str3);
    if (totalLength == 0) {
        return "required reference string"; // All strings are empty
    }

    *result = (string)malloc((totalLength + 1) * sizeof(char));
    if (*result == NULL) {
        return "Memory allocation failed"; // Memory allocation failed
    }

    (*result)[0] = '\0'; // Initialize with empty string
    strcpy(*result, str1); // Copy str1 to result
    strcat(*result, str2); // Concatenate str2 to result
    strcat(*result, str3); // Concatenate str3 to result

    (*result)[totalLength] = '\0'; // Ensure null termination

    return NULL; // Success
}

error mergeTwoStringsLen(string* result, const string str1, const string str2, const uint32 maxLen) {
    if (result == NULL) {
        return "required result pointer"; // Invalid result pointer
    }
    
    if (*result != NULL) {
        return "result string already exists"; // Invalid result string pointer
    }
    
    if (str1 == NULL || str2 == NULL) {
        if (str1 == NULL && str2 == NULL) {
            return "at least one string required"; // Both strings are NULL
        }
        if (str1 == NULL) {
            return allocateStringLen(result, str2, maxLen); // Allocate result with str2
        }
        return allocateStringLen(result, str1, maxLen); // Allocate result with str1
    }

    *result = (string)malloc((maxLen + 1) * sizeof(char));
    if (*result == NULL) {
        return "Memory allocation failed"; // Memory allocation failed
    }

    (*result)[0] = '\0'; // Initialize with empty string
    strcpy(*result, str1); // Copy str1 to result
    strcat(*result, str2); // Concatenate str2 to result
    
    (*result)[maxLen] = '\0'; // Ensure null termination

    return NULL; // Success
}

error mergeThreeStringsLen(string* result, const string str1, const string str2, const string str3, const uint32 maxLen) {
    if (result == NULL) {
        return "required result pointer"; // Invalid result pointer
    }
    
    if (*result != NULL) {
        return "result string already exists"; // Invalid result string pointer
    }
    
    if (str1 == NULL || str2 == NULL || str3 == NULL) {
        if (str1 == NULL && str2 == NULL && str3 == NULL) {
            return "at least one string required"; // All strings are NULL
        }
        if (str1 == NULL) {
            return mergeTwoStringsLen(result, str2, str3, maxLen); // Merge str2 and str3
        }
        if (str2 == NULL) {
            return mergeTwoStringsLen(result, str1, str3, maxLen); // Merge str1 and str3
        }
        return mergeTwoStringsLen(result, str1, str2, maxLen); // Merge str1 and str2
    }

    *result = (string)malloc((maxLen + 1) * sizeof(char));
    if (*result == NULL) {
        return "Memory allocation failed"; // Memory allocation failed
    }

    (*result)[0] = '\0'; // Initialize with empty string
    strcpy(*result, str1); // Copy str1 to result
    strcat(*result, str2); // Concatenate str2 to result
    strcat(*result, str3); // Concatenate str3 to result

    (*result)[maxLen] = '\0'; // Ensure null termination

    return NULL; // Success
}

// Helper function for creating a new string (missing in original)
error createString(string* result, const string source) {
    if (result == NULL) {
        return "required result pointer"; // Invalid result pointer
    }
    
    if (*result == NULL) {
        return "string not located yet"; // String already allocated
    }

    uint32 length = stringLen(source);
    if (length == 0) {
        return "source string required"; // No source string
    }
    strcpy(*result, source);
    return NULL; // Success
}

void FreeString(string *str) {
    if (str == NULL) return;
    if (*str == NULL) return; // Invalid string pointer
    free(*str); // Free the string memory
    *str = NULL; // Reset the pointer to NULL
}