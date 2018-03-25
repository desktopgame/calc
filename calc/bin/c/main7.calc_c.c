#include <stdio.h>

int main(int argc, char* argv[]) { 
    printf("%d", (int)(0 || 0));
    fflush(stdout);
    return 0;
}