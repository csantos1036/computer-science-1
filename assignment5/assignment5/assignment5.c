//
//  main.c
//  assignment5
//
//  Created by Carolina Santos
//  Copyright © 2020 Carolina Santos. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Type defs for the structs
typedef struct Stack Stack;
typedef struct Action Action;
typedef struct LinkedList LinkedList;
typedef struct Node Node;

// Stack data stucture to create stack of actions
struct Stack {
    Action * top;
};

// Action data structure to create an action based on the command and data
struct Action {
    char * commandVal;
    char data;
    Action * next;
};

// Doubly LinkedList data structure
struct LinkedList {
    Node * head;
    Node * tail;
};

// Node data structure
struct Node {
    char data;
    Node * prev;
    Node * next;
};

//Protoypes for different commands
void insertion(char, int, LinkedList *);
void deletion(int, LinkedList *);
int flipIt(int);
void stackActions(Stack *, Stack *, char *, int, LinkedList *);

// Prototypes for Stacks
Stack * createStack();
void pop(Stack * stack);
void push(Stack * stack, char * value, char data);
char * peek(Stack * stack);
void cleanStack(Stack *);
int isEmptyStack(Stack * stack);

// Prototypes for LL
Node * newNode(char);
void insertTail(LinkedList *, char);
void insertHead(LinkedList *, char);
void removeTail(LinkedList *);
void removeHead(LinkedList *);
int isEmpty(LinkedList *);
void printList(LinkedList *);
void printListBackward(LinkedList *);
void freeList(LinkedList *);


int main() {
    char command[6];
    char character;
    int isFlipped = 0;
    
    // Creating a linked list
    LinkedList * list = calloc(1, sizeof(LinkedList));
    
    // Creating Undo and Redo Stacks
    Stack * undo = createStack();
    Stack * redo = createStack();
    
    // Assigning command to a string literal to begin the while loop
    strcpy(command, "begin");

    // While loop as long as the user does not type "EXIT" it will continue asking for user input
    while (strcmp(command,"EXIT") != 0 )
    {
        // Asks for user input
        scanf("%s", command);
        
        // If else condtions for each one of the user input commands
        if(strcmp(command,"TYPE") == 0)
        {
            // Scans in character data
            scanf(" %c", &character);
            
            // Inserts the character data and adds the opposite action to the undo stack
            insertion(character, isFlipped, list);
            push(undo, "BACK", character);
            
            // Clears redo stack
            cleanStack(redo);
        }
        else if(strcmp(command,"SPACE") == 0)
        {
            // Inserts blank character data and adds the opposite action to the undo stack
            insertion(' ', isFlipped, list);
            push(undo, "BACK",' ');
            
            // Clears redo stack
            cleanStack(redo);
        }
        else if(strcmp(command,"BACK") == 0)
        {
            // Only removes character data if it already exists, if so adds the opposite action to the undo stack
            if(!isEmpty(list))
            {
                push(undo, "TYPE", list->tail->data);
                deletion(isFlipped, list);
            }
            
            // Clears redo stack
            cleanStack(redo);
        }
        else if(strcmp(command,"PRINT") == 0)
        {
            // Prints list in either order depending on the condition of isFlipped
            if(isFlipped == 0)
            {
                printList(list);
            }
            else
            {
               printListBackward(list);
            }
        }
        else if(strcmp(command,"FLIP") == 0)
        {
            // Changes the condition of isFlipped from 0 to 1 or vice versa
            isFlipped = flipIt(isFlipped);
            
            // Adds the action to the undo stack
            push(undo, "FLIP",' ');
            
            // Clears redo stack
            cleanStack(redo);
        }
        else if(strcmp(command,"UNDO") == 0)
        {
            // Perform opposite of last command
            strcpy(command, peek(undo));
            if (strcmp(command,"FLIP") == 0){
                // Adds action to redo stack
                push(redo, "FLIP",' ');
                
                // Flips the condition
                isFlipped = flipIt(isFlipped);
                
                // Removes the top element of the undo stack
                pop(undo);
            }
            else {
                // Calls function for all commands except "FLIP"
                stackActions(undo, redo, command, isFlipped, list);
            }

        }
        else if(strcmp(command,"REDO") == 0)
        {
            // Perform opposite of last undo
            strcpy(command, peek(redo));
            if (strcmp(command,"FLIP") == 0){
                // Adds action to undo stack
                push(undo, "FLIP",' ');
                
                // Flips the condition
                isFlipped = flipIt(isFlipped);
                
                // Removes the top element of the redo stack
                pop(redo);
            }
            else {
                // Calls function for all commands except "UNDO"
                stackActions(redo, undo, command, isFlipped, list);
            }
        }
    }
    freeList(list);
    return 0;
}

void stackActions(Stack * stack1, Stack * stack2, char * command, int isFlipped, LinkedList * list)
{
    // Function for the undo and redo stacks to add an action to the stack2 stack
    // and remove the top action from the stack1 stack
    
    if ((strcmp(command,"TYPE")) == 0){
        push(stack2, "BACK", stack1->top->data);
        insertion(stack1->top->data, isFlipped, list);
    }
    else if (strcmp(command,"BACK") == 0) {
        push(stack2, "TYPE", stack1->top->data);
        deletion(isFlipped, list);
    }
    pop(stack1);
}

void insertion(char character, int isFlipped, LinkedList * list) {
    if(isFlipped == 0)
    {
        insertTail(list, character);
    }
    else
    {
        insertHead(list, character);
    }
}

void deletion(int isFlipped, LinkedList * list) {
    if(isFlipped == 0)
    {
       removeTail(list);
    }
    else
    {
       removeHead(list);
    }
}

int flipIt(int isFlipped) {
    if (isFlipped == 1)
        return 0;
    return 1;
}

Stack * createStack()
{
   // We are creating only 1 stack
   Stack * ret = calloc(1, sizeof(Stack));
   
   // Start the stack as empty
   ret->top = NULL;
   
   // Return the created stack
   return ret;
}

Action * newAction(char * commandVal, char data)
{
   Action * ret = calloc(1, sizeof(Action));
   ret->commandVal = commandVal;
   ret->data = data;
   ret->next = NULL;
   return ret;
}

// Pop an element from a stack
void pop(Stack * stack)
{
    if(stack->top != NULL){
       Action * temp = stack->top;
       stack->top = temp->next;
       free(temp);
    }
}

// Push an element onto the top of a stack
void push(Stack * stack, char * commandVal, char data)
{
    Action * action = newAction(commandVal, data);
    if(isEmptyStack(stack))
    {
        action->next = NULL;
    }
    else
    {
        action->next = stack->top;
    }
    stack->top = action;
}

// Get the value on the top of a stack
char * peek(Stack * stack)
{
    
    if (isEmptyStack(stack)){
        return "\0";
    }
    
   // Return the value of the head of the linked list
   return stack->top->commandVal;
}


// Function to check if a stack is empty
int isEmptyStack(Stack * stack)
{
   return (stack->top == NULL);
}

void cleanStack(Stack * stack)
{
    if(stack->top != NULL){
       while (!isEmptyStack(stack))
          pop(stack);
       free(stack->top);
    }
}

Node * newNode(char data)
{
   Node * ret = calloc(1, sizeof(Node));
   ret->data = data;
   ret->next = NULL;
   ret->prev = NULL;
   return ret;
}

void insertTail(LinkedList * list, char data)
{
   // Empty list case
   if (isEmpty(list))
   {
      list->head = list->tail = newNode(data);
      return;
   }
    
   // Store the old and new tail
   Node * newTail = newNode(data);
   Node * oldTail = list->tail;
    
   // Link the old tail and the new tail
   oldTail->next = newTail;
   newTail->prev = oldTail;
    
   // Update the tail
   list->tail = newTail;
}

void insertHead(LinkedList * list, char data)
{
   // Empty list case
   if (isEmpty(list))
   {
      list->head = list->tail = newNode(data);
      return;
   }
   
   // Store the old and new head
   Node * newHead = newNode(data);
   Node * oldHead = list->head;
   
   // Link the old head and the new head
   oldHead->prev = newHead;
   newHead->next = oldHead;
   
   // Update the head
   list->head = newHead;
}

void removeTail(LinkedList * list)
{
   // Empty case
   if (isEmpty(list))
      return;
   
   // size 1 case
   if (list->tail->prev == NULL)
   {
      // Free the node
      free(list->tail);
      
      // Empty the list
      list->head = list->tail = NULL;
      
      // Exit
      return;
   }
   
   // Store the old and new tail
   Node * oldTail = list->tail;
   Node * newTail = list->tail->prev;
   
   // Free the old memory
   free(oldTail);
   
   // Update the new tail
   newTail->next = NULL;
   list->tail = newTail;
}

void removeHead(LinkedList * list)
{
   // Empty case
   if (isEmpty(list))
      return;
   
   // size 1 case
   if (list->head->next == NULL)
   {
      // Free the node
      free(list->head);
      
      // Empty the list
      list->head = list->tail = NULL;
      
      // Exit
      return;
   }
   
   // Store the old and new head
   Node * oldHead = list->head;
   Node * newHead = list->head->next;
   
   // Free the old memory
   free(oldHead);
   
   // Update the new head
   newHead->prev = NULL;
   list->head = newHead;
}

int isEmpty(LinkedList * list)
{
   return (list->head == NULL);
}

void printList(LinkedList * list)
{
    Node * cur = list->head;
    Node * space = list->head;
    int val = 0;
    
    if (isEmpty(list) || list->tail->data == ' '){
           printf("No word is found.");
    }
    
    while (cur != NULL)
    {
        // Checks for a blank space character
        if(cur->data == ' ')
        {
            // Walks the buffer to the first space character
            space = cur;
            val = 1;
        }
        cur = cur->next;
    }
    
    // Condition if there is a space character in the buffer
    if (val == 1)
    {
        cur = space->next;
        
        while (cur != NULL)
        {
            printf("%c", cur->data);
            cur = cur->next;
        }
        printf("\n");
    }
    
    // Condition if there is no space character in the buffer
    if (val == 0)
    {
        cur = list->head;
        
        while (cur != NULL && cur->data != ' ')
        {
            printf("%c", cur->data);
            cur = cur->next;
        }
        printf("\n");
    }
}

void printListBackward(LinkedList * list)
{
    Node * cur = list->tail;
    Node * space = list->tail;
    int val = 0;
    
    if (isEmpty(list) || list->head->data == ' '){
           printf( "No word is found.");
    }
    
    while (cur != NULL)
    {
        // Checks for a blank space character
        if(cur->data == ' ')
        {
            // Walks the buffer to the first space character
            space = cur;
            val = 1;
        }
        cur = cur->prev;
    }
    
    // Condition if there is a space character in the buffer
    if (val == 1)
    {
        cur = space->prev;
        
        while (cur != NULL)
        {
            printf("%c", cur->data);
            cur = cur->prev;
        }
        printf("\n");
    }
    
    // Condition if there is no space character in the buffer
    if (val == 0)
    {
        cur = list->tail;
        
        while (cur != NULL && cur->data != ' ')
        {
            printf("%c", cur->data);
            cur = cur->prev;
        }
        printf("\n");
    }
}

void freeList (LinkedList * list)
{
    while(!isEmpty(list))
    {
        removeHead(list);
    }
    free(list);
}
