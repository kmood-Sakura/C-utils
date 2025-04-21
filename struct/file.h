#ifndef FILE_H
#define FILE_H

#include "../datatype/int-type.h"
#include "../datatype/string-type.h"

#include "../common/status.h"
#include "../common/log.h"

#include "path.h"

typedef struct File {
    string filename; // file name
    Path dirPath; // file path
    string fileType; // file type
} File;

typedef struct Folder {
    string folderName; // folder name
    Path dirPath; // folder path
} Folder;

#endif // FILE_H