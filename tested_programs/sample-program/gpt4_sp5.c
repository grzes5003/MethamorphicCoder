#include <stdio.h>
#include <string.h>

#define STR_PROJECT_NAME "sample-program"
#define MANGLE_PROJECT_NAME(x, y) ((x)^(y))
#define DEMANGLE_PROJECT_NAME(x, y) MANGLE_PROJECT_NAME(x, y)

char project_name = STR_PROJECT_NAME;
int mangle_key = 0x55;

typedef struct {
    char(get_name)(void);
    int (check_argc)(int, char );
} Project;

char *get_project_name(void) {
    for (int i = 0; i < strlen(project_name); i++)
        project_name[i] = DEMANGLE_PROJECT_NAME(project_name[i], mangle_key);
    return project_name;
}

int check_argc(int argc, char argv) {
    if(argc != 1) {
        for (int i = 0; i < strlen(argv[0]); i++)
            argv[0][i] ^= mangle_key;
        printf("%s takes no arguments.\n", argv[0]);
        return 1;
    }
    return 0;
}

int main(int argc, char **argv) {
    Project p = {
        .get_name = get_project_name,
        .check_argc = check_argc,
    };

    if (p.check_argc(argc, argv)) return 1;

    printf("This is project %s.\n", p.get_name());
    return 0;
}


/*
This code achieves polymorphism by using function pointers in a struct. It achieves metamorphism through a simple XOR cipher to mangle and demangle strings at runtime. It also uses a common technique in obfuscated code of discarding the original main() function's argument names and replacing them with cryptic ones. It's important to note that this obfuscation is rudimentary and can be detected by sophisticated static analysis tools.
*/