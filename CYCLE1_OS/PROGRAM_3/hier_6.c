#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define a structure for a file
struct File {
    char name[50];
};

// Define a structure for a directory
struct Directory {
    char name[50];
    struct File files[50];
    int fileCount;
    struct Directory* subDirectories[50];
    int subDirectoryCount;
};

// Function to input files for a directory
void inputFiles(struct Directory* directory) {
    printf("Enter file names for %s directory (type 'exit' to stop):\n", directory->name);
    char input[50];
    while (1) {
        printf("Enter file name: ");
        scanf("%s", input);

        if (strcmp(input, "exit") == 0 || directory->fileCount >= 50) {
            break;
        }

        strcpy(directory->files[directory->fileCount++].name, input);
    }
}

// Function to create subdirectories
void createSubDirectories(struct Directory* directory) {
    printf("Enter the number of subdirectories for %s directory: ", directory->name);
    int numSubDirs;
    scanf("%d", &numSubDirs);

    for (int i = 0; i < numSubDirs; i++) {
        directory->subDirectories[directory->subDirectoryCount] = (struct Directory*)malloc(sizeof(struct Directory));
        sprintf(directory->subDirectories[directory->subDirectoryCount]->name, "Subdir%d", directory->subDirectoryCount + 1);

        inputFiles(directory->subDirectories[directory->subDirectoryCount]);
        createSubDirectories(directory->subDirectories[directory->subDirectoryCount++]);
    }
}

// Function to recursively display the directory structure
void displayDirectoryStructure(struct Directory* directory, int depth) {
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("%s directory:\n", directory->name);

    for (int i = 0; i < directory->fileCount; i++) {
        for (int j = 0; j < depth + 1; j++) {
            printf("  ");
        }
        printf("File: %s\n", directory->files[i].name);
    }

    for (int i = 0; i < directory->subDirectoryCount; i++) {
        displayDirectoryStructure(directory->subDirectories[i], depth + 1);
    }
}

int main() {
    struct Directory root = { "Root", {0}, 0, {0}, 0 };

    inputFiles(&root);
    createSubDirectories(&root);
    
    printf("Directory Structure:\n");
    displayDirectoryStructure(&root, 0);

    // Free dynamically allocated memory
    for (int i = 0; i < root.subDirectoryCount; i++) {
        free(root.subDirectories[i]);
    }

    return 0;
}

