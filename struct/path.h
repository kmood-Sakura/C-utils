#ifndef PATH_H  
#define PATH_H

#include "../datatype/int-type.h"
#include "../datatype/string-type.h"

#include "../common/status.h"
#include "../common/log.h"
#include "../common/request.h"

typedef struct Path Path; // Forward declaration of Path struct
typedef struct DataPath DataPath; // Forward declaration of DataPath struct

void initPath(Path* pathTC);
error createPath(Path* pathTC,const string path);
error createPathLen(Path* pathTC, const string path, const uint32 length);
error mergeTwoPaths(Path* pathTC,const Path path1, const Path path2);
error mergeThreePaths(Path* pathTC, const Path path1, const Path path2, const Path path3);
error createFilePath(Path* filepath, const Path filename, const Path dirPath, const Path fileType);
error createFolderPath(Path* folderPath, const string folderName, const Path dirPath);
error createFolderPathLen(Path* folderPath, const string folderName, const Path dirPath, const uint32 length);
error createDirPath(Path* folderPath, const Path folderName, const Path dirPath);
error createPathFileorFolder(Path* filepath, const Path filename, const Path dirPath);

void initDataPath(DataPath* dataPath);
error allocateDataPath(DataPath** dataPath);
error createDataPath(DataPath* dataPath, const Path path, const Path filename, const code isFolder);
error addChildDataPath(DataPath* parent, DataPath* child);
error findDataPathByFilename(const DataPath* parent, const string filename, DataPath** result);
error getDirDataPath(DataPath* dataPath);
error removeChildDataPath(DataPath* parent, const Path filename);

void FreeDirDataPath(DataPath* dataPath);
void PrintDataPath(DataPath* dataPath);
void PrintDataPathChildren(DataPath* dataPath, uint8 parentIsLast, uint16 level);

void FreeDataPath(DataPath* dataPath);
void FreeDataPathContent(DataPath* dataPath);
typedef void (*DataPathAction)(DataPath* node, void* userData);
void traverseDataPath(DataPath* dataPath, DataPathAction action, void* userData);

void FreePathContent(Path* path);
void FreePath(Path* path);

error getCurrentPath(Path* pathObj);

typedef struct Path {
    string path;
    uint32 length;
} Path; // Path is a string

typedef struct DataPath {
    Path path; // path to the data
    Path filename;
    code isFolder; // 1: folder, 0: file
    DataPath* parent;
    DataPath** Dir;
    uint16 sizeDir;
} DataPath;

#endif