#include <stdio.h>

int main(int argc, char* argv[]) { 
    int a = (int)((10 / 4) + 3 * 2 + (9 | (3 - 1)));
    printf("%d", a);
    printf("\n");
    return 0;
}