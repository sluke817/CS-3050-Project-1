/*
* Luke Schaefer
* 18186970
* LESDMG
*/

#include <stdlib.h>
#include <stdio.h>

#define MAX_NAME_SIZE 100
#define ARR_SIZE 101


//partial typdefs
typedef struct NodeStruct Node;
typedef struct ListStruct List;
typedef struct PersonStruct Person;
typedef struct UserInputStruct Input;


//structures
typedef struct NodeStruct {
	Person * p;
    struct NodeStruct * next;
} Node;

typedef struct ListStruct{
	Node * head;
	int size;
} List;

typedef struct UserInputStruct {
    char com;
    char name1[MAX_NAME_SIZE];
    char name2[MAX_NAME_SIZE]; 
} Input;

typedef struct PersonStruct {
    char name[MAX_NAME_SIZE];
    
    List * friendList;
} Person;


//Person and Input functions
Input * makeInput();
void scanForInput(Input * in);
Person * makePerson(char name[MAX_NAME_SIZE]);
int hash(char name[MAX_NAME_SIZE]);
Person ** makeArray(int size);
void processUserInput(Input * userInput, Person * array[ARR_SIZE]);
int checkInput(char c);
void freeUI(Input * input);
void freePersonArray(Person **);

//List and Node functions
int isValidIndex(List * list, int index);
Node * makeNode(Person * data, Node * next);
Person * freeNode(Node * node);
Node * nodeAtIndex(List * list, int index);
void clearList(List * list);
Node * setHead(List * list, Node * newHead);
int insertAtIndex(List * list, Person * object, int index);
Person * removeAtIndex(List * list, int index);
List * initList();
Person * getAtIndex(List * list, int index);
void freeList(List * list);
