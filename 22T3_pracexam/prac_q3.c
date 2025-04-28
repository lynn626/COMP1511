/*
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
int main (void) {
    int command = 1;
    int array[MAX];
    int i = 0;
    int count = 0;
    while (command != 0) {
        scanf("%d", &command);
        if(command != 0) {
        array[i++] = command;
        count++;
        }
    }
    for (i = 0; i < count; i = i+2 ) {
        printf("%d ", array[i]);
    }
    for (i = 1; i < count; i = i+2) {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}
*/

#include <stdio.h>
#define MAX 100
int main (void) {
    int numbers = 1;
    int array[MAX];
    int size = 0;
    int i = 0;
    while (numbers != 0) {
        scanf("%d", &numbers);
        if (numbers != 0) {
        array[i] = numbers;
        i++;
        size++;
        }
    }
    for (i = 0; i <size; i =i+2 ) {
        printf("%d ", array[i]);
    } 
    for (i = 1; i <size; i=i +2 ){
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}