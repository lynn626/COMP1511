#include <stdio.h>
/*int main(void) {
int my_char = 'c';
int my_updated_char = my_char - 'a' + 'A' + 5;
printf("%d %c", my_updated_char, my_updated_char);
return 0;
}*/



/*int main (void) {
    char c;
// '8' is scanned in
scanf("%c", &c);

if (0 <= c && c <= 9) {
    printf("A");
} else if ('0' <= c && c <= '9') {
    printf("B");
}
if ('a' <= c && c <= 'z') {
    printf("C");
} else {
    printf("D");
}
return 0;
}*/
/*
int main (void) {
    char c;
// 'B'  (a capital B) is scanned in
scanf("%c", &c);

if (c > 'A' && c > 'H') {
    printf("A");
} else if ((c > 'A' || c > 'H') && c < 'H') {
    printf("B");
} else if (c > 'A' || c > 'H') {
    printf("C");
} else {
    printf("D");
}
return 0;
}*/

/*
int main (void) {
    int array[5] = {-2, 4,2,1,-3};
int i = 0;
int multiply = -1;
while (i < 5) {
    multiply = multiply * array[i];
    printf("%d\n", multiply);

    i++;
}
return 0;
}*/
/*
#define SIZE 5
void my_function(int arr[SIZE][SIZE]);
int main (void) {
    
return 0;
}
 void my_function(int arr[SIZE][SIZE]) {
    int row = SIZE / 2;
    int col = SIZE / 2;
    while (row > 0 && row < SIZE - 1 && col > 0 && col < SIZE - 1) {
        int curr_value = arr[row][col];
        if (arr[row - 1][col] < curr_value) {
            row = row - 1;
        } else if (arr[row][col - 1] < curr_value) {
            col = col - 1;
        } else if (arr[row][col + 1] < curr_value) {
            col = col + 1;
        } else if (arr[row + 1][col] < curr_value) {
            row = row + 1;
        }
    }
    printf("(%d, %d)", row, col);
}*/
/*
#define SIZE 5


// option A
void function_a(int arr[]) {
    arr[1] = 5;
}

// option B
void function_b(int array[SIZE]) {
    array[1] = 5;
}

// option C
void function_c(int val) {
    val = 5;
}

// option D
void function_d(int arr[SIZE]) {
    arr[1] = 5;
}

// option E
int function_e(int arr[SIZE]) {
        return 5;
}

int main(void) {
    int arr[SIZE] = {1, 2, 3, 4, 5};

    // Which of the following function calls would change value(s) in the initial array of arr.
    // A:
    function_a(arr[]);
    // B:
   
    // C:
  
    // D:
    
    // E:
    
}
*/


    struct node {
    int data;
    struct node *next;
};

struct node *insert_nth(struct node *head, int data, int position) {
    struct node *new = malloc(sizeof(struct node));
    new->data = data;
    new->next = NULL;

    if (head == NULL) {
        if (position != 0) {
            return head;
        } else { 
            head = new;
            return head;
        }
    }

    if (head != NULL && position == 0) {
        new->next = head;
        head = new;
        return head;
    }

    struct node *current = head;
    struct node *previous = NULL;

    int i = 0;

    while (current != NULL && i < position) {
        previous = current;
        current = current->next;
        i++;
    }

    new->next = current;
    previous->next = new;
    return head;
}
int main (void) {
   insert_nth(struct node *head, int data, int position); 
}