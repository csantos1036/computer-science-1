//
//  assignment4.c
//  assignment4
//
//  Created by Carolina Santos
//  Copyright © 2020 Carolina Santos. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct City City;

struct City {
    char * name;
    long long int x;
    long long int y;
};

// Prototypes for array functions
void copy(City *, City *, int);
void printArray(City *, int);

// Prototypes for weather functions
City * createCity(char * name, long long int, long long int);
long long int calculateDotProduct(City *, long long int, long long int);

// Prototype for sorting function
int merge(City *, int, long long int, long long int);

// Method to sort using the merge method
int merge(City * arr, int size, long long int dx, long long int dy)
{
   int ans = 0;
   
   // BASE CASE
   if (size <= 1)
   {
      return ans;
   }
   
   // Get the mid point
   int mid = size / 2;
   
   // Get the sizes
   int s1 = mid;
   int s2 = size - mid;
   
   // RECURSIVELY SORT
   ans += merge(arr, s1, dx, dy);
   ans += merge(arr + mid, s2, dx, dy);
   
   // Make a temporary array to store values
   City * tmp = calloc(size, sizeof(City));
   int fptr = 0;
   int bptr = mid;
   int mptr = 0;
   
   // Loop while there are elements left to move into the tmp array
   for (mptr = 0; mptr < size; mptr++)
   {
      if (fptr == mid)
      {
         tmp[mptr] = arr[bptr];
         bptr++;
      }
      else if (bptr == size)
      {
         tmp[mptr] = arr[fptr];
         fptr++;
      }
      else
      {
         // Do a comparison
         ans++;
         
         // Store the correct value based on dot product
          if (calculateDotProduct(&arr[fptr],dx ,dy) < calculateDotProduct(&arr[bptr], dx, dy))
         {
            tmp[mptr] = arr[fptr];
            fptr++;
         }
         else
         {
            tmp[mptr] = arr[bptr];
            bptr++;
         }
      }
   }
   
   // Copy tmp into the original array
   copy(arr, tmp, size);
   free(tmp);
   
   // Return the total number of comparisons
   return ans;
}

// Function to copy the source array into the destination array
void copy(City * dst, City * src, int size)
{
   for (int i = 0; i < size; i++)
   {
      dst[i] = src[i];
   }
}

long long int calculateDotProduct(City * city, long long int dx, long long int dy)
{
    // dx*pointX+dy*pointY
    return ((city->x * dx) + (city->y * dy));
}

// Function to print an array
void printArray(City * arr, int num)
{
    for (int i = 0; i < num; i++)
    {
      printf("%s\n", arr[i].name);
    }
}

int main()
{
    int n; // Number of inputs
    char name[MAX + 1]; // City name
    long long int x; // X-location
    long long int y; // Y-location
    long long int dx; // Change in x
    long long int dy; // Change in y
    
    scanf("%d", &n);
    
    // Create a list of City elements
    City *cityList = (City *)calloc(n, sizeof(City));
    
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &x);
        scanf("%lld", &y);
        scanf("%s", name);
        
        // Create a new city and add to cityList
        City * city = createCity(name, x, y);
        cityList[i] = * city;
    }

    scanf("%lld", &dx);
    scanf("%lld", &dy);
    
    // Perform merge sort based on dx and dy
    merge(cityList, n, dx, dy);
    
    // Print the sorted array
    printArray(cityList, n);

    // Free the names of cities
    for (int i = 0; i < n; i++)
    {
        City * curCity = &cityList[i];
        free(curCity->name);
    }

    // Free the city list
    free(cityList);
    
    return 0;
}

City * createCity(char * name, long long int x, long long int y)
{
    // Create the city
    City * city = calloc(1, sizeof(City));
    city->x = x;
    city->y = y;
    
    // Copy name into city->name
    city->name = calloc(strlen(name) + 1, sizeof(char));
    strcpy(city->name, name);
    
    return city;
}
