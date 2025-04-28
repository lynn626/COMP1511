#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 100
struct skifieldboard{
    int row;
    int column;
};
//2d array 

int main (void) {
    int i = 0;
    int j = 0;
    int skifield[MAX_LENGTH][MAX_LENGTH];
    while (i < MAX_LENGTH) {
        while (j < MAX_LENGTH) {
   scanf("%d", &skifield[i][j]);
   j++;
        }
        i++;
    }



    return 0;
}
//out of time to continue but this is my thinking concept of this question
//AS this is a 2d array, i should first scan in the coordinates into the array
//create a struct so that it can be moved from left to right