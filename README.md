# Utils

## Description
The Utils submodule provides essential utilities and data structures for C applications. It contains core functionality for data management, date handling, file operations, authentication, and more.

## Components

### Data Types
- `string-type.h`: String handling and operations
- `int-type.h`: Integer type definitions (uint8, int16, etc.)
- `float-type.h`: Floating point type definitions
- `char-type.h`: Character manipulation functions
- `date-type.h`: Date and time handling structures and functions

### Core Utilities
- `auth.h`: Authentication system with user data management
- `calendar.h`: Calendar and task management
- `file.h`: File and folder operations with cross-platform support
- `leb2.h`: Learning management system components
- `notification.h`: Notification handling system
- `path.h`: Path manipulation and management

### Common Functions
- `status.h`: Status and error handling
- `log.h`: Logging functionality
- `request.h`: User input handling and requests

## Structure Overview

```
Utils Submodule
├── datatype/
│   ├── string-type.h
│   ├── int-type.h
│   ├── float-type.h
│   ├── char-type.h
│   └── date-type.h
├── common/
│   ├── status.h
│   ├── log.h
│   └── request.h
└── core components
    ├── auth.h
    ├── calendar.h
    ├── file.h
    ├── leb2.h
    ├── notification.h
    └── path.h
```

## Usage Examples

### String Operations
```c
#include "datatype/string-type.h"

string myString;
error err = allocateString(&myString, "Hello World");
if (err != NULL) {
    // Handle error
}

// Use string...

FreeString(&myString);
```

### File Operations
```c
#include "file.h"

File* file;
error err = allocateFile(&file);
if (err != NULL) {
    // Handle error
}

err = createFile(file, "data.txt", "/home/user/documents", "txt");
if (err != NULL) {
    // Handle error
}

err = MakeFile(file);
if (err != NULL) {
    // Handle error
}

FreeFile(file);
```

### Authentication
```c
#include "auth.h"

Auth auth;
initAuth(&auth);

error err = createAuth(&auth, "12345678", "password123");
if (err != NULL) {
    // Handle error
}

// Use auth...

FreeAuthContent(&auth);
```

## Memory Management

All components provide memory allocation and deallocation functions:
- `allocate*`: Allocate memory for a structure
- `create*`: Initialize a structure with data
- `Free*Content`: Free the content of a structure without freeing the structure itself
- `Free*`: Free the structure and its content

Always free allocated memory to prevent memory leaks.

## Error Handling

Functions that can fail return an `error` type (alias for `string`):
- `NULL`: Success
- Non-NULL: Error message

Example error handling:
```c
error err = someFunction();
if (err != NULL) {
    LogMsg(err);
    FreeString(&err);
    // Handle error
}
```

## Thread Safety

This library is not guaranteed to be thread-safe. Use appropriate synchronization mechanisms when accessing shared resources from multiple threads.