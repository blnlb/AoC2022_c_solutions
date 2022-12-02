#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    char buff[4];
    const char* filename = argv[1];
    FILE *fp = fopen(filename, "r");

    int me, elf;
    int mescore = 0;
    while(fgets(buff, 10, fp) != NULL) {
       elf = buff[0] - 'A' + 1;
       me = buff[2] - 'X' + 1;

       if (me == 2) mescore += elf + 3;
       else if (me == 3) mescore += 6 + (elf % 3) + 1;
       else mescore += elf == 2 ? 1 : (elf % 3) + 2;
    }

    printf("%d\n", mescore);

    return 0;
}