#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};


// compare_evens should return  1 if list1 has more evens than list2
// compare_evens should return  0 if list1 has the same evens as list2
// compare_evens should return -1 if list1 has less evens than list2
int compare_evens(struct node *head1, struct node *head2) {
    struct node *current = head1;
    struct node *currentt = head2;
    int even = 0;
    int evenn = 0;
    while ((current != NULL) && (currentt != NULL)) {
        if (current->data %2 == 0) {
            even++;
        }
        if (currentt->data %2 == 0) {
            evenn++;
        }
        current= current->next;
        currentt = currentt->next;
    } 
    
    if (even == evenn) {
        return 0;
    } else if (even > evenn) {
        return 1;
    } else if (even < evenn) {
        return -1;
    }
    
}

struct node *strings_to_list(int len, char *strings[]);

int main(int argc, char *argv[]) {
    // create two linked lists from command line arguments
    int dash_arg = argc - 1;
    while (dash_arg > 0 && strcmp(argv[dash_arg], "-") != 0) {
        dash_arg = dash_arg - 1;
    }
    struct node *head1 = strings_to_list(dash_arg - 1, &argv[1]);
    struct node *head2 = strings_to_list(argc - dash_arg - 1, &argv[dash_arg + 1]);

    int result = compare_evens(head1, head2);
    printf("%d\n", result);

    return 0;
}


// create linked list from array of strings
struct node *strings_to_list(int len, char *strings[]) {
    struct node *head = NULL;
    for (int i = len - 1; i >= 0; i = i - 1) {
        struct node *n = malloc(sizeof (struct node));
        assert(n != NULL);
        n->next = head;
        n->data = atoi(strings[i]);
        head = n;
    }
    return head;
}
