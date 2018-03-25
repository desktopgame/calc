#include <stdio.h>

int main(int argc, char* argv[]) { 
    printf("%d", (int)(1 && 0));
    fflush(stdout);
    return 0;
}