//
//  assignment3.c
//  assignment3
//
//  Created by Carolina Santos on 2/20/20.
//  Copyright © 2020 Carolina Santos. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FALSE 0
#define TRUE 1

void recData(int * usedData, int * originalData, int * usedDifference, int * originalDifference, int * permCurr, int * permLast, int num, int len);
int checkDifference(int * usedDifference, int * originalDifference, int * perm, int num, int len);
int compareArrays(int * permCurr, int * permLast, int len);

int count = 0;

int main() {
    int n;
    // The arrays that will be used
    int * usedData;         // Store 0's and 1's
    int * usedDifference;   // Store 0's and 1's
    int * originalData;     // Array of data points
    int * originalDifference; // Array of differences between data points
    int * permCurr;         // Current Permutation
    int * permLast;         // Last Permutation
    
    // Read in the input
    scanf("%d", &n);
    
    // Allocate the memory
    usedData = calloc(n, sizeof(int));
    originalData = calloc(n, sizeof(int));
    usedDifference = calloc(n - 1, sizeof(int));
    originalDifference = calloc(n - 1, sizeof(int));
    permCurr = calloc(n, sizeof(int));
    permLast = calloc(n, sizeof(int));
    
    // Loop and initialize the memory
    for (int i = 0; i < n; i++) {
        usedData[i] = FALSE;
        permCurr[i] = '\0';
        permLast[i] = '\0';
    }
    for (int i = 0; i < n - 1; i++) {
        usedDifference[i] = FALSE;
    }
    
    // Read in the input
    for (int i = 0; i < n; i++) {
        scanf("%d", &originalData[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        scanf("%d", &originalDifference[i]);
    }
    
    // Recursively call the function
    recData(usedData, originalData, usedDifference, originalDifference, permCurr, permLast, 0, n);
    
    // Print number of arrangements
    printf("%d", count);
    
    // Free all the allocated memory
    free(usedData);
    free(usedDifference);
    free(originalData);
    free(originalDifference);
    free(permCurr);
    free(permLast);
    
    // Return a zero
    return 0;
}

int compareArrays(int * permCurr, int * permLast, int len) {
    // Compare the current permutation to the last permutation to eliminate adjacent duplicates
    
    // If the current permutation and the last permutation are not the same, then the function will return FALSE
    for (int i = 0; i < len; i++){
        if (permCurr[i] != permLast[i]){
          return FALSE;
        }
    }
    return TRUE;
}

int checkDifference(int * usedDifference, int * originalDifference, int * perm, int num, int len){
    // Check the differences of every permutaion of data points to verify whether the differences are satisfied
    
    // If the difference between the data points are equivalent to one of the original differences, then orignalDifference[i] will be assigned TRUE
    for (int i = 0; i < len - 1; i++){
        for(int j = 0; j < len - 1; j++){
            if ((!usedDifference[j]) && ((abs(perm[i] - perm[i + 1])) == originalDifference[j])){
                usedDifference[j] = TRUE;
                break;
            }
        }
    }
    // If there is at least one difference that is not assigned TRUE, the function will return FALSE
    for (int i = 0; i < len - 1; i++){
        if (!usedDifference[i]){
            return FALSE;
        }
    }
    
    //If all usedDifference[i] = TRUE, then the function will return TRUE
    return TRUE;
}

void recData(int * usedData, int * originalData, int * usedDifference, int * originalDifference, int * permCurr, int * permLast, int num, int len){
    
    int val; // Store whether the checkDifference function is TRUE or FALSE
    int comparison; // Store whether the compareArrays is TRUE or FALSE

    // Base case
    if (num == len) {
        // Check the current permutation and the last permutation to make sure they are not duplicates
        comparison = compareArrays(permCurr, permLast, len);
        
        // If the two are not same
        if (comparison == FALSE) {
            for (int i = 0; i < len - 1; i++){
                usedDifference[i] = FALSE;
            }
            
            // Call checkDifference function to count only the arrangements that fulfill orignalDifference array
            val = checkDifference(usedDifference, originalDifference, permCurr, num,len);
            if (val == TRUE){
                count++;
                for (int i = 0; i < len; i++){
                    permLast[i] = permCurr[i];
                }
            }
        }
        return;
    }
    // Recursive step
    for (int i = 0; i < len; i++){
        if (!usedData[i]){
            
            // Make the decision
            usedData[i] = TRUE;
            permCurr[num] = originalData[i];
            
            // Recurse
            recData(usedData, originalData, usedDifference, originalDifference, permCurr, permLast, num + 1, len);
            
            // Unmake the decision
            usedData[i] = FALSE;
            permCurr[num] = '\0';
        }
    }
}
