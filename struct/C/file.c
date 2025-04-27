#include "../file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

error allocateFile(File** file) {
    if (file != NULL) {
        return NULL; // Invalid file pointer
    }
    
    *file = (File*)malloc(sizeof(File));
    if (file == NULL) {
        return "Memory allocation failed"; // Memory allocation failed
    }
    (*file)->filename.path = NULL; // Initialize filename
    (*file)->filename.length = 0; // Initialize filename length
    (*file)->dirPath.path = NULL; // Initialize dirPath
    (*file)->dirPath.length = 0; // Initialize dirPath length
    (*file)->fileType.path = NULL; // Initialize fileType
    (*file)->fileType.length = 0; // Initialize fileType length
    
    return NULL; // Success
}

error allocateFolder(Folder** folder) {
    if (folder != NULL) {
        return NULL; // Invalid folder pointer
    }
    
    (*folder) = (Folder*)malloc(sizeof(Folder));
    if ((*folder) == NULL) {
        return "Memory allocation failed"; // Memory allocation failed
    }
    (*folder)->folderName.path = NULL; // Initialize folder name
    (*folder)->folderName.length = 0; // Initialize folder name length
    (*folder)->dirPath.path = NULL; // Initialize dirPath
    (*folder)->dirPath.length = 0; // Initialize dirPath length
    
    return NULL; // Success
}

error createFile(File* file, const string filename, const string dir, const string fileType) {
    if (file == NULL) {
        return "File is required"; // Invalid file pointer
    }
    if (filename == NULL || dir == NULL || fileType == NULL) {
        return "Filename, directory, and file type are required"; // Invalid parameters
    }
    string err;
    
    err = createPath(&file->filename, filename);
    if (err != NULL) {
        FreeFile(file);
        return err; // Memory allocation failed
    }
    err = createPath(&file->dirPath, dir); // Copy dirPath
    if (err != NULL) {
        FreeFile(file);
        return err; // Memory allocation failed
    }
    err = createPath(&file->fileType, fileType); // Copy fileType
    if (err != NULL) {
        FreeFile(file);
        return err; // Memory allocation failed
    }
    
    return NULL; // Success
}

error createFileWithPath(File* file, const Path filename, const Path dirPath, const Path fileType) {
    if (file == NULL) {
        return "File is required"; // Invalid file pointer
    }
    if (filename.path == NULL || dirPath.path == NULL || fileType.path == NULL) {
        return "Filename, directory path, and file type are required"; // Invalid parameters
    }
    
    file->filename = filename;
    file->dirPath = dirPath; // Copy dirPath
    file->fileType = fileType;
    
    return NULL; // Success
}

error createFolder(Folder* folder, const string folderName, const string dir) {
    if (folder == NULL) {
        return "Folder is required"; // Invalid folder pointer
    }
    if (folderName == NULL || dir == NULL) {
        return "Folder name and directory are required"; // Invalid parameters
    }
    
    error err;
    
    err = createPath(&folder->folderName, folderName); // Copy folder name
    if (err != NULL) {
        FreeFolder(folder);
        return err; // Memory allocation failed
    }
    
    err = createPath(&folder->dirPath, dir); // Copy dirPath
    if (err != NULL) {
        FreeFolder(folder);
        return err; // Memory allocation failed
    }
    
    return NULL; // Success
}

error createFolderWithPath(Folder* folder, const Path folderName, const Path dirPath) {
    if (folder == NULL) {
        return "Folder is required"; // Invalid folder pointer
    }
    if (folderName.path == NULL || dirPath.path == NULL) {
        return "Folder name and directory path are required"; // Invalid parameters
    }
    
    folder->folderName = folderName; // Copy folder name
    folder->dirPath = dirPath; // Copy dirPath
    
    return NULL; // Success
}

error MakeFile(const File* filedata) {
    if (filedata == NULL) {
        return "file required"; // Invalid file pointer
    }
    Path filepath;
    error err = createFilePath(&filepath, filedata->filename, filedata->dirPath, filedata->fileType);
    if (err != NULL) {
        return err; // Memory allocation failed
    }
    return MakeFileByPath(filepath.path);
}

error MakeFileByPath(const string filepath) {
    if (filepath == NULL) {
        return "File path is required"; // Invalid file path
    }

    if (FileExist(filepath)) {
        return "File already exists"; // File already exists
    }
    
    FILE* file = fopen(filepath, "w");
    if (file == NULL) {
        fclose(file);
        return "Failed Make File"; // File does not exist
    }
    
    fclose(file);
    return NULL; // File exists
}

error MakeFolder(const Folder* folder) {
    if (folder == NULL) {
        return "Folder is required"; // Invalid folder pointer
    }
    
    Path folderPath;
    error err = createDirPath(&folderPath, folder->folderName, folder->dirPath);
    if (err != NULL) {
        return err; // Memory allocation failed
    }
    return MakeFolderByPath(folderPath.path);
}

error MakeFolderByPath(const string folderPath) {
    if (folderPath == NULL) {
        return "Folder path is required"; // Invalid folder path
    }

    if (FolderExist(folderPath)) {
        return "Folder already exists"; // Folder already exists
    }
    
    if (mkdir(folderPath) == -1) {
        return "Failed to create folder"; // Folder creation failed
    }
    
    return NULL; // Folder created successfully
}

code FileExist(const string filePath) {
    if (filePath == NULL) {
        Error("filepath is NULL");
        return 0; // Invalid file path
    }

    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        return 0;
    }
    return 1;
}

code FolderExist(const string folderPath) {
    if (folderPath == NULL) {
        Error("folderPath is NULL");
        return 0; // Invalid folder path
    }

    DIR* dir = opendir(folderPath);
    if (dir == NULL) {
        return 0; // Folder does not exist
    }

    closedir(dir);
    return 1; // Folder exists
}

void FreeFileContent(File* file) {
    if (file == NULL) return;

    if (file->filename.path != NULL) {
        FreeString(&file->filename.path); // Free filename string
    }
    if (file->dirPath.path != NULL) {
        FreeString(&file->dirPath.path); // Free dirPath string
    }
    if (file->fileType.path != NULL) {
        FreeString(&file->fileType.path); // Free fileType string
    }
}

void FreeFile(File* file) {
    if (file == NULL) return; // Invalid file pointer

    FreeFileContent(file); // Free file content
    free(file); // Free file structure
}

void FreeFolderContent(Folder* folder) {
    if (folder == NULL) return; // Invalid folder pointer

    if (folder->folderName.path != NULL) {
        FreeString(&folder->folderName.path); // Free folder name string
    }
    if (folder->dirPath.path != NULL) {
        FreeString(&folder->dirPath.path); // Free dirPath string
    }
}

void FreeFolder(Folder* folder) {
    if (folder == NULL) return; // Invalid folder pointer
    
    FreeFolderContent(folder); // Free folder content
    free(folder); // Free folder structure
}