//
//  main.c
//  assignment7-heap
//
//  Created by Carolina Santos.
//  Copyright © 2020 Carolina Santos. All rights reserved.
//
// This program uses an arraylist to represent
// a binary heap, which is used as a priority queue.

#include <stdio.h>
#include <stdlib.h>

#define DC 4
#define PARENT(x)   ((x-1)>>1)
#define LEFT(x)     (((x)<<1)+1)
#define RIGHT(x)    (((x)<<1)+2)
#define IMPOSSIBLE -1

typedef struct ArrayList ArrayList;
typedef struct Bugs Bugs;

struct ArrayList
{
    int cap, arraySize, flip;
    Bugs * bugs;
};

struct Bugs
{
    long long int index; // Index of the bug
    long long int time;  // Time to fix bug
    long long int order; // Order when bug is noticed/entered
};

// Prototypes for ArrayList
ArrayList * createArrayList();
ArrayList ** createArray(long long int);
void expandArrayList(ArrayList *);
void appendArray(ArrayList *, long long int, long long int, long long int);
void percolateUp(ArrayList *, int, long long int);
void percolateDown(ArrayList *, long long int, long long int);
void cleanArrayList(ArrayList *);
void heapAdd(ArrayList *, long long int, long long int, long long int);
long long int heapFront(ArrayList *);
void heapRemove(ArrayList *);

FILE * fp;
FILE * bp;

// The main function
int main()
{
    FILE * fp;
    FILE * bp;
    
    fp = fopen("/Users/carolinasantos/src/computer-science-1/testing/testing/input.txt", "r");
    bp = fopen("/Users/carolinasantos/src/computer-science-1/testing/testing/Output2.txt", "w");
    
    if(fp == NULL)
    {
       printf("Error opening!");
       exit(1);
    }
    
    if(bp == NULL)
    {
       printf("Error!");
       exit(1);
    }
    
    // Create the heap for bugs that have been uncovered
    ArrayList * heap = createArrayList();
    
    long long int B; // Number of bugs in the program
    long long int T; // Time left in seconds
    long long int t; // Time to fix bug
    long long int x; // Index of the bug
    long long int order = 1; // Order of when bug is noticed/entered
    long long int i = 0;
    
    fscanf(fp, "%lld", &B);
    fscanf(fp, "%lld", &T);
    
    // Create an array of ArrayLists to store hidden bugs
    ArrayList ** additionalBugs = createArray(B);
    
    i = B;
    
    while(i > 0) // Adding bugs to priority queue
    {
        fscanf(fp, "%lld", &t);
        fscanf(fp, "%lld", &x);
        
        if (x == -1)
        {
            heapAdd(heap, t, x, order); // Adds noticeable bugs without fixing others
        }
        else
        {
            heapAdd(additionalBugs[x], t, x, order); // Adds underlying bugs to a separate heap
        }
        order++;
        i--;
    }
    
    // A long long int arr to store the order of when bug is noticed/entered
    long long int * arr = malloc(B * sizeof(long long int));
    long long int counter = 0;
    
    // Removing bugs
    // While time left and bugs left are greater than or equal 0
    while(T > 0 && B > 0)
    {
        if (heap->bugs[0].time <= T && B > 0)
        {
            long long int top = heapFront(heap);
            arr[counter] = top;
            T -= heap->bugs[0].time;
            heapRemove(heap);
            
            // If an error is to happen
            if(top <= 0)
            {
                break;
            }
            
            if(additionalBugs[top]->arraySize > 0)
            {
                for (int j = 0; j < additionalBugs[top]->arraySize + 1; j++)
                {
                    heapAdd(heap, additionalBugs[top]->bugs[j].time, -1, additionalBugs[top]->bugs[j].order);
                    heapRemove(additionalBugs[top]);
                }
            }
            counter++;
            B--;
        }
    }
    
    fprintf(bp, "%lld\n", counter);
    for (int k = 0; k < counter; k++)
    {
        fprintf(bp,"%lld\n", arr[k]);
        // Free heaps
        cleanArrayList(additionalBugs[k + 1]);
    }
    // Free heap
    cleanArrayList(heap);
    
    fclose(fp);
    fclose(bp);
    return 0;
}

// Method to create an array list
ArrayList * createArrayList()
{
    ArrayList * ret;
    ret = malloc(DC * sizeof(ArrayList));
    ret->arraySize = 0;
    ret->cap = DC;
    ret->bugs = malloc(ret->cap * sizeof(Bugs));
    ret->bugs->order = 0;
    return ret;
}

// Method to create an array of ArrayLists
ArrayList ** createArray(long long int B)
{
    ArrayList ** ret;
    ret = malloc(B * sizeof(ArrayList));
    for (long long int size = 1; size <= B; size++)
    {
        ret[size] = createArrayList();
    }
    return ret;
}

// Method to update the size of the array list
void expandArrayList(ArrayList * al)
{
    al->cap *= 2;
    al->bugs = realloc(al->bugs, al->cap * sizeof(Bugs));
}

// Add the element to the end of the list
void appendArray(ArrayList * al, long long int time, long long int x, long long int order)
{
    // Check if full
    if (al->cap == al->arraySize)
    {
        expandArrayList(al);
    }

    // Add the element to the end
    al->bugs[al->arraySize].index = x;
    al->bugs[al->arraySize].time = time;
    al->bugs[al->arraySize].order = order;
    al->arraySize++;
}

// Method for moving an element up into the correct location
void percolateUp(ArrayList * al, int ind, long long int x)
{
    // Check if we are at the root
    if (ind == 0) return;

    // Check if the parent if worse than the current value
    if (al->bugs[ind].time < al->bugs[PARENT(ind)].time)
    {
        // Swap
        Bugs tmp = al->bugs[ind];
        al->bugs[ind] = al->bugs[PARENT(ind)];
        al->bugs[PARENT(ind)] = tmp;
        // Move the element (in the parent) up if necessary
        percolateUp(al, PARENT(ind), x);
    }
    else if (al->bugs[ind].time == al->bugs[PARENT(ind)].time)
    {
        if (al->bugs[ind].order < al->bugs[PARENT(ind)].order)
        {
            // Swap
            Bugs tmp = al->bugs[ind];
            al->bugs[ind] = al->bugs[PARENT(ind) + 1];
            al->bugs[PARENT(ind) + 1] = tmp;

            // Move the element (in the parent) up if necessary
            percolateUp(al, PARENT(ind), x);
                
        }
    }
}

// Method for moving an element down into the correct location
void percolateDown(ArrayList * al, long long int ind, long long int x)
{
    // Check if there is a left child
    if (LEFT(ind) >= al->arraySize)
    {
        return;
    }
    
    // Check if the right child exists and is better than the left
    if (RIGHT(ind) < al->arraySize && al->bugs[LEFT(ind)].time > al->bugs[RIGHT(ind)].time)
    {
        // Best child is on the right
        if (al->bugs[RIGHT(ind)].time < al->bugs[ind].time)
        {
            Bugs tmp = al->bugs[ind];
            al->bugs[ind]= al->bugs[RIGHT(ind)];
            al->bugs[RIGHT(ind)] = tmp;
            percolateDown(al, RIGHT(ind), x);
        }
        else if (al->bugs[RIGHT(ind)].time == al->bugs[ind].time)
        {
            if (al->bugs[RIGHT(ind)].order < al->bugs[ind].order)
            {
                Bugs tmp = al->bugs[ind];
                al->bugs[ind]= al->bugs[RIGHT(ind)];
                al->bugs[RIGHT(ind)] = tmp;
                percolateDown(al, RIGHT(ind), x);
            }
        }
    }
    else if (al->bugs[LEFT(ind)].time < al->bugs[ind].time)
    {
        // The left child  is better
        Bugs tmp = al->bugs[ind];
        al->bugs[ind] = al->bugs[LEFT(ind)];
        al->bugs[LEFT(ind)] = tmp;
        percolateDown(al, LEFT(ind), x);
    }
    else if (al->bugs[LEFT(ind)].time == al->bugs[ind].time)
    {
        if (al->bugs[LEFT(ind)].order < al->bugs[ind].order)
        {
            // The left child  is better
            Bugs tmp = al->bugs[ind];
            al->bugs[ind] = al->bugs[LEFT(ind)];
            al->bugs[LEFT(ind)] = tmp;
            percolateDown(al, LEFT(ind), x);
        }
    }
}

// Method to free up the array
void cleanArrayList(ArrayList * al)
{
    free(al->bugs);
    free(al);
}

// Method to add an element to a heap
void heapAdd(ArrayList * heap, long long int time, long long int x, long long int order)
{
    appendArray(heap, time, x, order);
    percolateUp(heap, heap->arraySize - 1, x);
}

// Method to return the order of the top element of the heap
long long int heapFront(ArrayList * heap)
{
    // Check if the heap is empty
    if (heap->arraySize == 0)
    {
        return IMPOSSIBLE;
    }
    return heap->bugs[0].order;
}

// Method to remove an element from a heap
void heapRemove(ArrayList * heap)
{
    heap->bugs[0] = heap->bugs[heap->arraySize - 1];
    heap->arraySize--;
    percolateDown(heap, 0, heap->bugs[0].index);
}

