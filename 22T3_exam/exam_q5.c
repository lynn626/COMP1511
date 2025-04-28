#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 100
#define ALPHABET SIZE 26

int alphabet (char character [MAX]);

int main(void) {
    // TODO: Implement exam_q5.c here!
    int ch = getchar();
    int i = 0;
    int size;
    char character[MAX];
    while (ch != EOF) {
        scanf("%c", character[i]);
        i++;
        size++;
        ch = getchar();
    }
    while (i < size) {
    tolower(character[i])- 'a';
    strcmp(ch, character[i]);
    printf(" %c", character[i]);
    i++;
    }

    return 0;
}

int alphabet (char character [MAX]) {
    if (character == 'a' && 'e' && 'i' && 'o' &&'u') {
        return 1;
    }
}