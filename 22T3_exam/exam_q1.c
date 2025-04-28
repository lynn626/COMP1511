#include <stdio.h>
#include <stdlib.h>

struct bread {
    char bread_type;
    int counter;
};

// Return the total number of sourdough and rye bread_type
int count_bread_types(int size, struct bread array[size]) {
    // TODO: Complete this function.
    int counter = 0;
    int i = 0;
    while (i <size) {
        if (array[i].bread_type == 's' || array[i].bread_type == 'r'){
            counter = counter + array[i].counter;
        }
        i++;
    }
    return counter;
}

// This is a simple main function which could be used
// to test your struct_bread function.
// It will not be marked.
// Only your struct_bread function will be marked.

#define TEST_ARRAY_SIZE 5

int main(void) {
    struct bread test_array[TEST_ARRAY_SIZE] = {
        { .bread_type = 'w', .counter = 20},
        { .bread_type = 'r', .counter = 23},
        { .bread_type = 's', .counter = 11},
        { .bread_type = 'S', .counter = 21},
        { .bread_type = 's', .counter = 11}
    };
    printf("%d\n", count_bread_types(TEST_ARRAY_SIZE, test_array));
    // Should print out 45
    return 0;
}
