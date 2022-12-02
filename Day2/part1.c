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
       
       mescore += me;
       if (me == ((elf % 3) + 1)) mescore += 6;
       else if (me == elf) mescore += 3;
    }

    printf("%d\n", mescore);

    return 0;
}