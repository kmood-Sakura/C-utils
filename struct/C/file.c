#include "../file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

File* initFile() {
    File* file = (File*)malloc(sizeof(File));
    if (file == NULL) {
        Error("Memory allocation failed for File");
        return NULL; // Memory allocation failed
    }
    file->filename = NULL;
    file->dirPath = *initPath(); // Initialize dirPath
    file->fileType = NULL;
    
    return file; // Success
}

File* createFile(const string filename, const string dir, const string fileType) {
    if (filename == NULL || dir == NULL || fileType == NULL) {
        Warning("Filename, directory, and file type are required");
        return NULL; // Invalid parameters
    }
    
    File* newFile = initFile();
    if (newFile == NULL) {
        return NULL; // Memory allocation failed
    }
    
    newFile->filename = createString(filename);
    if (newFile->filename == NULL) {
        Error("Failed to copy filename string");
        FreeFile(newFile);
        return NULL; // Memory allocation failed
    }
    
    newFile->dirPath = *createPath(dir); // Copy dirPath
    if (newFile->dirPath.path == NULL) {
        Error("Failed to copy directory path string");
        FreeFile(newFile);
        return NULL; // Memory allocation failed
    }
    
    newFile->fileType = createString(fileType);
    if (newFile->fileType == NULL) {
        Error("Failed to copy file type string");
        FreeFile(newFile);
        return NULL; // Memory allocation failed
    }
    
    return newFile; // Success
}

File* createFilePath(const string filename, const Path* dirPath, const string fileType) {
    if (filename == NULL || dirPath == NULL || fileType == NULL) {
        Warning("Filename, directory path, and file type are required");
        return NULL; // Invalid parameters
    }
    
    File* newFile = initFile();
    if (newFile == NULL) {
        return NULL; // Memory allocation failed
    }
    
    newFile->filename = createString(filename);
    if (newFile->filename == NULL) {
        Error("Failed to copy filename string");
        FreeFile(newFile);
        return NULL; // Memory allocation failed
    }
    
    newFile->dirPath = *createPath(dirPath); // Copy dirPath
    if (newFile->dirPath.path == NULL) {
        Error("Failed to copy directory path string");
        FreeFile(newFile);
        return NULL; // Memory allocation failed
    }
    
    newFile->fileType = createString(fileType);
    if (newFile->fileType == NULL) {
        Error("Failed to copy file type string");
        FreeFile(newFile);
        return NULL; // Memory allocation failed
    }
    
    return newFile; // Success
}

Status* makeFile(const File* file) {
    if (file == NULL) {
        Warning("File is required");
        return createStatus(-1, "File is required", NULL); // Invalid file
    }
    Path* filePath = createFilePath(file->filename, &file->dirPath, file->fileType);
    if (filePath == NULL) {
        Warning("Failed to create file path");
        return createStatus(0, "Failed to create file path", NULL); // Failed to create file path
    }
    if(FilePathExist(filePath) == 1) {
        return createStatus(0, "File have already exist", NULL); // File does not exist
    }
    FILE* file = fopen(filePath->path, "w"); // Open file in write mode
    if (file == NULL) {
        FreePath(filePath); // Free file path
        return createStatus(0, "Failed to create file", NULL); // Failed to create file
    }
    fclose(filePath->path); // Close file
    FreePath(filePath); // Free file path

    return createStatus(1, "File created successfully", NULL); // Success
}

Status* FilePathExist(const Path* filePath) {
    if (filePath == NULL || filePath->path == NULL) {
        Warning("File path is required");
        return createStatus(-1, "File path is required", NULL); // Invalid file path
    }
    
    FILE* file = fopen(filePath->path, "r"); // Open file in read mode
    if (file != NULL) {
        fclose(file); // Close file if it exists
        return createStatus(1, "File exists", NULL); // File exists
    }
    
    return createStatus(0, "File does not exist", NULL); // File does not exist
}

Status* FileExist(const File* file) {
    if (file == NULL) {
        Warning("File is required");
        return createStatus(-1, "File is required", NULL); // Invalid file
    }
    
    Path* filePath = createFilePath(file->filename, &file->dirPath, file->fileType);
    if (filePath == NULL) {
        Warning("Failed to create file path");
        return createStatus(0, "Failed to create file path", NULL); // Failed to create file path
    }
    
    FILE* f = fopen(filePath->path, "r"); // Open file in read mode
    if (f != NULL) {
        fclose(f); // Close file if it exists
        FreePath(filePath); // Free file path
        return createStatus(1, "File exists", NULL); // File exists
    }
    
    FreePath(filePath); // Free file path
    return createStatus(0, "File does not exist", NULL); // File does not exist
}


void FreeFile(File* file) {
    if (file != NULL) {
        if (file->filename != NULL) {
            free(file->filename);
        }
        if (file->dirPath.path != NULL) {
            free(file->dirPath.path);
        }
        if (file->fileType != NULL) {
            free(file->fileType);
        }
        free(file);
    }
}