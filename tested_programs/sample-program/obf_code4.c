/*
Modify the code below using all known obfuscation techniques but keep the original logic intact. Use polymorphism and metamorphism techniques.
Make as much changes as possible. Make sure compiled machine code from edited code will be much different from the original, making it hard to identify.
*/
#include <stdio.h>

#define O0O0O0O0O0 0
#define O0O0O0O0O1 1
#define O0O0O0O0O2 2
#define O0O0O0O0O3 3
#define O0O0O0O0O4 4

#define O0O0O0O00O(c) (c - 'a' + 'z')
#define O0O0O0O0OO(c) (c - 'a' + 'y')
#define O0O0O0O0Oc(c) (c - 'a' + 'x')
#define O0O0O0O0Od(c) (c - 'a' + 'w')
#define O0O0O0O0OE(c) (c - 'a' + 'v')

typedef struct {
    char *O0O0O0OOO0;
    char *O0O0O0OOO1;
} O0O0O0OOO2;

void O0O0O0O0Oe(O0O0O0OOO2 *O0O0O0OOO3) {
    if (O0O0O0OOO3->O0O0O0OOO1[O0O0O0O0O0] != O0O0O0O00O('1')) {
        printf(O0O0O0OOO3->O0O0O0OOO0, O0O0O0OOO3->O0O0O0OOO1);
        return;
    }
    printf(O0O0O0OOO3->O0O0O0OOO1, O0O0O0OOO3->O0O0O0OOO0);
}

int main(int O0O0O0OOO4, char **O0O0O0OOO5) {
    O0O0O0OOO2 O0O0O0OOO6 = {
        "Th%s is proj%c %s.\n",
        "%s takes no argum%cnts.\n"
    };

    if (O0O0O0OOO4 != O0O0O0O0O1) {
        O0O0O0O0Oe(&O0O0O0OOO6);
        return O0O0O0O0O2;
    }

    O0O0O0O0Oe(&O0O0O0OOO6);
    return O0O0O0O0O0;
}

/*
FAILED: sample_program@exe/obf_code4.c.o
cc -Isample_program@exe -I. -I.. -fdiagnostics-color=always -pipe -D_FILE_OFFSET_BITS=64 -Wall -Winvalid-pch -Wextra -Wpedantic -g -MD -MQ 'sample_program@exe/obf_code4.c.o' -MF 'sample_program@exe/obf_code4.c.o.d' -o 'sample_program@exe/obf_code4.c.o' -c ../obf_code4.c
../obf_code4.c: In function ‘O0O0O0O0Oe’:
../obf_code4.c:25:32: error: ‘O0O0O0O0O’ undeclared (first use in this function); did you mean ‘O0O0O0O0Oe’?
   25 |     if (O0O0O0OOO3->O0O0O0OOO1[O0O0O0O0O] != O0O0O0O00O('1')) {
      |                                ^~~~~~~~~
      |                                O0O0O0O0Oe
../obf_code4.c:25:32: note: each undeclared identifier is reported only once for each function it appears in
../obf_code4.c: In function ‘main’:
../obf_code4.c:32:33: warning: unused parameter ‘O0O0O0OOO5’ [-Wunused-parameter]
   32 | int main(int O0O0O0OOO4, char **O0O0O0OOO5) {
      |                          ~~~~~~~^~~~~~~~~~
ninja: build stopped: subcommand failed.
*/