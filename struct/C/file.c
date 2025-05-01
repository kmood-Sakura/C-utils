#include "../file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

/* Platform-specific includes */
#ifdef OS_WINDOWS
    #include <windows.h>
    #include <direct.h>
    #define mkdir(path, mode) _mkdir(path)
#else
    #include <dirent.h>
    #include <unistd.h>
    /* Default permission: read/write/execute for owner, read/execute for group and others */
    #define DEFAULT_MODE 0755
    #define mkdir(path) mkdir(path, DEFAULT_MODE)
#endif

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
        return NULL; // Folder already exists
    }
    
    #ifdef OS_WINDOWS
        if (_mkdir(folderPath) == -1) {
            return "Failed to create folder"; // Folder creation failed
        }
    #else
        if (mkdir(folderPath) == -1) {
            return "Failed to create folder"; // Folder creation failed
        }
    #endif
    
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
    fclose(file);
    return 1;
}

code FolderExist(const string folderPath) {
    if (folderPath == NULL) {
        Error("folderPath is NULL");
        return 0; // Invalid folder path
    }
    #ifdef OS_WINDOWS
        DWORD dwAttrib = GetFileAttributesA(folderPath);
        return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
            (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
    #else
        DIR* dir = opendir(folderPath);
        if (dir == NULL) {
            return 0; // Folder does not exist
        }
        closedir(dir);
        return 1; // Folder exists
    #endif
}

error readFileToTextLinesString(textline** head, const string filepath) {
    if (head == NULL) {
        return "Invalid head pointer";
    }
    
    if (filepath == NULL) {
        return "Invalid file path";
    }
    
    // Initialize head to NULL
    *head = NULL;
    
    // Open the file
    FILE* file = fopen(filepath, "r");
    if (file == NULL) {
        return "Failed to open file";
    }
    
    textline* lastLine = NULL;
    char buffer[1024];  // Buffer for reading lines
    
    // Read file line by line
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Create new textline node
        textline* newLine = (textline*)malloc(sizeof(textline));
        if (newLine == NULL) {
            fclose(file);
            FreeTextLine(*head); // Clean up already allocated lines
            
            return "Memory allocation failed";
        }
        
        // Remove newline character if present
        uint32 len = stringLen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }
        
        // Allocate and copy line content
        error err = allocateString(&newLine->line, buffer);
        if (err != NULL) {
            free(newLine);
            fclose(file);
            FreeTextLine(*head); // Clean up already allocated lines
            
            return err;
        }
        
        newLine->nextline = NULL;
        
        // Add to linked list
        if (*head == NULL) {
            *head = newLine;  // First node
        } else {
            lastLine->nextline = newLine;  // Add to end
        }
        
        lastLine = newLine;
    }
    
    fclose(file);
    
    // Check if file was empty
    if (*head == NULL) {
        return "File is empty";
    }
    
    return NULL;  // Success
}

error readFileToTextLinesPath(textline** head, const Path filepath) {
    if (head == NULL) {
        return "Invalid head pointer";
    }
    
    if (filepath.path == NULL) {
        return "Invalid file path";
    }
    
    // Initialize head to NULL
    *head = NULL;
    
    // Open the file
    FILE* file = fopen(filepath.path, "r");
    if (file == NULL) {
        return "Failed to open file";
    }
    
    textline* lastLine = NULL;
    char buffer[1024];  // Buffer for reading lines
    
    // Read file line by line
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Create new textline node
        textline* newLine = (textline*)malloc(sizeof(textline));
        if (newLine == NULL) {
            fclose(file);
            FreeTextLine(*head); // Clean up already allocated lines
            
            return "Memory allocation failed";
        }
        
        // Remove newline character if present
        uint32 len = stringLen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }
        
        // Allocate and copy line content
        error err = allocateString(&newLine->line, buffer);
        if (err != NULL) {
            free(newLine);
            fclose(file);
            FreeTextLine(*head); // Clean up already allocated lines
            
            return err;
        }
        
        newLine->nextline = NULL;
        
        // Add to linked list
        if (*head == NULL) {
            *head = newLine;  // First node
        } else {
            lastLine->nextline = newLine;  // Add to end
        }
        
        lastLine = newLine;
    }
    
    fclose(file);
    
    // Check if file was empty
    if (*head == NULL) {
        return "File is empty";
    }
    
    return NULL;  // Success
}

error writeTextLinesToFile(const textline* head, const string filepath) {
    if (head == NULL) {
        return "Invalid head pointer";
    }
    
    if (filepath == NULL) {
        return "Invalid file path";
    }
    
    // Open the file for writing
    FILE* file = fopen(filepath, "w");
    if (file == NULL) {
        return "Failed to open file for writing";
    }
    
    // Write each line to the file
    const textline* current = head;
    while (current != NULL) {
        fprintf(file, "%s\n", current->line);  // Write line content
        current = current->nextline;  // Move to next line
    }
    
    fclose(file);
    
    return NULL;  // Success
}

error addTextline(textline** head, const string line) {
    if (head == NULL) return "Invalid head pointer";
    
    if (line == NULL) return "Invalid line content";
    
    // Create new textline node
    textline* newLine = (textline*)malloc(sizeof(textline));
    if (newLine == NULL) return "Memory allocation failed";
    
    // Allocate and copy line content
    error err = allocateString(&newLine->line, line);
    if (err != NULL) {
        free(newLine);
        return err; // Memory allocation failed
    }
    
    newLine->nextline = NULL;
    
    // Add to linked list
    if (*head == NULL) {
        *head = newLine;  // First node
    } else {
        textline* current = *head;
        while (current->nextline != NULL) {
            current = current->nextline;  // Move to end of list
        }
        current->nextline = newLine;  // Add to end
    }
    
    return NULL;  // Success
}

void FreeTextLine(textline* head) {
    if (head == NULL) return;
    
    textline* current = head;
    while (current != NULL) {
        textline* next = current->nextline;
        FreeString(&current->line);
        free(current);
        current = next;
    }
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