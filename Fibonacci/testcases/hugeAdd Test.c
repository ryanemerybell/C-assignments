#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>
#include "Fibonacci.h"

int main(void)
{
    int i,j;
    HugeInteger p, q;
    HugeInteger *r;

    r = malloc(sizeof(HugeInteger));

    p.digits=malloc(sizeof(int)*7);
    p.length = 7;

    q.digits=malloc(sizeof(int)*7);
    q.length = 7;

    srand(time(NULL));

for(j=0;j<10;j++)
{
    for(i=0;i<7;i++)
        p.digits[i] = rand()%10;
    for(i=0;i<7;i++)
        q.digits[i] = rand()%10;

    if(p.digits[6] == 0)
        p.digits[6] = 1;
    if(q.digits[6] == 0)
        q.digits[6] = 1;

    printf("Fib number 1: ");
    for(i=0;i<7;i++)
        printf("%d",p.digits[i]);
    printf("\nFib number 2: ");
    for(i=0;i<7;i++)
        printf("%d",q.digits[i]);

    r = hugeAdd(&p,&q);
    printf("\nFib number 3: ");
    for(i=0;i<(r->length);i++)
        printf("%d",r->digits[i]);
    printf("\n\n");
}

    return 0;
}
