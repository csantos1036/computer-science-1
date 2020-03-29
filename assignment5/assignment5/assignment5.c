//
//  main.c
//  assignment5
//
//  Created by Carolina Santos on 3/28/20.
//  Copyright © 2020 Carolina Santos. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Type defs for the structs
typedef struct Stack Stack;
typedef struct LinkedList LinkedList;
typedef struct Node Node;

struct Stack {
    Node * tailLL;
};

struct LinkedList {
    Node * head;
    Node * tail;
};

struct Node {
    char data;
    Node * prev;
    Node * next;
};

// Prototypes for Stacks
Stack * createStack();
void pop(Stack * stack);
void push(Stack * stack, char value);
void clea

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
    LinkedList * list = calloc(1, sizeof(LinkedList));
    strcpy(command, "begim");

    while (strcmp(command,"EXIT") != 0 )
    {
        scanf("%s", command);
        if(strcmp(command,"TYPE") == 0)
        {
            scanf(" %c", &character);
            if(isFlipped == 0)
            {
                insertTail(list, character);
            }
            else
            {
                insertHead(list, character);
            }
        }
        else if(strcmp(command,"SPACE") == 0)
        {
            if(isFlipped == 0)
            {
                insertTail(list, ' ');
            }
            else
            {
                insertHead(list, ' ');
            }
        }
        else if(strcmp(command,"BACK") == 0)
        {
            if(isFlipped == 0)
            {
               removeTail(list);
            }
            else
            {
               removeHead(list);
            }
        }
        else if(strcmp(command,"PRINT") == 0)
        {
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
            isFlipped = 1;
        }
    }
    freeList(list);
    return 0;
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
