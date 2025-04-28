#include <stdio.h>
/*
int main (void) {
  char my_char = 'D';
printf("%c", my_char + 2);  
}*/

/*int main(void) {
    int x;
int y;

// The input is: 1 -1
scanf("%d %d", &x, &y);

if (x > 0 && y > 0) {
    printf("(%d, %d) is top-left.", x, y);
} else if (x > 0 && y < 0) {
    printf("(%d, %d) is top-right.", x, y);
} else {
    printf("(%d, %d) is not on the top.", x, y);
}
return 0;
}*/

/*
    int my_function(int number) {
    if (number > 0) {
        return number;
    } else {
        number = -number;
        return number;
    }
}
int main(void) {
    int number = -7;
    
    if (number > 0) {
        printf("A");
    }
    if (my_function(number) > 0) {
        printf("B");
    }
    if (number > 0) {
        printf("C");
    }
    number = my_function(number);
    if (number > 0) {
        printf("D");
    }
    return 0;

}*/


struct driver {
    char code[3];
    double points;
    struct driver *followed_by;
};

// Inserts a node at the head of the list, and returns the new head.
struct driver *insert_head(struct driver *standings, char code[3], double points);

int main(void) {
    struct driver *standings = NULL;
    standings = insert_head(standings, "NOR", 160.0);
    standings = insert_head(standings, "SAI", 164.5);
    standings = insert_head(standings, "PER", 190.0);
    standings = insert_head(standings, "BOT", 226.0);
    standings = insert_head(standings, "HAM", 387.5);
    standings = insert_head(standings, "VER", 395.5);

    struct driver *current = standings;

    while (current->followed_by != NULL) {
        if (current->points - current->followed_by->points < 10) {
            printf("%s is less than 10 points behind %s.\n", current->code, current->followed_by->code);
        }
        current = current->followed_by;
    }

    return 0;
}
 

