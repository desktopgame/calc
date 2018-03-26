#include <stdio.h>

int main(int argc, char* argv[]) { 
    int a = (int)(2 << (1 - 1));
    printf("%d", a);
    printf("\n");
    return 0;
}