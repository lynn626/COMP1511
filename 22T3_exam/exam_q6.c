#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_WORD_LENGTH 50

struct node {
    int data;
    char word[MAX_WORD_LENGTH];
    struct node *next;
};

struct sub_node {
    int data;
    struct sub_node *next;
};

void longest_sublist(struct node *list, struct sub_node *sublist);
struct node *create_node(int data, struct node *next);
struct node *strings_to_word_list(int len, char *strings[]);
struct sub_node *strings_to_sub_list(int len, char *strings[]);

//////////////////////////////////////////////
//  DO NOT MODIFY ANY CODE ABOVE THIS LINE  //
//////////////////////////////////////////////

// Finds the longest sequence of nodes in `list` matching `sublist` exactly -
// and prints the `word`s contained within the nodes in that sequence.
void longest_sublist(struct node *list, struct sub_node *sublist) {
    // TODO: Implement the function here!
    struct node *current = list;
    while (current != NULL) {
        current = currnet->next;
    }
    int cur_char;
    struct node *stack = NULL;
    struct node *temp;
    while ((cur_char = getchar()) != -1) {
        if (strchr("[]()<>{}", cur_char) == NULL) {
            continue;
        } else if (strcmp( ,curc_char) ) != NULL) {
            temp = malloc(sizeof(struct node));
            temp->c = *(strchr("[]()<>{}", cur_char) + 1);
            temp->next = stack;
            stack = temp;


}
//out of time to continue the workings;
//I am trying to search for the longest sequence of nodes in compare to the other list
//and then print out the word in company to the number

//////////////////////////////////////////////
//  DO NOT MODIFY ANY CODE BELOW THIS LINE  //
//////////////////////////////////////////////

int main(int argc, char *argv[]) {
    // create linked list from command line arguments
    struct node *head = NULL;
    struct sub_node *sub_head = NULL;
    int sep_pos = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-") == 0) {
            sep_pos = i;
        }
    }
    int list_len = sep_pos - 1;
    int sub_len = argc - sep_pos - 1;
    if (list_len % 2) {
        printf("List must be of the form <int> <word>!\n");
        printf("All integers must have a corresponding word, and vice versa.\n");
        printf("Invalid list provided. Exiting...\n");
        exit(1);
    }
    if (!list_len || !sub_len) {
        printf("Both lists must have at least one item!\n");
        printf("Invalid list provided. Exiting...\n");
        exit(1);
    }

    // Convert command line args to list
    head = strings_to_word_list(list_len, &argv[1]);
    sub_head = strings_to_sub_list(sub_len, &argv[sep_pos + 1]);

    longest_sublist(head, sub_head);

    return 0;
}

struct node *strings_to_word_list(int len, char *strings[]) {
    struct node *head = NULL;
    int i = len - 2;
    while (i >= 0) {

        struct node *n = malloc(sizeof (struct node));
        assert(n != NULL);
        n->next = head;
        n->data = atoi(strings[i]);
        strcpy(n->word, strings[i + 1]);
        head = n;
        i -= 2;
    }   
    return head;
}

// create linked list from array of strings
struct sub_node *strings_to_sub_list(int len, char *strings[]) {
    struct sub_node *head = NULL;
    int i = len - 1;
    while (i >= 0) {
        struct sub_node *n = malloc(sizeof (struct node));
        assert(n != NULL);
        n->next = head;
        n->data = atoi(strings[i]);
        head = n;
        i -= 1;
    }   
    return head;
}
