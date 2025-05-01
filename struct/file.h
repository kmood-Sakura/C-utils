#ifndef FILE_H
#define FILE_H

#include "../datatype/int-type.h"
#include "../datatype/string-type.h"

#include "path.h"

/* Platform detection */
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    #define OS_WINDOWS
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__) || defined(__unix) || defined(__unix__)
    #define OS_UNIX_LIKE
#else
    #error "Unsupported platform"
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
error writeTextLinesToFile(const textline* head, const string filepath);

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