#include <stdio.h>

int main(int argc, char* argv[]) { 
    int a = (int)(10 - (9 - (8 - (7 - 6 + (5 * (4 - 3 - 2 + 1))))));
    printf("%d", a);
    printf("\n");
    return 0;
}