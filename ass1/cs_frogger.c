// Assignment 1 (COMP1511) - CS_Frogger
//
// This program was written by [TAN JIAN LYNN] (z5439797)
// on [15/10/22]
//
// This is a simplified version of the 1981 arcade action game. 
// Code a program to get the frogger to the other 
// side of the river. The starter code is provided.

#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////  CONSTANTS  /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Provided constants
#define SIZE        9
#define TRUE        1
#define FALSE       0

// TODO: you may choose to add additional #defines here.

// Provided Enums
enum tile_type {LILLYPAD, BANK, WATER, TURTLE, LOG, BUG};

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////  STRUCTS  //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Provided structs
struct board_tile {
    // The type of piece it is (water, bank, etc.)
    enum tile_type type; 
    // TRUE or FALSE based on if Frogger is there.
    int occupied;        
};

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  FUNCTION PROTOTYPES  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Your function prototypes here

// Prints out the current state of the board.
void print_board(struct board_tile board[SIZE][SIZE]);
char type_to_char(enum tile_type type);

////////////////////////////////////////////////////////////////////////////////
//////////////////////////  FUNCTION IMPLEMENTATIONS  //////////////////////////
////////////////////////////////////////////////////////////////////////////////
//int check_lose(int frogger_col, game_board);
//int check_win(int frogger_row, int frogger_col, game_board);

int main(void) {

    printf("Welcome to CSE Frogger!\n");
    struct board_tile game_board[SIZE][SIZE];

    // TODO (Stage 1.1) Initialise the gameboard.
    int i;
    int j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {   
            if (j != 1 && j != 3 && 
                j != 5 && j != 7) {
                game_board [0][j].type = LILLYPAD;
                game_board [0][j].occupied = FALSE;  
            } else if (j == 1 || j == 3 ||
                j == 5 || j == 7) {
                game_board [0][j].type = WATER;
                game_board [0][j].occupied = FALSE;  
            }
        }
    }    
    for (i = 1; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            game_board[i][j].type = WATER;
            game_board[i][j].occupied = FALSE;      
        }
    }   
    for (i = 8; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {   
            if (j != 4) {
                game_board [8][j].type = BANK;
                game_board [8][j].occupied = FALSE;  
            } else {
                game_board [8][j].type = BANK;
                game_board [8][j].occupied = TRUE;  
            }
        } 
    }
    // Read user input and place turtles.
    printf("How many turtles? ");
    // TODO (Stage 1.2): Scan in the turtles, and place them on the map.
    int num_turtles;
    int pair_col;
    int pair_row;
    int row;
    int col;
    
    scanf("%d", &num_turtles);
    if (num_turtles != 0) {
        printf("Enter pairs: \n"); 
        scanf("%d %d", &row, &col);
        if (row != 8 && row < SIZE && row > 0 ) {
            game_board [row][col].type = TURTLE;
            game_board [row][col].occupied = FALSE;  
        } 
        int num_pairs = num_turtles;
        while (num_pairs > 1) { 
            scanf("%d %d", &pair_row, &pair_col);  
            if (pair_row != 8 && pair_row < SIZE && 
                pair_row > 0 && pair_col < SIZE && pair_col >= 0) {
                game_board [pair_row][pair_col].type = TURTLE;
                game_board [pair_row][pair_col].occupied = FALSE;  
            } 
            num_pairs--;
        }
    }

    // Start the game and print out the gameboard.
    printf("Game Started\n");
    print_board(game_board);
    char command;
    int frogger_row = SIZE - 1;
    int frogger_col = SIZE - 5;
    printf("Enter command: ");
    while (scanf(" %c", &command) == 1) { 
        // TODO (Stage 1.3): Create a command loop, to read and execute commands!
        int end_column;
        int start_column;
        if (command == 'l') {
            scanf("%d %d %d", &row, &start_column, &end_column);
            // if end column out of bounds
            // set end column to the end
            if (end_column >= SIZE) {
                end_column = SIZE - 1;
            }
            if (row < SIZE && row > 0 && 
                start_column < SIZE && 
                end_column < SIZE && start_column >= 0 && 
                end_column >= 0) {
                i = 0;
                int contains_turtle = 0;
                while (i < SIZE) {
                    if (game_board [row][start_column].type == TURTLE) {
                        contains_turtle = 1;
                    }
                    i++;
                }
                if (contains_turtle == 0) {
                    while (start_column <= end_column) {    
                        game_board [row][start_column].type = LOG;
                        game_board [row][start_column].occupied = FALSE;  
                        start_column++;
                    }
                }
            }
            print_board(game_board);
            printf("Enter command: ");
            
        } else if (command == 'c') {
            scanf("%d", &row);
            col = 0;
            i = 0;
            if (row < SIZE && row > 0) {
                int contains_frog = 0;
                while (i < SIZE) {
                    if (game_board [row][i].occupied == TRUE) {
                        contains_frog = 1;
                    }
                    i++;
                }
                if (contains_frog == 0) {
                    while (col < SIZE) {
                        if (row < 8 && row > 0) {
                            game_board [row][col].type = WATER;
                            game_board [row][col].occupied = FALSE;
                        }  
                        col++;
                    }
                }
            }
            print_board(game_board);
            printf("Enter command: ");

            //stage 2.2 
        } else if (command == 'r') {
            int p;
            scanf("%d %d", &row, &p);
            col = 0;
            if (row > 0 && row < SIZE - 1 && 
                p < SIZE && p >= 0 && 
                game_board[row][p].type == LOG) {
                col = p;
                while (col < SIZE && game_board [row][col].type == LOG ) {
                    game_board [row][col].type = WATER;
                    col++; 
                }
                col = p - 1;
                while (col >= 0 && game_board [row][col].type == LOG) {
                    game_board [row][col].type = WATER;
                    col--;
                }
            }
            print_board(game_board);
            printf("Enter command: ");
            
            //stage 2.3
        } else if (command == 'w') { 
            if (frogger_row < SIZE && frogger_row >= 1) {
                game_board [frogger_row][frogger_col].occupied = FALSE;
                game_board [frogger_row - 1][frogger_col].occupied = TRUE;
                frogger_row --;
            }
            print_board(game_board);
            printf("Enter command: ");
         
        } else if (command == 'a') {
            if (frogger_col < SIZE && frogger_col >= 1) {
                game_board [frogger_row][frogger_col].occupied = FALSE;
                game_board [frogger_row][frogger_col - 1].occupied = TRUE;
                frogger_col--;
            }      
            print_board(game_board);
            printf("Enter command: ");
            
        } else if (command == 's') {
            if (frogger_row < SIZE - 1 && frogger_row >= 0) {
                game_board [frogger_row][frogger_col].occupied = FALSE;
                game_board [frogger_row + 1][frogger_col].occupied = TRUE;
                frogger_row ++;
            }
            print_board(game_board);
            printf("Enter command: ");
            
        } else if (command == 'd') {
            if (frogger_col < SIZE - 1 && frogger_col >= 0) {
                game_board [frogger_row][frogger_col].occupied = FALSE;
                game_board [frogger_row][frogger_col + 1].occupied = TRUE;
                frogger_col ++;
            }  
            print_board(game_board);
            printf("Enter command: ");

        } else if (command == 'b') {
            int bug_col;
            int bug_row;
            scanf("%d %d", &bug_row, &bug_col);
            if (bug_col < SIZE && bug_col >= 0 &&
                bug_row < SIZE && bug_row > 0) {
                if (game_board [bug_row][bug_col].type == TURTLE ||
                    game_board [bug_row][bug_col].type == LOG ) {
                    game_board [bug_row][bug_col].type = BUG;
                }
            }
            print_board(game_board);
            printf("Enter command: ");
        }    
    }
    
    //stage 3 
    int win = 0;
    int lose = 0;
    //int past lives;
    //int lives = 3;
    //int num_lives_change;
    //win = check_win(game_board);
    //lose = check_lose(game_board);
    //  if (past_lives != lives){
    //      num_lives_change = 1;
    //  } else {
    //      num_lives_change = 0;
    //  }
    //if (lose == 0 && win != 1) { 
    //  if (lives > 0){    
    //      printf("\n# LIVES LEFT: %d #\n\n", lives);
    //      print_board(game_board);
    //  }
    //}
    if (win == 1) {
        printf("\nWahoo!! You Won!\n\n");
        printf("Thank you for playing CSE Frogger!\n");
    } else if (lose == 1) {
        printf("\n !! GAME OVER !! \n\n"); 
        printf("Thank you for playing CSE Frogger!\n");
    }
    
    printf("Thank you for playing CSE Frogger!\n");
    return 0;

}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////// ADDITIONAL FUNCTIONS /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Add more functions here!
//function used to check if frog falls into the water and loses the game.
//int check_lose(int frogger_col, game_board) {
//    int frogger_row = 0;
//    if (game_board [frogger_row][frogger_col].type = WATER) {
//        return 1;
//   }
//}
//function used to check if frog reaches Lilypad and win the game.
//int check_win(int frogger_col, int frogger_row, game_board) {
//    if (game_board [frogger_row][frogger_col].occupied = TRUE) {
//        return 1;
//    }
//}     

//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////// PROVIDED FUNCTIONS //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void print_board(struct board_tile board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            char type_char = '\0';
            if (board[row][col].occupied) {
                type_char = 'F';
            } else {
                type_char = type_to_char(board[row][col].type);
            }
            printf("%c ", type_char);
        }
        printf("\n");
    }
}

char type_to_char(enum tile_type type) {
    char type_char = ' ';
    if (type == LILLYPAD) {
        type_char = 'o';
    } else if (type == BANK) {
        type_char = 'x';
    } else if (type == WATER) {
        type_char = '~';
    } else if (type == TURTLE) {
        type_char = 'T';
    } else if (type == LOG) {
        type_char = 'L';
    } else if (type == BUG) {
        type_char = 'B';
    }
    return type_char;
}
