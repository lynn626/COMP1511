#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

struct node *delete_duplicate(struct node *head);
struct node *create_node(int data, struct node *next);
struct node *strings_to_list(int len, char *strings[]);
void print_list(struct node *head);
int lengthcount (struct node *head, int n);

// Delete the first instance of a duplicate node
struct node *delete_duplicate(struct node *head) {
    // TODO: Change this function.  
    struct node *current = head;
    if (head == NULL) {
        //list is empty no node to delete;
        return NULL;
    } else if (head->next == NULL) {
        //first node is the only node;
        //first node is definitely not the value;
        return head;
    }
    struct node *previous = NULL;
    while (current != NULL) {
        if (lengthcount (head, current->data) != 1) {
            free(previous);
            current = current->next;
        }
        current = current->next;
    }
    return head;
}

    int lengthcount (struct node *head, int n) {
    int count = 0;
    while (head != NULL) {
        if (head->data == n) {
            count++;
        }
        head = head->next;
    }
    return count;
}


//
// DO NOT CHANGE ANYTHING BELOW THIS COMMENT
//

int main(int argc, char *argv[]) {

    // create linked list from command line arguments
    struct node *head = NULL;
    if (argc > 1) {
        // list has elements
        head = strings_to_list(argc - 1, &argv[1]);
    }

    struct node *new_head = delete_duplicate(head);
    print_list(new_head);

    return 0;
}


// create linked list from array of strings
struct node *strings_to_list(int len, char *strings[]) {
    struct node *head = NULL;
    int i = len - 1;
    while (i >= 0) {
        struct node *n = malloc(sizeof (struct node));
        assert(n != NULL);
        n->next = head;
        n->data = atoi(strings[i]);
        head = n;
        i -= 1;
    }   
    return head;
}

// print linked list
void print_list(struct node *head) {
    printf("[");    
    struct node *n = head;
    while (n != NULL) {
        // If you're getting an error here,
        // you have returned an invalid list
        printf("%d", n->data);
        if (n->next != NULL) {
            printf(", ");
        }
        n = n->next;
    }
    printf("]\n");
}