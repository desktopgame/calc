#include <stdio.h>

int main(int argc, char* argv[]) { 
    int a = (int)(!(10 | 10));
    printf("%d", a);
    printf("\n");
    return 0;
}