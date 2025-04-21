#include "../path.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32 countTotalLength(const Path** paths, const uint8 count) {
    if (count == 0 || paths == NULL) {
        Warning("Path is required");
        return 0; // Invalid paths
    }
    
    uint32 totalLength = 0;
    for (uint8 i = 0; i < count; i++) {
        if (paths[i] != NULL) {
            totalLength += paths[i]->length;
        }
    }
    
    return totalLength; // Success
}

Path* createFilePath(const string filename, const Path* dirPath, const string fileType) {
    uint32 filenameLength = stringLen(filename);
    if( filenameLength == 0) {
        Warning("Filename is required");
        return NULL; // Invalid filename
    }
    uint32 filetypeLength = stringLen(fileType);
    if( filetypeLength == 0) {
        Warning("File type is required");
        return NULL; // Invalid file type
    }
    if (dirPath == NULL || dirPath->path == NULL) {
        // Check if dirPath is NULL or empty
        Warning("Directory path is required");
        return NULL; // Invalid directory path
    }
    
    Path* filePath = initPath();
    if (filePath == NULL) {
        return NULL; // Memory allocation failed
    }
    
    filePath->path = mergeThreeStringsLen(dirPath->path, filename, fileType, dirPath->length + filenameLength + filetypeLength + 1);
    if (filePath->path == NULL) {
        Error("Failed to create file path string");
        FreePath(filePath);
        return NULL; // Memory allocation failed
    }
    filePath->length = dirPath->length + filenameLength + filetypeLength;
    
    return filePath; // Success
}

Path* createDirPath(const string folderName, const Path* dirPath) {
    uint32 folderNameLength = stringLen(folderName);
    if (folderNameLength == 0) {
        Warning("Folder name is required");
        return NULL; // Invalid folder name
    }
    if (dirPath == NULL || dirPath->path == NULL) {
        // Check if dirPath is NULL or empty
        Warning("Directory path is required");
        return NULL; // Invalid directory path
    }
    
    Path* folderPath = initPath();
    if (folderPath == NULL) {
        return NULL; // Memory allocation failed
    }
    
    folderPath->path = mergeThreeStringsLen(dirPath->path, folderName,"/", dirPath->length + folderNameLength + 1 + 1);
    if (folderPath->path == NULL) {
        Error("Failed to create folder path string");
        FreePath(folderPath);
        return NULL; // Memory allocation failed
    }
    folderPath->length = dirPath->length + folderNameLength + 1; // +1 for the '/' character
    
    return folderPath; // Success
}

Path* initPath() {
    Path* path = (Path*)malloc(sizeof(Path));
    if (path == NULL) {
        Error("Memory allocation failed for Path");
        return NULL; // Memory allocation failed
    }
    path->path = NULL;
    path->length = 0;
    
    return path; // Success
}

Path* createPath(const string path) {
    uint16 length = stringLen(path);
    if (length == 0) {
        Warning("Path is required");
        return NULL; // Invalid path
    }
    
    Path* newPath = initPath();
    if (newPath == NULL) {
        return NULL; // Memory allocation failed
    }
    
    newPath->path = copyString(path, length);
    if (newPath->path == NULL) {
        Error("Failed to copy path string");
        FreePath(newPath);
        return NULL; // Memory allocation failed
    }
    newPath->length = length;
    
    return newPath; // Success
}

Path* createPathLen(const string path, const uint32 length) {
    if (length == 0 || path == NULL) {
        Warning("Path length is required");
        return NULL; // Invalid length
    }
    
    Path* newPath = initPath();
    if (newPath == NULL) {
        return NULL; // Memory allocation failed
    }
    
    newPath->path = copyString(path, length);
    if (newPath->path == NULL) {
        Error("Failed to copy path string");
        FreePath(newPath);
        return NULL; // Memory allocation failed
    }
    newPath->length = length;
    
    return newPath; // Success
}

Path* mergeTwoPaths(const Path* path1, const Path* path2) {
    if (path1 == NULL || path2 == NULL) {
        Warning("Path is required");
        return NULL; // Invalid paths
    }
    
    string mergedPath = mergeTwoStringsLen(path1->path, path2->path, path1->length + path2->length);
    if (mergedPath == NULL) {
        Error("Failed to merge paths");
        return NULL; // Memory allocation failed
    }
    Path* newPath = createPathLen(mergedPath, path1->length + path2->length);
    if (newPath == NULL) {
        Error("Failed to create merged path");
        FreePath(mergedPath);
        return NULL; // Memory allocation failed
    }
    return newPath; // Success
}

Path* mergeThreePaths(const Path* path1, const Path* path2, const Path* path3) {
    if (path1 == NULL || path2 == NULL || path3 == NULL) {
        Warning("Path is required");
        return NULL; // Invalid paths
    }
    
    string mergedPath = mergeThreeStringsLen(path1->path, path2->path, path3->path, path1->length + path2->length + path3->length);
    if (mergedPath == NULL) {
        Error("Failed to merge paths");
        return NULL; // Memory allocation failed
    }
    Path* newPath = createPathLen(mergedPath, path1->length + path2->length + path3->length);
    if (newPath == NULL) {
        Error("Failed to create merged path");
        FreePath(mergedPath);
        return NULL; // Memory allocation failed
    }
    return newPath; // Success
}

Path* mergePaths(const Path** paths, const uint8 count) {
    if (count == 0 || paths == NULL) {
        Warning("Path is required");
        return NULL; // Invalid paths
    }
    
    uint32 totalLength = countTotalLength(paths, count);
    if (totalLength == 0) {
        Warning("Total length is zero");
        return NULL; // Invalid paths
    }
    
    string mergedPath = mergeStringsLen(paths, count, totalLength);
    if (mergedPath == NULL) {
        Error("Failed to merge paths");
        return NULL; // Memory allocation failed
    }
    
    Path* newPath = createPathLen(mergedPath, totalLength);
    if (newPath == NULL) {
        Error("Failed to create merged path");
        FreePath(mergedPath);
        return NULL; // Memory allocation failed
    }
    
    return newPath; // Success
}

void FreePath(Path* path) {
    if (path != NULL) {
        if (path->path != NULL) {
            free(path->path);
        }
        free(path);
    }
}