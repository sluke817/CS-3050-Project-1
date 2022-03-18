/*
* Luke Schaefer
* 18186970
* LESDMG
*/

#include <stdio.h>
#include <stdlib.h>
#include "ProgAssign1.h"

#define MAX_NAME_SIZE 100
#define ARR_SIZE 101

int main () {

    //initial variables    
    Input * userInput = makeInput();
    Person ** array = makeArray(ARR_SIZE);
    
    puts("*** Luke Schaefer 18186970 ***");
    printf("Enter your commands in the correct format. Please refer to the README file for help.\n"); 

    do {
        scanForInput(userInput);
        processUserInput(userInput, array);
    } while(userInput->com != 'X');

    freeUI(userInput);
    freePersonArray(array);

    puts("Thank you. Goodbye.");
    return 0;

}
