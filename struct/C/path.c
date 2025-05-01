#include "../path.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

void initPath(Path* pathTC) {
    pathTC->path = NULL;
    pathTC->length = 0;
}

error allocatePath(Path** pathTC) {
    if (pathTC == NULL) return "Path pointer is NULL";

    *pathTC = (Path*)malloc(sizeof(Path)); 
    if (*pathTC == NULL) return "Memory allocation failed";

    initPath(*pathTC);

    return NULL;
}

error createPath(Path* pathTC,const string path) {
    if (pathTC == NULL) return "Path To Create required";

    if (pathTC->path != NULL) return "Path is already created";

    uint32 length = stringLen(path);
    if (length == 0) return "Path required";

    error err = allocateStringLen(&pathTC->path, path, length);
    if (err != NULL) return err;

    pathTC->length = length;

    return NULL;
}

error createPathLen(Path* pathTC, const string path, const uint32 length) {
    if (pathTC == NULL) return "Path To Create required";

    if (pathTC->path != NULL) return "Path is already created";

    if (length == 0 || path == NULL) return "Path length is required";

    error err = allocateStringLen(&pathTC->path, path, length);
    if (err != NULL) return err;

    pathTC->length = length;
    
    return NULL;
}

error mergeTwoPaths(Path* pathTC,const Path path1, const Path path2) {
    if (pathTC == NULL) return "Path To create Pointer required";

    error err = mergeTwoStringsLen(&pathTC->path, path1.path, path2.path, path1.length + path2.length);
    if (err != NULL) return err;

    pathTC->length = path1.length + path2.length;
    
    return NULL;
}

error mergeThreePaths(Path* pathTC, const Path path1, const Path path2, const Path path3) {
    if (pathTC == NULL) return "Path To create Pointer required";
    
    error err = mergeThreeStringsLen(&pathTC->path, path1.path, path2.path, path3.path, path1.length + path2.length + path3.length);
    if (err != NULL) return err;

    pathTC->length = path1.length + path2.length + path3.length;
    
    return NULL;
}

error createFilePath(Path* filepath, const Path filename, const Path dirPath, const Path fileType) {
    if (filepath == NULL) return "File path not located yet";

    if (filename.path == NULL || dirPath.path == NULL || fileType.path == NULL) return "Filename, directory path, and file type are required";
    
    error err = mergeThreePaths(filepath, filename, dirPath, fileType);
    if (err != NULL) return err;
    
    return NULL;
}

error createPathFileorFolder(Path* filepath, const Path filename, const Path dirPath) {
    if (filepath == NULL) return "File path not located yet";

    if (filename.path == NULL || dirPath.path == NULL) return "Filename and directory path are required";
    
    error err = mergeTwoPaths(filepath, dirPath, filename);

    if (err != NULL) return err;
    
    return NULL;
}

error createDirPath(Path* folderPath, const Path folderName, const Path dirPath) {
    if (folderPath == NULL) return "Folder path not located yet";

    if (folderName.path == NULL || dirPath.path == NULL) return "Folder name and directory path are required";

    error err = mergeThreeStringsLen(&folderPath->path, dirPath.path, folderName.path,"/", dirPath.length + folderName.length + 1);
    if (err != NULL) return err;

    folderPath->length = dirPath.length + folderName.length + 1;
    
    return NULL;
}

error createFolderPath(Path* folderPath, const string folderName, const Path dirPath) {
    if (folderPath == NULL) return "Folder path not located yet";

    if (folderName == NULL || dirPath.path == NULL) return "Folder name and directory path are required";

    error err = NULL;Path tempPath;
    initPath(&tempPath);
    
    err = createPath(&tempPath, folderName);
    if (err != NULL) return err;

    err = createDirPath(folderPath, tempPath, dirPath);
    if (err != NULL) return err;

    FreePathContent(&tempPath);

    return NULL;
}

error createFolderPathLen(Path* folderPath, const string folderName, const Path dirPath, const uint32 length) {

    if (folderPath == NULL) return "Folder path not located yet";

    if (folderName == NULL || dirPath.path == NULL) return "Folder name and directory path are required";

    error err = NULL; Path tempPath;
    initPath(&tempPath);
    
    err = createPathLen(&tempPath, folderName, length);
    if (err != NULL) return err;

    err = createDirPath(folderPath, tempPath, dirPath);
    if (err != NULL) return err;

    FreePathContent(&tempPath);
    
    return NULL;
}

void initDataPath(DataPath* dataPath) {
    dataPath->path.path = NULL;
    dataPath->path.length = 0;
    dataPath->filename.path = NULL;
    dataPath->filename.length = 0;
    dataPath->parent = NULL;
    dataPath->Dir = NULL;
    dataPath->sizeDir = 0;
    dataPath->isFolder = 0; // Default to file
}

error allocateDataPath(DataPath** dataPath) {
    if (dataPath == NULL) return "DataPath pointer is NULL";

    *dataPath = (DataPath*)malloc(sizeof(DataPath));
    if (*dataPath == NULL) return "Memory allocation failed for DataPath";

    initDataPath(*dataPath);

    return NULL;
}

/**
 * Create a new DataPath node with given path and filename.
 */
error createDataPath(DataPath* dataPath, const Path path, const Path filename, const code isFolder) {
    error err = NULL;
    
    if (dataPath == NULL) {
        return "data path pointer is NULL";
    }
    
    initDataPath(dataPath);
    
    err = createPathLen(&(dataPath->path), path.path, path.length);
    if (err != NULL) return err;
    
    // Copy filename
    err = createPathLen(&(dataPath->filename), filename.path, filename.length);
    if (err != NULL) {
        FreePathContent(&(dataPath->path));
        return err;
    }

    dataPath->isFolder = isFolder; // Set folder or file flag
    
    return NULL;
}

/**
 * Add a child directory to a parent DataPath.
 */
error addChildDataPath(DataPath* parent, DataPath* child) {
    if (parent == NULL || child == NULL) return "Parent or child pointer is NULL";
    
    DataPath** newDir = NULL;
    newDir = (DataPath**)realloc(parent->Dir, (parent->sizeDir + 1) * sizeof(DataPath*));
    if (newDir == NULL) return "Memory allocation failed for new directory array";
    
    parent->Dir = newDir;
    parent->Dir[parent->sizeDir] = child;
    parent->sizeDir++;
    
    // Set parent reference
    child->parent = parent;
    
    return NULL;
}

/**
 * Find a child DataPath by filename in a parent's directory.
 */
error findDataPathByFilename(const DataPath* parent, const Path filename, DataPath** result) {
    if (parent == NULL || result == NULL) return "Parent or result pointer is NULL";
    
    uint16 i;
    *result = NULL;
    
    for (i = 0; i < parent->sizeDir; i++) {
        if (parent->Dir[i] != NULL) {
            if (stringCmp(parent->Dir[i]->filename.path, filename.path) == 0) {
                *result = parent->Dir[i];
                return NULL;
            }
        }
    }
    
    return "Not Found"; // Not found
}

error removeChildDataPath(DataPath* parent, const Path filename) {    
    if (parent == NULL) return "Parent pointer is NULL";
    
    uint16 i, found = 0;

    for (i = 0; i < parent->sizeDir; i++) {
        if (found) {
            parent->Dir[i-1] = parent->Dir[i];
        } else if (parent->Dir[i] != NULL) {
            if (stringCmp(parent->Dir[i]->filename.path, filename.path) == 0) {
                // Free the found child
                FreeDataPath(parent->Dir[i]);
                found = 1;
            }
        }
    }
    
    if (found) {
        if (parent->sizeDir > 1) {
            DataPath** newDir = (DataPath**)realloc(parent->Dir, (parent->sizeDir - 1) * sizeof(DataPath*));
            if (newDir == NULL) {
                parent->Dir[parent->sizeDir - 1] = NULL;
            } else {
                parent->Dir = newDir;
            }
        } else {
            // Last element removed
            free(parent->Dir);
            parent->Dir = NULL;
        }
        parent->sizeDir--;
        return NULL;
    }
    
    return "Not Found"; // Not found
}

/**
 * Print the entire DataPath tree structure in a clean, ASCII-only format.
 * @param dataPath The root DataPath to print
 */
void PrintDataPath(DataPath* dataPath) {
    if (dataPath == NULL) {
        printf("(empty)\n");
        return;
    }
    
    if (dataPath->filename.path == NULL) {
        printf("(unnamed)\n");
        return;
    }
    
    // Print the root node
    printf("%s/\n", dataPath->filename.path);
    
    // Print all children with proper formatting
    for (uint16 i = 0; i < dataPath->sizeDir; i++) {
        DataPath* child = dataPath->Dir[i];
        if (child != NULL) {
            // Is this the last child?
            uint8 isLast = (i == dataPath->sizeDir - 1);
            
            // Print this child and its subtree
            if (isLast) {
                printf("+-- %s/", child->filename.path);
            } else {
                printf("|-- %s/", child->filename.path);
            }
            
            // Add comments for special folders
            if (stringCmp(child->filename.path, "Notification")) {
                printf("\t\t# Notifications folder");
            } else if (stringCmp(child->filename.path, "Calendar")) {
                printf("\t\t# Calendar events");
            } else if (stringCmp(child->filename.path, "LEB2")) {
                printf("\t\t# LEB2 module");
            }
            
            printf("\n");
            
            // Print children with proper indentation
            PrintDataPathChildren(child, isLast, 1);
        }
    }
}

/**
 * Helper function to print the children of a DataPath node with proper indentation.
 * @param dataPath The DataPath node whose children to print
 * @param parentIsLast Whether the parent is the last node in its level
 * @param level The current tree depth level (for indentation)
 */
void PrintDataPathChildren(DataPath* dataPath, uint8 parentIsLast, uint16 level) {
    if (dataPath == NULL || dataPath->sizeDir == 0 || dataPath->Dir == NULL) {
        return;
    }
    
    char indentation[256] = {0}; // Buffer for indentation
    uint16 indentPos = 0;
    uint16 i, j;
    
    // Build the indentation string
    for (i = 0; i < level; i++) {
        if (i == level - 1) {
            // Last level depends on whether this is the last child
            if (parentIsLast) {
                indentation[indentPos++] = ' ';
                indentation[indentPos++] = ' ';
                indentation[indentPos++] = ' ';
            } else {
                indentation[indentPos++] = '|';
                indentation[indentPos++] = ' ';
                indentation[indentPos++] = ' ';
            }
        } else {
            // Previous levels get either space or pipe
            indentation[indentPos++] = ' ';
            indentation[indentPos++] = ' ';
            indentation[indentPos++] = ' ';
        }
    }
    indentation[indentPos] = '\0';
    
    // Print each child with proper prefix
    for (j = 0; j < dataPath->sizeDir; j++) {
        DataPath* child = dataPath->Dir[j];
        if (child != NULL && child->filename.path != NULL) {
            uint8 isLast = (j == dataPath->sizeDir - 1);
            
            // Print this child
            if (isLast) {
                printf("%s+-- %s/", indentation, child->filename.path);
            } else {
                printf("%s|-- %s/", indentation, child->filename.path);
            }
            
            // Add comments for special folders
            if (stringCmp(child->filename.path, "Notification") == 0) {
                printf("\t\t# Notifications folder");
            } else if (stringCmp(child->filename.path, "Calendar") == 0) {
                printf("\t\t# Calendar events");
            } else if (stringCmp(child->filename.path, "LEB2") == 0) {
                printf("\t\t# LEB2 module");
            }
            
            printf("\n");
            
            // Recursively print this child's children
            PrintDataPathChildren(child, isLast, level + 1);
        }
    }
}

void FreeDataPath(DataPath* dataPath) {
    if (dataPath == NULL) return;
    
    FreeDataPathContent(dataPath);
    free(dataPath);
}

void FreeDataPathContent(DataPath* dataPath) {
    uint16 i;
    
    if (dataPath == NULL) return;
    
    // Free path and filename
    FreePathContent(&(dataPath->path));
    FreePathContent(&(dataPath->filename));
    
    // Free all child directories recursively
    if (dataPath->Dir != NULL) {
        for (i = 0; i < dataPath->sizeDir; i++) {
            if (dataPath->Dir[i] != NULL) {
                FreeDataPath(dataPath->Dir[i]);
                dataPath->Dir[i] = NULL;
            }
        }
        free(dataPath->Dir);
        dataPath->Dir = NULL;
    }
    
    dataPath->sizeDir = 0;
    dataPath->parent = NULL;  // Just nullify the pointer, don't free it
}

void traverseDataPath(DataPath* dataPath, DataPathAction action, void* userData) {
    uint16 i;
    
    if (dataPath == NULL || action == NULL) return;
    
    action(dataPath, userData);
    
    for (i = 0; i < dataPath->sizeDir; i++) {
        if (dataPath->Dir[i] != NULL) {
            traverseDataPath(dataPath->Dir[i], action, userData);
        }
    }
}

void FreePathContent(Path* path) {
    if (path == NULL) return;
    if (path->path != NULL) {
        FreeString(&path->path);
        path->path = NULL;
    }
    path->length = 0;
}

void FreePath(Path* path) {
    if (path == NULL) return;
    FreePathContent(path);
    free(path);
}

error getCurrentPath(Path* pathObj) {
    if (pathObj == NULL) {
        return "Path pointer is NULL";
    }
    initPath(pathObj);
    size_t bufferSize = 256;
    string buffer = NULL;
    
    while (1) {
        buffer = (string)malloc(bufferSize);
        if (buffer == NULL) return "Memory allocation failed";
        
        #ifdef _WIN32
            if (_getcwd(buffer, bufferSize) != NULL) break;
        #else
            if (getcwd(buffer, bufferSize) != NULL) break;
        #endif
        
        free(buffer);
        
        if (errno != ERANGE) return "Failed to get current directory";
        
        bufferSize *= 2;
        if (bufferSize > 65536) return "Path is unreasonably long";
    }
    uint32 length = stringLen(buffer);
    if (length == 0) {
        free(buffer);
        return "Path is empty";
    }
    Path bufferPath;
    initPath(&bufferPath);
    error err = createPathLen(&bufferPath, buffer, length);
    if (err != NULL) {
        free(buffer);
        FreePathContent(&bufferPath);
        return err;
    }

    Path tempPath;
    initPath(&tempPath);
    err = createPathLen(&tempPath, "/",1);
    if (err != NULL) {
        free(buffer);
        FreePathContent(&tempPath);
        FreePathContent(&bufferPath);
        return err;
    }

    err = mergeTwoPaths(pathObj, bufferPath, tempPath);
    if (err != NULL) {
        free(buffer);
        FreePathContent(&tempPath);
        FreePathContent(&bufferPath);
        return err;
    }

    free(buffer);
    FreePathContent(&tempPath);
    FreePathContent(&bufferPath);
    
    return NULL;
}