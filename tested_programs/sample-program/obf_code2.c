/*
Mutate the provided code. Change the control flow, add dead code, unnecessary code jumps
but keep the original logic intact
*/

#include <stdio.h>

#define PROJECT_NAME "sample-program"

int main(int argc, char **argv) {
    if(argc == 0) {
        printf("This should never happen.\n");
        goto unexpected;
    }

    if(argc != 1) {
        printf("%s takes no arguments.\n", argv[0]);
        goto cleanup;
    }

    // Introduce dead code
    if(0) {
        printf("Dead code block.\n");
    }

    printf("This is project %s.\n", PROJECT_NAME);

    // Introduce unnecessary code jumps
    goto skip;
    printf("Unreachable code.\n");
    skip:

    return 0;

    cleanup:
        printf("Cleanup process.\n");

    unexpected:
        printf("Unexpected case.\n");

    return 1;
}
