#include <stdio.h>

#define PROJECT_NAME "sample-program"

int main(int argc, char **argv) {
    int exit_code = 0;
    if(argc != 1) {
        printf("%s takes no arguments.\n", argv[0]);
        exit_code = 1;
    } else {
        printf("This is project %s.\n", PROJECT_NAME);
    }

    if (exit_code == 0) {
        // Dead code
        if (argc != 0) {
            printf("This message will never be printed.\n");
        }

        // Unnecessary code jump
        goto end;
        printf("This message will never be printed due to the goto command.\n");
    } else {
        // Dead code
        if (argc == 0) {
            printf("This message will never be printed.\n");
        }

        // Unnecessary code jump
        goto end;
    }

end:
    return exit_code;
}