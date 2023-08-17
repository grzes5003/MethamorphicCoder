#include <stdio.h>

#define PROJECT_NAME "sample-program"

int main(int argc, char **argv) {
    if(argc > 2) {
        printf("%s takes one or no arguments.\n", argv[0]);
        return 1;
    }
    if(argc == 2) {
        printf("The argument provided is %s.\n", argv[1]);
    }

    printf("This is project %s.\n", PROJECT_NAME);
    return 0;
}
