#include <stdio.h>

int main(int argc, char* argv[]) { 
    printf("%d", (int)((20 | 20) + 3 >= (5 & 5) ^ 7));
    fflush(stdout);
    return 0;
}