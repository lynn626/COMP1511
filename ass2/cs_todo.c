//Assignment 2 (cs_todo)
//by TAN JIAN LYNN (z5439797)
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID_PRIORITY -1

#define MAX_TASK_LENGTH 200
#define MAX_CATEGORY_LENGTH 40
#define MAX_STRING_LENGTH 1024

// You *should* #define each command
#define COMMAND_ADD_TASK 'a'
#define COMMAND_PRINT_LIST 'p'
#define COMMAND_UPDATE_PRIORITY 'i'
#define COMMAND_COUNT_TASK 'n'
#define COMMAND_COMPLETE_TASK 'c'
#define COMMAND_PRINT_COMPLETE 'P'
#define COMMAND_EXPECTED_COMPLETION_TIME 'e'
#define COMMAND_DELETE_TASK 'd'
#define COMMAND_DELETE_COMPLETED_LIST 'f'
#define COMMAND_REPEAT_TASK 'r'
#define COMMAND_SORT_TASK 's'

enum priority { LOW, MEDIUM, HIGH };

struct task {
    char task_name[MAX_TASK_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    enum priority priority;
    int repeated;
    struct task *next;
};

struct completed_task {
    struct task *task;
    int start_time;
    int finish_time;
    struct completed_task *next;
};

struct todo_list {
    struct task *tasks;
    struct completed_task *completed_tasks;
};

////////////////////////////////////////////////////////////////////////////////
///////////////////// YOUR FUNCTION PROTOTYPES GO HERE /////////////////////////
////////////////////////////////////////////////////////////////////////////////



void command_loop(struct todo_list *todo);
void add_task(struct todo_list *todo);
void print_list(struct todo_list *todo);
int count_task(struct todo_list *todo);
void update_priority(struct todo_list *todo);
void to_complete_task (struct todo_list *todo);
void print_completed_list(struct todo_list *todo);
int expected_completion_time (struct todo_list *todo, 
char category [MAX_CATEGORY_LENGTH]);
void print_expected_completion_time (struct todo_list *todo);
void delete_task (struct todo_list *todo);
void delete_completed_list (struct todo_list *todo);
void move_repeated_task (struct todo_list *todo,struct task *task);
void repeat_task (struct todo_list *todo);
void delete_lists (struct todo_list *todo);
void sort_task (struct todo_list *todo);
void swapping(struct task *task1, struct task *task2);
////////////////////////////////////////////////////////////////////////////////
//////////////////////// PROVIDED HELPER PROTOTYPES ////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void parse_add_task_line(
    char buffer[MAX_STRING_LENGTH], char task_name[MAX_TASK_LENGTH],
    char task_category[MAX_CATEGORY_LENGTH], enum priority *prio
);
void parse_task_category_line(
    char buffer[MAX_STRING_LENGTH], char task_name[MAX_TASK_LENGTH],
    char task_category[MAX_CATEGORY_LENGTH]
);
void parse_complete_task_line(
    char buffer[MAX_STRING_LENGTH], char task_name[MAX_TASK_LENGTH],
    char task_category[MAX_CATEGORY_LENGTH], int *start_time, int *finish_time
);

enum priority string_to_priority(char priority[MAX_STRING_LENGTH]);
void remove_newline(char input[MAX_STRING_LENGTH]);
void trim_whitespace(char input[MAX_STRING_LENGTH]);
void print_one_task(int task_num, struct task *task);
void print_completed_task(struct completed_task *completed_task);

int task_compare(struct task *t1, struct task *t2);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(void) {
    // Stage 1.1
    // You should initialize the `todo` variable below. You will need
    // to use the malloc() function to allocate memory for it!
    struct todo_list *todo = malloc(sizeof(struct todo_list));
    printf("Welcome to CS ToDo!\n");
    todo->tasks = NULL;
    todo->completed_tasks = NULL;
    
    command_loop(todo);
    printf("All done!\n");
    delete_lists(todo);
    return 0;
}

/**
 * The central loop that executes commands until the program is completed.
 *
 * Parameters:
 *     todo - The todo list to execute commands on.
 *
 * Returns:
 *     Nothing
 */
void command_loop(struct todo_list *todo) {
    printf("Enter Command: ");
    char command;
    while (scanf(" %c", &command) == 1) {
        // TODO: Add to this loop as you complete the assignment

        if (command == COMMAND_ADD_TASK) {
            // TODO: Add a task to the todo list here
            add_task(todo);
        } else if (command == COMMAND_PRINT_LIST) {
            print_list(todo);
        } else if (command == COMMAND_UPDATE_PRIORITY) {
            update_priority(todo);
        } else if (command == COMMAND_COUNT_TASK) {
            printf (
                "There are %d items on your list!\n", 
                count_task(todo));
        } else if (command == COMMAND_COMPLETE_TASK) {
            to_complete_task(todo);
        } else if (command == COMMAND_PRINT_COMPLETE) {
            print_completed_list(todo);
        } else if (command == COMMAND_EXPECTED_COMPLETION_TIME) {
            print_expected_completion_time(todo);
        } else if (command == COMMAND_DELETE_TASK) {
            delete_task(todo);
        } else if (command == COMMAND_DELETE_COMPLETED_LIST) {
            delete_completed_list(todo);
        } else if (command == COMMAND_REPEAT_TASK) {
            repeat_task(todo);
        }

        printf("Enter Command: ");
        
    }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////// YOUR HELPER FUNCTIONS ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////


// You should add any helper functions you create here
//function to add new tasks to the task list
void add_task(struct todo_list *todo) {
    char buffer[MAX_STRING_LENGTH];
    fgets(buffer, MAX_STRING_LENGTH, stdin);

    // Create variables for each part of the command being scanned in
    // (name of task, category of task and priority of task)
    char task_name[MAX_TASK_LENGTH];
    char task_category[MAX_CATEGORY_LENGTH];
    enum priority task_priority;
    parse_add_task_line(buffer, task_name, task_category, &task_priority);
    
    //create a new node at the end
    struct task *newtask = malloc(sizeof(struct task));
    strcpy (newtask->category, task_category);
    strcpy (newtask->task_name, task_name);
    newtask->priority = task_priority;
    newtask->repeated = 0;
    newtask->next = NULL;
    
    if (todo->tasks == NULL) {
        todo->tasks = newtask;
    } else {
        struct task *current = todo->tasks;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newtask;
    }
}
//function to print the task list
void print_list(struct todo_list *todo){
    int task_num = 1;
    struct task *current = todo->tasks;
    printf("==== Your ToDo List ====\n");
    if (todo->tasks == NULL) {
        printf("All tasks completed, you smashed it!\n");
    } else {
        while (current != NULL) {
            print_one_task(task_num, current);
            current = current->next;
            task_num++;
        }
    }
    printf("====   That's it!   ====\n");
}

    
//function to update the priority of tasks
void update_priority(struct todo_list *todo) {
    char buffer[MAX_STRING_LENGTH];
    fgets(buffer, MAX_STRING_LENGTH, stdin);

    // Create strings for `task`/`category` and populate them using the contents
    // of `buffer`
    char task[MAX_TASK_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    parse_task_category_line(buffer, task, category);
    
    struct task *current = todo->tasks;
    while (current != NULL) {
        if (strcmp(task, current->task_name) == 0 && 
        strcmp(category, current->category) == 0) {
            if (current->priority == LOW) {
                current->priority = MEDIUM;
            } else if (current->priority == MEDIUM) {
                current->priority = HIGH;
            } else if (current->priority == HIGH) {
                current->priority = LOW;
            }
            return;
        }
        
        current= current->next; 
    }
    // if this while loop ends, then our previous checker did not find a match
    printf("Could not find task '%s' in category '%s'.\n", task, category);
}

//function to count the number of tasks
int count_task(struct todo_list *todo){
    int count = 0;
    struct task *current = todo->tasks;
    while (current != NULL) {
        current= current->next;
        count ++;
    }
    return count;
}

//function to complete tasks
void to_complete_task(struct todo_list *todo) {
    char buffer[MAX_STRING_LENGTH];
    fgets(buffer, MAX_STRING_LENGTH, stdin);

    // Create strings for `task`/`category` and ints for times, then populate
    // them using the contents of `buffer`.
    char task[MAX_TASK_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    int start_time;
    int finish_time;
    parse_complete_task_line(buffer, task, category, &start_time, &finish_time);
    //search the task and removed it from the tasks list
    struct task *current = todo->tasks;
    struct task *previous = NULL;

    while (current != NULL && !(strcmp(task, current->task_name) == 0 &&
    strcmp(category, current->category) == 0)) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Could not find task '%s' in category '%s'.\n", task, category);
        return;
    } else {
        // Unlink the current
        if (previous != NULL) {
            previous->next = current->next;
        } else {
            todo->tasks = current->next;
        }
        current->next = NULL;

        // Create a new completed task and insert it at the head
        struct completed_task *newtask = malloc(sizeof(struct completed_task));      
        newtask->next = todo->completed_tasks;
        newtask->start_time = start_time;
        newtask->finish_time = finish_time;
        todo->completed_tasks = newtask;

        // relink the current task
        newtask->task = current; 
    }
} 
//function to print the completed task list
void print_completed_list (struct todo_list *todo) {
    struct completed_task *current = todo->completed_tasks;       
    printf("==== Completed Tasks ====\n");
    if (todo->completed_tasks == NULL) {
        printf("No tasks have been completed today!\n");
        
    } else {
        while (current != NULL) {
            print_completed_task(current);
            current = current->next;
        }
    }
    printf("=========================\n");
    
}


//function to calculate the expected completion time
int expected_completion_time (struct todo_list *todo, 
char category [MAX_CATEGORY_LENGTH]) {
    struct completed_task *current = todo->completed_tasks;
    int total_time = 0;
    int number_of_tasks_in_category = 0;
    if (todo->completed_tasks == NULL) {
        return 100;
    } else {
        while (current != NULL) {
            if (strcmp(current->task->category, category) == 0) {
                number_of_tasks_in_category ++;
                total_time = total_time + current->finish_time -current->start_time;
            }
            current = current->next;
        }
        if (total_time == 0 || number_of_tasks_in_category == 0) {
            return 100;
        } else {
            return total_time / number_of_tasks_in_category;
        }
    }
              
}
//function to print expected completion time
void print_expected_completion_time (struct todo_list *todo) {
    printf ("Expected completion time for remaining tasks: \n\n");
    if (todo->tasks != NULL) {
        struct task *current = todo->tasks;
        int task_num = 1;
        while (current != NULL) {
            print_one_task(task_num, current);
            printf("Expected completion time: %d minutes\n\n", 
            expected_completion_time(todo, current->category));
            current = current->next;
            task_num++;
        }
    }
}

//function to delete task from task list
void delete_task (struct todo_list *todo) {
    char buffer[MAX_STRING_LENGTH];
    fgets(buffer, MAX_STRING_LENGTH, stdin);

    // Create strings for `task`/`category` and populate them using the contents
    // of `buffer`
    char task[MAX_TASK_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    parse_task_category_line(buffer, task, category);

    struct task *current = todo->tasks;
    struct task *previous = NULL;

    if (current == NULL) {
        printf("Could not find task '%s' in category '%s'.\n", task, category);
    }
    if ((strcmp (current->task_name, task) == 0)) {
        todo->tasks = current->next;
        free(current);
        return;
    }
    while (current != NULL && (strcmp (current->task_name, task) != 0)) {
        previous = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Could not find task '%s' in category '%s'.\n", task, category);
        return;
    } else if ((strcmp (current->task_name, task) == 0)) {
        previous->next = current->next;
        free(current);
    }
    return;
}

//function to delete completed task from the list
void delete_completed_list (struct todo_list *todo) {
    struct completed_task *current = todo->completed_tasks;
    struct completed_task *previous = NULL;
    while (current != NULL) {
        previous = current;
        current = current->next;
        if (previous->task->repeated == 1) {
            move_repeated_task(todo, previous->task);
        } else {
            free(previous->task);
        }
        free(previous);
    }

    todo->completed_tasks = NULL;
    
}
// function to add repeated task back to the task list
void move_repeated_task (struct todo_list *todo, struct task *task) {
    //insert it at the end of the task list
    if (todo->tasks == NULL) {
        todo->tasks = task;
        return;
    }
    struct task *current = todo->tasks;
    while (current->next != NULL) {
        current= current->next;
    }
    current->next = task;
}
    

//function to repeat task
void repeat_task (struct todo_list *todo) {
    char buffer[MAX_STRING_LENGTH];
    fgets(buffer, MAX_STRING_LENGTH, stdin);
    char task[MAX_TASK_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    parse_task_category_line(buffer, task, category);
    
    struct task *current = todo->tasks;
    while (current != NULL) {
        if (strcmp (task, current->task_name) == 0 && 
        strcmp(category, current->category) == 0) {
        
            if (current->repeated == 0) {
                current->repeated = 1;
            } else if (current->repeated == 1) {
                current->repeated = 0;
            } 
            return;
        }
        current = current->next;
    }
    printf("Could not find task '%s' in category '%s'.\n", task, category);
    
}
//function to delete lists
void delete_lists (struct todo_list *todo) {
    struct task *current = todo->tasks;
    struct task *previous = NULL;
    while (current != NULL) {
        previous = current;
        current = current->next;
        free(previous);
    }

    struct completed_task *current2 = todo->completed_tasks;
    struct completed_task *previous2 = NULL;
    while (current2 != NULL) {
        previous2 = current2;
        current2 = current2->next;
        free(previous2->task);
        free(previous2);
    }
    free(todo);
    
}

//stage 4.1
//hash define the patterns
//stage 4.2
//delete incomplete tasks that match a given pattern 
//stage 4.3
//function to sort the task in prior to category, then priority, last by task_name
//incomplete functions below (would like to show some understanding towards stage 4.3)
void sort_task (struct todo_list *todo) {
    struct task *current = todo->tasks;
    //struct task *previous = NULL;
    int swap = 0;
    if (todo->tasks == NULL) {
        return;
    } 
    while (current->next != NULL) {
        if (current->category != current->next->category ) {
            task_compare(current, current->next);
            swapping(current,current->next);
            swap = 1;
        }
        current = current->next;
    }
    //previous = current;

    while (swap);
}

//function to swap two tasks
void swapping(struct task *task1, struct task *task2) {
    //char temp = strcpy(task1->task_name, temp);
    // task1->task_name = task2->task_name;
    //strcmp(task2->task_name, task1->task_name);
    //strcpy(temp, task2->task_name);
}


////////////////////////////////////////////////////////////////////////////////
/////////////////////// PROVIDED HELPER FUNCTIONS //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * Helper Function
 * You DO NOT NEED TO UNDERSTAND THIS FUNCTION, and will not need to change it.
 *
 * Given a raw string in the format: [string1] [string2] [enum priority]
 * This function will extract the relevant values into the given variables.
 * The function will also remove any newline characters.
 *
 * For example, if given: "finish_assignment_2 assignment2 high"
 * The function will copy the string:
 *     "finish_assignment_2" into the `task_name` array
 * Then copy the string:
 *     "assignment2" into the `task_category` array
 * And finally, copy over the enum:
 *     "high" into the memory that `prio` is pointing at.
 *
 * Parameters:
 *     buffer        - A null terminated string in the following format
 *                     [string1] [string2] [enum priority]
 *     task_name     - A character array for the [string1] to be copied into
 *     task_category - A character array for the [string2] to be copied into
 *     prio          - A pointer to where [enum priority] should be stored
 *
 * Returns:
 *     None
 */
void parse_add_task_line(
    char buffer[MAX_STRING_LENGTH],
    char task_name[MAX_TASK_LENGTH],
    char task_category[MAX_CATEGORY_LENGTH],
    enum priority *prio
) {
    remove_newline(buffer);

    // Extract value 1 as string
    char *name_str = strtok(buffer, " ");
    if (name_str != NULL) {
        strcpy(task_name, name_str);
    }

    // Extract value 2 as string
    char *category_str = strtok(NULL, " ");
    if (category_str != NULL) {
        strcpy(task_category, category_str);
    }
    
    // Extract value 3 as string
    char *prio_str = strtok(NULL, " ");
    if (prio_str != NULL) {
        *prio = string_to_priority(prio_str);
    }

    if (
        name_str == NULL ||
        category_str == NULL ||
        prio_str == NULL ||
        *prio == INVALID_PRIORITY
    ) {
        // If any of these are null, there were not enough words.
        printf("Could not properly parse line: '%s'.\n", buffer);
    }
}

/*
 * Helper Function
 * You DO NOT NEED TO UNDERSTAND THIS FUNCTION, and will not need to change it.
 *
 * See `parse_add_task_line` for explanation - This function is very similar,
 * with only the exclusion of an `enum priority`.
 */
void parse_task_category_line(
    char buffer[MAX_STRING_LENGTH],
    char task_name[MAX_TASK_LENGTH],
    char task_category[MAX_CATEGORY_LENGTH]
) {
    remove_newline(buffer);

    // Extract value 1 as string
    char *name_str = strtok(buffer, " ");
    if (name_str != NULL) {
        strcpy(task_name, name_str);
    }

    // Extract value 2 as string
    char *category_str = strtok(NULL, " ");
    if (category_str != NULL) {
        strcpy(task_category, category_str);
    }

    if (name_str == NULL || category_str == NULL) {
        // If any of these are null, there were not enough words.
        printf("Could not properly parse line: '%s'.\n", buffer);
    }
}

/*
 * Helper Function
 * You DO NOT NEED TO UNDERSTAND THIS FUNCTION, and will not need to change it.
 *
 * See `parse_add_task_line` for explanation - This function is very similar,
 * with only the exclusion of an `enum priority` and addition of start/end times
 */
void parse_complete_task_line(
    char buffer[MAX_STRING_LENGTH],
    char task_name[MAX_TASK_LENGTH],
    char task_category[MAX_CATEGORY_LENGTH],
    int *start_time,
    int *finish_time
) {
    remove_newline(buffer);

    // Extract value 1 as string
    char *name_str = strtok(buffer, " ");
    if (name_str != NULL) {
        strcpy(task_name, name_str);
    }

    // Extract value 2 as string
    char *category_str = strtok(NULL, " ");
    if (category_str != NULL) {
        strcpy(task_category, category_str);
    }
    
    // Extract value 2 as string
    char *start_str = strtok(NULL, " ");
    if (start_str != NULL) {
        *start_time = atoi(start_str);
    }
    
    // Extract value 2 as string
    char *finish_str = strtok(NULL, " ");
    if (finish_str != NULL) {
        *finish_time = atoi(finish_str);
    }


    if (
        name_str == NULL ||
        category_str == NULL ||
        start_str == NULL ||
        finish_str == NULL
    ) {
        // If any of these are null, there were not enough words.
        printf("Could not properly parse line: '%s'.\n", buffer);
    }
}

/**
 * Helper Function
 * You should not need to change this function.
 *
 * Given a raw string, will return the corresponding `enum priority`,
 * or INVALID_PRIORITY if the string doesn't correspond with the enums.
 *
 * Parameters:
 *     priority - string representing the corresponding `enum priority` value
 * Returns:
 *     enum priority
 */
enum priority string_to_priority(char priority[MAX_STRING_LENGTH]) {
    if (strcmp(priority, "low") == 0) {
        return LOW;
    } else if (strcmp(priority, "medium") == 0) {
        return MEDIUM;
    } else if (strcmp(priority, "high") == 0) {
        return HIGH;
    }

    return INVALID_PRIORITY;
}

/**
 * Helper Function
 * You should not need to change this function.
 *
 * Given an priority and a character array, fills the array with the
 * corresponding string version of the priority.
 *
 * Parameters:
 *     prio - the `enum priority` to convert from
 *     out  - the array to populate with the string version of `prio`.
 * Returns:
 *     Nothing
 */
void priority_to_string(enum priority prio, char out[MAX_STRING_LENGTH]) {
    if (prio == LOW) {
        strcpy(out, "LOW");
    } else if (prio == MEDIUM) {
        strcpy(out, "MEDIUM");
    } else if (prio == HIGH) {
        strcpy(out, "HIGH");
    } else {
        strcpy(out, "Provided priority was invalid");
    }
}

/*
 * Helper Function
 * You should not need to change this function.
 *
 * Given a raw string will remove and first newline it sees.
 * The newline character wil be replaced with a null terminator ('\0')
 *
 * Parameters:
 *     input - The string to remove the newline from
 *
 * Returns:
 *     Nothing
 */
void remove_newline(char input[MAX_STRING_LENGTH]) {
    // Find the newline or end of string
    int index = 0;
    while (input[index] != '\n' && input[index] != '\0') {
        index++;
    }
    // Goto the last position in the array and replace with '\0'
    // Note: will have no effect if already at null terminator
    input[index] = '\0';
}

/*
 * Helper Function
 * You likely do not need to change this function.
 *
 * Given a raw string, will remove any whitespace that appears at the start or
 * end of said string.
 *
 * Parameters:
 *     input - The string to trim whitespace from
 *
 * Returns:
 *     Nothing
 */
void trim_whitespace(char input[MAX_STRING_LENGTH]) {
    remove_newline(input);
    
    int lower;
    for (lower = 0; input[lower] == ' '; ++lower);
    
    int upper;
    for (upper = strlen(input) - 1; input[upper] == ' '; --upper);
    
    for (int base = lower; base <= upper; ++base) {
        input[base - lower] = input[base];
    }

    input[upper - lower + 1] = '\0';
}

/**
 * Helper Function
 * You SHOULD NOT change this function.
 *
 * Given a task, prints it out in the format specified in the assignment.
 *
 * Parameters:
 *     task_num - The position of the task within a todo list
 *     task     - The task in question to print
 *
 * Returns:
 *     Nothing
 */
void print_one_task(int task_num, struct task *task) {
    char prio_str[MAX_STRING_LENGTH];
    priority_to_string(task->priority, prio_str);

    printf(
        "  %02d. %-30.30s [ %s ] %s\n",
        task_num, task->task_name, task->category, prio_str
    );

    int i = 30;
    while (i < strlen(task->task_name)) {
        printf("      %.30s\n", task->task_name + i);
        i += 30;
    }
}

/**
 * Helper Function
 * You SHOULD NOT change this function.
 *
 * Given a completed task, prints it out in the format specified in the
 * assignment.
 *
 * Parameters:
 *     completed_task - The task in question to print
 *
 * Returns:
 *     Nothing
 */
void print_completed_task(struct completed_task *completed_task) {
    int start_hour = completed_task->start_time / 60;
    int start_minute = completed_task->start_time % 60;
    int finish_hour = completed_task->finish_time / 60;
    int finish_minute = completed_task->finish_time % 60;
    
    printf(
        "  %02d:%02d-%02d:%02d | %-30.30s [ %s ]\n",
        start_hour, start_minute, finish_hour, finish_minute,
        completed_task->task->task_name, completed_task->task->category
    );

    int i = 30;
    while (i < strlen(completed_task->task->task_name)) {
        printf("      %.30s\n", (completed_task->task->task_name + i));
        i += 30;
    }
}

/**
 * Compares two tasks by precedence of category -> priority -> name and returns
 * an integer referring to their relative ordering
 * 
 * Parameters:
 *     t1 - The first task to compare
 *     t2 - The second task to compare
 *
 * Returns:
 *     a negative integer if t1 belongs before t2
 *     a positive integer if t1 belongs after t2
 *     0 if the tasks are identical (This should never happen in your program)
 */
int task_compare(struct task *t1, struct task *t2) {
    int category_diff = strcmp(t1->category, t2->category);
    if (category_diff != 0) {
        return category_diff;
    }
    
    int priority_diff = t2->priority - t1->priority;
    if (priority_diff != 0) {
        return priority_diff;
    }
    
    return strcmp(t1->task_name, t2->task_name);
}
