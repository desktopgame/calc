#include <stdio.h>

int main(int argc, char* argv[]) { 
    printf("%d", (int)(12 != 2 - 2 + 3));
    fflush(stdout);
    return 0;
}