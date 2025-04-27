#ifndef PATH_H  
#define PATH_H

#include "../datatype/int-type.h"
#include "../datatype/string-type.h"

#include "../common/status.h"
#include "../common/log.h"
#include "../common/request.h"

typedef struct Path {
    string path;
    uint32 length;
} Path; // Path is a string

error createPath(Path* pathTC,const string path);
error createPathLen(Path* pathTC, const string path, const uint32 length);
error mergeTwoPaths(Path* pathTC,const Path path1, const Path path2);
error mergeThreePaths(Path* pathTC, const Path path1, const Path path2, const Path path3);
error createFilePath(Path* filepath, const Path filename, const Path dirPath, const Path fileType);
error createDirPath(Path* folderPath, const Path folderName, const Path dirPath);

void FreePathContent(Path* path);
void FreePath(Path* path);

#endif // PATH_H