#include <stdio.h>

int main(int argc, char* argv[]) { 
    printf("%d", (int)(10 - (9 - (8 - (7 - 6 + (5 * (4 - 3 - 2 + 1)))))));
    fflush(stdout);
    return 0;
}