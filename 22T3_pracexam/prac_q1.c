#include <stdio.h>
#include <stdlib.h>


struct coordinate {
    int x;
    int y;
};


// Return the sum of all negative x coordinates 
// and all positive y coordinates as a struct 
struct coordinate sum_coords(int size, struct coordinate array[size]){
 int i = 0;
 int x = 0;
 int y = 0;
 while ( i < size) {
     if (array[i].x < 0) {
        x = x + array[i].x;
     }
     if ( array[i].y > 0) {
         y = y +array[i].y;
     }
     i++;
 }
 struct coordinate result;
 result.x = x;
 result.y = y;
 return result;
}


// This is a simple main function which could be used
// to test your sum_cood function.
// It will not be marked.
// Only your sum_cood function will be marked.

#define TEST_ARRAY_SIZE 3

int main(void) {
    struct coordinate test_array[TEST_ARRAY_SIZE] = {
        { .x = -3, .y = 20},
        { .x = 10, .y = -20},
        { .x = -5, .y = 50}
    };
    struct coordinate result = sum_coords(TEST_ARRAY_SIZE, test_array);
    printf("(%d, %d)\n", result.x, result.y);

    return 0;
}



/*
   int x= 0;
    int y = 0
    for (int i = 0; i <size; i++) {
        if (array[i].x < 0) {
            x+= array[i].x;
        } 
        if (array[i].y >0) {
            y+=array[i].y;
        }
    }
    struct coordinate result;
    result.x = x;
    result.y= y;
    return result;
}*/
