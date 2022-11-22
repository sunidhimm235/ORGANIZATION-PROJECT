
// Header files included
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The supported commands
#define RESIZE 1
#define INSERT 2
#define PRINT  3
#define EXIT   4

// Typedefs for not using struct everywhere
typedef struct Zoo Zoo;
typedef struct Section Section;
typedef struct Cage Cage;

// The structs
struct Cage {
    char * name;
};
struct Section {
    Cage * array;
    int cageCount;
};
struct Zoo {
    Section * array;
    int sectionCount;
};

// The prototypes
void addAnimal(Zoo * myZoo, int section, int cage, char * name);
void resizeSection(Zoo * myZoo, int section, int newCageCount);
void printsAnimal(Zoo * myZoo, int section, int cage);

// The main function
int main() {
    // Read in the number of sections
    Zoo zoo;
    scanf("%d", &zoo.sectionCount);

    // Create the zoo
    zoo.array = (Section *) calloc(zoo.sectionCount, sizeof(Section));
    for (int i = 0; i < zoo.sectionCount; i++) {
        zoo.array[i].array = NULL;
        zoo.array[i].cageCount = 0;
    }
    
    // Handle all the commands until a 4 is reached
    int command = !EXIT;
    while (command != EXIT) {
        scanf("%d", &command);
        // Check if we need to resize
        if (command == RESIZE) {
            // Read in which section is modified and how many cages there
            // are going to be
            int sectionID, cageNumber;
            scanf("%d%d", &sectionID, &cageNumber);

            // Call the function
            resizeSection(&zoo, sectionID, cageNumber);
        }
        
        // Check if we need to insert an animal
        if (command == INSERT) {
            // Read in which section ID, cage ID, and animal name
            int cageID, sectionID;
            char name[1000 + 1];
            scanf("%d%d%s", &sectionID, &cageID, name);

            // Use the function to insert the animal if possible
            addAnimal(&zoo, sectionID, cageID, name);
        }

        // Check if we need to print an animal
        if (command == PRINT) {
            // Read in the section ID and cage ID to be used for printing
            int cageID, sectionID;
            scanf("%d%d", &sectionID, &cageID);

            // Use the function to print the name of the animal
            printsAnimal(&zoo, sectionID, cageID);
        }
    }

    // Clean up the memory
    for (int i = 0; i < zoo.sectionCount; i++) {
        for (int j = 0; j < zoo.array[i].cageCount; j++) {
            free(zoo.array[i].array[j].name);
        }
        free(zoo.array[i].array);
    }
    free(zoo.array);

    // Exit main
    return 0;
}

// Function to add an animal
void addAnimal(Zoo * myZoo, int section, int cage, char * name) {
    // Check that the section # is valid
    if (section < 1 || section > myZoo->sectionCount)
        return;
    
    // Check that the cage # is valid
    if (cage < 1 || cage > myZoo->array[section-1].cageCount)
        return;

    // Check that the cage is empty
    if (myZoo->array[section-1].array[cage-1].name != NULL)
        return;

    // Create the memory
    myZoo->array[section-1].array[cage-1].name = 
        calloc(strlen(name)+1, sizeof(char));

    // Move the name into the zoo
    strcpy(myZoo->array[section-1].array[cage-1].name, name);
}

// Function to resize a section
void resizeSection(Zoo * myZoo, int section, int newCageCount) {
    // Check that the section number is valid
    if (1 > section || myZoo->sectionCount < section)
        return;

    // Get the old number of cages
    int oldCageCount = myZoo->array[section - 1].cageCount;

    // If we are losing spots free them
    for (int i = newCageCount; i < oldCageCount; i++) {
        free(myZoo->array[section - 1].array[i].name);
    }

    // Reallocate the array based on the new size
    myZoo->array[section - 1].array = (Cage *) realloc(
            myZoo->array[section - 1].array,
            newCageCount * sizeof(Cage));
    
    // Initialize any extra cages
    for (int i = oldCageCount; i < newCageCount; i++) {
        myZoo->array[section - 1].array[i].name = NULL;
    }

    // Update the size of the section
    myZoo->array[section - 1].cageCount = newCageCount;
}

// Function to print out an animal in the given location
void printsAnimal(Zoo * myZoo, int section, int cage) {
    // Check that the section # is valid
    if (section < 1 || section > myZoo->sectionCount) {
        printf("No animal found.\n");
        return;
    }

    // Check that the cage # is valid
    if (cage < 1 || cage > myZoo->array[section - 1].cageCount) {
        printf("No animal found.\n");
        return;
    }

    // Check that the cage is not empty
    if (myZoo->array[section - 1].array[cage - 1].name == NULL) {
        printf("No animal found.\n");
        return;
    }

    // Print the animal
    printf("%s\n", myZoo->array[section - 1].array[cage - 1].name);
}

