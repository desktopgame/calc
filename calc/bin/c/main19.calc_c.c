#include <stdio.h>

int main(int argc, char* argv[]) { 
    printf("%d", (int)(~(2 + 2)));
    fflush(stdout);
    return 0;
}