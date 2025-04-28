#include <stdio.h>
#include <string.h>

#define MAX_LEN 10000

int main(void) {
    // write your code for exam_q3 here!
    int numbers[MAX_LEN];
    int command;
    int i = 0;
    int size;
    int count = 0;
    while (scanf("%d", &command) != EOF) {
        numbers[i] = command;
        //count how many times it appears in the array
        if (strcmp(numbers[i], command)== 0) {
            count++;
        }
        i++; 
        size++;
    }

    while (i< size) {
        //print out the number of times counted 
    printf("%d appears %d times",command, count);
    i++;
    }
    return 0;
}

