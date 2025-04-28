#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
int main(void) {
    //character use string
    char line1 [1024];
    char line2 [1024];
    int count_both_lines = 0;
    //count letters starting with an empty set;
    int letter_count[26] = {0};
    fgets(line1, 1024, stdin);
    fgets(line2, 1024, stdin);

    for (int i = 0; line1[i]; i++) {
        if (isalpha(line1 [i])) {
           letter_count[tolower(line1[i]) -'a'] ++; 
        }
    }
    for (int i = 0; line2 [i]; i++) {
        if (isalpha(line2[i])) {
            if (letter_count[tolower(line2[i]) - 'a']) {
                count_both_lines++;
                letter_count[tolower(line2[i])- 'a'] = 0;
            }
        }
    }
    printf("%d\n", count_both_lines);

    return 0;
}