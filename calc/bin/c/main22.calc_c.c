#include <stdio.h>

int main(int argc, char* argv[]) { 
    printf("%d", (int)(!(3 + 4) - 5));
    fflush(stdout);
    return 0;
}