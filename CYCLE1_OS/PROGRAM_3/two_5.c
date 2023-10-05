#include <stdio.h>
#include <string.h>

// Define a structure for a file
struct File {
    char name[50];
};

// Define a structure for a directory
struct Directory {
    char name[50];
    struct File files[50];
    int fileCount;
};

void inputFiles(struct Directory* directory) {
    printf("Enter file names for %s directory (type 'exit' to stop):\n", directory->name);
    char input[50];
    while (1) {
        printf("Enter file name: ");
        scanf("%s", input);

        if (strcmp(input, "exit") == 0 || directory->fileCount >= 50) {
            break; // Exit the loop if 'exit' is typed or directory is full
        }

        strcpy(directory->files[directory->fileCount++].name, input);
    }
}

// Function to display the contents of a directory
void displayDirectoryContents(struct Directory* directory) {
    printf("%s directory:\n", directory->name);
    for (int i = 0; i < directory->fileCount; i++) {
        printf("  File: %s\n", directory->files[i].name);
    }
}

int main() {
    struct Directory root = { "Root", {0}, 0 };
    
    // Ask the user to input files for the root directory
    inputFiles(&root);

    // Ask the user how many "SecondLevel" directories they want to create
    int numSecondLevelDirs;
    printf("Enter the number of 'SecondLevel' directories to create: ");
    scanf("%d", &numSecondLevelDirs);

    // Create "SecondLevel" directories at the root level
    for (int i = 1; i <= numSecondLevelDirs; i++) {
        struct Directory secondLevel = { "", {0}, 0 };
        sprintf(secondLevel.name, "SecondLevel%d", i);

        // Ask the user to input files for the "SecondLevel" directory
        inputFiles(&secondLevel);

        // Display the "SecondLevel" directory and its files
        displayDirectoryContents(&secondLevel);
    }

    // Display the contents of the root directory
    displayDirectoryContents(&root);

    return 0;
}

