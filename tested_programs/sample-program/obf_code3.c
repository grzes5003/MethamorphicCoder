/*
Mutate the provided code so it hardly resembles the input code.
Change the control flow, add dead code, unnecessary code jumps but keep the original logic intact
*/
#include <stdio.h>

#define PROJECT_NAME "sample-program"

int main(int argc, char **argv) {
    int flag = 0;

    for (int i = 0; i < argc; i++) {
        if (i != 0) {
            flag = 1;
            break;
        }
    }

    if (flag) {
        printf("This program does not accept arguments.\n");
        return 1;
    } else {
        printf("Welcome to the %s project!\n", PROJECT_NAME);

        if (flag) {
            goto end_label;
        } else {
            printf("Initialization complete.\n");
        }
    }

    goto final_label;

end_label:
    printf("This should never be printed.\n");

final_label:
    return 0;
}
