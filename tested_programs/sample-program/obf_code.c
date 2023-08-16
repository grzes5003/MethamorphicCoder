/**
Mutate the provided code
*/

#include <stdio.h>
#include <string.h>

#define PROJECT_NAME "evolved-program"

void customMessage(const char *name) {
    printf("Welcome to %s, %s!\n", PROJECT_NAME, name);
}

int main(int argc, char **argv) {
    if (argc != 1) {
        printf("Error: %s takes no arguments.\n", argv[0]);
        return 1;
    }

    char name[50];
    printf("Enter your name: ");
    scanf("%s", name);

    customMessage(name);
    return 0;
}
