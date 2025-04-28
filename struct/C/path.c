#include "../path.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

error getCurrentPath(Path* pathObj) {
    if (pathObj == NULL) {
        return "Path pointer is NULL";
    }
    
    initPath(pathObj); // Initialize path object
    
    // Initial buffer size
    size_t bufferSize = 256;
    string buffer = NULL;
    
    // Try with increasingly larger buffers until we succeed
    while (1) {
        buffer = (string)malloc(bufferSize);
        if (buffer == NULL) {
            return "Memory allocation failed";
        }
        
        #ifdef _WIN32
        // For Windows
        if (_getcwd(buffer, bufferSize) != NULL) {
            break; // Success
        }
        #else
        // For POSIX systems (Linux, macOS)
        if (getcwd(buffer, bufferSize) != NULL) {
            break; // Success
        }
        #endif
        
        free(buffer);
        
        // If error is not because buffer is too small, return error
        if (errno != ERANGE) {
            return "Failed to get current directory";
        }
        
        // Double the buffer size and try again
        bufferSize *= 2;
        if (bufferSize > 65536) {
            return "Path is unreasonably long";
        }
    }
    uint32 length = stringLen(buffer);
    if (length == 0) {
        free(buffer);
        return "Path is empty";
    }
    // Create string for path
    Path bufferPath;
    initPath(&bufferPath); // Initialize buffer path
    error err = allocateStringLen(&bufferPath.path, buffer, length);
    if (err != NULL) {
        free(buffer);
        FreePathContent(&bufferPath); // Free buffer path content
        return err; // Memory allocation failed
    }
    bufferPath.length = length;

    Path tempPath;
    initPath(&tempPath); // Initialize temporary path
    err = createPathLen(&tempPath, "/",1);
    if (err != NULL) {
        free(buffer);
        FreePathContent(&tempPath); // Free temporary path content
        FreePathContent(&bufferPath); // Free buffer path content
        return err; // Memory allocation failed
    }

    err = mergeTwoPaths(pathObj, bufferPath, tempPath); // Merge paths
    if (err != NULL) {
        free(buffer);
        FreePathContent(&tempPath); // Free temporary path content
        FreePathContent(&bufferPath); // Free buffer path content
        return err; // Memory allocation failed
    }
    pathObj->length = bufferPath.length + tempPath.length; // Update length

    free(buffer);
    FreePathContent(&tempPath); // Free temporary path content
    FreePathContent(&bufferPath); // Free buffer path content
    
    return NULL; // Success
}

void initPath(Path* pathTC) {
    pathTC->path = NULL; // Initialize path to NULL
    pathTC->length = 0; // Initialize length to 0
}

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

error createFolderPath(Path* folderPath, const string folderName, const Path dirPath) {
    if (folderPath == NULL) {
        return "Folder path not located yet"; // Invalid folder path
    }
    if (folderName == NULL || dirPath.path == NULL) {
        return "Folder name and directory path are required"; // Invalid parameters
    }
    error err = NULL;
    Path tempPath;
    initPath(&tempPath); // Initialize temporary path
    
    err = createPath(&tempPath, folderName); // Copy folder name
    if (err != NULL) {
        return err; // Memory allocation failed
    }

    err = createDirPath(folderPath, tempPath, dirPath); // Create folder path
    if (err != NULL) {
        return err; // Memory allocation failed
    }
    FreePathContent(&tempPath); // Free temporary path content

    return NULL; // Success
}

error createFolderPathLen(Path* folderPath, const string folderName, const Path dirPath, const uint32 length) {
    if (folderPath == NULL) {
        return "Folder path not located yet"; // Invalid folder path
    }
    if (folderName == NULL || dirPath.path == NULL) {
        return "Folder name and directory path are required"; // Invalid parameters
    }
    error err = NULL;
    Path tempPath;
    initPath(&tempPath); // Initialize temporary path
    
    err = createPathLen(&tempPath, folderName, length); // Copy folder name
    if (err != NULL) {
        return err; // Memory allocation failed
    }

    err = createDirPath(folderPath, tempPath, dirPath); // Create folder path
    if (err != NULL) {
        return err; // Memory allocation failed
    }
    FreePathContent(&tempPath); // Free temporary path content
    
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
