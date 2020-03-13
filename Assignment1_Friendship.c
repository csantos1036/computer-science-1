//
//  Assignment1_Friendship.c
//  Assignment1_Friendship
//
//  Created by Carolina Santos on 1/23/20.
//  Copyright © 2020 Carolina Santos. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEFAULT_CAP 1

// Array List of Strings
typedef struct SmallList {
    int size;
    int cap;
    char ** arr;
} SmallList;

// Array List of Array List of Strings
typedef struct BigList {
    int size;
    int cap;
    SmallList * arr;
} BigList;

// Prototypes for the Big Array Lists
BigList * createBig(); // done
void expandBig(BigList *); // done
void addNameToBig(BigList *, char * name); // done
// Prototypes for the Small Array Lists
void expandSmall(SmallList *); // done
void initializeSmall(SmallList *); // done
void addFriend(BigList *, char * name, char * friend);
void removeFriend(SmallList *, char * val);
// Method to find an index for the given string
int getInd(BigList *, char * val);

int main() {
    
    BigList * bl;
    SmallList * sl;
    
    bl = createBig();
    
    int q; //Number of queries
    
    char query[6];
    
    printf("Number of queries:\n");
    scanf("%d", &q);
    
    while (q > 500000) {
        printf("Number is too high. Please enter another number:\n");
        scanf("%d", &q);
    }
    
    
    while (q != 0 ) {
            

        if (strcmp(query, "ADD")){

        }
        else if(strcmp(query, "REMOVE")) {

        }
        else {

        }
        q--;
    }
        
}

BigList * createBig() {
    BigList * bl = calloc(1, sizeof(BigList));
    bl->size = 0;
    bl->cap = DEFAULT_CAP;
    bl->arr = calloc(bl->cap, sizeof(SmallList));
    return bl;
}

void expandBig(BigList * bl) {
    // Update the capacity
    bl->cap = bl->cap * 2;
    
    // Increase the array to the new capacity
    BigList * newArr = calloc(bl->arr, bl->cap * sizeof(BigList));
    
    // Check if allocation failed
     if (newArr == NULL) {
         bl->cap /= 2;
         printf("Error!");
         exit(0);
     }
    
}

void addNameToBig(BigList * bl, char * name) {
    // Update the array list
    SmallList * sl = name;
    bl->arr[bl->size] = *sl;
    bl->size++;
}

void expandSmall(SmallList * sl) {
    // Update the capacity
    sl->cap = sl->cap * 2;
    
    // Increase the array to the new capacity
    SmallList * newArr = calloc(sl->arr, sl->cap * sizeof(SmallList));
    
    // Check if allocation failed
     if (newArr == NULL) {
         sl->cap /= 2;
         printf("Error!");
         exit(0);
     }
}

void initializeSmall(SmallList * sl) {
    sl = calloc(1, sizeof(SmallList));
    sl->size = 0;
    sl->cap = DEFAULT_CAP;
    sl->arr = calloc(sl->cap, sizeof(char**));
}

void addFriend(BigList * bl, char * name, char * friend) {
    for (int i = 0; i < sizeof(BigList), i++) {
        
    }
        
}







