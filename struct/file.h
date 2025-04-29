#ifndef FILE_H
#define FILE_H

#include "../datatype/int-type.h"
#include "../datatype/string-type.h"

#include "path.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <direct.h>
#ifdef _WIN32
    // #include <direct.h>
    // Windows mkdir() only takes one argument
    #define MKDIR(dir) _mkdir(dir)
#else
    // #include <sys/stat.h>
    // #include <sys/types.h>
    // Mac/Unix mkdir() takes two arguments (path and permissions)
    #define MKDIR(dir) mkdir(dir, 0755)
#endif

typedef struct File File;
typedef struct Folder Folder;

error allocateFile(File** file);
error allocateFolder(Folder** folder);

error createFile(File* file, const string filename, const string dir, const string fileType);
error createFileWithPath(File* file, const Path filename, const Path dirPath, const Path fileType);
error createFolder(Folder* folder, const string folderName, const string dir);
error createFolderWithPath(Folder* folder, const Path folderName, const Path dirPath);

error MakeFile(const File* filedata);
error MakeFileByPath(const string filepath);
error MakeFolder(const Folder* folder);
error MakeFolderByPath(const string folderPath);

code FileExist(const string filePath);
code FolderExist(const string folderPath);

error readFileToTextLinesString(textline** head, const string filepath);
error readFileToTextLinesPath(textline** head, const Path filepath);

void FreeTextLine(textline* head);
void FreeFileContent(File* file);
void FreeFile(File* file);
void FreeFolderContent(Folder* folder);
void FreeFolder(Folder* folder);

typedef struct File {
    Path filename; // file name
    Path dirPath; // file path
    Path fileType; // file type
} File;

typedef struct Folder {
    Path folderName; // folder name
    Path dirPath; // folder path
} Folder;

#endif // FILE_H