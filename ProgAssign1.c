/*
* Luke Schaefer
* 18186970
* LESDMG
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ProgAssign1.h"

#define MAX_NAME_SIZE 100
#define ARR_SIZE 101

/************************/
/**** HASH FUNCTIONS ****/
/************************/

//initializes a Input struct
//returns a pointer to the Input on success or NULL on failure
Input * makeInput() {
    Input * a = malloc(sizeof(Input));
    return a;
}

//initializes an array of Person pointers
//returns a pointer to the array on success or NULL on failure
Person ** makeArray(int size) {
    Person ** array = malloc(sizeof(Person *) * size);
    if(array) {
        for(int i = 0; i < size; i++) {
            array[i] = NULL;
        }
    }
    return array;
}

//scans for the user input and stores this data in a Input struct. 
//Returns the character that specifies the command.
void scanForInput(Input * a) {

    //temp variables
    char tempC;
    char nameA[ARR_SIZE];
    char nameB[ARR_SIZE];
    int ctest;

    //scans for the initial command input
    scanf("%s", &tempC);
    a->com = tempC;
    ctest = checkInput(a->com);

    //determines the input command.
    if(ctest) {
        if(ctest == 2) {
            scanf("%s", nameA);
            strcpy(a->name1, nameA);
        }
        else if (ctest == 3) {
            scanf("%s %s", nameA, nameB);
            strcpy(a->name1, nameA);
            strcpy(a->name2, nameB);
        }
        else {
            //nothing, continue on
        }
    }
}

//checks the command. Returns 1 on X, 2 on P or L, and 3 on F U Q
int checkInput(char c) {
    if(c == 'X') {
        return 1;
    }
    else if(c == 'P' || c == 'F' || c == 'U' || c == 'Q' ||  c == 'L') {
        if(c == 'P' || c == 'L') {
            return 2;
        }
        return 3;
    }
    else {
        return 0;
    }
}

//creates a Person struct 
//Returns a pointer to the allocated memory
Person * makePerson(char name[MAX_NAME_SIZE]) {
    Person * a = malloc(sizeof(Person));
    strcpy(a->name, name);
    a->friendList = initList();
    return a;
}

//a simple hash function for hashing a name and storing it in an array of size ARR_SIZE. 
//Returns the calculated value from the hash function.
int hash(char name[MAX_NAME_SIZE]) {
    int sum = 0;
    for(int i = 0; i < strlen(name); i++) {
        sum += name[i];
    }
    int index = sum % ARR_SIZE;
    return index;
}

//attempts to find the index of the specified name in the Person array. 
//Returns the index if found. Returns -1 if not found.
int findIndex(char name[ARR_SIZE], Person * array[ARR_SIZE]) {

    int index = hash(name);
    while(array[index] != NULL) {
        if(!strcmp(name, array[index]->name)) {
            return index;
        }
        else {
            index++;
            if(index >= ARR_SIZE) {
                index = 0;
            }
        }
    }
    return -1;
}

//processes the user input from the Input sturct provided.
void processUserInput(Input * userInput, Person * array[ARR_SIZE]) {

    char comm = userInput->com;
    char nameA[ARR_SIZE];
    char nameB[ARR_SIZE];
    strcpy(nameA, userInput->name1);
    strcpy(nameB, userInput->name2);

    //adds nameA to the array
    if(comm == 'P') {

        int index = hash(nameA);
        int start = index;
        while(array[index] != NULL) {
            index++;
            if(index > ARR_SIZE) {
                index = 0;
            }
            if(index == start) {
                printf("    Could not add %s due to lack of space.\n", nameA);
            }
        }
        array[index] = makePerson(nameA);
        //finish

    }

    //adds nameA and nameB as friends
    else if(comm == 'F') {

        //add 2 people as friends
        int indexA = findIndex(nameA, array);
        int indexB = findIndex(nameB, array);
        
        //handle error
        if(indexA == -1) {
            printf("    Error: %s does not exist\n", nameA);
        }
        else if(indexB == -1) {
            printf("    Error: %s does not exist\n", nameB);
        }
        else {
            //inserting at the head of both friend lists

            //temporary variables
            Person * tempA = makePerson(nameA);
            Person * tempB = makePerson(nameB);

            //test variables
            int testerA = insertAtIndex(array[indexA]->friendList, tempB, 0);
            int testerB = insertAtIndex(array[indexB]->friendList, tempA, 0);

            if(!testerA){
                printf("    Error occured. Could not insert into %s's friend list\n", nameA);
            }
            
            if(!testerB) {
                printf("    Error occured. Could not insert into %s's friend list\n", nameB);
            }
        }
        //finish
    }
    //removes the two specified people from each other's friend lists.
    else if(comm == 'U') {

        int indexA = findIndex(nameA, array);
        int indexB = findIndex(nameB, array);

        //handle error
        if(indexA == -1) {
            printf("    Error: %s does not exist\n", nameA);
        }
        else if(indexB == -1) {
            printf("    Error: %s does not exist\n", nameB);
        }
        else if(array[indexA]->friendList->size == 0 || array[indexB]->friendList->size == 0) {
            printf("    Error: %s and %s are not friends\n", nameA, nameB);
        }
        else {

            //attempt to remove nameB from nameA
            int i = 0;
            for(i = 0; i < array[indexA]->friendList->size; i++) {
                if(!strcmp((getAtIndex(array[indexA]->friendList, i))->name, nameB)) {
                    removeAtIndex(array[indexA]->friendList, i);
                    break;
                }
            }
            
            //checks to see if A was friends with B 
            if(i > array[indexA]->friendList->size && i != 0) {
                printf("    Error: %s and %s are not friends\n", nameA, nameB);
            }
            else {

                //removes from B
                for(i = 0; i < array[indexB]->friendList->size; i++) {
                    if(!strcmp((getAtIndex(array[indexB]->friendList, i))->name, nameA)) {
                        removeAtIndex(array[indexB]->friendList, i);
                        break;
                    }
                }
                    
                
            }
        }
        
        //finish
    }
    //prints the friends of nameA
    else if(comm == 'L') {
        int index = findIndex(nameA, array);

        //handle error
        if(index == -1) {
            printf("    Error: %s does not exist\n", nameA);
            
        }
        else {
            printf("    ");
            for(int i = 0; i < array[index]->friendList->size; i++) {
                printf("%s ", ((getAtIndex(array[index]->friendList, i))->name));
            }
            puts(" ");
        }
        //finish
    }
    //checks if nameA and nameB are friends
    else if(comm == 'Q') {
        
        int indexA = findIndex(nameA, array);
        int indexB = findIndex(nameB, array);

        //handle error
        if(indexA == -1) {
            printf("    Error: %s does not exist\n", nameA);
        }
        else if(indexB == -1) {
            printf("    Error: %s does not exist\n", nameB);
        }
        //if the size of their friend's list is 0, then they are not friends
        else if (array[indexA]->friendList->size == 0 || array[indexB]->friendList->size == 0) {
            printf("    %s and %s are not friends\n", nameA, nameB);
        }
        else {
            //traverses nameA friend's list. If not on nameA, then they are not friends
            int i = 0;
            for(i = 0; i < array[indexA]->friendList->size; i++) {
                if(!strcmp((getAtIndex(array[indexA]->friendList, i))->name, nameB)) {
                    printf("    %s and %s are friends\n", nameA, nameB);
                    break;
                }
            }
            if(i > array[indexA]->friendList->size && i != 0) {
                printf("    %s and %s are not friends\n", nameA, nameB);
            }
        }
        
        
    }
    else if (comm == 'X') {
        
    }
    else {
        printf("    Invalid command. Please try again.\n");
    }

}

void freeUI(Input * a) {
    free(a);
}

void freePersonArray(Person * a[ARR_SIZE]) {
    for(int i = 0; i < ARR_SIZE; i++) {
        if(a[i] != NULL) {
            freeList(a[i]->friendList);
        }
    }
}


/************************/
/**** LIST FUNCTIONS ****/
/************************/

//checks if the specified index is in bounds of the list.
int isValidIndex(List * list, int index) {
	return index >= 0 && index < list->size;
}

//allocates space for a Node struct containing the specified person.
//Returns a pointer to the allocated memory.
Node * makeNode(Person * per, Node * next) {
	Node * a = malloc(sizeof(Node));
	if(a) {
		a->p = per;
        a->next = next;
	}
	return a;
}

//frees the given node struct pointer and returns the Person contained within.
Person * freeNode(Node * node) {
	Person * temp = node->p;
	free(node);
	return temp;
}

//returns the node at the requested index, or NULL on failure.
Node * nodeAtIndex(List *list, int index) {

	if(!isValidIndex(list, index)) {
		return NULL;
	}

	Node * tracer = list->head;

	for(int i = 0; i < index; i++) {
        tracer = tracer->next;
    }

	return tracer;
}


 //frees all of the allocated memory for the nodes in the given list.
void clearList(List * list) {

	Node * tracer = list->head;
	while(tracer) {
		Node * temp = tracer;
		tracer = tracer->next;
		free(temp);
	}
	list->head = NULL;
	list->size = 0;
}

//sets the head of the list to the given node, and returns the old head.
Node * setHead(List * list, Node * newHead) {
	Node * oldHead = list->head;
	list->head = newHead;
	return oldHead;
}


//inserts the given Person on the list at the given index. 
//Returns 1 on success and 0 on failure.
int insertAtIndex(List * list, Person * per, int index) {

	if(!isValidIndex(list, index) && (index != list->size)) {
		return 0;
	} 
    else if(index == 0) {
		Node * new = makeNode(per, NULL);
		if(new) {
            new->next = setHead(list, new);
        }
        else {
            return 0;
        }
	} 
    else {
		Node * previous = nodeAtIndex(list, index - 1);
		Node * new = makeNode(per, previous->next);
		if(new) {
            previous->next = new;
        }
		else {
            return 0;
        }
	}
	list->size++;
	return 1;
}

// Removes and returns the object at the given index. Returns NULL on failure.
Person * removeAtIndex(List * list, int index) {

	if(!isValidIndex(list, index)) {
		return NULL;
	}
	Person * per;

	if(index == 0) {
		per = freeNode(setHead(list, list->head->next));
	} 
    else {
		Node * previous = nodeAtIndex(list, index - 1);
		Node * temp = previous->next;
		previous->next = temp->next;
		per = freeNode(temp);
	}
	list->size--;
	return per;
}

//initializes a Linked List struct
//returns a pointer to the list on success or NULL on failure.
List* initList() {
	List *list = malloc(sizeof(List));
	if(list) {
		list->head = NULL;
        list->size = 0;
	}
	return list;
}

//returns the Person at the requested index, or NULL on failure.
Person * getAtIndex(List *list, int index) {
	Node * node = nodeAtIndex(list, index);
	if(node) {
		return node->p;
	}
	return NULL;
}

//frees all memory allocated to the list.
void freeList(List *list) {
	clearList(list);
	free(list);
}




