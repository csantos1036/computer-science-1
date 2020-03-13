#include <stdio.h>
#include <stdlib.h>

#define SMALL_VALUE 1e-9

#define ABS(x) (((x)<0)?(-(x)):(x))
#define MAX(a,b) (((a)<(b))?(b):(a))

int equal(double a, double b);
double f(double topLength, double totalLength);

int main() {
   double totalLength;
   scanf("%lf", &totalLength);
   
   // Search over the length of the frame
   // (width)
   double lo = 0;
   double hi = totalLength;
   
   while (!equal(lo, hi))
   {
      printf("lo:%lf  hi:%lf\n", lo, hi);
      double mid1 = (lo + lo + hi) / 3;
      double mid2 = (lo + hi + hi) / 3;
      
      // Compute possible areas
      double area1 = f(mid1, totalLength);
      double area2 = f(mid2, totalLength);
      
      // Compare these two areas
      if (area1 > area2) {
         // Eliminate the mid2 section
         // by bringing in the hi value to it
         hi = mid2;
      } else {
         lo = mid1;
      }
   }

   double idealTopLength = (lo + hi) / 2;
   double area = f(idealTopLength, totalLength);
   
   printf("%lf\n", area);
   
   return 0;
}


int equal(double a, double b)
{
   double diff = ABS(a - b);
   double max = MAX(ABS(a), ABS(b));
   
   // Absolute check and relative check
   return (diff < SMALL_VALUE) || (diff < SMALL_VALUE * max);
}

// Compute the area of the picture frame using the given
// top length and total length
double f(double topLength, double totalLength)
{
   double height = (totalLength - 2 * topLength) / 6;
   double width = topLength;
   return width * height;
}




