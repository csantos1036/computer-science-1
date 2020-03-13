//
//  main.c
//  Assignment0_CompSci1
//
//  Created by Carolina Santos on 1/8/20.
//  Copyright © 2020 Carolina Santos. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#define MAX 1000 // The maximum length of our string
#define FALSE 0
#define TRUE (!FALSE)
#define DNE -1

// Function protoypes or declarations
int getLoc(char * haystack, char * needle);
int beginsWith(char * phrase, char * beginning);

int main() {

    int t;                      // t represents the integer number of cases
    char phrase[MAX + 1];       // phrase represents the original phrase string
    char del[MAX + 1];          // del represents the distracting sequence string
    char rep[MAX + 1 ];         // rep represents the replacement string
    
    scanf("%d", &t);            // assigns input to t
    
    while (t > 0){
        
        scanf("%s %s %s", phrase, del, rep);
        
        char newPhrase[MAX + 1];
        char first[MAX + 1];
        char last[MAX + 1];
        
        while (strstr(phrase, del) != '\0')
        {
            int location = getLoc(phrase, del);
            
            if (location != DNE )
            {
                    // Create the first string.
                    strcpy(first, phrase);
                    first[location] = '\0';
                    
                    // Create the last string.
                    strcpy(last, &phrase[location + strlen(del)]);
                    
                    // newPhrase = first;
                if (strlen(first) == strlen(newPhrase)) {
                    strcpy(newPhrase, first);
                }
                else {
                    strcat(newPhrase,first);
                }
                    // newPhrase += rep;
                    strcat(newPhrase, rep);
                    
                    // newPhrase += last;
                strcpy(phrase, last);
                if (strstr(last, del) != '\0'){
                   strcpy(phrase, last);
                }
                else {
                    strcat(newPhrase, last);
                }
                    //}
            }
            //strcat(newPhrase, last);
            //strcpy(phrase, newPhrase);
        }
        strcpy(phrase, newPhrase);
        printf("%s\n", phrase);
        strcpy(newPhrase, "");
        t--;
    }
    
    // Return 0 to signify the program exited succesfully
    return 0;
}

int getLoc(char * haystack, char * needle) {
    int ans = 0;
    int done = FALSE;
    
    // Loop until the needle location is found
    while (!done)
    {
        if (haystack[ans] == '\0') {
         break;
        }
        // Check if the haystack offset by our answer
        // begins with our needle.
        if (beginsWith(&haystack[ans], needle))
        {
            return ans;
        }
        
        // Move the potential answer to the next position,
        // since the current one did not work.
        ans++;
    }
    
    // Return that the answer was never found
    return DNE;
}

int beginsWith(char * phrase, char * beginning) {
    // Store the position of where the first difference occurs
    int curPos = 0;
    
    // Look for the first position the strings differ.
    while (beginning[curPos] == phrase[curPos])
    {
        
        // Stop if the beginning is at the end of the string
        if (beginning[curPos] == '\0')
        {
            return TRUE;
        }
        
        // Increment the positoin.
        curPos++;
    }
        
    // Check if the current position was at the end of the
    // beginning.
    // Note: the below code could be replaced with the following,
    // "return (beginning[curPos] == '\0');"
    if (beginning[curPos] == '\0')
    {
        return TRUE;
    }
    
    // We could not reach the end of the beginning string, so
    // return that the phrase does not begin with the beginning.
    return FALSE;
}
