#include <stdio.h>
#include <stdlib.h>

int main()
{
    char* s = "1\n 24\n";
    char b;
    int a;
    char* c = (char*)malloc(20);
    //scanf("%d\n%c", &a, &b);
    //printf("%d, %c\n", a, b);
    fgets(c, 10, stdin);
    printf("%s", c);
    printf("%c\n", c[0]);
    //printf("%s",s);
    return 0;
}