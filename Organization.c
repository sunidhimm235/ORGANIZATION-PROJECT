#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defining the max value of SIZE of input size.
#define SIZE (100000 + 1)

// Struct for cages to hold the animal information presented in the cages.
struct cage {
    char animal[SIZE];  
};

// Struct for sections to hold multiple cages and int for determining how many cages are there.
struct section {
    struct cage * cages;
    int numCages;
};

// This resize function works when we are resizing any sections. 
// Create a new array of struct cages with the new number of cages presented in the sections. 
struct cage * resize(struct cage * cages, int cageNum) {

    // Creating a new struct cage with the new number of cages.
    struct cage * c = (struct cage *)malloc(sizeof(struct cage) * cageNum);
    
    // Using a nested for loop to copy all the information from past struct cage to new struct cage until the resize number.
    for(int x = 0; x < cageNum; x++) {

        // Determining the length of the current animal string.
        int len = strlen(cages[x].animal);

        // Copy the animal information from the past struct cage to new struct cage.
        for(int y = 0; y < len; y++) {
            c[x].animal[y] = cages[x].animal[y];
        }
    }
    
    // Returning the new struct cage.
    return c;
}

// Function to free all the heap memory that the program allocated before.
void freeMem(struct section * sections, int totalSections) {
    // For loop to free all the cages first.
    for(int x = 0; x < totalSections; x++) {
        free(sections[x].cages);
    }
    
    // Finally freeing the main section struct.
    free(sections);
}

int main() {
    // Declaring to store the number of struct section the program needs to create later.
    int NumOfSections = 0;
    // Declaring to hold the option number.
    int option = 0;

    // Taking the input as int for 'NumOfSections' to create the array of struct section.
    scanf("%d", &NumOfSections);

    // Creating an array of struct sections.
    // Allocating the memory in heap using calloc.
    struct section * sections = (struct section *)calloc(NumOfSections, sizeof(struct section));
    
    // Using do-while loop to keep the program running until the input for option int becomes 4.
    do {
        // Declaring integers for to hold section number and cage number to know where we are creating something/making the change.
        // Declaring len (int) to use it later as storing the string length of animal of the specified cage.
        int sectionNum = 0, cageNum = 0, len = 0;
        // Declaring char/string 'temp' to temporary hold the animal name input.
        char temp[SIZE];
        
        // Taking the input for option (int) to determine what commands to should program follow.
        scanf("%d", &option);
        // If the option is equal to 4, the program will automatically end.
        if(option == 4) break;

        // Taking the input for section number and cage number to determine at what place the command should happen.
        scanf("%d %d", &sectionNum, &cageNum);
        
        // Using switch statement to work the commands according to the option number.
        switch(option) {
            case 1:
                // Commands for option number -> 1.

                // Using if-else statement to determine if we are creating an array of struct sections or resizng it.
                if(sections[sectionNum-1].numCages > 0) { // Resizing if numCages (int) of the current section is more than 0.

                    // Changing the value of cageNum of the current struct section with the new number of cages presented in the section.
                    sections[sectionNum-1].numCages = cageNum;
                    // Using the resize function to create a new array with a new size and the same information from the last struct section.
                    sections[sectionNum-1].cages = resize(sections[sectionNum-1].cages, cageNum);

                } else { // Creating if numCages (int) of the current section is equal to 0.

                    // Assiging the value of cageNum of the current struct section with number of cages presented in the section.
                    sections[sectionNum-1].numCages = cageNum;
                    // Creating a array of struct cages in the struct section.
                    sections[sectionNum-1].cages = (struct cage *)calloc(cageNum, sizeof(struct cage));

                }
                break;
            case 2:
                // Commands for option number -> 2.

                // Assigning the animal name to the specified cage number of the current struct section using scanf.
                scanf("%s", temp);
                
                // Using if condition to check whether inputs of section number and cage number are right, and the specified section has cages or not.
                // If inputs of section number and cage number are wrong, and if the specified section has no cages, then it will turn true and ignore the rest of the commands.
                if((sectionNum < 1 || sectionNum > NumOfSections) || (cageNum < 1 || cageNum > sections[sectionNum-1].numCages) || (sections[sectionNum-1].numCages == 0)) {
                    continue;
                }

                // Using if condition to check if the cage already has a animal or not.
                if((strlen(sections[sectionNum-1].cages[cageNum-1].animal) > 0)) { // If it has animal inside the cage, the program will continue ignoring the rest of the commands. 
                    continue;
                }

                // For loop to store the input in the specified section's current cage.
                for(int x = 0; temp[x] != '\0'; x++) {
                    sections[sectionNum-1].cages[cageNum-1].animal[x] = temp[x];
                }

                break;
            case 3:
                // Commands for option number -> 3.

                // Using if condition to check whether inputs of section number and cage number are right, and the specified section has cages or not.
                // If inputs of section number and cage number are wrong, and if the specified section has no cages, then it will turn true and ignore the rest of the commands.
                if((sectionNum < 1 || sectionNum > NumOfSections) || (cageNum < 1 || cageNum > sections[sectionNum-1].numCages) || (sections[sectionNum-1].numCages == 0)) {
                    printf("No animal found.\n");
                    continue;
                }

                // Storing the length of animal name that is presented in the specified cage number of the current section number.
                len = strlen(sections[sectionNum-1].cages[cageNum-1].animal);

                // Using if-else statement to determine if the animal is presented in the specified cage number or not.
                if(len > 0) { // If the len is more than 0, there is an animal presented.

                    // Printing the name of the animal that is presented in the cage.
                    printf("%s\n", sections[sectionNum-1].cages[cageNum-1].animal);
                } else { // If the len is 0, then there is no animal presented.

                    // Printing "No animal found." because there is no animal presented in the cage. 
                    printf("No animal found.\n");
                }
                break;
        }
        
    } while(option != 4);// Ending the do-while loop when option is equal to 4.

    // Using funtion 'freeMem' to free all the heap memory that the program allocated.
    freeMem(sections, NumOfSections);

    return 0;
}