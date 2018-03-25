#include <stdio.h>

int main(int argc, char* argv[]) { 
    printf("%d", (int)(!(10 | 10)));
    fflush(stdout);
    return 0;
}