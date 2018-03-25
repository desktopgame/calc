#include <stdio.h>

int main(int argc, char* argv[]) { 
    printf("%d", (int)((10 / 4) + 3 * 2 + (9 | (3 - 1))));
    fflush(stdout);
    return 0;
}