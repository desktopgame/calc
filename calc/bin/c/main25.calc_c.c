#include <stdio.h>

int main(int argc, char* argv[]) { 
    int a = (int)(4 << 16);
    printf("%d", a);
    printf("\n");
    return 0;
}