#include "../path.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

error createPath(Path* pathTC,const string path) {
    if (pathTC == NULL) {
        return "Path To Create required"; // Invalid path pointer
    }
    if (pathTC->path != NULL) {
        return "Path is already created"; // Path is already allocated
    }

    uint32 length = stringLen(path);
    if (length == 0) {
        return "Path required";
    }
    error err = NULL;
    err = allocateStringLen(&pathTC->path, path, length); // Allocate memory for path
    if (err != NULL) {
        return err; // Memory allocation failed
    }
    pathTC->length = length;

    return NULL;
}

error createPathLen(Path* pathTC, const string path, const uint32 length) {
    if (pathTC == NULL) {
        return "Path To Create required"; // Invalid path pointer
    }
    if (pathTC->path != NULL) {
        return "Path is already created"; // Path is already allocated
    }
    if (length == 0 || path == NULL) {
        return "Path length is required";
    }
    error err = NULL;
    err = allocateStringLen(&pathTC->path, path, length); // Allocate memory for path
    if (err != NULL) {
        return err; // Memory allocation failed
    }
    pathTC->length = length;
    
    return NULL; // Success
}

error mergeTwoPaths(Path* pathTC,const Path path1, const Path path2) {
    if (pathTC == NULL) {
        return "Path To create Pointer required";
    }
    error err = NULL;
    err = mergeTwoStringsLen(&pathTC->path, path1.path, path2.path, path1.length + path2.length);
    if (err != NULL) {
        return err; // Memory allocation failed
    }
    pathTC->length = path1.length + path2.length;
    
    return NULL; // Success
}

error mergeThreePaths(Path* pathTC, const Path path1, const Path path2, const Path path3) {
    if (pathTC == NULL) {
        return "Path To create Pointer required";
    }
    error err = NULL;
    err = mergeThreeStringsLen(&pathTC->path, path1.path, path2.path, path3.path, path1.length + path2.length + path3.length);
    if (err != NULL) {
        return err; // Memory allocation failed
    }
    pathTC->length = path1.length + path2.length + path3.length;
    
    return NULL; // Success
}

error createFilePath(Path* filepath, const Path filename, const Path dirPath, const Path fileType) {
    if (filepath == NULL) {
        return "File path not located yet"; // Invalid file path
    }
    //required it all
    if (filename.path == NULL || dirPath.path == NULL || fileType.path == NULL) {
        return "Filename, directory path, and file type are required"; // Invalid parameters
    }
    
    error err = NULL;
    err = mergeThreePaths(filepath, filename, dirPath, fileType);
    if (err != NULL) {
        return err; // Memory allocation failed
    }
    filepath->length = dirPath.length + filename.length + fileType.length;
    
    return NULL; // Success
}

error createDirPath(Path* folderPath, const Path folderName, const Path dirPath) {
    if (folderPath == NULL) {
        return "Folder path not located yet"; // Invalid folder path
    }
    if (folderName.path == NULL || dirPath.path == NULL) {
        return "Folder name and directory path are required"; // Invalid parameters
    }
    error err = NULL;
    err = mergeThreeStringsLen(&folderPath->path, dirPath.path, folderName.path,"/", dirPath.length + folderName.length + 1);
    if (err != NULL) {
        return err; // Memory allocation failed
    }
    folderPath->length = dirPath.length + folderName.length + 1; // +1 for the '/' character
    
    return NULL; // Success
}

void FreePathContent(Path* path) {
    if (path == NULL) {
        return; // Invalid path pointer
    }
    if (path->path != NULL) {
        FreeString(&path->path); // Free path string
        path->path = NULL; // Reset path string
    }
    path->length = 0; // Reset length
}

void FreePath(Path* path) {
    if (path == NULL) {
        return; // Invalid path pointer
    }

    FreePathContent(path); // Free path content
    free(path); // Free path structure
}
