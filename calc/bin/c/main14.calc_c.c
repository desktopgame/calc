#include <stdio.h>

int main(int argc, char* argv[]) { 
    int a = (int)(0 | (0 || 2 & 2));
    printf("%d", a);
    printf("\n");
    return 0;
}